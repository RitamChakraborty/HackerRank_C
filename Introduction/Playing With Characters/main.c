#include <stdio.h>

int MAX_LEN = 1000;

int main(int argc, char const *argv[]) {
    char ch;
    char word[MAX_LEN];
    char sen[MAX_LEN];

    scanf("%c", &ch);
    scanf("%s", word);
    scanf("\n");
    scanf("%[^\n]%*c", sen);    

    printf("%c\n", ch);
    printf("%s\n", word);
    printf("%s\n", sen);

    return 0;
}
