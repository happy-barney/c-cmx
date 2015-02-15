
#ifndef CMX_TOKEN_H
#define CMX_TOKEN_H 1

#define CMX_TOKEN(A, B)                                                 \
    CMX_TOKEN_IMPL (A, B)
/**<@brief Concatenate parameters with underline
 **
 ** Macro expands parameters
 ** Usage:
 **   CMX_TOKEN (A, __LINE__) => A_123
 **/

#define CMX_TOKEN_IMPL(A, B)                                            \
    A ## _ ## B
/**< Implementation macro
 **/

#define CMX_TOKEN3(A, B, C)                                             \
    CMX_TOKEN3_IMPL (A, B, C)
/**<Produce token out of parameters concatenated with underline
 **
 ** Macro expands parameters
 **
 ** Usage:
 **   CMX_TOKEN (A, 1, 2) => A_1_2
 **/

#define CMX_TOKEN3_IMPL(A, B, C)                                        \
    A ## _ ## B ## _ ## C
/**< Implementation macro
 **/

#define CMX_TOKEN4(A, B, C, D)                                          \
    CMX_TOKEN4_IMPL (A, B, C, D)
/**<Produce token out of parameters concatenated with underline
 **
 ** Macro expands parameters
 **
 ** Usage:
 **   CMX_TOKEN (A, 1, 2, 4) => A_1_2_4
 **/

#define CMX_TOKEN4_IMPL(A, B, C, D)                                     \
    A ## _ ## B ## _ ## C ## _ ## D
/**< Transition macro to expand arguments
 **/

#define CMX_UNIQUE_TOKEN(Prefix)                                        \
    CMX_UNIQUE_TOKEN_TRAN (Prefix, __LINE__, __COUNTER__)
/**<Produce (as much as possible) unique token
 ** Appending current line and counter value to Prefix
 **/

#define CMX_UNIQUE_TOKEN_TRAN(A, B, C)                                  \
    CMX_UNIQUE_TOKEN_IMPL (A, B, C)
/**< Transition macro to expand arguments
 **/

#define CMX_UNIQUE_TOKEN_IMPL(A, B, C)                                  \
    A ## _ ## B ## _ ## C
/**< Implementation macro
 **/

#define CMX_STRINGIFY(X)                                                \
    CMX_STRINGIFY_IMPL (X)
/**<Produce string representation of parameter (after expansion)
 **/

#define CMX_STRINGIFY_IMPL(X)                                           \
    # X
/**<Implementation macro
 **/

#endif  /* guard */
