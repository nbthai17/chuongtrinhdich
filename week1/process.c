#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
    if(isupper(s[0])) // kiểm tra tên riêng và xử lý chữ hoa về chữ thường
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
            s[0] = tolower(s[0]);
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
        if(!isalpha(s[i]))
        {
            char *c = malloc(sizeof(char)*i);
            strcpyn(c,s,i);
            
        }
        if(isupper(s[i]))
        {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}
int main()
{
    char s[50];
    char *str;
    int b = 1;
    FILE * f = fopen("alice30.txt","r");
    while(fscanf(f,"%s",s) == 1)
    {
        printf("\nbefore: %s",s);
        str = process(s,&b);
        printf("\n%s",str);
    }
    return 1;
}