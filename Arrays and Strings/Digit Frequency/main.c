// https://www.hackerrank.com/challenges/frequency-of-digits-1/problem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char string[1000];
    int *arr = (int *) calloc(10, sizeof(int));
    scanf("%[^\n]%*c", string);

    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] < 58) {
            int num = string[i] - 48;
            ++arr[num];
        }
    }

    for (int i = 0; i < 10; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}
