/*
Filename:       Frequency_logchirp_interface.h
Written by:     Niranjan Bhujel
Date:           Nov-15-2023 11:53:14
*/

#ifndef Frequency_logchirp_interface_h
#define Frequency_logchirp_interface_h

#include "sim_code/Frequency_logchirp.h"

#if defined(_WIN32) || defined(_WIN64)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#define NULL_DEVICE "NUL:"
#elif defined(__linux__)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#define NULL_DEVICE "/dev/null"
#else
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif

EXPORT void initialize(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot);

EXPORT void one_step(real_T *inputpower1, real_T *deltaomega, real_T *deltaomegadot);

EXPORT void terminate();

#endif