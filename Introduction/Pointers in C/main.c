// https://www.hackerrank.com/challenges/pointer-in-c/problem

#include <stdio.h>
#include <stdlib.h>

void update(int *a,int *b) {
    int temp_a = *a + *b;
    int temp_b = abs(*a - *b);
    *a = temp_a;
    *b = temp_b;
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}