#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#define MAX_SYMBOLS_COUNT 26
#define MAX_STATES_COUNT 
struct dfa {
    int dfa[MAX_SYMBOLS_COUNT][MAX_STATES_COUNT];
    int finals[];
    int symbols[MAX_SYMBOLS_COUNT]
};
*/

bool isMatch(const char* string, const char* pattern) {
    
}


int ninputs;
int check(char,int ); //function declaration
int dfa[256][20];
char c[256], string[128];

int main(int argc, char ** argv)
{
    int nstates, nfinals;
    int f[128];
    int i,j,s=0,final=0;
    int state;
    char * pattern;
    int pattern_len;
    //bool star;
    /*
    printf("enter the number of states that your dfa consist of \n");
    scanf("%d",&nstates);
    printf("enter the number of input symbol that dfa have \n");
    scanf("%d",&ninputs);
    printf("\nenter input symbols\t");

    for(i=0; i<ninputs; i++)
    {
        printf("\n\n %d input\t", i+1);
        c[i] = getchar();
        printf("%c", c[i]);
    }

    printf("\n\nenter number of final states\t");
    scanf("%d",&nfinals);

    for(i=0;i<nfinals;i++)
    {
        printf("\n\nFinal state %d : q",i+1);
        scanf("%d",&f[i]);
    }

    printf("-----------------------------------------------------------------------");
    printf("\n\ndefine transition rule as (initial state, input symbol ) = final state\n");

    for(i=0; i<ninputs; i++)
    {
        for(j=0; j<nstates; j++)
        {
            printf("\n(q%d , %c ) = q",j,c[i]);
            scanf("%d",&dfa[i][j]);
        }
    }
    */
    //pattern = "a*t?b";
    //pattern = "a*?b";
    if (argc < 2) {
        printf("Give a pattern\n");
        exit(1);
    }
    pattern = argv[1];
    //pattern = "a?b";
    pattern_len = strlen(pattern);
    printf("pattern=%s\n", pattern);
    //pattern = "a*";
    //pattern = "*b";
    ninputs = 26;
    for(i = 0; i < ninputs; i++) {
      c[i] = i + 'a';
    }
    //count states
    for(i = 0, nstates = 1 ; i < pattern_len; i++) {
        if (pattern[i] == '*') {
            continue;
        }
        nstates++;
    }

    //fill trans table
    for(i = 0; i < nstates ; i++) {
        for(j = 0; j < ninputs; j++) {
            dfa[j][i] = -1;
        }
    }

    //star = false;
    for(i = 0, state = 0; i < pattern_len; i++) {
        if (pattern[i] == '*') {
            for (j = 0 ; j < ninputs ; j++) {
                dfa[c[j]][state] = state;
                dfa[c[j]][state + 1] = state;
            }
            if (i + 1 < pattern_len) {
                //if (pattern[i + 1] == '?') {}
                dfa[pattern[i + 1]][state] = state + 1;
                dfa[pattern[i + 1]][state + 1] = state + 1;
            }
            state++; /* take into account next letter */
            continue;
        } else if (pattern[i] == '?') {
            for(j = 0; j < ninputs; j++) {
                dfa[c[j]][state] = state + 1;
            }
            state++;
            continue;
        }
        //TODO check if pattern[i] letter is in c inputs chars array. 
        dfa[pattern[i]][state] = state + 1;
        state++;
    }
    nfinals = 1;
    f[0] = nstates - 1;

    /*
    nstates = 2;
    ninputs = 26;
    for(i = 0; i < ninputs; i++) {
        c[i] = i + 'a';
    }
    nfinals = 1;
    f[0] = 1;

    for(i = 0; i < ninputs; i++) {
        dfa[i][0] = 0;
        dfa[i][1] = 0;
    }
    dfa['b'][0] = 1;
    dfa['b'][1] = 1;
    */

    do
    {
        s = 0;
        final = 0;
        i = 0;
        printf("\n\nEnter Input String.. ");
        scanf("%s",string);

        while(string[i] != '\0')
        {
            printf("state:%d\n", s);
            if((s = check(string[i++], s)) < 0)
                break;
        }
        for(i=0 ; i < nfinals ; i++)
            if(f[i] == s)
                final = 1;
        if(final==1)
            printf("\n valid string");
        else
            printf("invalid string");
        getchar();

        printf("\nDo you want to continue.?  \n(y/n) ");
    }
    while(getchar()=='y');

    getchar();
}
int check(char b, int d)
{
    int j;
    for(j=0; j < ninputs; j++)
    {
        printf("%c - %c\n", b, c[j]);
        if(b == c[j])
        {
            printf("return state:%d\n", dfa[b][d]);
            return(dfa[b][d]);
        }
    }
    return -1;
}
