
#include <stdio.h>

#define CMX_STRUCT_SHAREABLE_NAME shared
#define CMX_MUTEX_TYPE            int
#define CMX_MUTEX_INIT(Var)       (Var) = 0
#define CMX_MUTEX_LOCK(Var)     ++(Var)
#define CMX_MUTEX_UNLOCK(Var)   --(Var)

#include <cmx/cmx-struct-shareable.h>

int on_share = 0;

struct Dummy {
    CMX_STRUCT_SHAREABLE_DEFINE;
};

struct Dummy * struct_shareable_share (struct Dummy *ptr) {
    CMX_STRUCT_SHAREABLE_SHARE (ptr) {
        on_share ++;
    }
}

int failed = 0;
char * status (int status) {
    if (! status) ++failed;
    return status ? "ok" : "not ok";
}

#define UNINITIALIZED_MUTEX_VALUE                                       \
    -1

#define DUMMY_STRUCT(name)                                              \
    struct Dummy name = { .shared = { -1, UNINITIALIZED_MUTEX_VALUE } };

void check_struct_shareable_init (void) {
    DUMMY_STRUCT (data);

    CMX_STRUCT_SHAREABLE_INIT (&data);

    printf ("  1..2\n");
    printf ("  %s 1 - not enabled by default\n", status (data.shared.enabled == 0));
    printf ("  %s 2 - mutex left uninitialized\n", status (data.shared.mutex == UNINITIALIZED_MUTEX_VALUE));
}

void check_struct_shareable_shared (void) {
    DUMMY_STRUCT (data);

    CMX_STRUCT_SHAREABLE_INIT (&data);

    on_share = -1;

    printf ("  1..4\n");
    printf ("  %s 1 - share retval\n", status (&data == struct_shareable_share (&data)));
    printf ("  %s 2 - on share block called\n", status (on_share == 0));
    printf ("  %s 3 - repeated share retval\n", status (&data == struct_shareable_share (&data)));
    printf ("  %s 4 - repeated share on share block not called\n", status (on_share == 0));
}

void check_struct_shareable_is_not_shared (void) {
    DUMMY_STRUCT (data);
    int pass = 0;

    CMX_STRUCT_SHAREABLE_INIT (&data);

    printf ("  1..4\n");
    printf ("  %s 1 - is not shared\n", status (! data.shared.enabled));
    printf ("  %s 2 - \"mutex\" value not initialized\n", status (data.shared.mutex == UNINITIALIZED_MUTEX_VALUE));

    CMX_STRUCT_SHAREABLE_SYNCHRONIZE (&data) {
        pass = 1;
        printf ("  %s 3 - locked \"mutex\" value left intact\n", status (data.shared.mutex == UNINITIALIZED_MUTEX_VALUE));
    }

    if (! pass)
        printf ("  %s 3 - protected area called\n", status (0));

    printf ("  %s 4 - unlocked \"mutex\" value left intact\n", status (data.shared.mutex == UNINITIALIZED_MUTEX_VALUE));
}

void check_struct_shareable_is_shared (void) {
    DUMMY_STRUCT (data);
    int pass = 0;

    CMX_STRUCT_SHAREABLE_INIT (&data);

    printf ("  1..4\n");
    struct_shareable_share (&data);

    printf ("  %s 1 - is shared\n", status (data.shared.enabled));
    printf ("  %s 2 - \"mutex\" value initialized\n", status (data.shared.mutex == 0));

    CMX_STRUCT_SHAREABLE_SYNCHRONIZE (&data) {
        pass = 1;
        printf ("  %s 3 - locked \"mutex\" value\n", status (data.shared.mutex == 1));
    }

    if (! pass)
        printf ("  %s 3 - protected area called\n", status (0));

    printf ("  %s 4 - unlocked \"mutex\" value\n", status (data.shared.mutex == 0));
}

void subtest (int num, const char * name, void (*function) (void)) {
    int local = failed;

    failed = 0;
    function ();

    printf ("  # %s\n", name);
    printf ("%s %d - %s\n", status (failed == 0), num, name);

    if (failed) local ++;
    failed = local;
}

int main (void) {
    int retval = 0;
    struct Dummy data = { 0 };
    CMX_STRUCT_SHAREABLE_INIT (&data);

    printf ("1..4\n");

    subtest (1, "init macro", check_struct_shareable_init);
    subtest (2, "struct share ()", check_struct_shareable_shared);
    subtest (3, "is not shared workflow", check_struct_shareable_is_not_shared);
    subtest (4, "is shared workflow", check_struct_shareable_is_shared);

    return failed;
}
