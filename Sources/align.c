#include <stddef.h>

size_t  align_16(size_t nbr) {
    return (((nbr - 1) | 15) + 1);
}
