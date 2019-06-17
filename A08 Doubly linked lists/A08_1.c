#include <stdio.h>
#include <stdlib.h>


typedef struct node{
            int data;                  //  Data which node holds
            struct node *prev, *next;    //  Pointers used for linking nodes
} NODE;


void add_node(NODE **phead, NODE **ptail, int data)
{
    NODE *p, *q = (NODE *)malloc(sizeof(NODE));    //  *q - new node, *p - pointer used for finding the last node in list
    q->data = data;
    q->prev = q->next = 0;
    if(*phead == 0)
        *phead = *ptail = q;
    else                                         
    {
        for(p = *phead; p->next; p = p->next);     //  In next line p is now pointing to last node in the list
        p->next = q;
        q->prev = p;
        *ptail = q;
    }
}

void insert_node(NODE **phead, NODE **ptail, int data, int position)  // Function for inserting a new node at desired position
{
    NODE *p, *q = (NODE *)malloc(sizeof(NODE));
    q->data = data;
    p = *phead;
    while(--position && p != NULL)
    {
        p = p->next;
    }
    if(p == NULL)
    {
        printf(" There aren't that many nodes!);
        return;
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

void print_list(NODE **phead)  
{
    NODE *p = *phead;
    printf("\n");
    while(p)
    {
        printf(" %d", p->data);
        p = p->next;
    }
}

void delete_list(NODE **phead, NODE **ptail)
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

    printf(" Number of data we want to store in nodes: "); scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf(" Data%d: ", i + 1); scanf("%d", &x);
        add_node(&head, &tail, x);
    }

    print_list(&head);

    printf("\n\n Insert behind node: ");
    scanf("%d", &n);
    printf(" Data: ");
    scanf("%d", &x);

    insert_node(&head, &tail, x, n);

    print_list(&head);

    printf("\n\n Second last node data: %d", tail->prev->data);   //  Performing a little check to see if list is linked properly
    printf("\n\n Last node data: %d", tail->data);

    delete_list(&head, &tail);

    printf("\n\n Content of list after deleting it: ");   //  Vrsimo provjeru da li funkcija deleteList uspjesno brise listu

    print_list(&head);

    return 0;
}
