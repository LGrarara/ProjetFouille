#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <string.h>

//definition structure pour le groupe
typedef struct Cluster
{
	int medoid;
	int taille;
} Cluster;
typedef Cluster *P_Cluster;

//definition structure point
typedef struct Point
{
	float Courage;
	float Loyaute;
	float Sagesse;
	float Malice;
	P_Cluster cluster;
} Point;
typedef Point *P_Point;

//definition structure couleur
typedef struct Color
{
	int r;
	int g;
	int b;
} Color;

//prototypes des fonctions
int minimun(int, int);
int maximum(int, int);
float getDistance(Point, Point);
// void afficheCluster(Cluster);
void initialisePoints(P_Point, int);
// void initialiseClusters(P_Point, P_Cluster, int, int);
// void initialiseDistance(float *distance[], P_Point, int);
// void affecterPointsMedoideProche(P_Point, P_Cluster, float *distance[], int, int);

//Definition des fonctions
//retourne le min de 2 valeur
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

//fonction qui retourne distance entre 2points
//Ici chaque point est representé dans le plan par 4 coordonnées (4D)
float getDistance(Point a, Point b)
{
	float s = sqrt(pow(a.Courage - b.Courage, 2) + pow(a.Loyaute - b.Loyaute, 2) + pow(a.Sagesse - b.Sagesse, 2) +
				   pow(a.Malice - b.Malice, 2));
	return s;
}
//fonction pour l'intialisation de n points
void initialisePoints(P_Point points, int n)
{
	int i;

	char *file_path = "choixpeauMagique.csv";
	FILE *fp = fopen(file_path, "r");

	if (!fp)
		printf("Can't open file\n");

	else
	{
		//Ici on a pris un tableau de taille 1084
		char buffer[1024];

		int row = 0;
		int column = 0;

		while (fgets(buffer,
					 1024, fp))
		{
			column = 0;
			row++;

			// Pour éviter l'affichage de la colonne
			// les noms dans le fichier peuvent être modifiés si besoin
			if (row == 1)
				continue;

			// Division des données
			char *value = strtok(buffer, ";");

			while (value)
			{
				// Column 1
				if (column == 0)
				{
					printf("Name :");
				}

				// Column 2
				if (column == 1)
				{
					printf("\tCourage :");
					points[row - 1].Courage = atof(value);
				}

				// Column 3
				if (column == 2)
				{
					printf("\tLoyaute :");
					points[row - 1].Loyaute = atof(value);
				}

				// Column 4
				if (column == 3)
				{
					printf("\tSagesse :");
					points[row - 1].Sagesse = atof(value);
				}

				// Column 5
				if (column == 4)
				{
					printf("\tMalice :");
					points[row - 1].Malice = atof(value);
				}

				// Column 6
				if (column == 5)
				{
					printf("\tVille :");
				}

				printf("%s", value);
				value = strtok(NULL, ";");
				column++;
			}

			printf("\n");
		}

		// Close the file
		fclose(fp);
	}

	/*for(i=0;i<n;i++){
        points[i].Courage=rand()%(40 + 1) + 1;
        points[i].Loyaute=rand()%(30 + 1) + 1;
        points[i].Sagesse=rand()%(30 + 1) + 1;
        points[i].Malice =rand()%(30 + 1) + 1;

    } */
}

int main(int argc, char **argv)
{

	int n = 50; //points
	return 0;
}