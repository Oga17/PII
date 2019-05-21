#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
            void *data;
            struct node *prev, *next;
} NODE;


int compare(const void *a, const void *b)    // Funkcija za poredjenje dva podatka tipa int
{
    return *(int *)a - *(int *)b;
}

void write_one(const void *Int)      // Funkcija za ispis int podataka
{
    printf(" %d", *(int *)Int);
}

NODE* search(NODE *phead, NODE *tail, const void *data, int (*cmp)(const void *, const void *))
{
    while(phead)
    {
        if((*cmp)(phead->data, data) == 0)
            return phead;
        phead = phead->next;
    }
    return NULL;
}

void sortedAdd(NODE **phead, NODE **ptail, void *data, int (*cmp)(const void *, const void *))
{
    if(search(*phead, *ptail, data, cmp) != NULL)
        return;
    NODE *p, *q, *New = (NODE *)malloc(sizeof(NODE));
    New->data = data;
    New->next = 0, New->prev = 0;
    if(*phead == NULL)
        *phead = *ptail = New;
    else if(((*cmp)(New->data, (*phead)->data)) < 0)
    {
        New->next = *phead;
        (*phead)->prev = New;
        *phead = New;
    }
    else if((*cmp)(New->data, (*ptail)->data) > 0)
    {
        New->prev = *ptail;
        (*ptail)->next = New;
        *ptail = New;
    }
    else
    {
        for(p = *phead, q = (*ptail)->prev; ((*cmp)(New->data, p->next->data)) > 0 && ((*cmp)(New->data, q->data) < 0); p = p->next, q = q->prev);
        if((*cmp)(New->data, q->data) > 0)
            p = q;
        New->next = p->next;
        New->prev = p;
        p->next->prev = New;
        p->next = New;
    }

}

void deleteNode(NODE **phead, NODE **ptail, const void *data, int (*cmp)(const void *, const void *))
{
    NODE *p = search(*phead, *ptail, data, cmp);    // *p dodjeljujemo adresu cvora kojoj podatak koji trazimo pripada
    if(p == NULL)
        return;
    else if(p == *phead && p == *ptail)
        *phead = *ptail = 0;
    else if(p == *phead)
    {
        *phead = (*phead)->next;
        (*phead)->prev = 0;
    }
    else if(p == *ptail)
    {
        *ptail = (*ptail)->prev;
        (*ptail)->next = 0;
    }
    else
    {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    free(p);
}

void printList(NODE *phead, void (*write_one)(const void *))
{
    NODE *p = phead;
    printf("\n Lista: ");
    while(p)
    {
        write_one(p->data);
        p = p->next;
    }
}

int main()
{
    NODE *head = 0, *tail = 0;
    int *p;
    char c;

    do{
            printf("\n ========================================================================");
            printf("\n Dodavanje/Azur. [D], brisanje [B], pretr [T], prikaz[P], kraj [0]? C = "); scanf("\n%c", &c);

            if(c == 'D')
            {
                    printf("\n Data: ");
                    p = malloc(sizeof(int));
                    scanf("%d", p);
                    sortedAdd(&head, &tail, p, compare);
            }
            else if(c == 'B')
            {
                    printf("\n Data: ");
                    p = malloc(sizeof(int));
                    scanf("%d", p);
                    deleteNode(&head, &tail, p, compare);
            }
            else if(c == 'P')
            {
                    printList(head, write_one);
            }
            else if(c == 'T')
            {
                    printf("\n Data: ");
                    p = malloc(sizeof(int));
                    scanf("%d", p);
                    NODE *q = search(head, tail, p, compare);
                    if(q != NULL) printf("\n Pretraga uspjesna!");
                    else printf("\n Pretraga neuspjesna!");
            }
            else if(c != '0') printf(" \n Nepoznata opcija %c .", c);

    }while(c != '0');

    return 0;
}
