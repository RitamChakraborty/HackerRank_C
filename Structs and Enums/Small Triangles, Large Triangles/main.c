#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct triangle {
    int a;
    int b;
    int c;
};

typedef struct triangle triangle;

float get_area(triangle tr) {
    int a = tr.a;
    int b = tr.b;
    int c = tr.c;

    float p = (a + b + c) / 2.0;
    float area_square = p * (p - a) * (p - b) * (p - c);

    return area_square;
}

void swap(triangle *tr1, triangle *tr2) {
    triangle *temp = (triangle *)malloc(sizeof(triangle));
    temp->a = tr1->a;
    temp->b = tr1->b;
    temp->c = tr1->c;

    tr1->a = tr2->a;
    tr1->b = tr2->b;
    tr1->c = tr2->c;

    tr2->a = temp->a;
    tr2->b = temp->b;
    tr2->c = temp->c;
}

void sort_by_area(triangle *tr, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            float area1 = get_area(tr[i]);
            float area2 = get_area(tr[j]);

            if (area2 < area1) {
                swap(&tr[i], &tr[j]);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    triangle *tr = malloc(n * sizeof(triangle));
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
    }
    sort_by_area(tr, n);
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
    }
    return 0;
}