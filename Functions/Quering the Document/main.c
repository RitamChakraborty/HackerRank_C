#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m,
                                                int n) {
    return document[n - 1][m - 1][k - 1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) {
    return document[m - 1][k - 1];
}

char*** kth_paragraph(char**** document, int k) { return document[k - 1]; }

char**** get_document(char* text) {
    char**** document;
    char*** paragraph;
    char** sentence;
    char* word;

    int document_index = 0;
    int paragraph_index = 0;
    int sentence_index = 0;
    int word_index = 0;
    int *sentence_size_arr;
    int sentence_size_arr_index = 0;

    for (int i = 0;; ++i) {
        // If letter is neither space, nor full stop nor new line, nor end of
        // input Then add letter in word
        if ((char)text[i] != ' ' && (char)text[i] != '.' &&
            (char)text[i] != '\n' && (int)text[i] != 0) {
            if (word_index == 0) {
                word = (char*)calloc(2, sizeof(char));
            } else {
                word = (char*)realloc(word, (word_index + 2) * sizeof(char));
            }

            word[word_index++] = (char) text[i];
        }

        // If letter is space
        // Then add word into sentence
        // Reset word
        if ((char)text[i] == ' ' || (char)text[i] == '.' ||
            (char)text[i] == '\n' || (int)text[i] == 0) {
            if (word_index != 0) {
                if (sentence_index == 0) {
                    sentence = (char**)malloc(sizeof(char*));
                } else {
                    sentence = (char**)realloc(
                        sentence, (sentence_index + 1) * sizeof(char*));
                }

                sentence[sentence_index] =
                    (char*)calloc(strlen(word), sizeof(char));
                strcpy(sentence[sentence_index], word);
                ++sentence_index;

                word_index = 0;
                free(word);
            }
        }

        // If letter is full stop
        // Then add sentence into paragraph
        // Reset setence
        if ((char)text[i] == '.') {
            if (paragraph_index == 0) {
                paragraph = (char***)malloc(sizeof(char**));
            } else {
                paragraph = (char***)realloc(
                    paragraph, (paragraph_index + 1) * sizeof(char**));
            }

            paragraph[paragraph_index] = (char **) calloc(sentence_index, sizeof(char *));

            for (int j = 0; j < sentence_index; ++j) {
                paragraph[paragraph_index][j] = (char *) calloc(strlen(sentence[j]), sizeof(char));
                strcpy(paragraph[paragraph_index][j], sentence[j]);
            }

            ++paragraph_index;

            // Append the size of the sentence in the sentence_index_arr
            if (sentence_size_arr_index == 0) {
                sentence_size_arr = (int *) malloc(sizeof(int));
            } else {
                sentence_size_arr = (int *) realloc(sentence_size_arr, (sentence_size_arr_index + 1) * sizeof(int));
            }

            sentence_size_arr[sentence_size_arr_index++] = sentence_index; 

            sentence_index = 0;
            free(sentence);
        }

        // If letter is new line or end of the input
        // Then add paragraph into document
        // Reset paragraph
        if ((char)text[i] == '\n' || (int)text[i] == 0) {
            if (document_index == 0) {
                document = (char****)malloc(sizeof(char***));
            } else {
                document = (char****)realloc(
                    document, (document_index + 1) * sizeof(char***));
            }

            document[document_index] = (char ***) calloc(paragraph_index, sizeof(char **));

            for (int j = 0; j < paragraph_index; ++j) {
                char **para = paragraph[j];
                int sentence_size = sentence_size_arr[j];

                document[document_index][j] = (char **) calloc(sentence_size, sizeof(char *));
                
                for (int k = 0; k < sentence_size; ++k) {
                    int word_size = strlen(para[k]);
                    document[document_index][j][k] = (char *) calloc(word_size, sizeof(char));
                    strcpy(document[document_index][j][k], para[k]);
                }
            }

            ++document_index;
            
            sentence_size_arr_index = 0;
            free(sentence_size_arr);
            
            paragraph_index = 0;
            free(paragraph);

            // Break the loop if end of input
            if ((int)text[i] == 0) {
                break;
            }
        }
    }

    return document;
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}