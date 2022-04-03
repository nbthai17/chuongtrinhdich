#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct node
{
    char *s;
    int a[20];
    int size;
    struct node *next;
}node;
node *createNode(char *c, int i)
{
    node *new = malloc(sizeof(struct node));
    new -> next = NULL;
    new -> s = malloc(sizeof(strlen(c)));
    strcpy( new -> s, c);
    new -> a[0] = i;
    new -> size = 1;
    return new;
} 
void addAd(node *n, int i)
{
    n -> a[n -> size] = i;
    (n -> size) ++;
}
void sort(node **head, char * s, int line)
{
    if (*head == NULL)
    {
        *head = createNode( s, line);
    }
    else
    {   
        node *p = *head;
        if((strcmp( p->s, s) > 0))
        { 
            node *q = createNode( s, line);
            q -> next = p;
            *head = q;
        }
        else
        {    
            do{
                if(strcmp( p->s, s) == 0) 
                {
                    addAd(p, line);
                    return;
                }
                if( p -> next == NULL)break;
                if(strcmp( p->next->s, s) <= 0)p = p->next;
                else break;
            }while(1);
            node *q = createNode( s, line);
            q -> next = p -> next;
            p -> next = q;
        }
    } 
}
char ** readstopw(char *filename, int * size)
{
    FILE *f = fopen(filename,"r");
    if(f == NULL) printf("\nCannot read file %s",filename);
    char temp[20];
    char **str = (char **)calloc(20, sizeof(char *));
    int i = 0;
    for(; fscanf(f,"%s",temp) == 1; i++)
    {
        str[i] = (char *)calloc(15, sizeof(char));
        strcpy(str[i],temp);
    }
    *(size) = i;
    return str;
}

char * process(char * s, int *b)
{   
    int i;
    for(i = 0; i < strlen(s); i++)
    {
        if(isalpha(s[i]))break;
    }
    if ( i < strlen(s))
    {
        memmove(s, s + i, strlen(s) - i+1);
    }
    else 
    {
        return NULL;
    }
    if('A' <= s[0] && s[0] <= 'Z') // kiểm tra tên riêng và xử lý chữ hoa về chữ thường
    {
        if((*b) == 0) //b = 1 co dau cham, b = 0 ko co dau cham
        {
            if(s[strlen(s) - 1] == '.'|| s[strlen(s) - 1] == '?')
            {
                (*b) = 1;
            }
            return NULL;
        }
        else
        {
            s[0] = s[0] + 32;
        }   
    }
    if(!isalpha(s[strlen(s) - 1]))
    {
        if(s[strlen(s) - 1] == '.'|| s[strlen(s) - 1] == '?')
        {
            (*b) = 1;
        }
        do
        {
            s[strlen(s) - 1] = '\0';
        }while(!isalpha(s[strlen(s) - 1]));
    }
    else
    {
        (*b) = 0;
    }
    for(int i = 0; i < strlen(s); i++)
    {
        if(isupper(s[i]))
        {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}
void display(node *head){
    node *p = head;
    while(p != NULL)
    {
        printf("\n%s ",p->s);
        for(int i = 0; i < p -> size - 1; i++)
        {
            printf("%d,",p->a[i]);
        }
        printf("%d",p->a[p -> size - 1]);
        p = p->next;
    }
}
node * solve(char * filename,char ** str,int size)
{
    FILE *f = fopen(filename,"r");
    if( f == NULL) printf("\nCannot read file %s",filename);
    char *s;
    node *n = NULL;
    int t = 1;
    int b = 1;
    int c = 0;
    char temp[25];
    char *d;
    while(fscanf(f,"%s",temp) == 1)
    {
        char k = getc(f);
        if(k == ' ') 
        {
            k = getc(f);
            if(isalpha(k))
            {
                fseek( f, -1, SEEK_CUR );
            }
            if(k == '\n')t++;
        }
        else if(k == '\n')t++;
        d = malloc(sizeof(temp));
        strcpy(d,temp);
        d = process(d, &b);

        if(d == NULL)
        {
            continue;
        }
        for(int i = 0; i < size; i++)
        {
            if(strcmp(d,str[i]) == 0)
            {
                c = 1;
                break;
            }
        }
        if(c == 0)sort(&n,d,t);
        else c = 0;
    }
    return n;
}

int main()
{
    int size;
    char **str = readstopw("stopw.txt", &size);
    node *n = solve("vanban.txt",str,size);
    display(n);
    return 1;
}
