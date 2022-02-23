#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000

//Initialisation des parametres 
/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
int gain_energie_proie=6;
int gain_energie_predateur=20;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;
float p_manger=0.5;


int main(void) {

  FILE *f; //Declaration du pointeur sur le fichier 
  int eco[SIZE_X][SIZE_Y]; //Declaration du terrain de la simulation 
  Animal *proie= NULL; //Declaration de la liste chainee des proies 
  Animal *predateur= NULL; //Declaration de la liste chainee des predateurs 
  int iteration =1; //Initialisation du nombre d'iterations  

  f = fopen("Evol_pop.txt", "w"); //Overture du fichier en mode ecriture (write)
  //initialisation des cases a 0 
  for(int i=0; i<SIZE_X; i++){
      for(int j=0; j<SIZE_Y; j++){
          eco[i][j]=0; 
      }
  }


    //Creation de 20 proies 
    for(int i=0; i<NB_PROIES; i++){
        ajouter_animal(rand()%(SIZE_X), rand()%(SIZE_Y), ((float)rand()/(float)(RAND_MAX/1.0))*10, &proie);  
    }

    //Creation de 20 predateurs 
    for(int i=0; i<NB_PREDATEURS; i++){
      ajouter_animal(rand()%(SIZE_X), rand()%(SIZE_Y),((float)rand()/(float)(RAND_MAX/1.0))*10, &predateur);  
    }

    afficher_ecosys(proie, predateur); //Premier affichage 
    fprintf (f, "%d %d %d\n", 0, compte_animal_it(proie), compte_animal_it(predateur));

    //Boucle pour rafraichir les prois et predateurs 
    while(compte_animal_it(proie) !=  0 && compte_animal_it(predateur) !=  0 ){
      rafraichir_proies(&proie, eco);
      rafraichir_predateurs(&predateur, &proie); 
      afficher_ecosys(proie, predateur); 
      usleep(T_WAIT); 
      //Ecrire dans le fichier Evol_pop.txt 
      fprintf (f, "%d %d %d\n", iteration, compte_animal_it(proie), compte_animal_it(predateur));
      iteration++;
    }
 
  /* A completer. Part 2:
   * exercice 6, question 1
   * exercice 7, question 2
   * exercice 8, question 3
   * exercice 9, question 1
   */

  return 0;
}

