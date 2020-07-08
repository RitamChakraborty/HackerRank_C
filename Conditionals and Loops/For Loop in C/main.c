# https://www.hackerrank.com/challenges/for-loop-in-c/problem

#include <stdio.h>

void print_word(int);

void check_even_odd(int);

int main(int argc, char const *argv[]) {
    int a, b;
    scanf("%d\n%d", &a, &b);

    for (int i = a; i <= b; ++i) {
        if (i <= 9) {
            print_word(i);
        } else {
            check_even_odd(i);
        }
    }

    return 0;
}

void print_word(int i) {
    switch (i)
    {
    case 0:
        printf("zero");
        break;
    case 1:
        printf("one");
        break;
    case 2:
        printf("two");
        break;
    case 3:
        printf("three");
        break;
    case 4:
        printf("four");
        break; 
    case 5:
        printf("five");
        break;
    case 6:
        printf("six");
        break;
    case 7:
        printf("seven");
        break;
    case 8:
        printf("eight");
        break;
    case 9:
        printf("nine");
        break;
    default:
        printf("Greater than 9");
        break;
    }
}

void check_even_odd(int i) {
    if (i % 2 == 0) {
        printf("even");
    } else {
        printf("odd");
    }
}
