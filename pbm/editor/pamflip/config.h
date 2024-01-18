#ifndef SSE_PBM_XY_FLIP
  #if WANT_SSE && HAVE_WORKING_SSE2
    #define SSE_PBM_XY_FLIP 1
  #else
    #define SSE_PBM_XY_FLIP 0
  #endif
#endif
