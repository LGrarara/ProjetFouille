#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>

typedef struct Point
{
	char nom[100];
	float Courage;
	float Loyaute;
	float Sagesse;
	float Malice;
	char maison[100];
} Point;
typedef Point P_Point;

typedef struct Cluster
{
	int taille;
	int centre;
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

void parsenPoint(int initalnumber, P_Point init[], FILE *fp)
{

	int i;
	int j = 0;
	char line[150];

	fgets(line, 150, fp);

	while (fgets(line, 150, fp))
	{
		char *str = strdup(line);

		int init_size = strlen(str);

		char *ptr = strtok(str, ";");
		int i = 1;

		while (ptr != NULL)
		{
			if (i == 1)
				strcpy(init[j].nom, ptr);

			if (i == 2)
				init[j].Courage = atof(ptr);

			if (i == 3)
				init[j].Loyaute = atof(ptr);

			if (i == 4)
				init[j].Sagesse = atof(ptr);

			if (i == 5)
				init[j].Malice = atof(ptr);

			if (i == 6)
				init[j].Courage = atof(ptr);

			if (i == 1)
				strcpy(init[j].maison, ptr);

			ptr = strtok(NULL, ";");
			i++;
		}
		j++;
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
void numercluster(int K, int initialnumber, P_Cluster clustertab[K], P_Point init[50])
{
	srand(time(0));
	int i;
	for (i = 0; i < K; i++)
		clustertab[i].taille = 0;

	for (i = 0; i < K; i++)
	{
		clustertab[i].centre = rand() % initialnumber + 1;
		P_Point buffer = init[clustertab[i].centre];

		clustertab[i].C_Cluster[0] = buffer;

		// printf("%f\n", clustertab[0].C_Cluster[0].Loyaute);
	}
}

void initialiseDistance(float distance[50][50], P_Point points[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < i + 1; j++)
		{
			distance[i][j] = getDistance(points[i], points[j]);
			if (i == 0 && j == 8)
				printf("%f", distance[0][8]);
		}
	}
}
void creecluster(int intab[], P_Cluster clustertab[], int initialnumber, P_Point init[50], int K)
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
	// Prend le fichier en parametre et convertit en tableau de point
	parsenPoint(initialnumber, init, fp);
	int K = 4;
	int intab[K];
	float distance[50][50];
	// Tableau avecc toute les distance entre chaque point
	initialiseDistance(distance, init, 50);
	P_Cluster clustertab[K];

	printf("%f", distance[0][8]);
	// genere K valeur aleatoire;
	numercluster(K, initialnumber, clustertab, init);

	// printf("%f", clustertab[0].C_Cluster[0].Malice);
	// 	for (int i = 0; i < K; i++)

	// 		creecluster(intab, clustertab, initialnumber, init, K);
	return 0;
}
