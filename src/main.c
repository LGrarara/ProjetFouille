#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>

typedef struct Point
{
	float Courage;
	float Loyaute;
	float Sagesse;
	float Malice;
	int cluster;
} Point;
typedef Point P_Point;

typedef struct Cluster
{
	int taille;
	int centre;
} Cluster;
typedef Cluster P_Cluster;

float getDistance(Point a, Point b)
{
	float s = sqrt(pow(a.Courage - b.Courage, 2) + pow(a.Loyaute - b.Loyaute, 2) + pow(a.Sagesse - b.Sagesse, 2) +
				   pow(a.Malice - b.Malice, 2));
	return s;
}

void initialisePoints(P_Point points[], int n)
{
	int i;

	char *file_path = "choixpeauMagique.csv";
	FILE *fp = fopen(file_path, "r");

	if (!fp)
		printf("Can't open file\n");

	else
	{

		char buffer[1024];

		int row = 0;
		int column = 0;

		while (fgets(buffer,
					 1024, fp))
		{
			column = 0;
			row++;

			if (row == 1)
				continue;

			char *value = strtok(buffer, ";");

			while (value)
			{

				// Column 2
				if (column == 1)
				{

					points[row - 1].Courage = atof(value);
				}

				// Column 3
				if (column == 2)
				{

					points[row - 1].Loyaute = atof(value);
				}

				// Column 4
				if (column == 3)
				{

					points[row - 1].Sagesse = atof(value);
				}

				// Column 5
				if (column == 4)
				{
					points[row - 1].Malice = atof(value);
				}

				value = strtok(NULL, ";");
				column++;
			}
		}

		// Close the file
		fclose(fp);
	}
}

void initialiseDistance(float distance[50][50], P_Point points[], int n)
{

	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			distance[i][j] = getDistance(points[i], points[j]);
		}
	}
}

void initialisecluster(int k, int n, P_Cluster clusters[], P_Point points[])
{

	srand(time(0));
	int i;
	for (i = 0; i < k; i++)
		clusters[i].taille = 0;

	for (i = 0; i < k; i++)
	{
		clusters[i].centre = rand() % n + 1;
		points[clusters[i].centre].cluster = 0;
		clusters[i].taille++;
	}
}

void afficheCluster(P_Cluster clusters[], int k)
{
	for (int i = 0; i < k; i++)
	{
		printf("centre: %d\n", clusters[i].centre);
		printf("Taille: %d\n", clusters[i].taille);
		printf("suivant\n");
	}
}

int find_minimum(float a[], int k)
{
	int c, index = 0;

	float min;

	for (c = 1; c < k; c++)
		if (a[c] < min)
			index = c;

	return index;
}

void affecter_cluster_le_plus_proche(int k, int n, P_Cluster clusters[], P_Point points[])
{
	//objet i de 0 à n, chercher le cluster le plus proche de de n, i++
	int i, j, e;
	float tmp;
	float minimum = 900000000;

	float minimumtab[k];

	for (e = 0; e < n; e++)
	{
		for (i = 0; i < k; i++)
			minimumtab[i] = minimum;

		for (j = 0; j < k; j++)
		{
			tmp = getDistance(points[e], points[clusters[j].centre]);
			if (tmp < minimumtab[j])
				minimumtab[j] = tmp;
		}
		points[e].cluster = find_minimum(minimumtab, k);
		clusters[find_minimum(minimumtab, k)].taille++;
	}
}

void trouver_le_meilleur_centre(int k, int n, P_Cluster clusters[], P_Point points[])
{
}

void afficher_cluser_bis(P_Point points[], int n)
{

	for (int i = 0; i < n; i++)
	{

		if (points[i].cluster == 0)
		{
			printf("%f\n", points[i].Loyaute);
		}
	}
}
int main()
{
	int n = 50; //points
	int k = 6;	//groupes
	if (k > n)
		exit(0);

	float distance[n][n];
	P_Point points[n];
	P_Cluster clusters[k];
	initialisePoints(points, n);
	initialiseDistance(distance, points, n);
	initialisecluster(k, n, clusters, points);
	affecter_cluster_le_plus_proche(k, n, clusters, points);
	trouver_le_meilleur_centre(k, n, clusters, points);
}
