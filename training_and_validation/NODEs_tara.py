"""
Filename    :NODEs.py
Date        :Apr 20, 2023
Written by  :Tara Aryal and Niranjan Bhujel 
"""

# getting system from matlab
from Frequency_logchirp_pyinterface import Frequency_logchirp
from square_validation_signal.Frequency_square_pyinterface import Frequency_square
# from Frequency_dynamics_negative_step_pyinterface import Frequency_dynamics_negative_step
import matplotlib as mpl
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
import torch.nn.functional as F
import time
import os
import sys

from neural_id import NeuralID
from utils import get_seq_data, StandardScaler, simulate_trajectory

plt.rcParams['mathtext.fontset'] = 'stix'
mpl.rc('font', family='times new roman')
mpl.rcParams['savefig.dpi'] = 600
mpl.rcParams['axes.unicode_minus'] = False
mpl.rcParams['agg.path.chunksize'] = 10000
plt.rcParams['font.size'] = 10

os.environ["KMP_DUPLICATE_LIB_OK"] = "TRUE"


models_dir = "network"
if not os.path.exists(models_dir):
    os.makedirs(models_dir)

models_dir2 = "figure"
if not os.path.exists(models_dir2):
    os.makedirs(models_dir2)

#Obtaining Training data sets
model0 = Frequency_logchirp(compile=False)
# fmin = np.array([0.1])
# fmax = np.array([1.0])
model0.reset()

name1 = "noisefree_net1_"
name2 = "noisefree_net2_"
name3 = "noisefree_net3_"
name4 = "true_"
name5 = "learned"


time_array0 = [model0.current_time]
delta_omega0 = [model0.deltaomega[0]]
delta_dotomega0 = [model0.deltaomegadot[0]]
inputpower0 = [model0.inputpower1[0]]


while model0.current_time <= 306:
    model0.one_step()
    time_array0.append(model0.current_time)
    delta_omega0.append(model0.deltaomega[0])
    delta_dotomega0.append(model0.deltaomegadot[0])
    inputpower0.append(model0.inputpower1[0])

# Data Formatting
# b = torch.tensor([[delta_omega[250:], delta_dotomega[250:]]],
#                  dtype=torch.float32)
# bn = torch.tensor(
#     [[delta_omega[250:], delta_dotomega[250:]]], dtype=torch.float32)
# # b=torch.tensor([[delta_omega[250:2501]]],dtype=torch.float32).to(device)
# true_y = torch.movedim(b, (0, 2), (1, 0))

# t = torch.tensor(time_array[250:], dtype=torch.float32)
# u = torch.tensor(inputpower[250:], dtype=torch.float32)
# true_y = true_y.transpose(0, 1)

b=torch.tensor([[delta_omega0[250:],delta_dotomega0[250:]]],dtype=torch.float32)
# b=torch.tensor([[delta_omega[250:2501]]],dtype=torch.float32).to(device)
true_y0=torch.movedim(b,(0,2),(1,0))
t=torch.tensor(time_array0[250:],dtype=torch.float32)
u0=torch.tensor(inputpower0[250:],dtype=torch.float32)
true_y0 = true_y0.transpose(0, 1)

#Validation Data Sets 1
model1 = Frequency_square(compile=False)
# fmin = np.array([0.1])
# fmax = np.array([1.0])
model1.reset()

time_array1 = [model1.current_time]
delta_omega1 = [model1.deltaomega[0]]
delta_dotomega1 = [model1.deltaomegadot[0]]
inputpower1 = [model1.inputpower1[0]]


while model1.current_time <= 306:
    model1.one_step()
    time_array1.append(model1.current_time)
    delta_omega1.append(model1.deltaomega[0])
    delta_dotomega1.append(model1.deltaomegadot[0])
    inputpower1.append(model1.inputpower1[0])

b=torch.tensor([[delta_omega1[250:],delta_dotomega1[250:]]],dtype=torch.float32)
# b=torch.tensor([[delta_omega[250:2501]]],dtype=torch.float32).to(device)
true_y1=torch.movedim(b,(0,2),(1,0))
t1=torch.tensor(time_array1[250:],dtype=torch.float32)
u1=torch.tensor(inputpower1[250:],dtype=torch.float32)
true_y1 = true_y1.transpose(0, 1)

class ODEFunc(nn.Module):
    def __init__(self):
        super().__init__()
        # make your ODE network
        # self.net1 = torch.load("noisefree_net1_6950")
        # self.net2 = torch.load("noisefree_net2_6950")
        # self.net3 = torch.load("noisefree_net3_6950")
        self.net1 = nn.Sequential(
            nn.Linear(2, 4),
            nn.Tanh(),
            nn.Linear(4, 8)
        )
        self.net2 = nn.Sequential(
            nn.Linear(1, 4),
            nn.Tanh(),
            nn.Linear(4, 8)
        )
        self.net3 = nn.Sequential(
            nn.Linear(16, 4),
            nn.Tanh(),
            nn.Linear(4, 2)
        )

        for m in self.net1.modules():
            if isinstance(m, nn.Linear):
                nn.init.normal_(m.weight, mean=0, std=0.1)
                nn.init.constant_(m.bias, val=0)

        for m in self.net2.modules():
            if isinstance(m, nn.Linear):
                nn.init.normal_(m.weight, mean=0, std=0.1)
                nn.init.constant_(m.bias, val=0)

        for m in self.net3.modules():
            if isinstance(m, nn.Linear):
                nn.init.normal_(m.weight, mean=0, std=0.1)
                nn.init.constant_(m.bias, val=0)

    def forward(self, y, u):
        output2 = self.net2(u)
        output1 = self.net1(y)
        output = torch.concat([output1, output2], axis=-1)
        output = self.net3(output)

        return output


# Main block to call NODEs
func = ODEFunc()
print(func)
optimizer = torch.optim.Adam(func.parameters(), lr=1e-3)

raw_train = {
    "t": t.flatten(),
    "u": u0.reshape((-1, 1)),
    "x": true_y0.reshape((-1, 2)),
}
raw_val1= {
    "t": t.flatten(),
    "u": u1.reshape((-1, 1)),
    "x": true_y1.reshape((-1, 2)),
}
# scaler = StandardScaler(key_=["u", "x"])
# scaler.learn(raw_train)
# raw_normalized = scaler.scale(raw_train)

data_train = get_seq_data(raw_train, rollout_steps=200)
data_val = get_seq_data(raw_val1, rollout_steps=200)

device = "cpu"

if sys.argv[1] == "train":
    my_node = NeuralID(
        nx=2,
        nu=1,
        fx=func,
        ts=0.02,
        optimizer=optimizer,
        loss="mse",
        device=device
    )

    metrics_all = my_node.learn(
        train_dataset=data_train,
        val_dataset=data_val,
        batch_size=200,
        n_epochs=50,
        verbose=True
    )

    torch.save(func.state_dict(), "./fx.pt")

    np.savetxt(
        "metrics2.csv", 
        np.hstack(list(metrics_all.values())),
        delimiter=",",
        header=",".join(list(metrics_all.keys())),
        comments=""
        )

elif sys.argv[1] == "test":
    func.load_state_dict(torch.load("./fx.pt"))
    metrics_all = np.genfromtxt(
        "metrics2.csv",
        delimiter=",",
        skip_header=0,
        encoding=None
    )
    x_pred_net = simulate_trajectory(
        fn=func,
        x0=torch.tensor([0.0]*2, dtype=torch.float32),
        u_traj=raw_train["u"],
        ts=0.02
    )

    _, ax = plt.subplots(1, 2,
                         figsize=(3.3, 1.5), 
                         constrained_layout=True)
    ax[0].plot(
        metrics_all[:,0],
        label="Training",
        linewidth=1.0)
    ax[0].plot(
        metrics_all[:,2],
        label="Validation",
        linewidth=1.0)
    # ax[0].legend(loc=0, labelspacing=0.1, borderpad=0.1, ncol=2, fontsize=8)
    ax[0].set_xlabel("epoch")
    ax[0].set_ylabel("loss")
    ax[0].grid(True, linestyle='--')
    ax[0].set_axisbelow(True)
    ax[0].ticklabel_format(axis="y", useMathText=True)
    # ax[0].set_xlim(40,50)

    ax[1].plot(
        metrics_all[:,1],
        label="Training",
        linewidth=1.0)
    ax[1].plot(
        metrics_all[:,3],
        label="Validation",
        linewidth=1.0)
    # ax[1].legend(loc=0, fontsize=10)
    ax[1].set_xlabel("epoch",fontsize=10)
    ax[1].set_ylabel("GoF (%)",fontsize=10)
    ax[1].grid(True, linestyle='--')
    ax[1].set_axisbelow(True)
    ax[1].ticklabel_format(axis="y", useMathText=True)
    # ax[1].set_xlim(40,50)
    # ax[0].set_ylim(0.9,1.01)
    plt.savefig("metrics2.svg", dpi=600)
    plt.show()

    _, ax = plt.subplots(3, 1, 
                         figsize=(4, 8), 
                         sharex=True, 
                         constrained_layout=True)
    ax[0].plot(
        raw_train["t"],
        raw_train["u"], 
        label="True",
        linewidth=2.0)
    # ax[0].legend(loc=0)
    ax[0].set_xlabel("time [s]")
    ax[0].set_ylabel("$\Delta P_e$ [p.u.]")
    ax[0].grid(True, linestyle='--')
    ax[0].set_axisbelow(True)

    ax[1].plot(raw_train["t"],
               raw_train["x"][:, 0], 
               label="True",
               color="#bda6bb",
               linewidth=4.0)
    ax[1].plot(
        raw_train["t"], 
        x_pred_net.detach().numpy()[:, 0], 
        label="Predicted",
        linewidth=2.0,
        linestyle='-.')
    ax[1].legend(loc=0)
    ax[1].set_xlabel("time [s]")
    ax[1].set_ylabel("$\Delta\omega$ [p.u.]")
    ax[1].grid(True, linestyle='--')
    ax[1].set_axisbelow(True)


    ax[2].plot(raw_train["t"],
               raw_train["x"][:, 1], 
               label="True",
               color="#bda6bb",
               linewidth=4.0)
    ax[2].plot(
        raw_train["t"], 
        x_pred_net.detach().numpy()[:, 1], 
        label="Predicted",
        linewidth=2.0,
        linestyle='-.')
    ax[2].legend(loc=0)
    ax[2].set_xlabel("time [s]")
    ax[2].set_ylabel("$\dot{\Delta\omega}$ [p.u.]")
    ax[2].grid(True, linestyle='--')
    ax[2].set_axisbelow(True)
    ax[0].set_xlim(250, 265)
    ax[1].set_xlim(250, 265)
    ax[2].set_xlim(250, 265)
    plt.savefig("time_dom_train1.svg", dpi=600)
    plt.show()

torch.save(func.net1,"net1_tara")
torch.save(func.net2,"net2_tara")
torch.save(func.net3,"net3_tara")