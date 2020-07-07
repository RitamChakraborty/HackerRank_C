#include <stdio.h>

int main(int argc, char const *argv[]) {
    char s[100];
    scanf("%[^\n]%*c", &s);

    printf("Hello, World!\n");
    printf("%\ns", s);

    return 0;
}
