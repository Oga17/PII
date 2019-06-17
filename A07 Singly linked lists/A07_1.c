#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{         // Self referential structure
            char *data;          // Data which node holds
            struct node *next;      // Pointer to next node (used for linking the nodes) 
} NODE;


char compare_data(const char *data1, const char *data2)    // Optional (using function pointer)
{                                                          // Const parameters indicates that true values of arguments passed won't be changed
    return strcmp(data1, data2);
}

void add_node(NODE **phead, char *data)
{
    NODE *p, *q = (NODE *)malloc(sizeof(NODE));
    q->data = data;
    q->next = 0;
    if(*phead == 0) *phead = q;
    else
        {
            for(p = *phead; p->next; p = p->next);
            p->next = q;
        }
    }

int delete_node(NODE **phead, char *data)
{
    NODE *q, *p = *phead;
    while(p){
        if(strcmp(p->data, data) == 0)
        {
            if(p == *phead)
            {
                *phead = p->next;
                free(p->data);
                free(p);
                return 1;
            }
            else
            {
                for(q = *phead; q->next != p && q->next != 0; q = q->next);
                q->next = p->next;
                free(p->data);
                free(p);
                return 1;
            }
        }
        p = p->next;
    }
    return 0;
}

void delete_list(NODE **phead)
{
    NODE *p;
    while(*phead)
    {
        p = (*phead)->next;
        free((*phead)->data);
        free(*phead);
        (*phead) = p;
    }
}

void print_list(NODE **phead)
{
    NODE *p = *phead;
    printf(" List: ");
    while(p){
        printf("%s ", p->data);
        p = p->next;
    }
}


int main()
{
    NODE *head = 0;
    char *string, c;

    do{
        printf("\n ==================================================\n");
        printf(" Add/insert [D], delete [B], print [P], end [0]? "); scanf("\n%c", &c);

        if(c == 'D')
        {
            printf(" Data: ");
            string = (char *)malloc(18 * sizeof(char));
            scanf("%s", string);
            add_node(&head, string);
            printf(" Node successfully added!");
        }
        else if(c == 'B')
        {
            int r;
            printf(" Delete:\n  1)list\n  2)node\n R: ");
            scanf("\n%d", &r);
            if(r == 1)
            {
                delete_list(&head);
                printf(" List successfully deleted!");
            }
            else if(r == 2)
            {
                printf(" Data: ");
                string = (char *)malloc(18 * sizeof(char));
                scanf("%s", string);
                if(delete_node(&head, string)) printf(" Node successfully deleted!");
                else printf(" Node with data %s does not exist!", string);
            }
            else
                printf(" Non-existing mode of work!");
        }
        else if(c == 'P')
        {
            print_list(&head);
        }
        else if(c != '0') printf(" Non-existing mode of work - %c .", c);
    }while(c != '0');

    printf("\n END!\n\n");

    return 0;
}
