# NODES-in-Power-System
This is the final version of the code for the application of Neural Ordinary Differential Equations for the Simplified Power system Frequency Dynamics system without controller gain. 
The system setup in MATLAB/Simulink generates the ``true'' $\Delta\omega$ and $\Delta\dot{\omega}$. Simulink Coder creates C-code from a Simulink model to integrate Simulink with Python. The generated C code is compiled into the shared library using "gcc" compiler. The compiled shared library is imported into Python using "ctypes" library, which is then run to generate training data. The training data sets are obtained from frequency_logchirp, whereas validation data sets are obtained from Frequency_squarechirp and Frequency_stepchirp. 

To start the training process via the command line the code is: python NODEs_tara.py train
Once the model is trained, the test can be observed either by replacing the train with a test in the above code line or "validation.ipynb" file can be used which has the flexibility to observe both accuracy of both type of validation data sets. 
