#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct node
{
    char *w;
    int *a;
    struct node *next;
}node;
node *createNode(char x[], int i)
{
    node *new = malloc(sizeof(struct node));
    new -> next = NULL;
    new -> w = malloc(sizeof(strlen(x)));
    strcpy( new -> w, x);
    new -> a[0] = i;
    return new;
} 

// void addAd(node *n, int i)
// {
//     int j = 0;
//     while(n -> a[j] != NULL)
//     {
//         j++;
//     }
//     n -> a[j] = i;
// }
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

char * process(char * s, int *b, int *t)
{   
    printf("\nbefore: %s %d",s,*b);
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
        if(s[strlen(s) -1] == '\n')
        {
            (*t) ++;
        }
        return NULL;
    }
    if('A' <= s[0] && s[0] <= 'Z') // kiểm tra tên riêng và xử lý chữ hoa về chữ thường
    {
        if((*b) == 0) //b = 1 co dau cham, b = 0 ko co dau cham
        {
            if(s[strlen(s) - 1] == '\n')
            {
                (*t) ++;
                if(s[strlen(s) - 2] == '.' ||s[strlen(s) - 2] == '?')
                {
                    (*b) = 1;
                }
            }
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
        if(s[strlen(s) - 1] == '\n')
        {
            (*t) ++;
            if(s[strlen(s) - 2] == '.' ||s[strlen(s) - 2] == '?')
            {
                (*b) = 1;
            }
        }
        if(s[strlen(s) - 1] == '.'|| s[strlen(s) - 1] == '?')
        {
            (*b) = 1;
        }
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
    
    printf("\n\n b: %d",*b);
    return s;
}

void solve(char * filename,char ** str,int size)
{
    FILE *f = fopen(filename,"r");
    if( f == NULL) printf("\nCannot read file %s",filename);
    char *s;
    node *n;
    int t = 1;
    int b = 1;
    int c = 0;
    char temp[25];
    char *d;
    while(fscanf(f,"%s",temp) == 1)
    {
                 
            d = malloc(sizeof(temp));
            strcpy(d,temp);

            d = process(d, &b, &t);

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

            if(c == 0) printf("\n%s",d);
            c = 0;
        
    }
}
void main()
{
    int size;
    char **str = readstopw("stopw.txt", &size);
    // solve("vanban.txt",str,size);
    char s[] = "adf.\n";
    int a = 0,b = 0;
    char *st = process(s,&a,&b);
    printf("\n%s %d %d",st,a,b);
    // printf("\n%s",d);
}
