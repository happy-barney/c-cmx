
/** @file
 **
 ** @section Summary
 **
 ** Provides standardized API for shareable structs.
 **
 ** @section Proposed Workflow
 **
 ** Struct API will provide *_share () function to enable synchronization.
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
 **/

#ifndef CMX_STRUCT_SHAREABLE_H
#define CMX_STRUCT_SHAREABLE_H 1

struct _CMX_Struct_Shareable {
    int enabled;
    CMX_MUTEX_TYPE mutex;
};

#ifndef CMX_STRUCT_SHAREABLE_NAME
#define CMX_STRUCT_SHAREABLE_NAME cmx_share
/**<Structure member name generated and used by other macros.
 ** Default: cmx_share
 **/
#endif

#define CMX_STRUCT_SHAREABLE_DEFINE                                     \
    struct _CMX_Struct_Shareable CMX_STRUCT_SHAREABLE_NAME
/**<Structure member definition.
 **
 ** Usage:
 **   struct {
 **     CMX_STRUCT_SHAREABLE_DEFINE;
 **     ...;
 **   };
 **/

#define CMX_STRUCT_SHAREABLE_SHARE(Ptr)                                 \
    CMX_STRUCT_SHAREABLE_SHARE_IMPL_1 (                                 \
        (Ptr),                                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_SHAREABLE_SHARE)                   \
    )
/** Defines core body of *_share function.
 ** Macro recognizes following BLOCK else ELSE statements.
 **
 ** BLOCK is executed only once, when shareing is enabled
 ** ELSE is executed every subsequent call.
 **
 ** @param Pointer to structure
 **
 ** Usage:
 ** struct xyz * xyz_share (struct xyz *
 **/

#define CMX_STRUCT_SHAREABLE_SHARE_IMPL_1(Ptr, Prefix)                  \
    CMX_STRUCT_SHAREABLE_SHARE_IMPL_2 (                                 \
        (Ptr),                                                          \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Else),                                       \
        CMX_TOKEN (Prefix, Finish)                                      \
    )
/**< Transition macro to expand arguments and provide tokens required
 **  by implementation macro.
 **/

#define CMX_STRUCT_SHAREABLE_SHARE_IMPL_2(Ptr, Body, Else, Finish)      \
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
/**< Implementation macro
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE(Ptr)                           \
    CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL_1 (                           \
        (Ptr),                                                          \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_SHAREABLE_SYNCHRONIZE)             \
    )
/**< Synchronize BLOCK evaluation using struct pointer.
 **  Synchronization is used only if struct sharing was enabled.
 **
 **  @param Ptr struct pointer
 **
 **  Macro generates NULL safe code (BLOCK is not executed then)
 **  Macro allows 'break' in BLOCK.
 **  Macro expands as single statement.
 **
 **  Usage:
 **    type public_function (struct xyz *ptr, ...) {
 **      type rv;
 **      CMX_STRUCT_SHAREABLE_SYNCHRONIZE (ptr) {
 **        ...;
 **      }
 **      return rv;
 **    }
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL_1(Ptr, Prefix)            \
    CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL_2 (                           \
        (Ptr),                                                          \
        CMX_TOKEN (Prefix, Mutex),                                      \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Finish)                                      \
    )
/**< Transition macro to expand arguments and provide tokens required
 **  by implementation macro.
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL_2(Ptr, Name, Body, Finish) \
    if ((NULL == (Ptr)) || (! (Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled)) \
        goto Body;                                                      \
    else CMX_SYNCHRONIZE_INTERNAL_IMPL_2 (                              \
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
/**< Implementation macro
 **/

#endif  /* header guard */
