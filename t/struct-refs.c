
#include <stdio.h>

#define CMX_ATOMIC_INT_TYPE                                             \
    int

#define CMX_ATOMIC_INT_SET(Var, Value)                                  \
    (Var) = (Value)

#define CMX_ATOMIC_INT_INCREMENT(Var)                                   \
    ++(Var)

#define CMX_ATOMIC_INT_DECREMENT_AND_TEST(Var)                          \
    (--(Var) == 0)

#include <cmx/cmx-struct-refs.h>

int on_ref           = 0;
int on_unref_prevent = 0;
int on_unref_destroy = 0;

struct Dummy {
    CMX_STRUCT_REFS_DEFINE;
};

struct Dummy * dummy_ref (struct Dummy *ptr) {
    CMX_STRUCT_REFS_REF (ptr)
        ++on_ref;
}

void dummy_unref (struct Dummy *ptr) {
    CMX_STRUCT_REFS_UNREF (ptr)
        ++on_unref_destroy;
    else
        ++on_unref_prevent;
}

int failed = 0;
char * status (int status) {
    if (! status) ++failed;
    return status ? "ok" : "not ok";
}

int main (void) {
    struct Dummy *ptr;
    struct Dummy data = { .CMX_STRUCT_REFS_NAME = -1 };

    printf ("# cmx-struct-refs workflow (using custom, \"mocked\", atomic macros)\n");
    printf ("1..11\n");
    printf ("%s 1 - static init\n", status (data.CMX_STRUCT_REFS_NAME == -1));

    CMX_STRUCT_REFS_INIT (&(data));
    printf ("%s 2 - refcount after init\n", status (data.CMX_STRUCT_REFS_NAME == 1));

    on_ref = on_unref_prevent = on_unref_destroy = 0;
    ptr = dummy_ref (&data);
    printf ("%s 3 - ref block called (once)\n", status (on_ref == 1));
    printf ("%s 4 - refcount after ref\n", status (data.CMX_STRUCT_REFS_NAME == 2));
    printf ("%s 5 - ref return value\n", status (ptr == &data));

    on_ref = on_unref_prevent = on_unref_destroy = 0;
    dummy_unref (&data);
    printf ("%s 6 - unref 'still live' block called\n", status (on_unref_prevent == 1));
    printf ("%s 7 - unref 'destroy' block not called\n", status (on_unref_destroy == 0));
    printf ("%s 8 - refcount after first unref\n", status (data.CMX_STRUCT_REFS_NAME == 1));

    on_ref = on_unref_prevent = on_unref_destroy = 0;
    dummy_unref (&data);
    printf ("%s 9 - unref 'still live' block not called\n", status (on_unref_prevent == 0));
    printf ("%s 10 - unref 'destroy' block called\n", status (on_unref_destroy == 1));
    printf ("%s 11 - refcount after second unref\n", status (data.CMX_STRUCT_REFS_NAME == 0));

    return failed;
}
