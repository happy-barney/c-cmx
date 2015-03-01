
#ifndef CMX_STRUCT_REFS_H
#define CMX_STRUCT_REFS_H 1

#include <cmx/cmx-token.h>
#include <cmx/cmx-meta.h>
#include <cmx/cmx-env.h>

/** @file
 **
 ** @section Summary
 **
 ** Provides standardized API for structs with reference counting.
 **
 ** @section Idea behind
 **
 ** Many data structures use ref counting instead of plain
 ** duplication. These macros helps you to implement it
 ** "properly".
 **
 ** Macros require environment with CMX_ATOMIC_INT_ defined
 **
 ** @section Proposed usage
 **
 ** - use CMX_STRUCT_REFS_DEFINE in your structure definition
 ** - use CMX_STRUCT_REFS_INIT in your constructor
 ** - use CMX_STRUCT_REFS_REF and CMX_STRUCT_REFS_UNREF
 **   to define your ref/unref functions
 **/

#ifndef CMX_STRUCT_REFS_NAME
#define CMX_STRUCT_REFS_NAME                                            \
    cmx_refs
/**<Structure member name
 **/
#endif

#define CMX_STRUCT_REFS_DEFINE                                          \
    CMX_ATOMIC_INT_TYPE CMX_STRUCT_REFS_NAME
/**<Structure member definition
 **
 ** Uses CMX_STRUCT_REFS_NAME as member name
 **
 ** Macro uses:
 **  CMX_ATOMIC_INT_TYPE
 **  CMX_STRUCT_REFS_NAME
 **
 ** Usage:
 ** struct {
 **   CMX_STRUCT_REFS_DEFINE;
 **   ...
 ** };
 **/

#define CMX_STRUCT_REFS_INIT(Ptr)                                       \
    CMX_ATOMIC_INT_SET ((Ptr)->CMX_STRUCT_REFS_NAME, 1)
/**<Initialize ref counter
 **
 ** Uses:
 ** - CMX_ATOMIC_INT_SET
 ** - CMX_STRUCT_REFS_NAME
 **/

#define CMX_STRUCT_REFS_REF(Ptr)                                        \
    CMX_STRUCT_REFS_REF_TRAN (                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_REFS_REF),                         \
        (Ptr)                                                           \
    )
/**<Define body of ref function
 **
 ** Macro evaluates increasing ref count and evaluates following BLOCK.
 ** Macro can be followed by block, single statement and also empty command
 **
 ** Macro ends with "return Ptr"
 ** 'break' can be used in statement.
 **
 ** Macro generates NULL-safe code.
 ** Macro generates single statement code.
 **
 ** Macro uses:
 ** - CMX_ATOMIC_INT_INCREMENT
 ** - CMX_STRUCT_REFS_NAME
 **
 ** Usage:
 **   struct xyz * xyz_ref (struct xyz * ptr) {
 **     CMX_STRUCT_REFS_REF (ptr) { ... }
 **   }
 **/

#define CMX_STRUCT_REFS_REF_TRAN(Prefix, Ptr)                           \
    CMX_STRUCT_REFS_REF_IMPL (                                          \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Finish),                                     \
        (Ptr)                                                           \
    )
/**<Transient macro to evaluate arguments and generate tokens
 ** required by implementation macro
 **/

#define CMX_STRUCT_REFS_REF_IMPL(Body, Finish, Ptr)                     \
    if (1) {                                                            \
        if (NULL != (Ptr)) {                                            \
            CMX_ATOMIC_INT_INCREMENT ((Ptr)->CMX_STRUCT_REFS_NAME);     \
            goto Body;                                                  \
        }                                                               \
    Finish:                                                             \
        return (Ptr);                                                   \
    } CMX_META_BODY_BREAK (Body, Finish)
/**Implementation macro
 **/

#define CMX_STRUCT_REFS_UNREF(Ptr)                                      \
    CMX_STRUCT_REFS_UNREF_TRAN (                                        \
        (Ptr),                                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_REFS_UNREF)                        \
    )
/**<Define unref function body
 **
 ** Macro decreases ref count and evaluates blockstatement if it drops
 ** to zero. Optional else statement is evaluated otherwise.
 ** If Ptr evaluates to NULL nor block neither else statement is evaluated.
 **
 ** 'break' can be used in statements.
 **
 ** Macro generates NULL-safe code.
 ** Macro generates single statement code.
 **
 ** Uses
 ** - CMX_ATOMIC_INT_DECREMENT_AND_TEST
 ** - CMX_STRUCT_REFS_NAME
 **
 ** Usage:
 ** void xyz_unref (struct xyz * ptr) {
 **   CMX_STRUCT_REFS_UNREF (ptr) { clenaup (ptr); }
 **   CMX_STRUCT_REFS_UNREF (ptr) { clenaup (ptr); } else { ... }
 ** }
 **/

#define CMX_STRUCT_REFS_UNREF_TRAN(Ptr, Prefix)                         \
    CMX_STRUCT_REFS_UNREF_IMPL (                                        \
        (Ptr),                                                          \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Else)                                        \
    )
/**<Transition macro to evaluate arguments and generate tokens
 ** required by implementation macro
 **/

#define CMX_STRUCT_REFS_UNREF_IMPL(Ptr, Body, Else)                     \
    if (1) {                                                            \
        if (NULL != (Ptr)) {                                            \
            if (CMX_ATOMIC_INT_DECREMENT_AND_TEST ((Ptr)->CMX_STRUCT_REFS_NAME)) \
                goto Body;                                              \
            else                                                        \
                goto Else;                                              \
        }                                                               \
    } CMX_META_DO_ELSE_BREAK (Body, Else)
/**<Implementation macro
 **/

#endif  /* guard */
