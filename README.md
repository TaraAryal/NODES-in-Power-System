# NODES-in-Power-System
This is the final version of the code for the paper entitled "Application of Neural Ordinary Differential Equations for the Simplified Power system Frequency Dynamics System" published in NAPS 2023.  
The system setup in MATLAB/Simulink generates the ``true'' $\Delta\omega$ and $\Delta\dot{\omega}$. Simulink Coder creates C-code from a Simulink model to integrate Simulink with Python. The generated C code is compiled into the shared library using "gcc" compiler. The compiled shared library is imported into Python using "ctypes" library, which is then run to generate training data. The training data sets are obtained from frequency_logchirp, whereas validation data sets are obtained from Frequency_squarechirp and Frequency_stepchirp.

Note: The system set up in MATLAB/Simulink shared here is from 2021b version. Therefore, the Simulink file can be opened either in same version or the latest version.

To generate the training data sets used in the paper, The following steps has to be followed:
1) All the necessary interface files are updated in the "training_and_validation" folder. Clone all the files first in your local computer. Before starting the training process, make sure the GnuWin software is installed in your computer. It can be obtained in following link. https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download?use_mirror=cfhcable&download= 
2) After installing the software, open command window or git bash window and hit the command " make shared_lib" in the same folder. This will generate .so file used to run the matlab simulink file in python. This has to be done for both training datasets as well as for validation data sets (i.e inside "square_validation_signal" and "step_validation_signal" folder).
3) Once this is set up, the training process can be started using the following command: python NODEs_tara.py train. Once the model is trained, the test can be done either by replacing the train with a test in the above code line.
4) If you simply want to observe the results from the paper , you can also simply run "validation.ipynb" file where you can extract training and validation data sets, load the trained model and visualize the predictions for both the cases. The ipynb file has the flexibility to observe both accuracy of both type of validation data sets. 
5) Alternatively, if the above command is still giving the issue, you can generate training and validation data sets from simulink files and generate .mat file. Finally, you can simply read the .mat file in Python and start either training or validation process. However, c-code generation process has the flexibility to run the simulink directly from python upto desirable time limit. 

You can also find the full instruction in the validation.ipynb file as well. 

Thank you for your interest in this paper and feel free to send an email on " Tara.Aryal@jacks.sdstate.edu" if you have any inquiry.
