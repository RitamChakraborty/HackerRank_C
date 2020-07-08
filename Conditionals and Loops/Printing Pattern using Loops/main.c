// https://www.hackerrank.com/challenges/printing-pattern-2/problem

#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            printf("%d ", (n - i));
        }

        for (int j = i; j < n; ++j) {
            printf("%d ", (n - j));
        }

        for (int j = 1; j < i; ++j) {
            printf("%d ", (n - i));
        }

        printf("\n");
    }

    return 0;
}
