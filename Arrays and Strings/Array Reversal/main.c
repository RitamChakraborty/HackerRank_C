// https://www.hackerrank.com/challenges/reverse-array-c/problem

#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    
    int arr[n];
    int arr_reversed[n];

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; ++i) {
        arr_reversed[n - (i + 1)] = arr[i];
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr_reversed[i]);
    }

    return 0;
}

