
/** @file
 **
 ** CMX env macros using GCC extensions
 **/

#ifndef CMX_ENV_GCC_DEFINE_H
#define CMX_ENV_GCC_DEFINE_H 1

#ifdef HAVE_CMX_ENV_GCC

#define CMX_ENV_GCC_ATOMIC_INT_TYPE                                    \
    int

#  if CMX_ATOMIC_INT_TYPE
#  define CMX_ATOMIC_INT_TYPE CMX_ENV_GCC_ATOMIC_INT_TYPE
#  endif

#define CMX_ENV_GCC_ATOMIC_INT_SET(Var, Value)                         \
    __sync_lock_test_and_set (& (Var), (Value))

#  if CMX_ATOMIC_INT_SET
#  define CMX_ATOMIC_INT_SET CMX_ENV_GCC_ATOMIC_INT_SET
#  endif

#define CMX_ENV_GCC_ATOMIC_INT_INCREMENT(Var)                          \
    __sync_add_and_fetch (& (Var), 1)

#  if CMX_ATOMIC_INT_INCREMENT
#  define CMX_ATOMIC_INT_INCREMENT CMX_ENV_GCC_ATOMIC_INT_INCREMENT
#  endif

#define CMX_ENV_GCC_ATOMIC_INT_DECREMENT_AND_TEST(Var)                 \
    (0 == __sync_sub_and_fetch (& (Var), 1))

#  if CMX_ATOMIC_INT_DECREMENT_AND_TEST
#  define CMX_ATOMIC_INT_DECREMENT_AND_TEST CMX_ENV_GCC_ATOMIC_INT_DECREMENT_AND_TEST
#  endif


#define CMX_ENV_GCC_LABEL_UNUSED                                       \
    __attribute__((__unused__))

#  if CMX_ENV_BIND_GCC_P (LABEL_UNUSED)
#  define CMX_LABEL_UNUSED CMX_ENV_GCC_LABEL_UNUSED
#  endif

#endif  /* env conditional */
#endif  /* header guard */
