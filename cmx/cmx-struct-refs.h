
/** @file
 **
 ** Defines macros that help to write reference counting
 ** structures.
 **/

#ifndef CMX_STRUCT_REFS_H
#define CMX_STRUCT_REFS_H 1

#ifndef CMX_STRUCT_REFS_NAME
#define CMX_STRUCT_REFS_NAME cmx_refs
/**<Structure member name
 **/
#endif

#define CMX_STRUCT_REFS_DEFINE                                          \
    CMX_ATOMIC_TYPE CMX_STRUCT_REFS_NAME
/**<Structure member definition
 **
 ** Usage:
 ** struct {
 **   CMX_STRUCT_REFS_DEFINE;
 **   ...
 ** };
 **/

#define CMX_STRUCT_REFS_REF(Ptr)                                        \
    CMX_STRUCT_REFS_REF_IMPL_1 (                                        \
        (Ptr),                                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_REFS_REF)                          \
    )
/**< Define body of *_ref function
 **
 ** Macro evaluates increasing ref count and evaluates statement.
 ** Macro ends with "return Ptr"
 ** 'break' can be used in statement.
 **
 ** Macro generates NULL-safe code.
 ** Macro generates single statement code.
 **
 ** Usage:
 ** struct xyz * xyz_ref (struct xyz * ptr) {
 **   CMX_STRUCT_REFS_REF (ptr) { ... }
 ** }
 **/

#define CMX_STRUCT_REFS_REF_IMPL_1(Ptr, Prefix)                         \
    CMX_STRUCT_REFS_REF_IMPL_2 (                                        \
        (Ptr),                                                          \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Finish)                                      \
    )
/**< Transition macro to evaluate arguments and generate tokens
 **  required by implementation macro
 **/

#define CMX_STRUCT_REFS_REF_IMPL_2(Ptr, Body, Finish)                   \
    if (1) {                                                            \
        if (NULL != (Ptr)) {                                            \
            CMX_ATOMIC_INCREMENT ((Ptr)->CMX_STRUCT_REFS_NAME);         \
            goto Body;                                                  \
        }                                                               \
    Finish:                                                             \
        return (Ptr);                                                   \
    } CMX_META_BODY_BREAK (Body, Finish)
/** Implementation macro
 **/

#define CMX_STRUCT_REFS_UNREF(Ptr)                                      \
    CMX_STRUCT_REFS_UNREF_IMPL_1 (                                      \
        (Ptr),                                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_REFS_UNREF)                        \
    )
/**< Define body of *_unref function
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
 ** Usage:
 ** void xyz_unref (struct xyz * ptr) {
 **   CMX_STRUCT_REFS_UNREF (ptr) { clenaup (ptr); }
 **   CMX_STRUCT_REFS_UNREF (ptr) { clenaup (ptr); } else { ... }
 ** }
 **/

#define CMX_STRUCT_REFS_UNREF_IMPL_1(Ptr, Prefix)                       \
    CMX_STRUCT_REFS_UNREF_IMPL_2 (                                      \
        (Ptr),                                                          \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Else)                                        \
    )
/**< Transition macro to evaluate arguments and generate tokens
 **  required by implementation macro
 **/

#define CMX_STRUCT_REFS_UNREF_IMPL_2(Ptr, Body, Else)                   \
    if (1) {                                                            \
        if (NULL != (Ptr)) {                                            \
            if (CMX_ATOMIC_DECREMENT_AND_TEST ((Ptr)->CMX_STRUCT_REFS_NAME)) \
                goto Body;                                              \
            else                                                        \
                goto Else;                                              \
        }                                                               \
    } CMX_META_DO_ELSE_BREAK (Body, Else)
/**< Implementation macro
 **/

#endif  /* guard */
