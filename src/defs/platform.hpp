#pragma once

#include <stdint.h>

using LevelId = int64_t; // 64-bit
static_assert(sizeof(LevelId) == 8, "level id is not 8 bytes");

#include <Geode/platform/cplatform.h>

/*
* platform macros
* GLOBED_IS_UNIX - unix-like system
* GLOBED_IS_64BIT - 64-bit
* GLOBED_IS_X86 - x86
* GLOBED_IS_X86_64 - x86_64
* GLOBED_IS_ARM - arm
* GLOBED_IS_ARMV7 - armv7
* GLOBED_IS_ARM64 - aarch64

* GLOBED_PLATFORM_STRING_PLATFORM - string in format like "Mac", "Android", "Windows"
* GLOBED_PLATFORM_STRING_ARCH - string in format like "x86", "x64", "armv7", "arm64"
* GLOBED_PLATFORM_STRING - those two above combined into one, i.e. "Windows x86"
*/

#if !defined(GEODE_IS_WINDOWS)
# define GLOBED_IS_UNIX 1
#endif

#if UINTPTR_MAX > 0xffffffff
# define GLOBED_IS_64BIT
#endif

#ifdef GEODE_IS_MACOS
# define GLOBED_PLATFORM_STRING_PLATFORM "Mac"
#  ifdef GEODE_IS_MAC_ARM
#   define GLOBED_PLATFORM_STRING_ARCH "arm64"
#   define GLOBED_IS_ARM 1
#   define GLOBED_IS_ARM64 1
#  else
#   define GLOBED_PLATFORM_STRING_ARCH "x86_64"
#   define GLOBED_IS_X86_64 1
#   define GLOBED_IS_X86 1
#  endif
#elif defined(GEODE_IS_WINDOWS)
# define GLOBED_PLATFORM_STRING_PLATFORM "Windows"
# define GLOBED_PLATFORM_STRING_ARCH "x86_64"
# define GLOBED_IS_X86 1
# define GLOBED_IS_X86_64 1
#elif defined(GEODE_IS_ANDROID)
# define GLOBED_PLATFORM_STRING_PLATFORM "Android"
#  define GLOBED_IS_ARM 1
# ifdef GEODE_IS_ANDROID64
#  define GLOBED_PLATFORM_STRING_ARCH "arm64-v8a"
#  define GLOBED_IS_ARM64 1
# else
#  define GLOBED_PLATFORM_STRING_ARCH "armeabi-v7a"
#  define GLOBED_IS_ARMV7
# endif
#elif defined(GEODE_IS_IOS)
# define GLOBED_PLATFORM_STRING_PLATFORM "iOS"
#  define GLOBED_PLATFORM_STRING_ARCH "arm64"
# define GLOBED_IS_ARM 1
# define GLOBED_IS_ARM64 1
#endif

#define GLOBED_PLATFORM_STRING GLOBED_PLATFORM_STRING_PLATFORM " " GLOBED_PLATFORM_STRING_ARCH

constexpr bool GLOBED_LITTLE_ENDIAN = true;

// dllexport macro

#ifdef GEODE_IS_WINDOWS
    #ifdef GLOBED_EXPORTING
        #define GLOBED_DLL __declspec(dllexport)
    #else
        #define GLOBED_DLL __declspec(dllimport)
    #endif
#else
    #ifdef GLOBED_EXPORTING
        #define GLOBED_DLL __attribute__((visibility("default")))
    #else
        #define GLOBED_DLL
    #endif
#endif
