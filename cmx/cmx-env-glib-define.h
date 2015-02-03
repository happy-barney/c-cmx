
/** @file
 **
 ** defines env macros with CMX_ENV_GLIB prefix
 **/

#ifndef CMX_ENV_GLIB_DEFINE_H
#define CMX_ENV_GLIB_DEFINE_H 1

#ifdef CMX_WITH_ENV_GLIB

//#include <glib.h>

#define CMX_ENV_GLIB_MUTEX_TYPE                                         \
    GMutex

#define CMX_ENV_GLIB_MUTEX_STATIC                                       \
    { 0 }

#define CMX_ENV_GLIB_MUTEX_LOCK(Var)                                    \
    g_mutex_lock (& (Var))

#define CMX_ENV_GLIB_MUTEX_UNLOCK(Var)                                  \
    g_mutex_unlock (& (Var))

#define CMX_ENV_GLIB_ATOMIC_TYPE                                        \
    gint

#define CMX_ENV_GLIB_ATOMIC_INCREMENT(Var)                              \
    g_atomic_int_inc (& (Var))

#define CMX_ENV_GLIB_ATOMIC_DECREMENT_AND_TEST(Var)                     \
    g_atomic_int_dec_and_test (& (Var))

#define CMX_ENV_GLIB_LABEL_UNUSED                                       \
    G_GNUC_UNUSED

#endif  /* env conditional */
#endif  /* header guard */
