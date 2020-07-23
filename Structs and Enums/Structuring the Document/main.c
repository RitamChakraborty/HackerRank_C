#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char *data;
};

struct sentence {
    struct word *data;
    int word_count;  // denotes number of words in a sentence
};

struct paragraph {
    struct sentence *data;
    int sentence_count;  // denotes number of sentences in a paragraph
};

struct document {
    struct paragraph *data;
    int paragraph_count;  // denotes number of paragraphs in a document
};

struct document get_document(char *text) {
    int letter_count = 0;
    struct word w;
    struct sentence s;
    s.word_count = 0;
    struct paragraph p;
    p.sentence_count = 0;
    struct document d;
    d.paragraph_count = 0;

    for (int i = 0;; ++i) {
        // Not a break
        if ((char)text[i] != ' ' && (char)text[i] != '.' &&
            (char)text[i] != '\n' && (int)text[i] != 0) {
            if (letter_count == 0) {
                w.data = (char *)calloc(2, sizeof(char));
            } else {
                w.data = (char *)realloc(w.data,
                                         (strlen(w.data) + 1) * sizeof(char));
            }

            w.data[letter_count] = (char)text[i];
            ++letter_count;
        }

        // Word break
        if ((char)text[i] == ' ' || (char)text[i] == '.' ||
            (char)text[i] == '\n' || (int)text[i] == 0) {
            if (letter_count != 0) {
                if (s.word_count == 0) {
                    s.data = (struct word *)malloc(sizeof(struct word));
                } else {
                    s.data = (struct word *)realloc(
                        s.data, (s.word_count + 1) * sizeof(struct word));
                }

                s.data[s.word_count].data =
                    (char *)calloc((strlen(w.data) + 1), sizeof(char));
                strcpy(s.data[s.word_count].data, w.data);
                ++s.word_count;

                letter_count = 0;
            }
        }

        // Sentence break
        if ((char)text[i] == '.') {
            if (p.sentence_count == 0) {
                p.data = (struct sentence *)malloc(sizeof(struct sentence));
            } else {
                p.data = (struct sentence *)realloc(
                    p.data, (p.sentence_count + 1) * sizeof(struct sentence));
            }

            // Allocate memory for words
            p.data[p.sentence_count].data =
                (struct word *)calloc(s.word_count, sizeof(struct word));
            p.data[p.sentence_count].word_count = s.word_count;

            for (int j = 0; j < s.word_count; ++j) {
                p.data[p.sentence_count].data[j].data =
                    (char *)calloc((strlen(s.data[j].data) + 1), sizeof(char));
                strcpy(p.data[p.sentence_count].data[j].data, s.data[j].data);
            }

            ++p.sentence_count;
            s.word_count = 0;
            free(s.data);
        }

        // Paragraph break;
        if ((char)text[i] == '\n' || (int)text[i] == 0) {
            if (d.paragraph_count == 0) {
                d.data = (struct paragraph *)malloc(sizeof(struct paragraph));
            } else {
                d.data = (struct paragraph *)realloc(
                    d.data, (d.paragraph_count + 1) * sizeof(struct paragraph));
            }

            d.data[d.paragraph_count].data = (struct sentence *)calloc(
                p.sentence_count, sizeof(struct sentence));
            d.data[d.paragraph_count].sentence_count = p.sentence_count;

            for (int j = 0; j < p.sentence_count; ++j) {
                d.data[d.paragraph_count].data[j].data = (struct word *)calloc(
                    p.data[j].word_count, sizeof(struct word));
                d.data[d.paragraph_count].data[j].word_count =
                    p.data[j].word_count;

                for (int k = 0; k < p.data[j].word_count; ++k) {
                    d.data[d.paragraph_count].data[j].data[k].data =
                        (char *)calloc((strlen(p.data[j].data[k].data) + 1),
                                       sizeof(char));
                    strcpy(d.data[d.paragraph_count].data[j].data[k].data,
                           p.data[j].data[k].data);
                }
            }

            ++d.paragraph_count;

            p.sentence_count = 0;
            free(p.data);

            // Document break
            if ((int)text[i] == 0) {
                break;
            }
        }
    }

    return d;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc,
                                                      int k, int m, int n) {
    return Doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k,
                                              int m) {
    return Doc.data[m - 1].data[k - 1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k - 1];
}

void print_word(struct word w) { printf("%s", w.data); }

void print_sentence(struct sentence sen) {
    for (int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for (int i = 0; i < para.sentence_count; i++) {
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for (int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1) printf("\n");
    }
}

char *get_input_text() {
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1) strcat(doc, "\n");
    }

    char *returnDoc = (char *)malloc((strlen(doc) + 1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() {
    char *text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3) {
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w =
                kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen = kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else {
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }
}