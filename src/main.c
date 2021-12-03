
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

typedef struct Point
{
	// char nom[100];
	float Courage;
	float Loyaute;
	float Sagesse;
	float Malice;
	// char maison[100];
} Point;
typedef Point P_Point;

typedef struct Cluster
{
	int taille;
	P_Point C_Cluster[];
} Cluster;
typedef Cluster P_Cluster;

float getDistance(Point a, Point b)
{
	float s = sqrt(pow(a.Courage - b.Courage, 2) + pow(a.Loyaute - b.Loyaute, 2) + pow(a.Sagesse - b.Sagesse, 2) +
				   pow(a.Malice - b.Malice, 2));
	return s;
}

int minimum(int i, int j)
{
	int m = (i < j) ? i : j;
	return m;
}

//retourne le max de 2 valeur
int maximum(int i, int j)
{
	int m = (i > j) ? i : j;
	return m;
}

const char *getfield(char *str, int num, char buffer[40])
{

	int init_size = strlen(str);
	char delim[] = ";";

	char *ptr = strtok(str, delim);
	int i = 1;
	while (ptr != NULL)
	{

		ptr = strtok(NULL, delim);
		if (i == 5)
		{
			i++;
		}

		if (i == num)
		{
			strcpy(buffer, ptr);
			break;
		}
		i++;
	}
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
		char buffer[40];
		getfield(tmp, 1, buffer);
		printf("%s\n", buffer);
		getfield(tmp, 2, buffer);
		printf("%s\n", buffer);
		getfield(tmp, 3, buffer);
		printf("%s\n", buffer);
		getfield(tmp, 4, buffer);
		printf("%s\n", buffer);
		getfield(tmp, 5, buffer);
		printf("%s\n", buffer);
		getfield(tmp, 6, buffer);
		printf("%s\n", buffer);
		printf("Next\n");

		// init[i].Courage = atof(getfield(tmp, 2));
		// init[i].Loyaute = atof(getfield(tmp, 3));
		// init[i].Sagesse = atof(getfield(tmp, 4));
		// init[i].Malice = atof(getfield(tmp, 5));
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

void addnearestpointtocluster(P_Cluster clustertab[])
{
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
	printf("%f", clustertab[0].C_Cluster[0].Courage);
	fclose(fp);
}
