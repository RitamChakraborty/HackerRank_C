// https://www.hackerrank.com/challenges/sum-of-digits-of-a-five-digit-number/problem

#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n, sum = 0;
    scanf("%d", &n);

    while (n) {
        sum += n % 10;
        n /= 10;
    }

    printf("%d", sum);

    return 0;
}
