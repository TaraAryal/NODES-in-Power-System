"""
Filename    :neural_id.py
Date        :Apr 24, 2023
Written by  :Niranjan Bhujel 
"""


import torch as th
import torch.nn as nn
from torch import optim
from torch.utils.data import DataLoader
import numpy as np
import time
from typing import Union, Callable, Any, Dict
from utils import gof, simulate_trajectory


class NeuralID:
    def __init__(
            self,
            nx: int,
            nu: int,
            fx: nn.Module,
            ts: float,
            optimizer: optim.Optimizer,
            loss: Union[str, Callable[[th.Tensor, th.Tensor], th.Tensor]] = "mse",
            device: str = "cpu") -> None:
        """
        Class to train a neural network ODE having control input.

        Parameters
        ----------
        nx : int
            Number of states
        nu : int
            Number of inputs
        fx : nn.Module
            ODE function
        ts : float
            Sample time
        optimizer : optim.Optimizer
            Optimizer to train neural network
        loss : Union[str, Callable[[th.Tensor, th.Tensor], th.Tensor]], optional
            Loss function, by default "mse"
        device : str, optional
            Device to train the network on, by default "cpu"
        """

        self.nx = nx
        self.nu = nu

        self.fx = fx.to(th.device(device))
        self.ts = ts
        self.device = device
        self.optimizer = optimizer

        if loss == "mse":
            self.loss_fn = lambda x_true, x_pred: th.mean((x_true - x_pred)**2)
        elif loss == "mae":
            self.loss_fn = lambda x_true, x_pred: th.mean(
                th.abs(x_true - x_pred))
        elif hasattr(loss, "__call__"):
            self.loss_fn = loss
        else:
            raise Exception(f"Error: Unknown loss function {loss}")

    def learn(
            self,
            train_dataset: Dict[str, th.Tensor],
            val_dataset: Union[Dict[str, th.Tensor], None] = None,
            batch_size: int = 64,
            n_epochs: int = 10,
            verbose: bool = True) -> Dict[str, np.ndarray]:
        """
        Train the neural network ODE.

        Parameters
        ----------
        train_dataset : Dict[str, th.Tensor]
            Training dataset
        val_dataset : Dict[str, th.Tensor], optional
            Validation dataset, by default None
        batch_size : int, optional
            Batch size, by default 64
        n_epochs : int, optional
            Number of epochs to train, by default 10
        verbose : bool, optional
            Whether to print info or not, by default True
        """

        dl = DataLoader(
            list(zip(train_dataset["x"], train_dataset["u"])),
            batch_size=batch_size,
            shuffle=True,
            # pin_memory=True
        )

        if val_dataset is not None:
            for k, v in val_dataset.items():
                val_dataset[k] = v.to(self.device)

        print(f"Training on {self.device}...")

        t_wall = time.time_ns()

        metrics_all = {
            "train_loss": np.zeros((n_epochs, 1), dtype=np.float32),
            "train_gof": np.zeros((n_epochs, 1), dtype=np.float32),
        }
        if val_dataset is not None:
            metrics_all["validation_loss"] = np.zeros(
                (n_epochs, 1), dtype=np.float32)
            metrics_all["validation_gof"] = np.zeros(
                (n_epochs, 1), dtype=np.float32)

        for ep in range(n_epochs):
            train_loss = 0.0
            train_gof = 0.0
            count_batch = 0

            for d in dl:
                x_batch = d[0].to(self.device)
                u_batch = d[1].to(self.device)

                self.optimizer.zero_grad()

                x_pred = simulate_trajectory(
                    fn=self.fx,
                    x0=x_batch[..., 0, :],
                    u_traj=u_batch,
                    ts=self.ts
                )

                loss = self.loss_fn(
                    x_batch,
                    x_pred
                )

                loss.backward()
                self.optimizer.step()

                train_loss += float(loss.to("cpu").detach().numpy())
                train_gof += float(gof(x_batch,
                                   x_pred).to("cpu").detach().numpy())
                count_batch += 1

            train_loss = train_loss / count_batch
            train_gof = train_gof / count_batch
            metrics_all["train_loss"][ep, 0] = train_loss
            metrics_all["train_gof"][ep, 0] = train_gof

            verbose_print = f"Epoch: {ep+1}/{n_epochs}\n\ttrain_loss={train_loss}\n\ttrain_gof={train_gof}"
            if val_dataset is not None:
                x_val_pred = simulate_trajectory(
                    fn=self.fx,
                    x0=val_dataset["x"][..., 0, :],
                    u_traj=val_dataset["u"],
                    ts=self.ts
                )

                val_loss = self.loss_fn(val_dataset["x"], x_val_pred)
                val_gof = float(gof(val_dataset["x"], x_val_pred).to(
                    "cpu").detach().numpy())
                metrics_all["validation_loss"][ep, 0] = val_loss
                metrics_all["validation_gof"][ep, 0] = val_gof

                verbose_print += f"\n\tvalidation_loss={val_loss}\n\tvalidation_gof={val_gof}"
            verbose_print += f"\n\ttime_elapsed: {(time.time_ns() - t_wall) / 1e9} s"

            if verbose:
                print(verbose_print, flush=True)

        return metrics_all
