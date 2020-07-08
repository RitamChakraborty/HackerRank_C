// https://www.hackerrank.com/challenges/sum-of-digits-of-a-five-digit-number/problem

#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n, k, maxAND = 0, maxOR = 0, maxXOR = 0;
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; ++i) {
        for (int j = (i + 1); j <= n; ++j) {
            int and = j & i;
            int or = j | i;
            int xor = j ^ i;

            if (and < k) {
                maxAND = and > maxAND ? and : maxAND;
            } if (or < k) {
                maxOR = or > maxOR ? or : maxOR;
            } if (xor < k) {
                maxXOR = xor > maxXOR ? xor : maxXOR;
            }
        }
    }

    printf("%d\n%d\n%d", maxAND, maxOR, maxXOR);

    return 0;
}
