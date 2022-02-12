#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int pow;
    struct Node *next;
} Node;

Node* createNode(int c, int p) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->coeff = c;
    node->pow = p;
    node->next = NULL;
    return node;
}

typedef struct Polynomial {
    Node *head;
} Polynomial;

Polynomial* createPolynomial() {
    Polynomial* list = (Polynomial*)malloc(sizeof(Polynomial));
    list->head = NULL;
    return list;
}

Polynomial* add(Polynomial* poly1, Polynomial* poly2) {
    Polynomial* poly = createPolynomial();
    
    Node* tail=NULL;
    Node* temp=NULL;
    Node* p1=poly1->head;
    Node* p2=poly2->head;

    while (p1 != NULL || p2 != NULL) {
        if (p1 == NULL || p1->pow < p2->pow) {
            temp = createNode(p2->coeff, p2->pow);
            p2 = p2->next;
        } else if (p2 == NULL || p1->pow > p2->pow) {
            temp = createNode(p1->coeff, p1->pow);
            p1 = p1->next;
        } else if (p1->pow == p2->pow) {
            temp = createNode(p1->coeff + p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }

        if(poly->head == NULL)
            poly->head = tail = temp;
        else {
            tail->next = temp;
            tail=tail->next;
        }
    }
    return poly;
}

Polynomial* create(int coeffs[], int pows[], int size) {
    Polynomial* poly = createPolynomial();
    Node *tail=NULL, *temp=NULL;
    for (int i=0; i < size; i++) {
        temp = createNode(coeffs[i], pows[i]);
        if(poly->head == NULL)
            poly->head = tail = temp;
        else {
            tail->next = temp;
            tail=tail->next;
        }
    }
    return poly;
}

void print(Polynomial* poly) {
    Node* head = poly->head;
    while (head != NULL) {
        printf("%d", head->coeff);
        if(head->pow != 0)
            printf("x^%d", head->pow);
        
        if (head->next != NULL)
            printf(" + ");
        head = head->next;
    }
}
    
int main() {
    int c1[] = { 6, 5, 4 };
    int p1[] = { 2, 1, 0 };
    int s1 = 3;
    Polynomial* first = create(c1, p1, s1);
    
    int c2[] = { 3, 2, 1 };
    int p2[] = { 3, 1, 0 };
    int s2 = 3;
    Polynomial* second = create(c2, p2, s2);
    
    Polynomial* sum = add(first, second);
    print(sum);
    return 0;
}

/*
3x^3 + 6x^2 + 7x^1 + 5
*/