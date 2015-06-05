
/** @file
 **
 ** CMX env macros using glib (http://glib.org/).
 **/

#ifndef CMX_ENV_GLIB_DEFINE_H
#define CMX_ENV_GLIB_DEFINE_H 1

#ifdef HAVE_CMX_ENV_GLIB

#include <glib.h>

#define CMX_ENV_GLIB_MUTEX_TYPE                                         \
    GMutex

#  ifndef CMX_MUTEX_TYPE
#  define CMX_MUTEX_TYPE CMX_ENV_GLIB_MUTEX_TYPE
#  endif

#define CMX_ENV_GLIB_MUTEX_INIT(Var)                                  \
    { 0 }

#  ifndef CMX_MUTEX_INIT
#  define CMX_MUTEX_INIT CMX_ENV_GLIB_MUTEX_INIT
#  endif

#define CMX_ENV_GLIB_MUTEX_LOCK(Var)                                    \
    g_mutex_lock (& (Var))

#  ifndef CMX_MUTEX_LOCK
#  define CMX_MUTEX_LOCK CMX_ENV_GLIB_MUTEX_LOCK
#  endif

#define CMX_ENV_GLIB_MUTEX_UNLOCK(Var)                                  \
    g_mutex_unlock (& (Var))

#  ifndef CMX_ENV_GLIB_MUTEX_UNLOCK
#  define CMX_MUTEX_UNLOCK CMX_ENV_GLIB_MUTEX_UNLOCK
#  endif

#define CMX_ENV_GLIB_ATOMIC_INT_TYPE                                    \
    gint

#  ifndef CMX_ATOMIC_INT_TYPE
#  define CMX_ATOMIC_INT_TYPE CMX_ENV_GLIB_ATOMIC_INT_TYPE
#  endif

#define CMX_ENV_GLIB_ATOMIC_INT_SET(Var, Value)                         \
    g_atomic_int_set (& (Var), (Value))

#  ifndef CMX_ATOMIC_INT_SET
#  define CMX_ATOMIC_INT_SET CMX_ENV_GLIB_ATOMIC_INT_SET
#  endif

#define CMX_ENV_GLIB_ATOMIC_INT_INCREMENT(Var)                          \
    g_atomic_int_inc (& (Var))

#  ifndef CMX_ATOMIC_INT_INCREMENT
#  define CMX_ATOMIC_INT_INCREMENT CMX_ENV_GLIB_ATOMIC_INT_INCREMENT
#  endif

#define CMX_ENV_GLIB_ATOMIC_INT_DECREMENT_AND_TEST(Var)                 \
    g_atomic_int_dec_and_test (& (Var))

#  ifndef CMX_ATOMIC_INT_DECREMENT_AND_TEST
#  define CMX_ATOMIC_INT_DECREMENT_AND_TEST CMX_ENV_GLIB_ATOMIC_INT_DECREMENT_AND_TEST
#  endif

#define CMX_ENV_GLIB_LABEL_UNUSED                                       \
    G_GNUC_UNUSED

#  ifndef CMX_LABEL_UNUSED
#  define CMX_LABEL_UNUSED CMX_ENV_GLIB_LABEL_UNUSED
#  endif

#endif  /* env conditional */
#endif  /* header guard */
