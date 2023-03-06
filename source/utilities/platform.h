#ifndef __C_UTILITY_PLATFORM_H__
#define __C_UTILITY_PLATFORM_H__

#define OS_WINDOWS "WINDOWS" /// @brief The identification for Microsoft Windows.
#define OS_IPHONE "IPHONE" /// @brief The identification for Apple Iphones.
#define OS_MACOSX "MACOS" /// @brief The identification for Apple Macintoshes.
#define OS_IOSEMD "IOSEMBEDDED" /// @brief The identification for Apple mobile devices. (Ipad, Iphone, Ipod)
#define OS_LINUX "LINUX" /// @brief The identification for Linux operating systems.
#define OS_POSIX "POSIX" /// @brief The identification for posix compliant operating systems.
#define OS_UNIX "UNIX" /// @brief The identification for Unix based operating systems.
#define OS_ANDROID "ANDROID" /// @brief The identification for Android or ChromeOS.
#define OS_SUNMS "SUNMICROSYSTEM" /// @brief The identification for Orcale Sun Microsystems.
#define OS_HPUX "HPUX" /// @brief The identification for HP UX devices.
#define OS_BSD "BSD" /// @brief The identification for BSD compliant operating systems.
#define OS_DFLY "DRAGONFLY" /// @brief The identification for DragonFly.
#define OS_FBSD "FREEBSD" /// @brief The identification for FreeBSD.
#define OS_NBSD "NETBSD" /// @brief The identification for NetBSD.
#define OS_OBSD "OPENBSD" /// @brief The identification for OpenBSD.

#ifdef __WIN32

        #define OS_PLATFORM OS_WINDOWS

#elif __APPLE__ || __MACH__

    #include <TargetConditionals.h>

    #ifdef TARGET_OS_MAC

        #define OS_PLATFORM OS_MACOSX

    #elif TARGET_OS_IPHONE

        #define OS_PLATFORM OS_IPHONE

    #elif TARGET_OS_EMBEDDED

        #define OS_PLATFORM OS_IOSEMD

    #endif

#elif __linux__

    #define OS_PLATFORM OS_LINUX

#elif _POSIX_VERSION

    #define OS_PLATFORM OS_POSIX

#elif __unix__

    #define OS_PLATFORM OS_UNIX

#elif __ANDROID__

    #define OS_PLATFORM OS_ANDROID

#elif __sun

    #define OS_PLATFORM OS_SUNMS

#elif __hpux

    #define OS_PLATFORM OS_HPUX

#elif BSD

    #define OS_PLATFORM OS_BSD

#elif __DragonFly__

    #define OS_PLATFORM OS_DFLY

#elif __FreeBSD__

    #define OS_PLATFORM OS_FBSD

#elif __NetBSD__

    #define OS_PLATFORM OS_NBSD

#elif __OpenBSD__

    #define OS_PLATFORM OS_OBSD


#else
    #define OS_PLATFORM "UNKNOWN"

#endif

#endif //__C_UTILITY_PLATFORM_H__
