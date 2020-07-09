// https://www.hackerrank.com/challenges/sorting-array-of-strings/problem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return -strcmp(a, b);
}

int get_distinct_characters_number(const char *str) {
    int *arr = (int *) calloc(66, sizeof(int));
    int count = 0;

    for (int i = 0; i < strlen(str); ++i) {
        if (arr[str[i] % 65] == 0) {
            ++arr[str[i] % 65];
            ++count;
        }
    }

    return count;
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int a_count = get_distinct_characters_number(a);
    int b_count = get_distinct_characters_number(b);


    if (a_count == b_count) {
        return lexicographic_sort(a, b);
    } 

    return a_count - b_count;
}

int sort_by_length(const char* a, const char* b) {
    int a_len = strlen(a);
    int b_len = strlen(b);

    if (a_len == b_len) {
        return lexicographic_sort(a, b);
    } 

    return a_len - b_len;
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    for (int i = 0; i < len; ++i) {
        for (int j = (i + 1); j < len; ++j) {
            if ((*cmp_func)(arr[i], arr[j]) >= 0) {
                char *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}