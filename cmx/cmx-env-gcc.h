
/** @file
 **
 ** CMX env macros using GCC extensions
 **
 ** Env file defines macros with CMX_ENV_GCC_ prefix.
 ** Env file defines env dependant macros only if they are not defined yet.
 **/

#ifndef CMX_ENV_GCC_H
#define CMX_ENV_GCC_H 1

#ifdef __GNUC__

#define CMX_ENV_GCC_ATOMIC_INT_TYPE                                     \
    int

#  ifndef CMX_ATOMIC_INT_TYPE
#  define CMX_ATOMIC_INT_TYPE CMX_ENV_GCC_ATOMIC_INT_TYPE
#  endif

#define CMX_ENV_GCC_ATOMIC_INT_SET(Var, Value)                          \
    __sync_lock_test_and_set (& (Var), (Value))

#  ifndef CMX_ATOMIC_INT_SET
#  define CMX_ATOMIC_INT_SET CMX_ENV_GCC_ATOMIC_INT_SET
#  endif

#define CMX_ENV_GCC_ATOMIC_INT_INCREMENT(Var)                           \
    __sync_add_and_fetch (& (Var), 1)

#  ifndef CMX_ATOMIC_INT_INCREMENT
#  define CMX_ATOMIC_INT_INCREMENT CMX_ENV_GCC_ATOMIC_INT_INCREMENT
#  endif

#define CMX_ENV_GCC_ATOMIC_INT_DECREMENT_AND_TEST(Var)                  \
    (0 == __sync_sub_and_fetch (& (Var), 1))

#  ifndef CMX_ATOMIC_INT_DECREMENT_AND_TEST
#  define CMX_ATOMIC_INT_DECREMENT_AND_TEST CMX_ENV_GCC_ATOMIC_INT_DECREMENT_AND_TEST
#  endif


#define CMX_ENV_GCC_LABEL_UNUSED                                        \
    __attribute__((__unused__))

#  ifndef CMX_LABEL_UNUSED
#  define CMX_LABEL_UNUSED CMX_ENV_GCC_LABEL_UNUSED
#  endif

#define CMX_ENV_GCC_LOCAL_STORE(Name, Var)                              \
    typeof (Var) Name = Var

#  ifndef CMX_LOCAL_STORE
#  define CMX_LOCAL_STORE CMX_ENV_GCC_LOCAL_STORE
#  endif

#define CMX_ENV_GCC_LOCAL_RESTORE(Name, Var)                            \
    Var = Name

#  ifndef CMX_LOCAL_RESTORE
#  define CMX_LOCAL_RESTORE CMX_ENV_GCC_LOCAL_RESTORE
#  endif

#endif  /* env conditional */
#endif  /* header guard */
