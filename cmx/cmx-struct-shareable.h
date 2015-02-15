
/** @file
 **
 ** @section Summary
 **
 ** Provides standardized API for shareable structs.
 **
 ** @section Proposed usage
 **
 ** Struct API will provide share function to enable synchronization.
 **
 ** Public API functions will be defined via skeleton:
 **   public_function (struct *ptr, ...) {
 **     return_type rv;
 **     CMX_STRUCT_SHAREABLE_SYNCHRONIZE (ptr) {
 **       rv = private_function (ptr, ...);
 **     };
 **     return rv;
 **   }
 **
 ** @section API Functions
 **
 ** @fn struct xyz * xyz_share (struct xyz *ptr)
 ** By default structures are not shared. Shareing (using access mutex) must
 ** be allowed by calling this function.
 **
 ** Turning shareing on is irrevertible.
 **
 ** Function, as well as *_ref() proposed by cmx-struct-refs.h, returns
 ** it's argument.
 **
 ** @section Proposed usage
 **
 ** - use CMX_STRUCT_SHAREABLE_DEFINE in your structure definition
 ** - use CMX_STRUCT_SHAREABLE_INIT in your constructor
 ** - use CMX_STRUCT_SHAREABLE_SHARE to define your share function
 ** - call your share function to enable feature
 **/

#ifndef CMX_STRUCT_SHAREABLE_H
#define CMX_STRUCT_SHAREABLE_H 1

#ifndef CMX_MUTEX_TYPE
#error "cmx-share-shareable.h requires CMX_MUTEX_TYPE (see cmx-env.h)"
#endif

#ifndef CMX_MUTEX_INIT
#error "cmx-share-shareable.h requires CMX_MUTEX_INIT (see cmx-env.h)"
#endif

#ifndef CMX_MUTEX_LOCK
#error "cmx-share-shareable.h requires CMX_MUTEX_LOCK (see cmx-env.h)"
#endif

#ifndef CMX_MUTEX_UNLOCK
#error "cmx-share-shareable.h requires CMX_MUTEX_UNLOCK (see cmx-env.h)"
#endif

struct _CMX_Struct_Shareable {
    int enabled;
    CMX_MUTEX_TYPE mutex;
};

#ifndef CMX_STRUCT_SHAREABLE_NAME
#define CMX_STRUCT_SHAREABLE_NAME cmx_shareable
/**<Structure member name generated and used by other macros.
 ** Default: cmx_shareable
 **/
#endif

#define CMX_STRUCT_SHAREABLE_DEFINE                                     \
    struct _CMX_Struct_Shareable CMX_STRUCT_SHAREABLE_NAME
/**<Structure member definition.
 **
 ** Uses:
 ** - CMX_STRUCT_SHAREABLE_NAME
 ** - CMX_MUTEX_TYPE
 **
 ** Usage:
 **   struct {
 **     CMX_STRUCT_SHAREABLE_DEFINE;
 **     ...;
 **   };
 **/

#define CMX_STRUCT_SHAREABLE_SHARE(Ptr)                                 \
    CMX_STRUCT_SHAREABLE_SHARE_TRAN (                                   \
        (Ptr),                                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_SHAREABLE_SHARE)                   \
    )
/** Defines core body of *_share function.
 ** Macro recognizes following BLOCK and ELSE statements.
 **
 ** BLOCK is executed only once, when share is enabled
 ** ELSE is executed otherwise.
 **
 ** @param Pointer to structure
 **
 ** Uses:
 ** - CMX_STRUCT_SHAREABLE_NAME
 ** - CMX_MUTEX_STATIC_INIT
 **
 ** Usage:
 ** struct xyz * xyz_share (struct xyz *)
 **/

#define CMX_STRUCT_SHAREABLE_SHARE_TRAN(Ptr, Prefix)                    \
    CMX_STRUCT_SHAREABLE_SHARE_IMPL (                                   \
        (Ptr),                                                          \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Else),                                       \
        CMX_TOKEN (Prefix, Finish)                                      \
    )
/**< Transition macro to expand arguments and provide tokens required
 **  by implementation macro.
 **/

#define CMX_STRUCT_SHAREABLE_SHARE_IMPL(Ptr, Body, Else, Finish)        \
    if (1) {                                                            \
        if (NULL != (Ptr)) {                                            \
            if (! ((Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled)) {         \
                (Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled = 1;           \
                (Ptr)->CMX_STRUCT_SHAREABLE_NAME.mutex =                \
                    CMX_MUTEX_STATIC_INIT;                              \
                goto Body;                                              \
            } else {                                                    \
                goto Else;                                              \
            }                                                           \
        }                                                               \
    Finish:                                                             \
        return (Ptr);                                                   \
    } CMX_META_BODY_ELSE_BREAK (Body, Else, Finish)
/**<Implementation macro
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE(Ptr)                           \
    CMX_STRUCT_SHAREABLE_SYNCHRONIZE_TRAN (                             \
        (Ptr),                                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_SHAREABLE_SYNCHRONIZE)             \
    )
/**<Synchronize BLOCK evaluation using struct pointer.
 ** Synchronization is used only if struct sharing was enabled.
 **
 ** @param Ptr struct pointer
 **
 ** Macro generates NULL safe code (BLOCK is not executed then)
 ** Macro allows 'break' in BLOCK.
 ** Macro expands as single statement.
 **
 ** Uses:
 ** - CMX_STRUCT_SHAREABLE_NAME
 ** Usage:
 **   type safe_function_foo (struct bar *ptr, ...) {
 **     type rv = DEFAULT;
 **     CMX_STRUCT_SHAREABLE_SYNCHRONIZE (ptr)
 **       rv = unsafe_function_foo (ptr, ...);
 **     return rv;
 **   }
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE_TRAN(Ptr, Prefix)              \
    CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL (                             \
        (Ptr),                                                          \
        CMX_TOKEN (Prefix, Mutex),                                      \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Finish)                                      \
    )
/**< Transition macro to expand arguments and provide tokens required
 **  by implementation macro.
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL(Ptr, Name, Body, Finish)  \
    if ((NULL == (Ptr)))                                                \
        ;                                                               \
    else if (! (Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled)                \
        goto Body;                                                      \
    else CMX_SYNCHRONIZE_INTERNAL_IMPL (                                \
             CMX_SYNCHRONIZE_INTERNAL_MUTEX_PTR_TYPE,                   \
             CMX_SYNCHRONIZE_INTERNAL_MUTEX_PTR_VAR,                    \
             CMX_SYNCHRONIZE_INTERNAL_DO_DO_JUMP,                       \
             CMX_SYNCHRONIZE_INTERNAL_DO_DO_BODY,                       \
             Name,                                                      \
             Body,                                                      \
             Else,                                                      \
             Finish,                                                    \
             (Ptr)->CMX_STRUCT_SHAREABLE_NAME.mutex,                    \
             1                                                          \
    )
/**<Implementation macro
 **/

#endif  /* header guard */
