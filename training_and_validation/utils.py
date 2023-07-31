"""
Filename    :utils.py
Date        :Apr 20, 2023
Written by  :Niranjan Bhujel 
"""

import torch as th
from typing import Dict, Callable


def get_seq_data(
        data: Dict[str, th.Tensor],
        rollout_steps: int,
        shift_step: int = 1) -> Dict[str, th.Tensor]:
    """
    Convert a timeseries data into multiple timeseries of `rollout_steps` by shifting window by `shift_step`

    Parameters
    ----------
    data : Dict[str, th.Tensor]
        Dictionary of data
    rollout_steps : int
        Rollout steps
    shift_step : int, optional
        Steps to shift the horizon by, by default 1

    Returns
    -------
    Dict[str, th.Tensor]
        Multiple timeseries data with `rollout_steps`
    """
    ny = data["x"].shape[-1]
    nu = data["u"].shape[-1]

    N = data["x"].shape[0]

    bs = int((N-rollout_steps) / shift_step) + 1

    if "t" in data.keys():
        data_out = {
            "t": th.zeros((bs, rollout_steps, ), dtype=th.float32),
            "x": th.zeros((bs, rollout_steps, ny), dtype=th.float32),
            "u": th.zeros((bs, rollout_steps, nu), dtype=th.float32),
        }
    else:
        data_out = {
            "x": th.zeros((bs, rollout_steps, ny), dtype=th.float32),
            "u": th.zeros((bs, rollout_steps, nu), dtype=th.float32),
        }

    for k in range(0, bs):
        if "t" in data.keys():
            data_out["t"][k, :] = data["t"][k *
                                            shift_step:k*shift_step+rollout_steps]
        data_out["x"][k, :, :] = data["x"][k *
                                           shift_step:k*shift_step+rollout_steps, :]
        data_out["u"][k, :, :] = data["u"][k *
                                           shift_step:k*shift_step+rollout_steps, :]

    return data_out


def rk4(f, x0, u0, h):
    k1 = f(x0, u0)
    k2 = f(x0+h/2*k1, u0)
    k3 = f(x0+h/2*k2, u0)
    k4 = f(x0 + h*k3, u0)
    xf = x0 + h/6*(k1 + 2*k2 + 2*k3 + k4)
    return xf


def simulate_trajectory(
        fn: Callable[[th.Tensor, th.Tensor], th.Tensor],
        x0: th.Tensor,
        u_traj: th.Tensor,
        ts: float) -> th.Tensor:
    """
    Simulates the trajectory.

    Parameters
    ----------
    fn : Callable[[th.Tensor, th.Tensor], th.Tensor]
        ODE function to be simulated
    x0 : th.Tensor
        Initial state
    u_traj : th.Tensor
        Input for entire trajectory
    ts : float
        Sample time

    Returns
    -------
    th.Tensor
        Solution for entire trajectory
    """

    traj_len = u_traj.shape[-2]

    sol = th.empty(
        (*u_traj.shape[0:-1], x0.shape[-1]),
        dtype=th.float32,
        device=x0.device,
    )

    state = x0
    sol[..., 0, :] = x0
    for k in range(traj_len-1):
        next_state = rk4(fn, state, u_traj[..., k, :], ts)
        sol[..., k+1, :] = next_state
        state = next_state

    return sol


def gof(
        x_true: th.Tensor,
        x_pred: th.Tensor) -> th.Tensor:
    """
    Compute goodness of fit

    Parameters
    ----------
    x_true : th.Tensor
        True data
    x_pred : th.Tensor
        Predicted data

    Returns
    -------
    th.Tensor
        Goodness of fit
    """
    x_true_f = x_true.flatten()
    x_pred_f = x_pred.flatten()
    g_of = 1 - th.sqrt(th.mean((x_true_f - x_pred_f)**2)) / \
        th.sqrt(th.mean((x_true_f - x_true_f.mean())**2))
    if g_of <= 0.0:
        g_of = th.Tensor([0.0])
    return g_of


class StandardScaler:
    """
    Scaler class for normalizing the data using z-score.
    """

    def __init__(self, key_=[]):
        """
        Normalizes the data using z-score i.e., `z = (x-mu)/sigma`

        Parameters
        ----------
        key_ : list, optional
            Keyword of datavariable to normalize, by default []
        """
        self.key_ = key_

        self.mean_ = {}
        self.std_ = {}
        for k in self.key_:
            self.mean_[k] = 0.0
            self.std_[k] = 1.0

    def learn(self, data: Dict[str, th.Tensor]):
        for k in self.key_:
            self.mean_[k] = th.mean(data[k], dim=0)
            self.std_[k] = th.std(data[k], dim=0)

    def scale(self, data: Dict[str, th.Tensor]) -> Dict[str, th.Tensor]:
        data_out = {}

        for k, v in data.items():
            if k in self.key_:
                data_out[k] = (data[k] - self.mean_[k]) / self.std_[k]
            else:
                data_out[k] = data[k]

        return data_out

    def unscale(self, data: Dict[str, th.Tensor]) -> Dict[str, th.Tensor]:
        data_out = {}

        for k, v in data.items():
            if k in self.key_:
                data_out[k] = data[k] * self.std_[k] + self.mean_[k]
            else:
                data_out[k] = data[k]

        return data_out
