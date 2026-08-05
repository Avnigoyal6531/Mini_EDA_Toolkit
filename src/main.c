#include <stdio.h>
#include "../include/parser.h"

int main()
{
    FILE *fp;
    char line[200];

    fp = fopen("input/AND_GATE.v","r");

    if(fp==NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    while(fgets(line,200,fp)!=NULL)
    {
        parseLine(line);
    }

    fclose(fp);

    return 0;
}