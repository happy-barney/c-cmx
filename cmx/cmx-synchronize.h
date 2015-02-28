
#ifndef CMX_SYNCHRONIZE_H
#define CMX_SYNCHRONIZE_H 1

#include <cmx/cmx-token.h>
#include <cmx/cmx-meta.h>
#include <cmx/cmx-synchronize-internal.h>

#define CMX_SYNCHRONIZE                                                 \
    CMX_SYNCHRONIZE_INTERNAL_TRAN (                                     \
        VALUE,                                                          \
        DO,                                                             \
        CMX_UNIQUE_TOKEN (CMX_SYNCHRONIZE),                             \
        CMX_MUTEX_STATIC_INIT,                                          \
        1                                                               \
    )
/**<Synchronize following block
 **
 ** Macro generates break-safe code.
 ** Macro generates single statement code.
 ** Single or empty statement can be used as block
 **
 ** Usage:
 ** CMX_SYNCHRONIZE { ... }
 **/

#define CMX_SYNCHRONIZE_WITH(Mutex)                                     \
    CMX_SYNCHRONIZE_INTERNAL_TRAN (                                     \
        PTR,                                                            \
        DO,                                                             \
        CMX_UNIQUE_TOKEN (CMX_SYNCHRONIZE_WITH),                        \
        Mutex,                                                          \
        1                                                               \
    )
/**<Synchronize following statement / block using mutex
 **
 ** Macro generates break-safe code.
 ** Macro generates single statement code.
 **
 ** @param Mutex mutex initialization expression
 **
 ** @see CMX_MUTEX_TYPE
 **
 ** Usage:
 ** CMX_SYNCHRONIZE_WITH (big_global_mutex) { ... }
 **/

#define CMX_SYNCHRONIZE_IF(Cond)                                        \
    CMX_SYNCHRONIZE_INTERNAL_TRAN (                                     \
        VALUE,                                                          \
        COND,                                                           \
        CMX_UNIQUE_TOKEN (CMX_SYNCHRONIZE_IF),                          \
        CMX_MUTEX_STATIC_INIT,                                          \
        Cond                                                            \
    )
/**<Synchronize execution of following block with in-place mutex.
 **
 ** Macro executes following block, if Cond expression evaluates TRUE.
 ** Macro can also execute optional else-clause if Cond evaluate FALSE.
 ** Also else-clause is synchronized.
 **
 ** Macro generates break-safe code.
 ** Macro generates single statement code.
 **
 ** @param Cond boolean expression
 **
 ** Usage:
 **   CMX_SYNCHRONIZE_IF (cond) { ... }
 **   CMX_SYNCHRONIZE_IF (cond) { ... } else { ... }
 **/

#define CMX_SYNCHRONIZE_IF_WITH(Init, Cond)                             \
    CMX_SYNCHRONIZE_INTERNAL_TRAN (                                     \
        PTR,                                                            \
        COND,                                                           \
        CMX_UNIQUE_TOKEN (CMX_SYNCHRONIZE_IF),                          \
        (Init),                                                         \
        (Cond)                                                          \
    )
/**<Synchronize execution of following block using provided CMX_Mutex
 ** expression.
 **
 ** If Init expression evaluates as NULL, block is executed immediately.
 **
 ** Macro executes following block, if Cond expression evaluates TRUE.
 ** Macro can also execute following else-clause if Cond evaluates FALSE.
 **
 ** Macro generetes break-safe code.
 ** Macro generates single statement code.
 **
 ** @param Mutex mutex initialization expression
 ** @param Cond ... boolean expression
 **
 ** @see CMX_MUTEX_TYPE
 ** Usage:
 **   CMX_SYNCHRONIZE_IF_WITH (mutex, cond) { ... }
 **   CMX_SYNCHRONIZE_IF_WITH (mutex, cond) { ... } else { ... }
 **/

#define CMX_RUN_ONCE                                                    \
    CMX_RUN_ONCE_TRAN (                                                 \
        CMX_UNIQUE_TOKEN (CMX_RUN_ONCE)                                 \
    )
/**<Keyword-like expression to evaluate following statement only once.
 ** Supports also optional else-clause evaluated on subsequent call.
 **
 ** Statement evaluation is synchronized.
 **
 ** Macro generates break-safe code.
 ** Macro generates single-statement code.
 **
 ** Usage:
 **   CMX_RUN_ONCE { ... }
 **   CMX_RUN_ONCE { ... } else { ... }
 **/

#define CMX_RUN_ONCE_TRAN(Prefix)                                       \
    CMX_RUN_ONCE_IMPL (                                                 \
        CMX_TOKEN (Prefix, State),                                      \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Else)                                        \
    )
/**<Intermediate macro to expand params and produce
 ** tokens used by implementation macro
 **/

#define CMX_RUN_ONCE_IMPL(State, Body, Else)                            \
    CMX_SYNCHRONIZE                                                     \
    if (1) {                                                            \
        static int State = 0;                                           \
        if (State == 0) {                                               \
            State = 1;                                                  \
            goto Body;                                                  \
        } else                                                          \
            goto Else;                                                  \
    } else CMX_META_DO_ELSE_BREAK (Body, Else)
/**<Implementation macro
 **/

#endif  /* header guard */
