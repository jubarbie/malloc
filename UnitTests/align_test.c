#include <stdio.h> 
#include <stddef.h>

size_t  align_16(size_t nbr);

int    test_pointer_equal_16(void) {
    size_t ret;
    size_t exp;

    exp = 16;
    ret = align_16(16);
    return (ret == exp);
}

int    test_pointer_under_16(void) {
    size_t ret;
    size_t exp;

    exp = 16;
    ret = align_16(15);
    return (ret == exp);
}

int    test_pointer_over_16(void) {
    size_t ret;
    size_t exp;

    exp = 32;
    ret = align_16(17);
    return (ret == exp);
}

int    main(void) {
    int test;

    test = 1;
    if (!(test &= test_pointer_equal_16()))
        printf("Equal 16: Not valid\n");
    if (!(test &= test_pointer_under_16()))
        printf("Under 16: Not valid\n");
    if (!(test &= test_pointer_over_16()))
        printf("Over 16: Not valid\n");
    if (test)
        printf("All tests passed\n");
    return (0);
}
