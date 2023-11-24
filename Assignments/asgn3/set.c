#include "set.h"

Set set_empty(void) {
    return 0;
}

Set set_universal(void) {
    return 0xff;
}

bool set_member(Set s, int x) {
    Set s1 = 1;
    s1 <<= x;
    s = s & s1;
    s >>= x;
    return s;
}

Set set_insert(Set s, int x) {
    Set s1 = 1;
    s1 <<= x;
    return s | s1;
}

Set set_remove(Set s, int x) {
    Set s1 = 1;
    s1 <<= x;
    s1 = ~s1;
    return s & s1;
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}

Set set_complement(Set s) {
    return ~s;
}
