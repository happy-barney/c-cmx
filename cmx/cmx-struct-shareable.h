
#ifndef CMX_STRUCT_SHAREABLE_H
#define CMX_STRUCT_SHAREABLE_H 1

/**
 ** @file
 **
 ** @section Shareable structures
 **
 ** These macros help you with implementation of shared struct API.
 **
 ** Structs (instances) can be used directly or can be part of other structs.
 ** When used directly in multithread environment one needs synchronized API.
 **
 ** Common approach is:
 **     mutex_lock (self->mutex);
 **     do_something with possible "if error unlock and return"
 **     mutex_unlock (self->mutex);
 **
 ** Although it is correct it has some problems:
 ** - protected area is not clearly visible (same indent level for example)
 ** - call of paired functions is not (and cannot be) verified by compiler
 ** - it's quite noisy if mutex is optional
 ** - lock/unlock call as well as mutex type differs between libraries
 **
 ** So compare it with CMX alternative:
 **     CMX_STRUCT_SHAREABLE_SYNCHRONIZE (self) {
 **        do something with possible "if error break"
 **     }
 **
 ** @subsection Proposed usage (aka best practice)
 **
 ** @subsubsection API Function(s)
 **
 ** @fn struct XYZ * xyz_share (struct XYZ *ptr)
 ** Enable synchronized of ptr instance
 **
 ** By default structures are not shared.
 ** Synchronization (using access mutex) must be allowed by calling this function.
 ** Once enabled synchronization cannot be disabled.
 **
 ** Function returns its argument.
 **
 ** @subsubsection Structure definition
 **
 ** Use CMX_STRUCT_SHAREABLE_DEFINE to provide necessary data.
 ** Macro creates struct member with CMX_STRUCT_SHAREABLE_DEFINE name.
 **
 **     struct XYZ {
 **         CMX_STRUCT_SHAREABLE_DEFINE;
 **         ...;
 **     };
 **
 ** @subsubsection Structure constructor
 **
 ** Use CMX_STRUCT_SHAREABLE_INIT() to initialize data
 **
 **     struct XYZ * constructor (...) {
 **         retval = malloc;
 **         CMX_STRUCT_SHAREABLE_INIT (retval);
 **         ...;
 **     }
 **
 ** CMX macros handles properly initialization with bzero() (ie static initialization)
 **
 ** @subsubsection Enable shareing function
 **
 ** Struct API should provide _share() function to enable synchronization.
 **
 **     struct XYZ * xyz_share (struct XYZ *self) {
 **         CMX_STRUCT_SHAREABLE_SHARE (self);
 **     }
 **
 ** @subsubsection API functions
 **
 ** CMX_STRUCT_SHAREABLE_SYNCHRONIZE() macro can detect enabled synchronization
 ** and wraps following block with proper lock/unlock calls.
 **
 **     rettype xyz_function (struct XYZ *self, ...) {
 **         rettype retval;
 **         CMX_STRUCT_SHAREABLE_SYNCHRONIZE (self) {
 **             ... do someting in protected area ...;
 **         }
 **         return retval;
 **     }
 **
 ** Best practice is to provide public synchronized and private non-synchronized API
 **
 **     rettype xyz_private_function (struct XYZ *self, ...) {
 **         rettype retval;
 **         ... do someting in protected area ...;
 **         return retval;
 **     }
 **
 **     rettype xyz_function (struct XYZ *self, ...) {
 **         rettype retval;
 **         CMX_STRUCT_SHAREABLE_SYNCHRONIZE (self) {
 **             retval = xyz_private_function (self, ...);
 **         }
 **         return retval;
 **     }
 **/

#include <cmx/cmx-env.h>
#include <cmx/cmx-token.h>
#include <cmx/cmx-meta.h>
#include <cmx/cmx-synchronize.h>

struct _CMX_Struct_Shareable {
    int enabled;
    CMX_MUTEX_TYPE mutex;
};

#ifndef CMX_STRUCT_SHAREABLE_NAME
#define CMX_STRUCT_SHAREABLE_NAME                                       \
    cmx_struct_shareable
/**
 **<@brief Structure member name generated and used by CMX_STRUCT_SHAREABLE_* macros.
 **
 ** Default: cmx_struct_shareable
 **
 ** You can override default value defining this macro before including cmx.h
 **     #define CMX_STRUCT_SHAREABLE_NAME i_want_different_name
 **     #include <cmx.h>
 **/
#endif

#define CMX_STRUCT_SHAREABLE_DEFINE                                     \
    struct _CMX_Struct_Shareable CMX_STRUCT_SHAREABLE_NAME
/**
 **<@brief Structure member definition.
 **
 ** Uses other CMX macros:
 ** - CMX_STRUCT_SHAREABLE_NAME
 ** - CMX_MUTEX_TYPE
 **
 ** Usage:
 **   struct {
 **     CMX_STRUCT_SHAREABLE_DEFINE;
 **     ...;
 **   };
 **/

#define CMX_STRUCT_SHAREABLE_INIT(Ptr)                                  \
    do {                                                                \
        if (NULL != (Ptr))                                              \
            (Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled = 0;               \
    } while (0);
/**
 **<@brief Initialize data declared by CMX_STRUCT_SHAREABLE_DEFINE
 **
 ** You have to use this macro if you initialize dynamically allocated
 ** memory unless you clear whole structure with zeros (bzero())
 **/

#define CMX_STRUCT_SHAREABLE_SHARE(Ptr)                                 \
    CMX_STRUCT_SHAREABLE_SHARE_TRAN (                                   \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_SHAREABLE_SHARE),                  \
        (Ptr)                                                           \
    )
/**
 **<@brief Defines core body of *_share function.
 **
 ** Macro recognizes following BLOCK and ELSE statements.
 **
 ** BLOCK is executed only once, when share is enabled
 ** ELSE is executed otherwise.
 **
 ** Macro returns its argument
 ** Macro generates NULL safe code (BLOCK is not executed then)
 ** Macro allows 'break' in BLOCK.
 ** Macro expands as single statement.
 **
 ** @param Pointer to structure
 **
 ** Uses:
 ** - CMX_STRUCT_SHAREABLE_NAME
 ** - CMX_MUTEX_INIT
 ** - CMX_META_BODY_ELSE_BREAK
 **/

#define CMX_STRUCT_SHAREABLE_SHARE_TRAN(Prefix, Ptr)                    \
    CMX_STRUCT_SHAREABLE_SHARE_IMPL (                                   \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Else),                                       \
        CMX_TOKEN (Prefix, Finish),                                     \
        (Ptr)                                                           \
    )
/**
 **<Transition macro to expand arguments and provide tokens required
 ** by implementation macro.
 **/

#define CMX_STRUCT_SHAREABLE_SHARE_IMPL(Body, Else, Finish, Ptr)        \
    if (1) {                                                            \
        if (NULL != (Ptr)) {                                            \
            if (! ((Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled)) {         \
                (Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled = 1;           \
                CMX_MUTEX_INIT (                                        \
                    (Ptr)->CMX_STRUCT_SHAREABLE_NAME.mutex              \
                );                                                      \
                goto Body;                                              \
            } else {                                                    \
                goto Else;                                              \
            }                                                           \
        }                                                               \
    Finish:                                                             \
        return (Ptr);                                                   \
    } else CMX_META_BODY_ELSE_BREAK (Body, Else, Finish)
/**
 **<Implementation macro
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE(Ptr)                           \
    CMX_STRUCT_SHAREABLE_SYNCHRONIZE_TRAN (                             \
        CMX_UNIQUE_TOKEN (CMX_STRUCT_SHAREABLE_SYNCHRONIZE),            \
        (Ptr)                                                           \
    )
/**
 **<@brief Synchronize BLOCK evaluation using struct pointer.
 **
 ** Synchronization is used only if struct synchronization is enabled,
 ** see CMX_STRUCT_SHAREABLE_SHARE()
 **
 ** @param Ptr struct pointer
 **
 ** Macro generates NULL safe code (BLOCK is not executed then)
 ** Macro allows 'break' in BLOCK.
 ** Macro expands as single statement.
 **
 ** Uses:
 ** - CMX_STRUCT_SHAREABLE_NAME
 ** - CMX_MUTEX_LOCK
 ** - CMX_MUTEX_UNLOCK
 ** - CMX_META_BODY_BREAK
 **
 ** Usage:
 **   type safe_function_foo (struct bar *ptr, ...) {
 **     type rv = DEFAULT;
 **     CMX_STRUCT_SHAREABLE_SYNCHRONIZE (ptr)
 **       rv = unsafe_function_foo (ptr, ...);
 **     return rv;
 **   }
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE_TRAN(Prefix, Ptr)              \
    CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL (                             \
        CMX_TOKEN (Prefix, Enabled),                                    \
        CMX_TOKEN (Prefix, Body),                                       \
        CMX_TOKEN (Prefix, Finish),                                     \
        (Ptr)                                                           \
    )
/**
 **<Transition macro to expand arguments and provide tokens required
 ** by implementation macro.
 **/

#define CMX_STRUCT_SHAREABLE_SYNCHRONIZE_IMPL(Enabled, Body, Finish, Ptr) \
    if (1) {                                                            \
        int Enabled = 0;                                                \
        if ((NULL != (Ptr))) {                                          \
            Enabled = (Ptr)->CMX_STRUCT_SHAREABLE_NAME.enabled;         \
            if (Enabled)                                                \
                CMX_MUTEX_LOCK ((Ptr)->CMX_STRUCT_SHAREABLE_NAME.mutex); \
            goto Body;                                                  \
        }                                                               \
    Finish:                                                             \
        if (Enabled)                                                    \
            CMX_MUTEX_UNLOCK ((Ptr)->CMX_STRUCT_SHAREABLE_NAME.mutex);  \
    } else CMX_META_BODY_BREAK (Body, Finish)
/**
 **<Implementation macro
 **
 ** Implementation notes
 ** - if Struct ptr is NULL, skip protected block
 ** - if synchronization is not enabled, skip mutex
 ** - synchronization status is preserved locally to prevent unlock without lock
 **/

#endif  /* header guard */
