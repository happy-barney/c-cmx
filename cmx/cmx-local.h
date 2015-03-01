
/** @file
 **
 ** CMX local variable value
 **
 ** CMX_LOCAL allows you to locally modify upper scope variable
 ** and revert to origin value after your code finishes.
 **
 ** Macro is inspired by perl's local keyword.
 **
 ** Be aware that if Var expression is known by multiple threads then
 ** its value is changed in all of them.
 **
 ** Usage:
 **   CMX_LOCAL (var) { var = value; ... }
 **
 **   CMX_LOCAL (foo)
 **   CMX_LOCAL (bar)
 **   { block }
 **/

#ifndef CMX_LOCAL_H
#define CMX_LOCAL_H 1

#include <cmx/cmx-token.h>
#include <cmx/cmx-meta.h>
#include <cmx/cmx-env.h>

#define CMX_LOCAL(Var)                                                  \
    CMX_LOCAL_TRAN (                                                    \
        CMX_UNIQUE_TOKEN (CMX_LOCAL),                                   \
        (Var)                                                           \
    )
/**<Make Var value local, revert to origin value after block finishes.
 ** Var value is intact
 **
 ** Macro generates single statement expression.
 ** Block can be terminated by break.
 **/

#define CMX_LOCAL_TRAN(Prefix, Var)                                     \
    CMX_LOCAL_IMPL (                                                    \
        CMX_TOKEN (Prefix, Name),                                       \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Finish),                                     \
        (Var)                                                           \
    )
/**<Transient macro to expand arguments and define tokens required
 ** by implementation macro
 **/

#define CMX_LOCAL_IMPL(Name, Body, Finish, Var)                         \
    if (1) {                                                            \
        CMX_LOCAL_STORE (Name, Var);                                    \
        goto Body;                                                      \
    Finish:                                                             \
        CMX_LOCAL_RESTORE (Name, Var);                                  \
    } else CMX_META_BODY_BREAK (Body, Finish)
/**<Implementation macro
 **/

#endif  /* header guard */
