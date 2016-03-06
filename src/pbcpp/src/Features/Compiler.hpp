#ifndef PBCPP_COMPILER_DETECT_HPP
#define PBCPP_COMPILER_DETECT_HPP

#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define PBCPP_CPP11
#    define PBCPP_CPP 11
#  else
#    define PBCPP_CPP98
#    define PBCPP_CPP 9
#  endif
#endif

#if defined(__GNUC__)
#  define PBCPP_GNUC
#  if defined(__GNUC_PATCHLEVEL__)
#    define PBCPP_GNUC_VERSION (__GNUC__ * 10000 \
                                + __GNUC_MINOR__ * 100 \
                                + __GNUC_PATCHLEVEL__)
#  else
#    define PBCPP_GNUC_VERSION (__GNUC__ * 10000 \
                                + __GNUC_MINOR__ * 100)
#  endif
#  if defined(__clang__)
#    define PBCPP_CLANG
#  endif
#elif defined(_MSC_VER)
#  define PBCPP_MSVC
#endif

#endif //PBCPP_COMPILER_DETECT_HPP
