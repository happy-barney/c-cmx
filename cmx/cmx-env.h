
/**
 ** @file
 **
 ** Defines environment macros to use their environment implementation
 **
 ** @section Environment macros
 **
 ** Environment macros specify data types and functions used by other
 ** macros.
 **
 ** @subsection Mutexes
 **
 ** - CMX_MUTEX_TYPE
 **   Mutex data type
 **
 ** - CMX_MUTEX_INIT (Var)
 **   Expression to initialize mutex variable.
 **   Macro must expand as expression of CMX_MUTEX_TYPE type.
 **   Macro may define its own temporary variables suffixing Var parameter.
 **   Macro may expand into multistatement code.
 **
 **   Macro usage:
 **     CMX_MUTEX_INIT (Expr)
 **
 ** - CMX_MUTEX_LOCK (Var)
 **   Lock mutex.
 **   Var is a CMX_ATOMIC_TYPE variable.
 **
 ** - CMX_MUTEX_UNLOCK (Var)
 **   Unlock mutex.
 **   Var is a CMX_ATOMIC_TYPE variable.
 **
 ** @subsection Atomic operations
 **
 ** - CMX_ATOMIC_INT_TYPE
 **   Atomic data type
 **
 ** - CMX_ATOMIC_INT_SET (Var, Value)
 **   Set atomically Value to Var.
 **   Var is a CMX_ATOMIC_INT_TYPE variable.
 **
 ** - CMX_ATOMIC_INT_INCREMENT (Var)
 **   Increment Var value.
 **   Var is a CMX_ATOMIC_INT_TYPE variable.
 **
 ** - CMX_ATOMIC_INT_DECREMENT_AND_TEST (Var)
 **   Assign Value to Var. Var is a CMX_ATOMIC_INT_TYPE variable.
 **
 ** @subsection Misc macros
 **
 ** Macros to use advantages of compiler extensions
 ** All those macros have default implementantion
 **
 ** - CMX_LABEL_UNUSED
 **   Macros may declare labels which will not be used. Compilers
 **   may consider it as warning and provide feature(s) to avoid
 **   it when label is generated by macro.
 **
 ** - CMX_LOCAL_STORE (Name, Var)
 **   create variable Name and initialize it with value of Var expression
 **   Example: (using gcc)
 **     typeof (Var) Name = Var
 **
 ** - CMX_LOCAL_RESTORE (Name, Var)
 **   Assign value of Name variable into Var expression
 **   Example: (using gcc)
 **     Var = Name
 **/

#ifndef CMX_ENV_H
#define CMX_ENV_H 1

/* library specific env */
#include <cmx/cmx-env-glib.h>
#include <cmx/cmx-env-posix.h>

/* compiler specific env */
#include <cmx/cmx-env-gcc.h>

/* default implementation */
#include <cmx/cmx-env-default.h>

#endif  /* header guard */

