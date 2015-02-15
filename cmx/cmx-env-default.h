
/** @file
 **
 ** Implement default env macros
 **/

#ifndef CMX_ENV_DEFAULT_H
#define CMX_ENV_DEFAULT_H 1

#ifndef CMX_LABEL_UNUSED
#define CMX_LABEL_UNUSED
#endif

#ifndef CMX_LOCAL_STORE
#include <string.h>
#define CMX_LOCAL_STORE(Name, Var)                                      \
    char Name[sizeof (Var)];                                            \
    memcpy (&Name, &(Var), sizeof (Var))
#endif

#ifndef CMX_LOCAL_RESTORE
#include <string.h>
#define CMX_LOCAL_RESTORE(Name, Var)                                    \
    memcpy (&(Var), &Name, sizeof (Var))
#endif

#endif  /* header guard */
