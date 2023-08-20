include(cmake/Macros.cmake)

# detect our OS
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  set(MIM_OS_WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(MIM_OS_LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(MIM_OS_MACOS 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^k?FreeBSD$")
  set(MIM_OS_FREEBSD 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^OpenBSD$")
  set(MIM_OS_OPENBSD 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^NetBSD$")
  set(MIM_OS_NETBSD 1)
else()
    message(WARNING "Mim could not detected a know supported OS: ${CMAKE_SYSTEM_NAME}")
endif()


# detect the compiler
# Note: The detection order is important because:
# - Visual Studio can both use MSVC and Clang
# - GNUCXX can still be set on macOS when using Clang
if(MSVC)
  set(MIM_COMPILER_MSVC 1)

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(MIM_COMPILER_CLANG_CL 1)
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(MIM_COMPILER_CLANG 1)
elseif(CMAKE_COMPILER_IS_GNUCXX)
  set(MIM_COMPILER_GCC 1)

  execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION)
  string(REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" MIM_COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}")
else()
  message(FATAL_ERROR "Unsupported compiler")
  return()
endif()


# detect the architecture (note: this test won't work for cross-compilation)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(MIM_ARCH_X64 1)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(MIM_ARCH_X86 1)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^armv7")
  set(MIM_ARCH_ARM 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch64")
  set(MIM_ARCH_ARM64 1)
else()
  message(FATAL_ERROR "Unsupported architecture")
  return()
endif()
