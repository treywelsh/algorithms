#include<stdio.h>

/*
#define SYMBOLS_COUNT 
#define STATES_COUNT 
struct dfa {
    int dfa[SYMBOLS_COUNT][STATES_COUNT];
    int finals[];
    int symbols[]
};
*/


int ninputs;
int check(char,int ); //function declaration
int dfa[256][10];
char c[256], string[128];

int main()
{
    int nstates, nfinals;
    int f[128];
    int i,j,s=0,final=0;
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
    //pattern = "a*b";
    //pattern = "a*";
    //pattern = "*b";
    //pattern_len = strlen(pattern);
    //ninputs = 26;
    //for(i = 0; i < ninputs; i++) {
    //  c[i] = i + 'a';
    //}
    //nstates = 1; //Initial state
    //for(i = 0; i < pattern_len; i++) {
    //  if (pattern[i] == '*') {
    //      dfa[nstates][pattern[i]] = nstates;
    //      star_flag = true;
    //      continue;
    //  } else if (pattern[i] == '?') {
    //      for(j = 0; j < ninputs; j++) {
    //          dfa[nstates][j] = nstates + 1;
    //      }
    //  }
    //  if (star_flag == true) {
    //      //for all other char than pattern i
    //      dfa[nstates][] = nstates - 1
    //  }
    //  dfa[nstates][pattern[i]] = nstates + 1;
    //  nstates++;
    //}
    //nfinals = 1
    //f[0] = nstates;

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
            printf("return state:%d\n", dfa[c[j]][d]);
            return(dfa[c[j]][d]);
        }
    }
    return -1;
}
