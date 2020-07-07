#include <stdio.h>

int main(int argc, char const *argv[]) {
    int i1, i2;
    double d1, d2;

    scanf("%d%d", &i1, &i2);
    scanf("%lf%lf", &d1, &d2);

    int i3 = i1 + i2;
    int i4 = i1 - i2;
    double d3 = d1 + d2;
    double d4 = d1 - d2;

    printf("%d ", i3);
    printf("%d\n", i4);
    printf("%.1lf ", d3);
    printf("%.1lf", d4);

    return 0;
}
