#ifndef SLSA_SIM_ENGINE_H
#define SLSA_SIM_ENGINE_H

/**
 * @file slsa_sim_engine.h
 *
 * This file declares functions which provide
 * access to new execution engine.
**/ 

/* Copyright 2011-2021 The MathWorks, Inc. */

#include "libmwslsa_sim.h"
#include "matrix.h"

/* Custom save function signature for saving the block specific execution data.
 * Saved data is returned as 'void*' which has to be deallocated by the caller.
 * Size of the data saved is returned in argument 'sizeInBytes'.
 *
 * NOTE : It is assumed that the memory is allocated by 'malloc' or it's sister functions and
 * on the rapid accelerator side 'free' is used cleanup the memory */
typedef void* (*SlsaCustomOPSaveFcn)(void* dworkPtr, unsigned int* sizeInBytes);

/* Custom restore function signature for saving the block specific execution data.*/
typedef void  (*SlsaCustomOPRestoreFcn)(void* dworkPtr, const void* data, unsigned int sizeInBytes);

/* Returns the set of blocks which do not support save/restore OperatingPoint
 * in rapid accelerator mode.*/
typedef mxArray*  (*SlsaDisallowedBlocksFcn)();

/* Pointer to GetWork function */
typedef mxArray*  (*SlsaGetWorkFcn)();

/* Pointer to SetWork function */
typedef void  (*SlsaSetWorkFcn)(const mxArray* workData);

/* run simulation */
SLSA_SIM_PUBLISHED_C void ssRunSimulation(void* ss);

SLSA_SIM_PUBLISHED_C void ssWriteSimMetadata(
    void* ss,
    const char* metadataFilePath
    );

/* Create OperatingPoint ModelData */
SLSA_SIM_PUBLISHED_C void allocOPModelData(void* executionInfo);

/* Delete OperatingPoint ModelData */
SLSA_SIM_PUBLISHED_C void freeOPModelData(void* executionInfo);

/* Cache the pointers */
SLSA_SIM_PUBLISHED_C void slsaCacheDWorkPointerForSimTargetOP(void* ss, void** ptr);

/* Cache the data */
SLSA_SIM_PUBLISHED_C void slsaCacheDWorkDataForSimTargetOP(void* ss, void* dataPtr, unsigned int sizeInBytes);

/* Cache the raw memory */
SLSA_SIM_PUBLISHED_C void slsaSaveRawMemoryForSimTargetOP(
        void* ss,
        const char* key,
        void** ptr,
        unsigned int sizeInBytes,
        SlsaCustomOPSaveFcn customOPSaveFcn,
        SlsaCustomOPRestoreFcn customOPRestoreFcn
        );

/* Set the different WORK sizes in bytes */
SLSA_SIM_PUBLISHED_C void ssSetWorkSizeInBytes(
        void*  ss,
        unsigned int sizeInBytes,
        const char*  type
        );

/* Unsupported blocks for save/restore OperatingPoint */
SLSA_SIM_PUBLISHED_C void slsaDisallowedBlocksForSimTargetOP(
        void* ss,
        SlsaDisallowedBlocksFcn disallowedBlocksFcn
        );

/* Set the <model>_GetDWork function pointer on SimStruct 'ss' */
SLSA_SIM_PUBLISHED_C void slsaGetWorkFcnForSimTargetOP(
        void*  ss,
        SlsaGetWorkFcn getWorkFcn
        );

/* Set the <model>_SetDWork function pointer on SimStruct 'ss' */
SLSA_SIM_PUBLISHED_C void slsaSetWorkFcnForSimTargetOP(
        void*  ss,
        SlsaSetWorkFcn setWorkFcn
        );

/* Call back to MATLAB interpreter for string-to-string functions.*/
SLSA_SIM_PUBLISHED_C
char *rtCallMATLABInterpStr2Str(const char *cmd, const char *input);

/* Release memory used for the result of rtCallMATLABInterpStr2Str. */
SLSA_SIM_PUBLISHED_C void rtCallMATLABInterpStr2StrFree(char *str);


/* Verifying results of rtCallMATLABInterpStr2Str call. */
SLSA_SIM_PUBLISHED_C
bool rtCallMATLABInterpStr2StrVerify(const char *str1, const char *str2);

/* Call back to MATLAB interpreter for double-to-double functions.*/
SLSA_SIM_PUBLISHED_C
double rtCallMATLABInterpDouble2double(const char *cmd, const double u);

/* System Object setup function. It is invoked from MATLAB System Block start. */
SLSA_SIM_PUBLISHED_C void ssRevalSysObjSetup(const char *sysObjName);

/* System Object step function. It is invoked from MATLAB System Block output. */
SLSA_SIM_PUBLISHED_C double ssRevalSysObjStep(const double u);

/* System Object terminate function. It is invoked from MATLAB System Block 
terminate. */
SLSA_SIM_PUBLISHED_C void ssRevalSysObjTerminate();

/* System Object reset function. It is invoked from MATLAB System Block 
initialize. */
SLSA_SIM_PUBLISHED_C void ssRevalSysObjReset();

/* System Object update function. It is invoked from MATLAB System Block 
update. */
SLSA_SIM_PUBLISHED_C void ssRevalSysObjUpdate();

/* Add a network outbound rule to allow the rapid accelerator to communicate
 * with MATLAB over a TCP port */
SLSA_SIM_PUBLISHED_C int addOutBoundRule(size_t port, const char* program);

#endif /* SLSA_SIM_ENGINE_H */
