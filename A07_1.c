#include <stdio.h>
#include <stdlib.h>


typedef struct node{
            int data;                  // Podatak koji sadrzi cvor
            struct node *prev, *next;  // Pokazivaci jednog cvora na njegovog prethodnika i sljedbenika
} NODE;


void addNode(NODE **phead, NODE **ptail, int data)
{
    NODE *p, *q = (NODE *)malloc(sizeof(NODE));    // *p - Pomocni pokazivac; *q - Novi cvor koji dodajemo
    q->data = data;
    q->next = 0;
    if(*phead == 0)
        *phead = *ptail = q;
    else
    {
        for(p = *phead; p->next; p = p->next);
        p->next = q;
        q->prev = p;
        *ptail = q;
    }
}

void insertNode(NODE **phead, NODE **ptail, int data, int position)  // Ubacivanje novog cvora iza unesene pozicije
{
    NODE *p, *q = (NODE *)malloc(sizeof(NODE));
    q->data = data;
    int i = 1;
    p = *phead;
    while(i < position && p != NULL)
    {
        p = p->next;
        i++;
    }
    if(p->next == 0)
    {
        p->next = q;
        q->prev = p;
        q->next = 0;
        *ptail = q;
    }
    else
    {
        p->next->prev = q;
        q->next = p->next;
        p->next = q;
        q->prev = p;
    }
}

void printList(NODE **phead)  // Printanje sadrzaja liste
{
    NODE *p = *phead;
    printf("\n");
    while(p)
    {
        printf(" %d", p->data);
        p = p->next;
    }
}

void deleteList(NODE **phead, NODE **ptail)
{
    while(*phead)
    {
        NODE *p = (*phead)->next;
        free(*phead);
        *phead = p;
    }
}

int main()
{
    NODE *head = 0, *tail = 0;
    int x, n;

    printf(" Koliko podataka zelimo da unesemo: ");
    scanf("%d", &n);
    printf("\n Unosimo podatke... \n\n");

    for(int i = 0; i < n; i++)
    {
        printf(" Node %d: ", i + 1);
        scanf("%d", &x);
        addNode(&head, &tail, x);
    }

    printList(&head);

    printf("\n\n Insert behind node: ");
    scanf("%d", &n);
    printf(" Data: ");
    scanf("%d", &x);

    insertNode(&head, &tail, x, n);

    printList(&head);

    printf("\n\n Second last data: %d", tail->prev->data);  // Mala provjera
    printf("\n\n Last last data: %d", tail->data);

    deleteList(&head, &tail);

    printf("\n\n Content of list after deleting it: ");  // Vrsimo provjeru da li funkcija deleteList uspjesno brise listu

    printList(&head);

    return 0;
}
