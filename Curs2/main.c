#include <stdio.h>

int main() {

    register int vreg;
    int d;

    d = 8;
    vreg = d;

    printf("vreg = %d",vreg);

    __asm
    {
        mov eax, vreg
    };
    return 0;
}
