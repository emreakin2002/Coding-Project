#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Données numériques
#define pi 3.141592653589793  //la valeur de pi
#define pts 100  // Le nombre de points en x
#define T0 30  // La tension
#define u0 0.1  // La masse linéique de la corde
#define L 30e-2  // Longueur de la corde
 
typedef float mat[100][1000] ; // création d'un tableau 100 lignes et 1000 colonnes
typedef float vect[100] ;  // création d'un vecteur 100 lignes

// Prototypes des fonctions
void ecriture(char *filepath, mat y, vect x, int n);

int main(void)
{
    int i, j, n, nt, type_donde, extremite;
    float c, k, pt, ps, a;
    mat y;
    vect x;

    c = sqrt(T0 / u0);  //vitesse de l'onde
    ps = L / (pts - 1); // pas spatial
    pt = ps / c;  //pas temporel
    nt = round((2 * L) / (c * pt)); //nbres de points
    a = pow((c * pt) / ps, 2);  //CFL

    for (i = 0; i < pts; i++)
    {
        x[i] = ps * i ;
    }
    printf(" \n ");

    printf("Veuillez saisir :\n 1 pour une onde stationnaire \n 2 pour une deformation initiale a vitesse nulle \n 3 pour une deformation initiale a vitesse non nulle \n 4 pour la propagation d'un train onde	\n ");
    scanf("%d", &type_donde);

    switch (type_donde)
    {
    case 1:
        printf("Veuillez saisir le mode  \n");
        scanf("%d", &n);

        for (i = 0; i < pts; i++)
        {
            y[i][0] = sin(n * pi * x[i] / L) / 100;
            y[i][1] = y[i][0];
        }
        break;

    case 2:
        for (i = 0; i < pts; i++)
        {
            y[i][0] = (1 / sqrt(2 * pi)) * exp(-pow((x[i] - 0.15) / 0.2 * 10, 2) / 2) / 0.50 * 0.012;
            y[i][1] = y[i][0];
        }
        break;

    case 3:
        for (i = 0; i < pts; i++)
        {
            y[i][0] = (1 / sqrt(2 * pi)) * exp(-pow((x[i] - 0.15) / 0.2 * 10, 2) / 2) / 0.50 * 0.012;
            y[i][1] = (1 / sqrt(2 * pi)) * exp(-pow((x[i] - 32 * ps - 0.15) / 0.2 * 10, 2) / 2) / 0.50 * 0.012;
        }
        break;

    case 4:
        for (i = 0; i < pts; i++)
        {
            y[i][0] = cos(x[i]) * (1 / sqrt(2 * pi)) * exp((-1 * x[i] * x[i]) / 2) / 100;
            y[i][1] = y[i][0];
        }
        break;

    default:
        printf("Type de onde non reconnu.\n");
        return 1;
    }

    printf(" Veuillez saisir : \n 1 pour fixer la corde a deux extremites \n 2 pour fixer la corde a une seule extremite \n ");
    scanf("%d", &extremite);

    switch (extremite)
    {
    case 1:
        for (j = 0; j < nt; j++)
        {
            y[0][j] = 0;
            y[pts - 1][j] = 0;
        }
        break;

    case 2:
        for (j = 0; j < nt; j++)
        {
            y[0][j] = 0;
            y[pts - 1][j + 1] = y[pts - 2][j];
        }
        break;

    default:
        printf("Option d'extrémité non reconnue.\n");
        return 1;
    }

    //Méthode des différences finies
    for (j = 2; j < nt - 1; j++)
    {
        for (i = 1; i < pts - 1; i++)
        {
            y[i][j + 1] = a * (y[i + 1][j] - 2 * y[i][j] + y[i - 1][j]) + 2 * y[i][j] - y[i][j - 1];
        }
    }

    for (j = 0; j <= nt - 1; j++)
    {
        for (i = 0; i <= pts - 1; i++)
        {
            printf(" \t ");
        }
        printf(" \n ");
    }
    printf(" \n ");

    ecriture("hacenemre.txt", y, x, 100);
    printf("%f \n", ps) ;
    printf("\nVotre fichier hacenemre.txt a ete cree, il se trouve au meme emplacement que ce programme \n ") ;

    return 0;
}

void ecriture(char *filepath, mat y, vect x, int n)
{
    FILE *nom = fopen(filepath, "w");
    if (nom == NULL)
    {
        perror("Erreur d'ouverture du fichier en écriture");
        exit(EXIT_FAILURE);
    }

    // Écriture du vecteur x dans le fichier
    for (int i = 0; i < n; i++)
    {
        fprintf(nom, "%f ", x[i]);
    }
    fprintf(nom, "\n");

    // Écriture de la matrice y dans le fichier
    for (int j = 0; j < 198; j++)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(nom, "%f ", y[i][j]);
        }
        fprintf(nom, "\n");
    }

    fclose(nom);
}