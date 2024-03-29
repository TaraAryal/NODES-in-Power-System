/* Published header for libmex, the mex library.
Copyright 1984-2018 The MathWorks, Inc.
This file containes types, macros, and declarations necessary to
interface mex files with the current version of MATLAB.

See the release notes for information on supporting earlier versions. */

#if defined(_MSC_VER)
# pragma once
#endif
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3))
# pragma once
#endif

#ifndef mex_h
#define mex_h

#ifdef __cplusplus
# define LIBMWMEX_API_EXTERN_C extern "C"
#else
# define LIBMWMEX_API_EXTERN_C extern
#endif

#ifdef _MSC_VER
# define MWMEX_EXPORT_SYM __declspec(dllexport)
#elif __GNUC__ >= 4
# define MWMEX_EXPORT_SYM __attribute__ ((visibility("default")))
#else
# define MWMEX_EXPORT_SYM
#endif

#ifdef MW_NEEDS_VERSION_H
# define MEXFUNCTION_LINKAGE LIBMWMEX_API_EXTERN_C MWMEX_EXPORT_SYM
#else
# define MEXFUNCTION_LINKAGE LIBMWMEX_API_EXTERN_C
#endif

#include <stdio.h>


typedef struct impl_info_tag *MEX_impl_info;

#include "matrix.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef void (*mex_exit_fn)(void);
#ifdef __cplusplus
}
#endif

typedef struct mexGlobalTableEntry_Tag
{
const char *name;             /* The name of the global */
mxArray    **variable;        /* A pointer to the variable */
} mexGlobalTableEntry, *mexGlobalTable;

#ifdef _WIN32
#define cicompare(s1,s2) utStrcmpi((s1),(s2))
#else
#define cicompare(s1,s2) strcmp((s1),(s2))
#endif
#define cscompare(s1,s2) strcmp((s1),(s2))

typedef struct mexFunctionTableEntry_tag {
const char *  name;
mxFunctionPtr f;
int           nargin;
int           nargout;
struct _mexLocalFunctionTable *local_function_table;
} mexFunctionTableEntry, *mexFunctionTable;

typedef struct _mexLocalFunctionTable {
size_t           length;
mexFunctionTable entries;
} _mexLocalFunctionTable, *mexLocalFunctionTable;

typedef struct {
void (*initialize)(void);
void (*terminate)(void);
} _mexInitTermTableEntry, *mexInitTermTableEntry;

#define MEX_INFORMATION_VERSION 1

typedef void (*fn_clean_up_after_error)(void);
typedef const char *(*fn_simple_function_to_string)(mxFunctionPtr f);

typedef mexLocalFunctionTable (*fn_mex_get_local_function_table)(void);
typedef mexLocalFunctionTable (*fn_mex_set_local_function_table)(mexLocalFunctionTable);


#if defined(TARGET_API_VERSION)
#if !(TARGET_API_VERSION == 700 || TARGET_API_VERSION == 800)
#error invalid TARGET_VERSION_API definition
#elif defined(MEX_DOUBLE_HANDLE) && TARGET_API_VERSION != 700
#error It is illegal to use MEX_DOUBLE_HANDLE with linear versioning
#elif defined(MX_COMPAT_32) && TARGET_API_VERSION != 700
#error It is illegal to use MX_COMPAT_32 with linear versioning
#endif
#endif


#if !defined(TARGET_API_VERSION) || TARGET_API_VERSION == 700
#ifndef MEX_DOUBLE_HANDLE
#define mexCallMATLAB mexCallMATLABWithObject
#define mexCallMATLABWithTrap mexCallMATLABWithTrapWithObject
#define mexGetVariable mexGetVariableWithObject
#define mexGet(a,b) \
NULL;do{mexGetIsDeprecated x;}while(0)
#define mexSet(a,b,c) \
0;do{mexSetIsDeprecated x;}while(0)
#endif /* MEX_DOUBLE_HANDLE */
#define mexSetTrapFlag(a) \
0;do{mexSetTrapFlagIsDeprecated x;}while(0)


#elif TARGET_API_VERSION == 800

#define mexCallMATLAB mexCallMATLAB_800
#define mexCallMATLABWithTrap mexCallMATLABWithTrap_800
#define mexEvalString mexEvalString_800
#define mexEvalStringWithTrap mexEvalStringWithTrap_800
#define mexGet mexGetIsDeprecated
#define mexSet mexSetIsDeprecated
#define mexGetVariable mexGetVariable_800
#define mexGetVariablePtr mexGetVariablePtr_800
#define mexPutVariable mexPutVariable_800
#define mexPrintf mexPrintf_800
#define mexSetTrapFlag mexSetTrapFlagIsDeprecated
#define mexErrMsgIdAndTxt mexErrMsgIdAndTxt_800
#define mexWarnMsgIdAndTxt mexWarnMsgIdAndTxt_800
#define mexErrMsgTxt mexErrMsgTxt_800
#define mexWarnMsgTxt mexWarnMsgTxt_800
#define mexIsLocked mexIsLocked_800
#define mexLock mexLock_800
#define mexUnlock mexUnlock_800
#define mexMakeArrayPersistent mexMakeArrayPersistent_800
#define mexMakeMemoryPersistent mexMakeMemoryPersistent_800
#define mexPrintAssertion mexPrintAssertion_800
#define mexIsGlobal mexIsGlobal_800
#define mexFunctionName mexFunctionName_800
#define mexAtExit mexAtExit_800

#endif /* TARGET_API_VERSION */
/*
* Issue error message and return to MATLAB prompt
*/
LIBMWMEX_API_EXTERN_C void mexErrMsgTxt(
const char	*error_msg	/* string with error message */
);


/*
* Issue formatted error message with corresponding error identifier and return to MATLAB
* prompt.
*/
LIBMWMEX_API_EXTERN_C void mexErrMsgIdAndTxt(
const char * identifier, /* string with error message identifier */
const char * err_msg,    /* string with error message printf-style format */
...                      /* any additional arguments */
);


/*
* Invoke an unidentified warning. Such warnings can only be affected by the M-code
* 'warning * all', since they have no specific identifier. See also mexWarnMsgIdAndTxt.
*/
LIBMWMEX_API_EXTERN_C void mexWarnMsgTxt(
const char	*warn_msg	/* string with warning message */
);


/*
* Invoke a warning with message identifier 'identifier' and message derived from 'fmt' and
* subsequent arguments. The warning may either get printed as is (if it is set to 'on'), or
* not actually get printed (if set to 'off'). See 'help warning' in MATLAB for more
* details.
*/
LIBMWMEX_API_EXTERN_C void mexWarnMsgIdAndTxt(
const char * identifier,    /* string with warning message identifer */
const char * warn_msg,	/* string with warning message printf-style format */
...                         /* any additional arguments */
);


/*
* mex equivalent to MATLAB's "disp" function
*/
LIBMWMEX_API_EXTERN_C int mexPrintf(
const char	*fmt,	/* printf style format */
...				/* any additional arguments */
);


#define printf mexPrintf


/*
* Remove all components of an array plus the array header itself
* from MATLAB's memory allocation list.  The array will now
* persist between calls to the mex function.  To destroy this
* array, you will need to explicitly call mxDestroyArray().
*/
LIBMWMEX_API_EXTERN_C void mexMakeArrayPersistent(
mxArray *pa              /* pointer to array */
);


/*
* Remove memory previously allocated via mxCalloc from MATLAB's
* memory allocation list.  To free this memory, you will need to
* explicitly call mxFree().
*/
LIBMWMEX_API_EXTERN_C void mexMakeMemoryPersistent(void *ptr);


/*
* call MATLAB function
*/
LIBMWMEX_API_EXTERN_C int mexCallMATLAB(
int		nlhs,			/* number of expected outputs */
mxArray	*plhs[],		/* pointer array to outputs */
int		nrhs,			/* number of inputs */
mxArray	*prhs[],		/* pointer array to inputs */
const char	*fcn_name		/* name of function to execute */
);


/*
* call MATLAB function with Trap
*/
LIBMWMEX_API_EXTERN_C mxArray	*mexCallMATLABWithTrap(
int         nlhs,       /* number of expected outputs */
mxArray     *plhs[],    /* pointer array to outputs */
int         nrhs,       /* number of inputs */
mxArray     *prhs[],    /* pointer array to inputs */
const char  *fcn_name   /* name of function to execute */
);


/*
* Print an assertion-style error message and return control to the
* MATLAB command line.
*/
LIBMWMEX_API_EXTERN_C void mexPrintAssertion(
const char *test,
const char *fname,
int linenum,
const char *message);


/*
* This function is deprecated and always return false.
*/
LIBMWMEX_API_EXTERN_C bool mexIsGlobal(const mxArray *pA);


/*
* Place a copy of the array value into the specified workspace with the
* specified name
*/
LIBMWMEX_API_EXTERN_C int mexPutVariable(
const char *workspace,
const char *name,
const mxArray *parray		/* matrix to copy */
);


/*
* return a pointer to the array value with the specified variable
* name in the specified workspace
*/
LIBMWMEX_API_EXTERN_C const mxArray *mexGetVariablePtr(
const char *workspace,
const char *name		/* name of symbol */
);


/*
* return a copy of the array value with the specified variable
* name in the specified workspace
*/
LIBMWMEX_API_EXTERN_C mxArray *mexGetVariable(
const char	*workspace,
const char  *name                /* name of variable in question */
);


/*
* Lock a MEX-function so that it cannot be cleared from memory.
*/
LIBMWMEX_API_EXTERN_C void mexLock(void);


/*
* Unlock a locked MEX-function so that it can be cleared from memory.
*/
LIBMWMEX_API_EXTERN_C void mexUnlock(void);


/*
* Return true if the MEX-function is currently locked, false otherwise.
*/
LIBMWMEX_API_EXTERN_C bool mexIsLocked(void);


/*
* Return the name of a the MEXfunction currently executing.
*/
LIBMWMEX_API_EXTERN_C const char *mexFunctionName(void);


/*
* Parse and execute MATLAB syntax in string.  Returns zero if successful,
* and a non zero value if an error occurs.
*/
LIBMWMEX_API_EXTERN_C int mexEvalString(
const char *str	   /* matlab command string */
);


/*
* Parse and execute MATLAB syntax in string.  Returns NULL if successful,
* and an MException if an error occurs.
*/
LIBMWMEX_API_EXTERN_C mxArray* mexEvalStringWithTrap(
const char *str	   /* matlab command string */
);


/*
* Register Mex-file's At-Exit function (accessed via MEX callback)
*/
LIBMWMEX_API_EXTERN_C int mexAtExit(mex_exit_fn exit_fcn);
#ifdef MEX_DOUBLE_HANDLE

/* API interface which mimics the "get" function */
LIBMWMEX_API_EXTERN_C const mxArray *mexGet(double handle, const char *property);


/*
* mex equivalent to MATLAB's "set" function
*/
LIBMWMEX_API_EXTERN_C int mexSet(double handle, const char *property, mxArray *value);

#endif


MEXFUNCTION_LINKAGE
/*
* mexFunction is the user-defined C routine that is called upon invocation
* of a MEX-function.
*/
void mexFunction(
int           nlhs,           /* number of expected outputs */
mxArray       *plhs[],        /* array of pointers to output arguments */
int           nrhs,           /* number of inputs */
const mxArray *prhs[]         /* array of pointers to input arguments */
);

#endif /* mex_h */