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

typedef struct Clustertemp
{
    P_Point point;
    int numero;
} Clustertemp;

float getDistance(Point a, Point b)
{
    float s = sqrt(pow(a.Courage - b.Courage, 2) + pow(a.Loyaute - b.Loyaute, 2) + pow(a.Sagesse - b.Sagesse, 2) +
                   pow(a.Malice - b.Malice, 2));
    return s;
}

// Initialise les point a partir du fichier csv
void initialisePoints(P_Point points[])
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

            //Lit chaque ligne et la divise avec strtok
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

// Cree un tableau de distance avec la distance entre chaque point
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

// Cree des clusters avec des centre aleatoire
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
        printf("centre: %d   ", clusters[i].centre);
        printf("Taille: %d   ", clusters[i].taille);
        printf("suivant\n");
    }

    printf("cluster suivant\n\n");
}

// Ajoute les points les plus proches a chaque clusters
void affecter_cluster_le_plus_proche(int k, int n, P_Cluster clusters[], P_Point points[])
{
    // Pour chaque centre comparer a un pont n, garder valeur minimum
    //objet i de 0 à n, chercher le cluster le plus proche de de n, i++
    int i, j, e;
    float tmp;
    int mincluster;
    for (e = 0; e < n; e++)
    {
        float minimum = 900000000;
        for (j = 0; j < k; j++)
        {
            tmp = getDistance(points[clusters[j].centre], points[e]);
            if (tmp < minimum)
            {
                minimum = tmp;
                mincluster = j;
            }
        }

        points[e].cluster = mincluster;
        clusters[mincluster].taille++;
    }

    for (i = 0; i < k; i++)
    {
        clusters[i].taille--;
    }
}

int bestdistancetotal(P_Point points[], int numero_cluster, P_Cluster clusters[], int n)
{
    // Cree un tableau qui represente le cluster en y ajoutant tout les points qui corresponde au cluster
    Clustertemp clusterstemp[clusters[numero_cluster].taille];
    float distancetotal;
    int intbestdistancetotal = 9000000;
    float floatbestdistance = 9000000;
    int i;
    int f = 0;
    for (i = 0; i < n; i++)
    {
        if (points[i].cluster == numero_cluster)
        {
            P_Point buff = points[i];
            clusterstemp[f].point = buff;
            clusterstemp[f].numero = i;
            f++;
        }
    }

    // Calculer la distance mis pour parcouris a partit d'un point

    for (int e = 0; e < f; e++)
    {
        for (i = 0; i < f; i++)
            distancetotal += getDistance(points[e], clusterstemp[i].point);

        if (distancetotal < floatbestdistance)
        {
            floatbestdistance = distancetotal;
            intbestdistancetotal = e;
        }
    }
    return clusterstemp[intbestdistancetotal].numero;
}
// Trouve le meilleur centre pour chaque cluster en calculant la distance max
void trouver_le_meilleur_centre(int k, int n, P_Cluster clusters[], P_Point points[])
{

    // Calculer meilleur distance pour chaque cluster
    for (int i = 0; i < k; i++)
    {
        clusters[i].centre = bestdistancetotal(points, i, clusters, n);
    }
}

void afficher_pam(int k, P_Cluster clusters[], P_Point points[])
{
    for (int i = 0; i < k; i++)
    {
    }
}

int main()
{
    int n = 50; //points
    int k = 3;  //groupes
    if (k > n)
        exit(0);

    float distance[n][n];
    P_Point points[n];
    P_Cluster clusters[k];
    initialisePoints(points);
    initialiseDistance(distance, points, n);
    initialisecluster(k, n, clusters, points);
    affecter_cluster_le_plus_proche(k, n, clusters, points);
    trouver_le_meilleur_centre(k, n, clusters, points);
    afficheCluster(clusters, k);
    afficher_pam(k, clusters, points);
}