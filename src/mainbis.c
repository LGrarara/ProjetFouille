
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

typedef struct Cluster
{
    int taille;
    P_Point C_Cluster[];
} Cluster;
typedef Cluster P_Cluster;

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
        free(tmp);
        i++;
    }
}

void numercluster(int K, int initialnumber, int tab[])
{
    for (int i = 0; i < K; i++)
    {
        tab[i] = rand() % initialnumber + 1;
    }
}

void creecluster(int intab[], P_Cluster clustertab[], int initialnumber, P_Point init[], int K)
{
    for (int i = 0; i < K; i++)
    {
        clustertab[i].taille = 1;
        P_Point C_Cluster[initialnumber];
        C_Cluster[i] = init[intab[i]];
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
    int K = 4;
    int intab[K];
    numercluster(K, initialnumber, intab);
    P_Cluster clustertab[K];
    creecluster(intab, clustertab, initialnumber, init, K);
    fclose(fp);
}
