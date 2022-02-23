#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"


/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(x >=0 && x<=SIZE_X); //Assert pour verification de la validite de x
  assert(y>= 0 && y<=SIZE_Y); //Assert pour verification de la validite de y 
  Animal *a = creer_animal(x, y, energie); //Appeler la fonction creer_animal pour creer un nouveau animal
  //En utilisant le pointeur sur pointeur sur Animal, modifier la liste directement et 
  //ajouter l'animal au debut de la liste. 
  *liste_animal = ajouter_en_tete_animal(*liste_animal, a); 
  /*A Completer*/
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  //Verification si on veut supprimer le 1er element 
  if (animal==*liste){
    Animal *nl= animal->suivant; //On a affecte le reste de la liste chaine a nl
    free(animal); //Liberer la memoire 
    animal= NULL;
    *liste=nl; //La nouvelle liste apres suppression de l'element
  }
  else{
    Animal *tmp= *liste;//On fait une copie tmp de la liste chaine dans un pointeur tmp
    //Parcourir la liste jusqu'a trouver l'element 'animal' a supprimer. 
    while((tmp) && (tmp->suivant != animal)){
      tmp= tmp->suivant; 
    }
    if(tmp->suivant == animal){ //Si l'animal suivant est bien l'animal a supprimer 
      //On saute l'element a supprimer et on effecue a la liste tmp l'element qui suit 'animal'
      tmp->suivant= animal->suivant;
      //on libere la memoire
      free(animal);
      animal=NULL;  
    }
    else{ printf("Attention animal n'est pas present dans la liste");
    }
  }
  /*A Completer*/
  return ;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal *tmp = NULL;
  //Tant que liste n'est pas egale a NULL on rentre dans la boucle while 
  while(liste){
    tmp= liste->suivant; //Affecter l'element suivant de la liste a un pointeur temporaire. 
    free(liste); //Liberation de la memoire 
    liste=tmp; //Affecter la liste temporaire a la liste de depart
  }
   /*A Completer*/
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred=0,nbproie=0;
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }
    /*A Completer*/


  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ++nbproie;
    assert (pa->x >= 0 && pa->x <= SIZE_X && pa->y >= 0 && pa->y <= SIZE_Y);
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }
    /*A Completer*/

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
  ++nbpred;
  assert (pa->x >= 0 && pa->x <= SIZE_X && pa->y >= 0 && pa->y <= SIZE_Y);
  if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /*proies aussi present */
    ecosys[pa->x][pa->y] = '@';
  } else {
    ecosys[pa->x][pa->y] = 'O';
  }
  pa = pa->suivant;
  }
  /*A Completer*/

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
  printf("-");
  }
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 5, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
  Animal *aa=la;
  while(aa){
    //Verification de la validite de x et y 
    assert(aa->x >= 0 && aa->x <=SIZE_X);
    assert(aa->y >=0 && aa->y <=SIZE_Y);

    // Conformement a l'enonce, la case d'origine est celle qui se trouve en haut a gauche donc 
    // le bord sur l'axe des x se trouve a droite et a comme valeur SIZE_X
    //et le bord sur l'axe des y se trouve en bas et a comme valeur SIZE_Y

    // L'animal bouge seulement si la probabilite p_ch_dir est satisfaite 
    if ( (float)rand()/(float)(RAND_MAX/1.0) < p_ch_dir ){ 

    //Si l'animale souhaite bouger en haut alors qu'il est sur la premiere ligne (x, 0) il se retrouve sur
    //le bord en bas
        if (aa->y == 0 && aa->dir[0] == 1){ aa->y = SIZE_Y; }
    //S'il souhaite descendre alors qu'il est sur la derniere ligne, il se retrouve sur la premiere ligne 
        if (aa->y == SIZE_Y && aa->dir[0] == -1){ aa->y = 0; }
    //S'il souhaite bouger a droite alors qu'il se trouve a la limite droite, il se trouve sur le bord gauche 
        if(aa->x == SIZE_X && aa->dir[1] == -1){ aa->x = 0; }
    //S'il souhaite bouger a gauche alors qu'il se trouve a la limite gauche (0, y), il se trouve 
    //sur le bord droite.  
        if(aa->x == 0 && aa->dir[1] == 1){ aa->x = SIZE_X; }
    //S'il souhaite bouger en haut et il n'est pas sur la premiere ligne (x,0), on decremente la coordonnee y 
        if (aa->dir[0] == 1 && aa->y != 0) { aa->y--; }
    //S'il souhaite descendre et il n'est pas sur la derniere ligne, on incremente la coordonnee y 
        if (aa->dir[0] == -1 && aa->y != SIZE_Y ) { aa->y++; }
    //S'il souhaite bouger a gauche et il ne se trouve pas sur la limite gauche, on decremente la coordonnee x 
        if (aa->dir[1] == 1 && aa->x != 0) { aa->x--; }
    //S'il souhaite bouger a droite et il ne se trouve pas sur la limite droite, on incremente la coordonnee x 
        if (aa->dir[1] == -1 && aa->x!= SIZE_X ) { aa->x++; }
    }
    aa=aa->suivant; //Apres avoir bouge l'animal courant, on passe au suivant 
  }
}

/* Part 2. Exercice 5, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *ani= *liste_animal; //Stocker la liste chaine dans un pointeur appelle ani 
  while(ani){
    //Un animal peut reproduire seulement si la probabilite est satisfaite  
    if ( (float)rand()/(float)(RAND_MAX/1.0) < p_reproduce){
    //Un nouveau animal est ajoute a la liste avec les memes coordonnees qu'ani et la moitie de son energie  
    ajouter_animal(ani->x, ani->y, (ani->energie)/2, liste_animal);
    //l'animal perd la moitie de son energie apres la reproduction 
    ani->energie= (ani->energie)/2; 
    }
    ani=ani->suivant; //Passer a l'animal suivant 
  }
   /*A Completer*/

}


/* Part 2. Exercice 7, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie); //Appeler la fonction bouger animaux pour bouger les proies 
  Animal *a= *liste_proie; //Stocker la liste des proies dans un pointeur a 
  while(a) {
    a->energie--; //Baisser l'energie des proies
    if(monde[a->x][a->y] >= 0){ //S'il y a de l'herbe, la proie peut le manger 
      a->energie+=gain_energie_proie;//L'energie de la proie augmente apres consommation de l'herbe 
      monde[a->x][a->y]=temps_repousse_herbe;
      //l'herbe tombe a une valeur negative (donc il ne sera plus consommable pour quelques 
      //iterations durant la simulation)
    }
    if(a->energie < 0){ //Si une proie a une energie negative, elle va disparaitre 
      Animal *tmp= a; // Stocker la proie a enlever dans un nouveau pointeur 
      a=a->suivant; //Passer a l'element suivant
      enlever_animal(liste_proie, tmp); //Enlever la proie avec une energie negative (pointeur tmp)
    }
    else{a=a->suivant;} //Si la proie n'a pas d'energie negative, on passe a la suivante
  }
  reproduce(liste_proie, p_reproduce_proie); //Passer l'adresse de la liste des proies pour la reproduction 
    /*A Completer*/
}

/* Part 2. Exercice 8, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  Animal *a= l; 
  while(a){ //Parcourir la liste des proies
    if( a->x == x && a->y == y){ 
      //Si une proie a les memes coordonnees x et y donnee en argument on renvoi son pointeur 
      return a; 
    }
    a=a->suivant; //Passer a la proie suivante 
  }
    /*A Completer*/

  return NULL;
} 

/* Part 2. Exercice 8, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur); //Bouger tout les predateurs  
  Animal *a= *liste_predateur; 
  while(a) { //Parcourir la liste des predateurs 
    a->energie--; //Baisser l'energie du predateur 
    Animal *b= animal_en_XY(*liste_proie, a->x , a->y); //Verifier si une proie existe sur la meme case 
    if(b){//Si b n'est pas NULL 
      if ( (float)rand()/(float)(RAND_MAX/1.0) < p_manger){ //Si la probabilite p_manger est satisfaite 
        a->energie+=b->energie;//Le predateur prends l'energie de la proie 
        b->energie= -1; //Rendre l'energie de la proie negative pour qu'elle soit enleve 
      }
    }
    if(a->energie < 0){ //Si un predateur a une energie negative il sera enleve 
      Animal *tmp= a;
      a=a->suivant; 
      enlever_animal(liste_predateur, tmp); //Appeler la fonction enlever 
    }
    else{a=a->suivant;}
  }
  reproduce(liste_predateur, p_reproduce_predateur); //Reproduction des predateurs 
   /*A Completer*/
}

/* Part 2. Exercice 6, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
    //Parcourir les cases dans le tableau 
    for(int i=0; i<SIZE_X; i++){ 
      for(int j=0; j<SIZE_Y; j++){
        monde[i][j]+=1; //Incrementer les cases a 1 
    }
  }
   /*A Completer*/
}

