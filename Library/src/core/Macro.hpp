#pragma once

#ifdef _WIN32
    #ifdef MExport
        #define API __declspec(dllexport)
    #else
        #define API __declspec(dllimport)
    #endif
#else
    #ifdef MExport
        #define API __attribute((visibility("default")))
    #else
        #define API 
    #endif
#endif

#define SDLW_NAMESPACE_BEGIN namespace sdlw {
#define SDLW_NAMESPACE_END }