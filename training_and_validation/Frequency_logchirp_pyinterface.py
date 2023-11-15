"""
Filename:       Frequency_logchirp_pyinterface.py
Written by:     Niranjan Bhujel
Date:           Nov-15-2023 11:53:14
"""

import argparse
import ctypes
import importlib
import os
import sys
import time

import numpy as np


class Frequency_logchirp:
    def __init__(self, filename: str = "Frequency_logchirp_lib", compile: bool = False):
        """
        Class to simulate the Frequency_logchirp system. The model input and output are shown below:

        Input:

        Output:
            inputpower1 [1]
            deltaomega [1]
            deltaomegadot [1]

        """
        filepath = __file__
        filepath = os.path.split(filepath)[0]
        if filepath == "":
            filepath = "./"

        filename += ".so"
        if compile:
            compile_cmd = "gcc -fPIC -shared -DRT -O3 -lm " + '"' +\
                os.path.join(filepath, 'Frequency_logchirp_interface.c') + '"' + ' "' +\
                os.path.join(filepath, 'sim_code"/*.c') + ' -o ' + '"' +\
                os.path.join(filepath, filename) + '"'
            # print(compile_cmd)
            os.system(compile_cmd)

        self.start_time = 0.0
        self.step_time = 0.02
        self.current_time = self.start_time
        self.next_time = self.current_time + self.step_time

        self.Frequency_logchirp_system = ctypes.cdll.LoadLibrary(
            os.path.join(filepath, filename))

        self.Frequency_logchirp_system.initialize.restype = None
        self.Frequency_logchirp_system.initialize.argtypes = [
            np.ctypeslib.ndpointer(dtype=np.float64),
            np.ctypeslib.ndpointer(dtype=np.float64),
            np.ctypeslib.ndpointer(dtype=np.float64),

        ]

        self.Frequency_logchirp_system.one_step.restype = None
        self.Frequency_logchirp_system.one_step.argtypes = [
            np.ctypeslib.ndpointer(dtype=np.float64),
            np.ctypeslib.ndpointer(dtype=np.float64),
            np.ctypeslib.ndpointer(dtype=np.float64),

        ]

        self.inputpower1 = np.zeros((1,), dtype=np.float64)
        self.deltaomega = np.zeros((1,), dtype=np.float64)
        self.deltaomegadot = np.zeros((1,), dtype=np.float64)

    def reset(self, ):
        """
        Reset the simulation back to initial state.
        """
        self.current_time = self.start_time
        self.next_time = self.current_time + self.step_time

        self.Frequency_logchirp_system.initialize(
            self.inputpower1, self.deltaomega, self.deltaomegadot)

        # return {
        #     "inputpower1": self.inputpower1,
        #     "deltaomega": self.deltaomega,
        #     "deltaomegadot": self.deltaomegadot,
        #
        # }

    def one_step(self, ):
        """
        Run one step of simulation
        """

        self.Frequency_logchirp_system.one_step(
            self.inputpower1, self.deltaomega, self.deltaomegadot)

        self.current_time += self.step_time
        self.next_time = self.current_time + self.step_time

        # return {
        #     "inputpower1": self.inputpower1,
        #     "deltaomega": self.deltaomega,
        #     "deltaomegadot": self.deltaomegadot,
        #
        # }

    def terminate(self):

        self.Frequency_logchirp_system.terminate()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="Frequency_logchirp_pyinterface",
        description="Python interface to Frequency_logchirp.",
    )
    parser.add_argument(
        "--stop_time", help="Simulation stop time. Total time of simulation.", type=float)
    args = parser.parse_args()
    if args.stop_time is None:
        raise Exception(
            "Stop time not specified. Type `python Frequency_logchirp_pyinterface.py --help` for more info!!!")

    STEP_TIME = 0.02
    STOP_TIME = args.stop_time

    if STEP_TIME == -1:
        raise Exception("STEP_TIME not specified.")
    if STOP_TIME == -1:
        raise Exception("STOP_TIME not specified.")

    m = Frequency_logchirp("Frequency_logchirp_lib")

    # Specify value of input here

    m.reset()

    LAST_CURRENT_TIME = m.current_time
    WALL_TIME_ORIGIN = time.time_ns()
    __counter__ = 0
    while m.current_time < STOP_TIME:
        # Specify value of input here
        #

        m.one_step()
        __counter__ += 1

        if (m.current_time - LAST_CURRENT_TIME) / STOP_TIME * 100 > 5:
            print(f"{round(m.current_time / STOP_TIME * 100, 0)}% complete. Total time elapsed: {(time.time_ns() - WALL_TIME_ORIGIN)/1e9} !!!")
            LAST_CURRENT_TIME = m.current_time

    m.terminate()

    if round(LAST_CURRENT_TIME / STOP_TIME * 100, 0) != 5:
        print(f"{round(100.0, 0)}% complete. Total time elapsed: {(time.time_ns() - WALL_TIME_ORIGIN)/1e9}!!!")
