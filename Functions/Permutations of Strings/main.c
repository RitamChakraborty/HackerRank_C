#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **s, int i, int j) {
    char *temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void reverse(int i, int n, char **s) {
    int j = n - 1;

    while (i < j) {
        char *temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        ++i;
        --j;
    }
}

int next_permutation(int n, char **s) {
    int i = n - 1;

    while (strcmp(s[i - 1], s[i]) >= 0) {
        if (--i == 0) {
            return 0;
        }
    }

    int j = n - 1;

    while (j > i && strcmp(s[j], s[i - 1]) <= 0) {
        j--;
    }

    swap(s, i - 1, j);
    reverse(i, n, s);

    return 1;
}

int main() {
    char *s[] = {"a", "bc", "bc"};
    int n = 3;
    // char **s;
    // int n;
    // scanf("%d", &n);
    // s = calloc(n, sizeof(char *));
    // for (int i = 0; i < n; i++) {
    //     s[i] = calloc(11, sizeof(char));
    //     scanf("%s", s[i]);
    // }

    do {
        for (int i = 0; i < n; i++)
            printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
    } while (next_permutation(n, s));
    // for (int i = 0; i < n; i++) free(s[i]);
    // free(s);
    return 0;
}