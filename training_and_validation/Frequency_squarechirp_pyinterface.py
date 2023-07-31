"""
Filename:       Frequency_squarechirp_pyinterface.py
Written by:     Niranjan Bhujel
Date:           2023-07-31
"""


import os
import ctypes
import numpy as np
import h5py
import time
import argparse


class Frequency_squarechirp:
    def __init__(self, out_lib_name: str="Frequency_squarechirp_lib.so", compile: bool=True):
        """
        Class to simulate the Frequency_squarechirp system. The model input and output are shown below:
        
        Input:
            
        Output:
            inputpower1 [1]
            deltaomega [1]
            deltaomegadot [1]
            
        """
        filepath = __file__
        filepath = os.path.split(filepath)[0]
        if filepath=="":
            filepath = "./"

        if compile:
            compile_cmd = "gcc -fPIC -shared -O3 -lm " + '"' +\
                os.path.join(filepath, 'Frequency_squarechirp_interface.c') + '"' + ' "' +\
                os.path.join(filepath, 'sim_code"/*.c') + ' -o ' + '"' +\
                os.path.join(filepath, out_lib_name) + '"'
            # print(compile_cmd)
            os.system(compile_cmd)

        self.start_time = 0.0
        self.step_time = 0.02
        self.current_time = self.start_time
        self.next_time = self.current_time + self.step_time
        
        self.Frequency_squarechirp_system = ctypes.cdll.LoadLibrary(os.path.join(filepath, out_lib_name))

        self.Frequency_squarechirp_system.initialize.restype = None
        self.Frequency_squarechirp_system.initialize.argtypes = [
            np.ctypeslib.ndpointer(dtype=np.float64),
            np.ctypeslib.ndpointer(dtype=np.float64),
            np.ctypeslib.ndpointer(dtype=np.float64),
            
        ]

        self.Frequency_squarechirp_system.one_step.restype = None
        self.Frequency_squarechirp_system.one_step.argtypes = [
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
        self.Frequency_squarechirp_system.initialize( self.inputpower1, self.deltaomega, self.deltaomegadot)
        
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
        self.Frequency_squarechirp_system.one_step( self.inputpower1, self.deltaomega, self.deltaomegadot)
        self.current_time += self.step_time
        self.next_time = self.current_time + self.step_time

        # return {
        #     "inputpower1": self.inputpower1,
        #     "deltaomega": self.deltaomega,
        #     "deltaomegadot": self.deltaomegadot,
        # 
        # }


# if __name__=="__main__":
#     parser = argparse.ArgumentParser(
#         prog="Frequency_squarechirp_pyinterface",
#         description="Python interface to Frequency_squarechirp.",
#     )
#     parser.add_argument("--stop_time", help="Simulation stop time. Total time of simulation.", type=float)
#     parser.add_argument("--decimation", help="Decimation factor. Data is saved once every specified decimation factor time steps.", default=1, type=int)
#     args = parser.parse_args()
#     if args.stop_time is None:
#         raise Exception("Stop time not specified. Type `python Frequency_squarechirp_pyinterface.py --help` for more info!!!")

#     STEP_TIME = 0.02
#     STOP_TIME = args.stop_time
#     DECIMATION = args.decimation

#     if STEP_TIME==-1:
#         raise Exception("STEP_TIME not specified.")
#     if STOP_TIME==-1:
#         raise Exception("STOP_TIME not specified.")
    
#     def to_numpy(*args):
#         return np.array(args, dtype=np.float64)

#     m = Frequency_squarechirp("Frequency_squarechirp_lib.so", step_time=STEP_TIME, compile=True)
    
#     DATA_OUT = np.zeros((1+int(STOP_TIME/(STEP_TIME*DECIMATION)), 1+1 + 1 + 1), dtype=np.float64)

#     # Specify value of input here
#     # 
#     m.reset()
#     DATA_OUT[0,:] = to_numpy(m.current_time, m.inputpower1[0], m.deltaomega[0], m.deltaomegadot[0])
    
#     LAST_CURRENT_TIME = m.current_time
#     WALL_TIME_ORIGIN = time.time_ns()
#     __counter__ = 0
#     while m.current_time < STOP_TIME:
#         # Specify value of input here
#         # 

#         m.one_step()
#         __counter__ += 1

#         if __counter__ % DECIMATION == 0:
#             try:
#                 DATA_OUT[int(__counter__ / DECIMATION),:] = to_numpy(m.current_time, m.inputpower1[0], m.deltaomega[0], m.deltaomegadot[0])
#             except:
#                 pass

#         if (m.current_time - LAST_CURRENT_TIME) / STOP_TIME * 100 > 5:
#             print(f"{round(m.current_time / STOP_TIME * 100, 0)}% complete. Total time elapsed: {(time.time_ns() - WALL_TIME_ORIGIN)/1e9} !!!")
#             LAST_CURRENT_TIME = m.current_time

#     if round(LAST_CURRENT_TIME / STOP_TIME * 100, 0)!=5:
#         print(f"{round(100.0, 0)}% complete. Total time elapsed: {(time.time_ns() - WALL_TIME_ORIGIN)/1e9}!!!")
#     hf = h5py.File("Frequency_squarechirp_out.h5", "w")
#     hf.create_dataset("sim_out", data=DATA_OUT)
#     hf.close()