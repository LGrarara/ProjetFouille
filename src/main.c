#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "uvsqgraphics.h"

typedef struct Point {
  float Courage;
  float Loyaute;
  float Sagesse;
  float Malice;
  int cluster;
} Point;
typedef Point P_Point;

typedef struct Cluster {
  int taille;
  int centre;
} Cluster;
typedef Cluster P_Cluster;

typedef struct Clustertemp {
  P_Point point;
  int numero;
} Clustertemp;

// Calcul la distance entre 2 points
float getDistance(Point a, Point b) {
  float s = sqrt(pow(a.Courage - b.Courage, 2) + pow(a.Loyaute - b.Loyaute, 2) +
                 pow(a.Sagesse - b.Sagesse, 2) + pow(a.Malice - b.Malice, 2));
  return s;
}

// Initialise les point a partir du fichier csv
void initialisePoints(P_Point points[]) {
  char *file_path = "choixpeauMagique.csv";
  FILE *fp = fopen(file_path, "r");

  if (!fp)
    printf("Can't open file\n");

  else {

    char buffer[1024];

    int row = 0;
    int column = 0;
    // Lit une ligne du fichier
    while (fgets(buffer, 1024, fp)) {
      column = 0;
      row++;

      if (row == 1)
        continue;
      // Le seprateur est defini sur ;
      char *value = strtok(buffer, ";");

      // divisine une ligne avec strtok
      while (value) {

        // Column 2
        if (column == 1) {

          points[row - 1].Courage = atof(value);
        }

        // Column 3
        if (column == 2) {

          points[row - 1].Loyaute = atof(value);
        }

        // Column 4
        if (column == 3) {

          points[row - 1].Sagesse = atof(value);
        }

        // Column 5
        if (column == 4) {
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
void initialiseDistance(float distance[50][50], P_Point points[], int n) {

  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      distance[i][j] = getDistance(points[i], points[j]);
    }
  }
}

// Cree des clusters avec des centre aleatoire
void initialisecluster(int k, int n, P_Cluster clusters[], P_Point points[]) {

  // Initialise la tailles des clusters a 0;
  srand(time(0));
  int i;
  for (i = 0; i < k; i++)
    clusters[i].taille = 0;

  // Initialise aleatoire le centre d'un cluster
  for (i = 0; i < k; i++) {
    clusters[i].centre = rand() % n + 1;
    points[clusters[i].centre].cluster = 0;
    clusters[i].taille++;
  }
}

void afficheCluster(P_Cluster clusters[], int k) {
  for (int i = 0; i < k; i++) {
    printf("centre: %d   ", clusters[i].centre);
    printf("Taille: %d   ", clusters[i].taille);
    printf("suivant\n");
  }

  printf("cluster suivant\n\n");
}

// Ajoute les points les plus proches a chaque clusters
void affecter_cluster_le_plus_proche(int k, int n, P_Cluster clusters[],
                                     P_Point points[]) {
  // Pour chaque centre comparer a un point n, garder valeur minimum
  // objet i de 0 à n, chercher le cluster le plus proche de de n, i++
  int i, j, e;
  float tmp;
  int mincluster;

  // Calcul la distance minium d'un point par rapport a chaque centre de cluster
  for (e = 0; e < n; e++) {
    float minimum = 900000000;
    for (j = 0; j < k; j++) {
      tmp = getDistance(points[clusters[j].centre], points[e]);
      if (tmp < minimum) {
        minimum = tmp;
        mincluster = j;
      }
    }
    // Ajoute le point au cluster si la distance est minimum au centre
    points[e].cluster = mincluster;
    clusters[mincluster].taille++;
  }

  for (i = 0; i < k; i++) {
    clusters[i].taille--;
  }
}

int bestdistancetotal(P_Point points[], int numero_cluster,
                      P_Cluster clusters[], int n) {
  // Cree un tableau qui represente le cluster en y ajoutant tout les points qui
  // corresponde au cluster
  Clustertemp clusterstemp[clusters[numero_cluster].taille];
  float distancetotal;
  int intbestdistancetotal = 9000000;
  float floatbestdistance = 9000000;
  int i;
  int f = 0;
  // Crée un tableau avec tout les elements du cluster
  for (i = 0; i < n; i++) {
    if (points[i].cluster == numero_cluster) {
      P_Point buff = points[i];
      clusterstemp[f].point = buff;
      clusterstemp[f].numero = i;
      f++;
    }
  }

  // Calculer la distance mis pour parcouris a partit d'un point pour joindre
  // tout les point du cluster

  for (int e = 0; e < f; e++) {
    for (i = 0; i < f; i++)
      distancetotal += getDistance(points[e], clusterstemp[i].point);

    if (distancetotal < floatbestdistance) {
      floatbestdistance = distancetotal;
      intbestdistancetotal = e;
    }
  }
  return clusterstemp[intbestdistancetotal].numero;
}
// Trouve le meilleur centre pour chaque cluster en calculant la distance max
void trouver_le_meilleur_centre(int k, int n, P_Cluster clusters[],
                                P_Point points[]) {

  // Calculer meilleur distance pour chaque cluster
  for (int i = 0; i < k; i++) {
    clusters[i].centre = bestdistancetotal(points, i, clusters, n);
  }
}

void afficher_pam(int n, P_Point points[], P_Cluster clusters[], int k) {
  // Espace chaque point de 20 pixel
  int ecart = 20;
  int ecarspe = 20;
  // Abscisse = n et Ordonnée la total des points de Courage Loyauté Sagesse et
  // Malice
  init_graphics(1000, 500);
  int r = 250;
  int g = 0;
  int b = 0;
  // i = 0 si le premier cluster à le numéro 0
  for (int i = 0; i < k; i++) {
    // On cherche la position x du metoid
    int position = 0;
    int nombredepoints = 0;
    for (int j = 0; j < n; j++) {
      if (points[j].cluster == i) {
        position += j + ecarspe;
        nombredepoints += 1;
        ecarspe += 10;
      }
    }
    // p2 est le point centré du cluster
    POINT p2;
    p2.y = (points[clusters[i].centre].Courage +
            points[clusters[i].centre].Loyaute +
            points[clusters[i].centre].Sagesse +
            points[clusters[i].centre].Malice) *
           10;
    p2.x = position / nombredepoints;
    for (int j = 0; j < n; j++) {
      if (points[j].cluster == i) {
        POINT p1;
        p1.x = j + ecart;
        ecart += 10;
        p1.y = (points[j].Courage + points[j].Loyaute + points[j].Sagesse +
                points[j].Malice) *
               10;
        // Trace le point(c'est un cercle pcq on voit rien avec un pixel)
        draw_fill_circle(p1, n / 15, couleur_RGB(r, g, b));
        // Trace un ligne entre le point créé et le centre du cluster
        draw_line(p1, p2, couleur_RGB(r, g, b));
      }
    }
    // On différencie les clusters par couleur
    if (i % 3 == 0) {
      r = 0;
      g = 250;
      b = 0;
    }

    if (i % 3 == 1) {
      r = 0;
      g = 0;
      b = 250;
    }

    if (i % 3 == 2) {
      r = 250;
      g = 0;
      b = 0;
    }
  }
  wait_escape();

  /*////A SUPPR SI PAS DE RETOUCHE AU CENTRE

          int ecart = 20;
          //copie de ecart
          int ecarspe = 20;
          //Absicce = n et Ordonnée la total des points de Courage Loyauté
     Sagesse et Malice init_graphics(1000,500);

          int r = 250;
          int g = 0;
          int b = 0;

          int ptmedoi = 0;

          // i = 0 si le premier cluster à le numéro 0
          for (int i = 0; i < k; i++)
                  {
                  for (int j = 0; j < n; j++)
                          {
                                  if (points[j].cluster == i)
                                  {
                                          f (
                                          (points[j].Courage ==
     points[clusters[i].centre].Courage)&& (points[j].Loyaute ==
     points[clusters[i].centre].Loyaute)&& (points[j].Sagesse ==
     points[clusters[i].centre].Sagesse)&& (points[j].Malice ==
     points[clusters[i].centre].Malice) )
                                          {
                                          printf("%d\n",j);
                                          ptmedoi = j+ecarspe;
                                          }
                                          ecarspe+=10;

                                  }
                          }

                  POINT p2;
                  p2.y = (points[clusters[i].centre].Courage +
     points[clusters[i].centre].Loyaute + points[clusters[i].centre].Sagesse +
     points[clusters[i].centre].Malice)*10; p2.x = ptmedoi; for (int j = 0; j <
     n; j++)
                  {
                                  if (points[j].cluster == i)
                                  {
                                          POINT p1;
                                          p1.x = j+ecart;
                                          ecart += 10;
                                          p1.y = (points[j].Courage +
     points[j].Loyaute + points[j].Sagesse + points[j].Malice)*10;
                                      //On fait un cercle pcq on voit rien avec
     un pixel draw_fill_circle(p1,n/15,couleur_RGB(r,g,b));
                                          //Trace un ligne entre le point créé
     et le centre du cluster draw_line(p1,p2,couleur_RGB(r,g,b));
                                  }
                          }
                                  //On différencie les clusters par couleur
                                  if(i%3==0){
                                          r = 0;
                                          g = 250;
                                          b = 0;}

                                  if(i%3==1){
                                          r = 0;
                                          g = 0;
                                          b = 250;}

                                  if(i%3==2){
                                          r=250;
                                          g = 0;
                                          b = 0;}
                          }

          wait_escape();
          */
}

void resetclustersize(P_Cluster clusters[], int k) {
  int i;
  for (i = 0; i < k; i++) {
    clusters[i].taille = 1;
  }
}

void putintinarray(int array[], P_Cluster clusters[], int k) {

  for (int i = 0; i < k; i++) {
    array[i] = clusters[i].centre;
  }
}

int samearray(int array1[], int array2[], int k) {
  int i;
  for (i = 0; i < k; i++) {
    if (array1[i] != array2[i]) {
      return 0;
    }
  }
  return 1;
}

int main() {
  int n = 50; // points
  int k = 3;  // groupes
  if (k > n)
    exit(0);

  float distance[n][n];
  P_Point points[n];
  P_Cluster clusters[k];
  initialisePoints(points);
  initialiseDistance(distance, points, n);
  initialisecluster(k, n, clusters, points);
  int array1[k];
  int array2[k];
  int o = 0;
  while (o == 0) {
    affecter_cluster_le_plus_proche(k, n, clusters, points);
    putintinarray(array1, clusters, k);
    trouver_le_meilleur_centre(k, n, clusters, points);
    afficheCluster(clusters, k);
    putintinarray(array2, clusters, k);
    if (samearray(array1, array2, k)) {
      break;
    } else {
      resetclustersize(clusters, k);
      continue;
    }
  }

  afficher_pam(n, points, clusters, k);

  return 0;
}
