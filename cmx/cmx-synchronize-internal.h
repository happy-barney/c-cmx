
#ifndef CMX_SYNCHRONIZE_INTERNAL_H
#define CMX_SYNCHRONIZE_INTERNAL_H 1

#include <cmx/cmx-token.h>
#include <cmx/cmx-meta.h>

#define CMX_SYNCHRONIZE_INTERNAL_TRAN(Type, Do, Prefix, Init, Cond)     \
    CMX_SYNCHRONIZE_INTERNAL_IMPL (                                     \
        CMX_SYNCHRONIZE_INTERNAL_MUTEX_##Type##_TYPE,                   \
        CMX_SYNCHRONIZE_INTERNAL_MUTEX_##Type##_VAR,                    \
        CMX_SYNCHRONIZE_INTERNAL_DO_##Do##_JUMP,                        \
        CMX_SYNCHRONIZE_INTERNAL_DO_##Do##_BODY,                        \
        CMX_TOKEN (Prefix, Mutex),                                      \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Else),                                       \
        CMX_TOKEN (Prefix, Finish),                                     \
        Init,                                                           \
        Cond                                                            \
    )
/**<@brief "All purpose" synchronization macro
 **
 ** Synchronously executes following BLOCK (with optional ELSE)
 ** statements.
 **
 ** @param Type - VALUE | PTR - How to treat Init (new or reference)
 ** @param Do   - DO | COND - How to treat Cond (ignore or evaluate)
 ** @param Prefix - unique prefix for internal tokens
 ** @param Init   - Mutex initialization statement
 ** @param Cond   - Condition
 **
 ** Expects that following macros exists:
 ** - CMX_SYNCHRONIZE_INTERNAL_MUTEX_ ## Type ## _TYPE
 ** - CMX_SYNCHRONIZE_INTERNAL_MUTEX_ ## Type ## _VAR
 ** - CMX_SYNCHRONIZE_INTERNAL_DO_    ## Do   ## _JUMP
 ** - CMX_SYNCHRONIZE_INTERNAL_DO_    ## Do   ## _BODY
 **/

#define CMX_SYNCHRONIZE_INTERNAL_IMPL(                                  \
    MUTEX_TYPE, MUTEX_VAR,                                              \
    DO_COND, DO_BODY,                                                   \
    Name, Body, Else, Finish,                                           \
    Init, Cond                                                          \
)                                                                       \
    if (1) {                                                            \
        CMX_MUTEX_TYPE MUTEX_TYPE (Name) = MUTEX_VAR ((Init));          \
        CMX_MUTEX_LOCK (MUTEX_TYPE (Name));                             \
        DO_COND ((Cond), Body, Else);                                   \
    Finish:                                                             \
        CMX_MUTEX_UNLOCK (MUTEX_TYPE (Name));                           \
    } DO_BODY (Body, Else, Finish)
/**<Implementation macro
 **
 ** @param MUTEX_TYPE What is internal variable (value or pointer)
 ** @param MUTEX_VAR  How to get MUTEX_TYPE from Init expression
 ** @param DO_COND    Evaluate condition and goto Body/Else labels
 ** @param DO_BODY    Following block evaluation
 **/

#define CMX_SYNCHRONIZE_INTERNAL_MUTEX_VALUE_TYPE(Name)                 \
    Name

#define CMX_SYNCHRONIZE_INTERNAL_MUTEX_VALUE_VAR(Value)                 \
    Value

#define CMX_SYNCHRONIZE_INTERNAL_MUTEX_PTR_TYPE(Name)                   \
    * Name

#define CMX_SYNCHRONIZE_INTERNAL_MUTEX_PTR_VAR(Value)                   \
    & (Value)

#define CMX_SYNCHRONIZE_INTERNAL_DO_DO_BODY(Body, Else, Finish)         \
    CMX_META_BODY_BREAK (Body, Finish)

#define CMX_SYNCHRONIZE_INTERNAL_DO_DO_JUMP(Cond, Body, Else)           \
    goto Body;

#define CMX_SYNCHRONIZE_INTERNAL_DO_COND_BODY(Body, Else, Finish)       \
    CMX_META_BODY_ELSE_BREAK (Body, Finish)

#define CMX_SYNCHRONIZE_INTERNAL_DO_COND_JUMP(Cond, Body, Else)         \
    if (Cond) goto Body; else goto Else;

#endif  /* header guard */
