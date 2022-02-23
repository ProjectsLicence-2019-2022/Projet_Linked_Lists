#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20

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
    Animal *proie= NULL;

    Animal *k= creer_animal(2, 4, 7); 
    Animal *b= creer_animal(5, 0, 8);

    proie= ajouter_en_tete_animal(proie, k);
    proie= ajouter_en_tete_animal(proie, b);

    ajouter_animal(8, 6, 2.0, &proie);

    printf("Nombre de proies originale : %d\n", compte_animal_it(proie)); 
    
    enlever_animal(&proie, k);

    printf("Nombre de proies apres suppression d'un animal : %d\n", compte_animal_it(proie)); 
    //Verification que l'animal a ete enleve 

    liberer_liste_animaux(proie); //Liberation de la memoire  


  /* A Completer. Exercice 5, question 3 */

  //rthbrst
  return 0;
}
