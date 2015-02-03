
/** @file
 **
 ** Define environment specific macros using glib (http://glib.org)
 ** Environment is controlled by true value of macro CMX_WITH_ENV_GLIB
 **/

#ifndef CMX_ENV_GLIB_H
#define CMX_ENV_GLIB_H 1

#ifdef CMX_WITH_ENV_GLIB

#include <cmx/cmx-env-glib-define.h>
#include <cmx/cmx-env-glib-bind.h>

#endif  /* env conditional */
#endif  /* header guard */
