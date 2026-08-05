#include <stdio.h>
#include <string.h>
#include "../include/parser.h"

void parseLine(char line[])
{
    char *word;

    word = strtok(line," ");

    if(word==NULL)
        return;

    if(strcmp(word,"module")==0)
    {
        printf("Module Declaration Found\n");
    }

    else if(strcmp(word,"input")==0)
    {
        char *name;

        name=strtok(NULL," ");
        name=strtok(name,";");

        printf("Input Name : %s\n",name);
    }

    else if(strcmp(word,"output")==0)
    {
        char *name;

        name=strtok(NULL," ");
        name=strtok(name,";");

        printf("Output Name : %s\n",name);
    }

    else if(strcmp(word,"and")==0)
    {
        char *gateName;
        char *output;
        char *input1;
        char *input2;

        gateName=strtok(NULL,"(,);");
        output=strtok(NULL,"(,);");
        input1=strtok(NULL,"(,);");
        input2=strtok(NULL,"(,);");

        printf("\n");
        printf("Gate Type : AND\n");
        printf("Gate Name : %s\n",gateName);
        printf("Output    : %s\n",output);
        printf("Input1    : %s\n",input1);
        printf("Input2    : %s\n",input2);
    }

    else if(strcmp(word,"or")==0)
    {
        char *gateName;
        char *output;
        char *input1;
        char *input2;

        gateName=strtok(NULL,"(,);");
        output=strtok(NULL,"(,);");
        input1=strtok(NULL,"(,);");
        input2=strtok(NULL,"(,);");

        printf("\n");
        printf("Gate Type : OR\n");
        printf("Gate Name : %s\n",gateName);
        printf("Output    : %s\n",output);
        printf("Input1    : %s\n",input1);
        printf("Input2    : %s\n",input2);
    }

    else if(strcmp(word,"xor")==0)
    {
        char *gateName;
        char *output;
        char *input1;
        char *input2;

        gateName=strtok(NULL,"(,);");
        output=strtok(NULL,"(,);");
        input1=strtok(NULL,"(,);");
        input2=strtok(NULL,"(,);");

        printf("\n");
        printf("Gate Type : XOR\n");
        printf("Gate Name : %s\n",gateName);
        printf("Output    : %s\n",output);
        printf("Input1    : %s\n",input1);
        printf("Input2    : %s\n",input2);
    }

    else if(strcmp(word,"not")==0)
    {
        char *gateName;
        char *output;
        char *input1;

        gateName=strtok(NULL,"(,);");
        output=strtok(NULL,"(,);");
        input1=strtok(NULL,"(,);");

        printf("\n");
        printf("Gate Type : NOT\n");
        printf("Gate Name : %s\n",gateName);
        printf("Output    : %s\n",output);
        printf("Input1    : %s\n",input1);
    }

    else if(strcmp(word,"endmodule")==0)
    {
        printf("End of Module Found\n");
    }
}