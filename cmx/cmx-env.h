
/** @file
 **
 ** Defines environment macros to use their environment implementation
 **
 ** Environment type is defined via macro CMX_ENV
 **
 ** @section Environment macros
 ** (TODO detailed documentation)
 **
 ** CMX_MUTEX_TYPE
 ** CMX_MUTEX_STATIC_INIT
 ** CMX_MUTEX_LOCK (Var)
 ** CMX_MUTEX_UNLOCK (Var)
 **
 ** CMX_ATOMIC_TYPE
 ** CMX_ATOMIC_INCREMENT (Var)
 ** CMX_ATOMIC_DECREMENT_AND_TEST (Var)
 **
 ** CMX_LABEL_UNUSED
 **
 ** @section Best practice
 **
 ** Environment implementation will use their own prefix and bind
 ** environment macros with their prefixed implementation.
 **   #define CMX_ENV_XYZ_MUTEX_TYPE
 **   #ifndef CMX_MUTEX_TYPE
 **   #define CMX_MUTEX_TYPE CMX_ENV_XYZ_MUTEX_TYPE
 **   #endif
 **
 ** @subsection cmx-gen-bind.pl
 **
 ** This script will generate environment bind macros
 **
 ** Usage:
 **   In Makefile:
 **   cmx-env-xyz-bind.h:
 **           cmx-gen-bind.pl XYZ > $@
 **
 **   In cmx-env-xyz.h
 **   #define CMX_ENV_XYZ_...
 **   #define CMX_ENV_XYZ_...
 **   ...
 **   #include <cmx/cmx-env-xyz-bind.h>
 **/
