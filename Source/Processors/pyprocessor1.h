#ifndef __PYX_HAVE__pyprocessor1
#define __PYX_HAVE__pyprocessor1


#ifndef __PYX_HAVE_API__pyprocessor1

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

__PYX_EXTERN_C DL_IMPORT(void) pyprocess(AudioSampleBuffer);

#endif /* !__PYX_HAVE_API__pyprocessor1 */

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initpyprocessor1(void);
#else
PyMODINIT_FUNC PyInit_pyprocessor1(void);
#endif

#endif /* !__PYX_HAVE__pyprocessor1 */
