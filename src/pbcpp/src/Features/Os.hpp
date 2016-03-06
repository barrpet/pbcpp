#ifndef PBCPP_OS_DETECT_HPP
#define PBCPP_OS_DETECT_HPP

//------------------------------------------------------------------------------
// WINDOWS (NATIVE, MINGW, CYGWIN POSIX)
//------------------------------------------------------------------------------
#if defined(_WIN32)
   //_WIN32 defined for both x86 and x86_64
#  if defined(_WIN64)
#    define PBCPP_WIN 64
#    define PBCPP_WIN64
#    define PBCPP_MCPU 64
#    if defined(__MINGW64__)
#      define PBCPP_MINGW 64
#      define PBCPP_MINGW64
#    endif
#  else
#    define PBCPP_WIN 32
#    define PBCPP_WIN32
#    define PBCPP_MCPU 32
#    if defined(__MINGW32__)
#      define PBCPP_MINGW 32
#      define PBCPP_MINGW32
#    endif
#  endif
#elif defined(__CYGWIN__)
   //Cygwin under Windows (32-bit only)
#  define PBCPP_CYGWIN
#  define PBCPP_MCPU 32
#endif

//------------------------------------------------------------------------------
// OSX, IOS, AND DARWIN
//------------------------------------------------------------------------------
#if defined(__APPLE__) && defined(__MACH__)
#  define PBCPP_APPLE
#  include <TargetConditionals.h>
#  if TARGET_IPHONE_SIMULATOR == 1
#    define PBCPP_APPLE_SIMULATOR
#  elif TARGET_OS_IPHONE == 1
#    define PBCPP_IOS
#  elif TARGET_OS_MAC == 1
#    define PBCPP_OSX
#  endif
#endif

//------------------------------------------------------------------------------
// LINUX
//------------------------------------------------------------------------------
#if defined(__linux__)
#  define PBCPP_LINUX
#endif

//------------------------------------------------------------------------------
// POSIX AND UNIX
//------------------------------------------------------------------------------
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || \
    (defined(__APPLE__) && defined(__MACH__)))
#  define PBCPP_UNIX
#  include <unistd.h>
#  if defined(_POSIX_VERSION)
#    define PBCPP_POSIX _POSIX_VERSION
#  endif
#endif

//------------------------------------------------------------------------------
// BSD
//------------------------------------------------------------------------------
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#  include <sys/param.h>
#  if defined(BSD)
	   //BSD (DragonFly BSD, FreeBSD, OpenBSD, NetBSD)
#    define PBCPP_BSD
#  endif
#endif

//------------------------------------------------------------------------------
// IBM AIX
//------------------------------------------------------------------------------
#if defined(_AIX)
#  define PBCPP_AIX
#endif

//------------------------------------------------------------------------------
// HEWLETT-PACKARD HP-UX
//------------------------------------------------------------------------------
#if defined(__hpux)
#  define PBCPP_HPUX
#endif

//------------------------------------------------------------------------------
// SOLARIS
//------------------------------------------------------------------------------
#if defined(__sun) && defined(__SVR4)
#  define PBCPP_SOLARIS
#  if !defined(__sun__) && defined(__SunOS) 
#    define PBCPP_SOLARIS_STUDIO
#  endif
#endif

#endif //PBCPP_OS_DETECT_HPP

__unix__
__linux__


#endif //PB_CPP_OS_DETECT_HPP
