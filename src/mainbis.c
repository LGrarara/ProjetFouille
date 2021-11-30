
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Point
{
    float Courage;
    float Loyaute;
    float Sagesse;
    float Malice;
} Point;
typedef Point P_Point;

const char *getfield(char *line, int num)
{
    const char *tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int initialnumberobject(FILE *fp)
{
    int ch = 0;
    int lines = 0;

    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            lines++;
        }
    }
    rewind(fp);
    return lines - 1;
}
void parsenPoint(int initalnumber, P_Point init[], FILE *fp)
{

    int i = 0;
    char line[150];

    fgets(line, 150, fp);

    while (fgets(line, 150, fp))
    {
        char *tmp = strdup(line);
        // strcpy(init[i].nom, getfield(tmp, 1));
        init[i].Courage = atof(getfield(tmp, 2));
        init[i].Loyaute = atof(getfield(tmp, 3));
        init[i].Sagesse = atof(getfield(tmp, 4));
        init[i].Malice = atof(getfield(tmp, 5));
        // strcpy(init[i].maison, getfield(tmp, 6));
        // NOTE strtok clobbers tmp
        free(tmp);
        i++;
    }
}
int main()

{
    FILE *fp = fopen("choixpeauMagique.csv", "r");
    if (fp == NULL)
    {
        printf("Erreur de lecture");
        exit(EXIT_FAILURE);
    }

    int initialnumber = initialnumberobject(fp);
    P_Point init[initialnumber];
    rewind(fp);
    parsenPoint(initialnumber, init, fp);
    printf("%f", init[0].Courage);
    fclose(fp);
}
