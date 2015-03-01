
#include <stdio.h>

#include <cmx/cmx-local.h>

int failed = 0;
const char * status (int status) {
    if (! status) failed ++;
    return status ? "ok" : "not ok";
}

int * ptr;
void check_ptr (int value, const char * text) {
    printf ("%s %s\n", status (*ptr == value), text);
}

int main (void) {
    int value = 0;
    ptr = &value;

    check_ptr (0, "1 - level 0 value");
    CMX_LOCAL (value) {
        value = 1;
        check_ptr (1, "2 - level 1 value changed");
        CMX_LOCAL (value) {
            value = 2;
            check_ptr (2, "3 - level 2 value changed");
        }
        check_ptr (1, "4 - level 1 value reverted");
    }
    check_ptr (0, "5 - level 0 value reverted");

    return failed;
}
