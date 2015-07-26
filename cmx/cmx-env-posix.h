
/** @file
 **
 ** CMX env using POSIX threads.
 **/

#ifndef CMX_ENV_POSIX_H
#define CMX_ENV_POSIX_H 1

#ifdef HAVE_CMX_ENV_POSIX

#include <pthread.h>

#define CMX_ENV_POSIX_MUTEX_TYPE                                         \
    pthread_mutex_t

#  ifndef CMX_MUTEX_TYPE
#  define CMX_MUTEX_TYPE CMX_ENV_POSIX_MUTEX_TYPE
#  endif

#define CMX_ENV_POSIX_MUTEX_CREATE                                      \
    PTHREAD_MUTEX_INITIALIZER

#  if CMX_MUTEX_CREATE
#  define CMX_MUTEX_CREATE CMX_ENV_POSIX_MUTEX_CREATE
#  endif

#define CMX_ENV_POSIX_MUTEX_INIT(Var)                                  \
    ((Var) = CMX_MUTEX_CREATE)

#  if CMX_MUTEX_INIT
#  define CMX_MUTEX_INIT CMX_ENV_POSIX_MUTEX_INIT
#  endif

#define CMX_ENV_POSIX_MUTEX_LOCK(Var)                                    \
    pthread_mutex_lock (& (Var))

#  if CMX_MUTEX_LOCK
#  define CMX_MUTEX_LOCK CMX_ENV_POSIX_MUTEX_LOCK
#  endif

#define CMX_ENV_POSIX_MUTEX_UNLOCK(Var)                                 \
    pthread_mutex_unlock (& (Var))

#  if CMX_ENV_BIND_POSIX_P (MUTEX_UNLOCK)
#  define CMX_MUTEX_UNLOCK CMX_ENV_POSIX_MUTEX_UNLOCK
#  endif

#endif  /* env conditional */
#endif  /* header guard */
