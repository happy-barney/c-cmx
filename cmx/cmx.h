
/** @file
 **
 ** C Meta Extensions
 **
 ** @search Naming convention
 **
 ** @subsection Implementation macro MACRO_IMPL
 **
 ** Additional macro is required to expand orig macro arguments.
 ** Such macros have a suffix _IMPL
 **
 ** @subsection Transient macro MACRO_TRAN
 **
 ** Macros using/generating additional (hidden) parameters for
 ** implementation macro have a suffix _TRAN
 **/

#ifndef CMX_H
#define CMX_H 1

#include <cmx/cmx-env.h>

#include <cmx/cmx-token.h>
#include <cmx/cmx-meta.h>
#include <cmx/cmx-local.h>
#include <cmx/cmx-synchronize.h>
#include <cmx/cmx-struct-refs.h>
#include <cmx/cmx-struct-shareable.h>

#endif
