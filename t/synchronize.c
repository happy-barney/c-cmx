
#include <stdio.h>

#define CMX_STRUCT_SHAREABLE_NAME shared
#define CMX_MUTEX_TYPE            int
#define CMX_MUTEX_INIT(Var)       (Var) = 0
#define CMX_MUTEX_LOCK(Var)     ++(Var)
#define CMX_MUTEX_UNLOCK(Var)   --(Var)
#define CMX_MUTEX_CREATE          0

#include <cmx/cmx.h>

int t_run_only_once (void) {
    static int counter = 0;

    CMX_RUN_ONCE {
        ++counter;
    };

    return 1 == counter;
}

int failed = 0;
const char * status (int status) {
    if (! status) failed ++;
    return status ? "ok" : "not ok";
}

int main (void) {
    printf ("1..2\n");
    printf ("%s - 1 - run_only_once 1st time\n", status (t_run_only_once ()));
    printf ("%s - 2 - run_only_once 2nd time\n", status (t_run_only_once ()));

    return failed;
}

