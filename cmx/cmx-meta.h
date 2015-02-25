
/** @file
 **
 ** Helper meta programming macros for custom control structures.
 **
 ** Based on article: http://www.chiark.greenend.org.uk/~sgtatham/mp/
 **
 **/

#ifndef CMX_META_H
#define CMX_META_H 1

#define CMX_META_TEMPLATE(Prefix, Pre, Post, Do)                        \
    CMX_META_TEMPLATE_TRAN (                                            \
        CMX_UNIQUE_TOKEN (Prefix),                                      \
        Pre, Post, Do                                                   \
    )

#define CMX_META_TEMPLATE_TRAN(Prefix, Pre, Post, Do)                   \
    CMX_META_TEMPLATE_IMPL (                                            \
        CMX_TOKEN (Prefix, p),                                          \
        CMX_TOKEN (Prefix, l_body),                                     \
        CMX_TOKEN (Prefix, l_else),                                     \
        CMX_TOKEN (Prefix, l_finish),                                   \
        Pre, Post, Do                                                   \
    )

#define CMX_META_TEMPLATE_IMPL(Prefix, Body, Else, Finish, Pre, Post, Do) \
    if (1) {                                                            \
        Pre (Prefix, Body, Else);                                       \
    Finish: CMX_LABEL_UNUSED;                                           \
        Post (Prefix, Body, Else);                                      \
    } else Do (Prefix, Body, Else, Finish)

#define CMX_META_TEMPLATE_BODY(Prefix, Body, Else, Finish)              \
    CMX_META_BODY_BREAK (Body, Finish)

#define CMX_META_TEMPLATE_BODY_ELSE(Prefix, Body, Else, Finish)         \
    CMX_META_BODY_ELSE_BREAK (Body, Finish)

#define CMX_META_TEMPLATE_DO(Prefix, Body, Else, Finish)                \
    CMX_META_DO_BREAK (Body)

#define CMX_META_TEMPLATE_DO_ELSE(Prefix, Body, Else, Finish)           \
    CMX_META_DO_ELSE_BREAK (Body, Else)

#define CMX_META_BODY_BREAK(Body, Finish)                               \
    while (1)                                                           \
        if (1)                                                          \
            goto Finish;                                                \
        else                                                            \
            while (0)                                                   \
            Body: CMX_LABEL_UNUSED
/**< Helper macro for meta-macros
 **
 ** Provides common structure for meta macros ending with BODY block/statement
 ** Allows and handles break.
 **
 ** @param Body   Label name to enter body
 ** @param Finish Label name where to return after body is executed
 **
 ** Usage:
 **    if (1) {
 **      ... init code ...
 **      goto Body;
 **    Finish:
 **      ... cleanup code ...
 **    } CMX_META_BODY_BREAK (Body, Finish)
 **/

#define CMX_META_BODY_ELSE_BREAK(Body, Else, Finish)                    \
    while (1)                                                           \
        if (1)                                                          \
            goto Finish;                                                \
        else                                                            \
            while (0)                                                   \
            Else: CMX_LABEL_UNUSED                                      \
                if (0)                                                  \
                Body: CMX_LABEL_UNUSED
/**< Helper macro for meta macros
 **
 ** Provides common structure for meta macros ending with BODY and ELSE clause
 ** Allows and handles break.
 **
 ** @param Body   Label name to enter body
 ** @param Else   Label name to enter else part
 ** @param Finish Label name where to return after body is executed
 **
 ** Usage:
 **   if (1) {
 **     ... init code ...
 **     if (Cond) goto Body; else goto Else;
 **   Finish:
 **     ... cleanup code ...
 **   } CMX_META_BODY_ELSE_BREAK (Body, Else, Finish)
 **/

#define CMX_META_DO_BREAK(Body)                                         \
    while (0)                                                           \
    Body: CMX_LABEL_UNUSED
/**< Helper macro for meta-macros
 **
 ** Provides common structure for meta macros ending with BODY
 ** Allows and handles break.
 **
 ** It's a version of CMX_META_BODY_BREAK without Finish
 **
 ** @param Body   Label name to enter body
 **
 ** Usage:
 **   if (1) {
 **     ...
 **     goto Body;
 **   } else CMX_META_DO_BREAK (Body)
 **/

#define CMX_META_DO_ELSE_BREAK(Body, Else)                              \
    while (0)                                                           \
    Else: CMX_LABEL_UNUSED                                              \
        if (0)                                                          \
        Body: CMX_LABEL_UNUSED
/**< Helper macro for meta macros
 **
 ** Provides common structure for meta macros ending with BODY else ELSE
 ** Allows and handles break.
 **
 ** @param Body   Label name to enter body
 ** @param Else   Label name to enter else part
 **
 ** Usage:
 **   if (1) {
 **     if (...) goto Body; else goto Else;
 **   } else CMX_META_DO_ELSE (Body, Else)
 **/

#endif  /* header guard */
