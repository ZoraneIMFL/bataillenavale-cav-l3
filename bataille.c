#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <stdlib.h>
#define max_bat 5

/* DBILIJ Zeineddine */
/* Nakkache Hamza */


typedef struct cordonnees{
  int posx;
  int posy;
}coord;

typedef struct b{
  coord *emplacement;
  int taille;
  int vie;
}bateau;

typedef struct j{
  char *nom;
  char grille[10][10];
  char grilleIA[10][10];
  bateau *navires;
  int nb_bat;
}joueur;


void init_bateau(joueur *A){
  int tab[5]={5,4,3,3,2},i;
  A->navires=malloc(sizeof(bateau)*5);
  A->nb_bat=5;
  for(i=0;i<5;i++){
    A->navires[i].taille=tab[i];
    A->navires[i].vie=A->navires[i].taille;
    A->navires[i].emplacement=malloc(sizeof(coord)*A->navires[i].taille);
  }

}

void init_grille(char grille[10][10]){
  int i,j;
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      grille[i][j]='.';
    }
  }
}


int verif_pascolle(int taille_bat, int d, char grille[10][10], int x , int y){
  for(int i =0; i<taille_bat;i++){

  }
  if(d==0){
    for(int i =0; i<taille_bat+1;i++){
      int j=1;
      if(grille[x-i][y] == 'O' || grille[x-i][y+j] == 'O' || grille[x-i][y-j] == 'O' || grille[x+1][y]=='O' ){
        return 0;
      }
    }
  }
  if(d==1){
    for(int i =0; i<taille_bat+1;i++){
      int j=1;
      if(grille[x][y+i] == 'O' || grille[x-j][y+i] == 'O' || grille[x+j][y+i] == 'O' || grille[x][y-1]=='O'){
        return 0;
      }
    }
  }
  if(d==2){
    for(int i =0; i<taille_bat+1;i++){
      int j=1;
      if(grille[x+i][y] == 'O' || grille[x+i][y+j] == 'O' || grille[x+i][y-j] == 'O' || grille[x-1][y]=='O' ){
        return 0;
      }
    }
  }
  if(d==3){
    for(int i =0; i<taille_bat+1;i++){
      int j=1;
      if(grille[x][y-i] == 'O' || grille[x-j][y-i] == 'O' || grille[x+j][y-i] == 'O' || grille[x][y+1]=='O'  ){
        return 0;
      }
    }
  }
  return 1;
}





void placer_bateau(joueur *A,char grille[10][10]){
  int nb_bat=0;
  int valider=1;
  int x,y,d;
  while(nb_bat<max_bat){
    if(valider){
      d =rand()%4;
      x =rand()%10;
      y =rand()%10;
    }
    if(grille[x][y] != 'O'){
      if(d== 0 && verif_pascolle(A->navires[nb_bat].taille,d,grille,x,y) ){
        if((x-A->navires[nb_bat].taille)<0){
          d=1;
        }
        else{
          for(int i=0;i<A->navires[nb_bat].taille;i++){
            grille[x-i][y]='O';
            A->navires[nb_bat].emplacement[i].posx=x-i;
            A->navires[nb_bat].emplacement[i].posy=y;
            valider=1;
          }
          nb_bat++;
        }
      }
      if(d == 1  && verif_pascolle(A->navires[nb_bat].taille,d,grille,x,y)){
        if((y+A->navires[nb_bat].taille)>9){
          d=2;
        }
        else{
          for(int i=0;i<A->navires[nb_bat].taille;i++){
            grille[x][y+i]='O';
            A->navires[nb_bat].emplacement[i].posx=x;
            A->navires[nb_bat].emplacement[i].posy=y+i;
            valider=1;
          }
          nb_bat++;
        }
      }
      if(d == 2 && verif_pascolle(A->navires[nb_bat].taille,d,grille,x,y) ){
        if((x+A->navires[nb_bat].taille)>9){
          d=3;
        }
        else{
          for(int i=0;i<A->navires[nb_bat].taille;i++){
            grille[x+i][y]='O';
            A->navires[nb_bat].emplacement[i].posx=x+i;
            A->navires[nb_bat].emplacement[i].posy=y;
            valider=1;
          }
          nb_bat++;
        }
      }
      if(d == 3 && verif_pascolle(A->navires[nb_bat].taille,d,grille,x,y)){
        if((y-A->navires[nb_bat].taille)<0){
          d=0;
          valider=0;
        }
        else{
          for(int i=0;i<A->navires[nb_bat].taille;i++){
            grille[x][y-i]='O';
            A->navires[nb_bat].emplacement[i].posx=x;
            A->navires[nb_bat].emplacement[i].posy=y-i;
            valider=1;
          }
          nb_bat++;
        }
      }
    }
  }
}


void affiche_grille(char grille[10][10], char grille2[10][10] ) {
  int i,j;
  for(i=0;i<10;i++)
  {
      for(j=0;j<10;j++){
          printf(" ");
        }
      if(i==0)
      {
          printf("  ");
          for(j=0;j<10;j++){
            printf("%c ",'A'+j);

          }
          printf("         ");
          for(j=0;j<10;j++){
            printf("%c ",'A'+j);

          }
          printf("\n");
          for(j=0;j<10;j++)
          printf(" ");
      }

      printf("%d ",i);




      for(j=0;j<10;j++){
          printf("%c ",grille[i][j]);
      }
      printf("       ");
      printf("%d ",i);
      for(j=0;j<10;j++){
          printf("%c ",grille2[i][j]);
      }


      printf("\n");
  }
}

int verif_case(joueur *B,int x ,int y, int nb_bat){
  if(x>=0 && x<=9 && y>=0 && y<=9 ){
    if(B->grille[x][y]=='.' || B->grille[x][y]=='#' ){
      if(B->grille[x][y]=='.'){
        B->grille[x][y]='X';
        B->grilleIA[x][y]='X';
        return 0;
      }
    }
    else if(B->grille[x][y]=='O'){
      B->grille[x][y]='#';
      B->grilleIA[x][y]='#';
      for(int i=0;i<nb_bat;i++){
        for(int j=0;j<B->navires[i].taille;j++){
          if(x==B->navires[i].emplacement[j].posx && y==B->navires[i].emplacement[j].posy ){
            if(B->navires[i].vie > 0 ){
              B->navires[i].vie--;
            }
            if (B->navires[i].vie == 0){
              B->nb_bat--;
              printf("\nUn bateau des Bateaux de l'ia a coulé \n");
            }
          }
        }
      }
      return 1;
    }
  }
  return 0;
}



int verif_case_ia(joueur *B,int x ,int y, int nb_bat){
  if(x>=0 && x<=9 && y>=0 && y<=9 ){
    if(B->grille[x][y]=='.' || B->grille[x][y]=='#' ){
      if(B->grille[x][y]=='.'){
        B->grille[x][y]='X';
        B->grilleIA[x][y]='X';
        printf("\nL'ia a raté son tire, profitez-en pour l'achever !\n");
        printf("\n");
        return 0;
      }
    }
    else if(B->grille[x][y]=='O'){
      B->grille[x][y]='#';
      B->grilleIA[x][y]='#';
      printf("\nL'Ia a touche son tire, faitez attention, elle peut être redoutable quand elle veut haha !\n ");
      for(int i=0;i<nb_bat;i++){
        for(int j=0;j<B->navires[i].taille;j++){
          if(x==B->navires[i].emplacement[j].posx && y==B->navires[i].emplacement[j].posy ){
            if(B->navires[i].vie > 0 ){
              B->navires[i].vie--;
            }
            if (B->navires[i].vie == 0){
              B->nb_bat--;
              printf("\n L'Ia a fait couler un de vos Bateaux, faites attention ! \n");
            }
          }
        }
      }
      return 1;
    }
  }
  return 0;
}



void tire_specialligne(joueur *B,int x,int y, int nb_bat){
  int i,j,miss=0,t,d;
  printf("Donnez une direction: taper 1 pour une frappe verticale / 2 pour une frappe horizontale \n");
  scanf("%d",&d);
  if(d==1){
    for(i=0;i<10;i++){
      if(B->grille[x+i][y]=='.' || B->grille[x+i][y]=='X' || B->grille[x+i][y]=='#' || B->grille[x+i][y]=='O' || B->grille[x-i][y]=='.' || B->grille[x-i][y]=='X' || B->grille[x-i][y]=='#' || B->grille[x-i][y]=='O'){
        if(B->grille[x+i][y]=='.' || B->grille[x+i][y]=='X' || B->grille[x+i][y]=='#' || B->grille[x-i][y]=='.' || B->grille[x-i][y]=='X' || B->grille[x-i][y]=='#'){
          t=verif_case(B,x+i,y,nb_bat);
          t=verif_case(B,x-i,y,nb_bat);
          miss++;
        }
        else{
          t=verif_case(B,x+i,y,nb_bat);
          t=verif_case(B,x-i,y,nb_bat);
        }
      }
    }
  }
  else{
    for(i=0;i<10;i++){
      if(B->grille[x][y+i]=='.' || B->grille[x][y+i]=='X' || B->grille[x][y+i]=='#' || B->grille[x][y+i]=='O' || B->grille[x][y-i]=='.' || B->grille[x][y-i]=='X' || B->grille[x][y-i]=='#' || B->grille[x][y-i]=='O'){
        if(B->grille[x][y+i]=='.' || B->grille[x][y+i]=='X' || B->grille[x][y+i]=='#' || B->grille[x][y-i]=='.' || B->grille[x][y-i]=='X' || B->grille[x][y-i]=='#'){
          t=verif_case(B,x,y+i,nb_bat);
          t=verif_case(B,x,y-i,nb_bat);
          miss++;
        }
        else{
          t=verif_case(B,x,y+i,nb_bat);
          t=verif_case(B,x,y-i,nb_bat);
        }
      }
    }
  }
  if(miss==10){
    printf("\n                                                                  Vous avez raté \n");
  }
  else{
    printf("\n                                                                  Vous avez touché ! \n");
  }
}

void tire_specialcroix(joueur *B,int x, int y, int nb_bat){
  int i,j,miss=0;
  if(B->grille[x-1][y-1]=='O' || B->grille[x-1][y-1]=='X' || B->grille[x-1][y-1]=='.'|| B->grille[x-1][y-1]=='#'){
    if(B->grille[x-1][y-1]=='X' || B->grille[x-1][y-1]=='.'|| B->grille[x-1][y-1]=='#'){
      verif_case(B,x-1,y-1,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x-1,y-1,nb_bat);
    }
  }
  if(B->grille[x][y]=='O' || B->grille[x][y]=='#' || B->grille[x][y]=='.' || B->grille[x][y]=='X'){
    if( B->grille[x][y]=='#' || B->grille[x][y]=='.' || B->grille[x][y]=='X'){
      verif_case(B,x,y,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x,y,nb_bat);
    }
  }
  if(B->grille[x-1][y+1]=='O' || B->grille[x-1][y+1]=='.' || B->grille[x-1][y+1]=='X' || B->grille[x-1][y+1]=='#'){
    if(B->grille[x-1][y+1]=='.' || B->grille[x-1][y+1]=='X' || B->grille[x-1][y+1]=='#'){
      verif_case(B,x-1,y+1,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x-1,y+1,nb_bat);
    }
  }
  if(B->grille[x+1][y-1]=='O' || B->grille[x+1][y-1]=='.' || B->grille[x+1][y-1]=='#' || B->grille[x+1][y-1]=='X'){
    if(B->grille[x+1][y-1]=='.' || B->grille[x+1][y-1]=='#' || B->grille[x+1][y-1]=='X'){
      verif_case(B,x+1,y-1,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x+1,y-1,nb_bat);
    }
  }
  if(B->grille[x+1][y+1]=='O' || B->grille[x+1][y+1]=='X' || B->grille[x+1][y+1]=='.' || B->grille[x+1][y+1]=='#'){
    if(B->grille[x+1][y+1]=='X' || B->grille[x+1][y+1]=='.' || B->grille[x+1][y+1]=='#'){
      verif_case(B,x+1,y+1,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x+1,y+1,nb_bat);
    }
  }
  if(miss==5){
    printf("\nVous avez raté vos 5 tirs\n");
  }
  else{
    printf("\nVous avez touché un de vos 5 tirs \n");
  }

}

void tire_specialplus(joueur *B,int x,int y, int nb_bat){
  int i,j,miss;
  if(B->grille[x][y]=='O' || B->grille[x][y]=='#' || B->grille[x][y]=='.' || B->grille[x][y]=='X'){
    if( B->grille[x][y]=='#' || B->grille[x][y]=='.' || B->grille[x][y]=='X'){
      verif_case(B,x,y,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x,y,nb_bat);
    }
  }
  if(B->grille[x][y+1]=='O' || B->grille[x][y+1]=='.' || B->grille[x][y+1]=='X' || B->grille[x][y+1]=='#'){
    if(B->grille[x][y+1]=='.' || B->grille[x][y+1]=='X' || B->grille[x][y+1]=='#'){
      verif_case(B,x,y+1,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x,y+1,nb_bat);
    }
  }
  if(B->grille[x][y-1]=='O' || B->grille[x][y-1]=='.' || B->grille[x][y-1]=='#' || B->grille[x][y-1]=='X'){
    if(B->grille[x][y-1]=='.' || B->grille[x][y-1]=='#' || B->grille[x][y-1]=='X'){
      verif_case(B,x,y-1,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x,y-1,nb_bat);
    }
  }
  if(B->grille[x+1][y]=='O' || B->grille[x+1][y]=='X' || B->grille[x+1][y]=='.' || B->grille[x+1][y]=='#'){
    if(B->grille[x+1][y]=='X' || B->grille[x+1][y]=='.' || B->grille[x+1][y]=='#'){
      verif_case(B,x+1,y,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x+1,y,nb_bat);
    }
  }
  if(B->grille[x-1][y]=='O' || B->grille[x-1][y]=='X' || B->grille[x-1][y]=='.' || B->grille[x-1][y]=='#'){
    if(B->grille[x-1][y]=='X' || B->grille[x-1][y]=='.' || B->grille[x-1][y]=='#'){
      verif_case(B,x-1,y,nb_bat);
      miss++;
    }
    else{
      verif_case(B,x-1,y,nb_bat);
    }
  }
  if(miss==5){
    printf("\nVous avez raté vos 5 tirs\n");
  }
  else{
    printf("\nVous avez touché un de vos 5 tirs \n");
  }
}

void tire_specialcarre(joueur *B,int x,int y, int nb_bat){
    int i,j,miss;
    if(B->grille[x][y]=='O' || B->grille[x][y]=='#' || B->grille[x][y]=='.' || B->grille[x][y]=='X'){
      if( B->grille[x][y]=='#' || B->grille[x][y]=='.' || B->grille[x][y]=='X'){
        verif_case(B,x,y,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x,y,nb_bat);
      }
    }
    if(B->grille[x-1][y-1]=='O' || B->grille[x-1][y-1]=='X' || B->grille[x-1][y-1]=='.'|| B->grille[x-1][y-1]=='#'){
      if(B->grille[x-1][y-1]=='X' || B->grille[x-1][y-1]=='.'|| B->grille[x-1][y-1]=='#'){
        verif_case(B,x-1,y-1,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x-1,y-1,nb_bat);
      }
    }
    if(B->grille[x-1][y+1]=='O' || B->grille[x-1][y+1]=='.' || B->grille[x-1][y+1]=='X' || B->grille[x-1][y+1]=='#'){
      if(B->grille[x-1][y+1]=='.' || B->grille[x-1][y+1]=='X' || B->grille[x-1][y+1]=='#'){
        verif_case(B,x-1,y+1,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x-1,y+1,nb_bat);
      }
    }
    if(B->grille[x+1][y-1]=='O' || B->grille[x+1][y-1]=='.' || B->grille[x+1][y-1]=='#' || B->grille[x+1][y-1]=='X'){
      if(B->grille[x+1][y-1]=='.' || B->grille[x+1][y-1]=='#' || B->grille[x+1][y-1]=='X'){
        verif_case(B,x+1,y-1,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x+1,y-1,nb_bat);
      }
    }
    if(B->grille[x+1][y+1]=='O' || B->grille[x+1][y+1]=='X' || B->grille[x+1][y+1]=='.' || B->grille[x+1][y+1]=='#'){
      if(B->grille[x+1][y+1]=='X' || B->grille[x+1][y+1]=='.' || B->grille[x+1][y+1]=='#'){
        verif_case(B,x+1,y+1,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x+1,y+1,nb_bat);
      }
    }
    if(B->grille[x][y+1]=='O' || B->grille[x][y+1]=='.' || B->grille[x][y+1]=='X' || B->grille[x][y+1]=='#'){
      if(B->grille[x][y+1]=='.' || B->grille[x][y+1]=='X' || B->grille[x][y+1]=='#'){
        verif_case(B,x,y+1,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x,y+1,nb_bat);
      }
    }
    if(B->grille[x][y-1]=='O' || B->grille[x][y-1]=='.' || B->grille[x][y-1]=='#' || B->grille[x][y-1]=='X'){
      if(B->grille[x][y-1]=='.' || B->grille[x][y-1]=='#' || B->grille[x][y-1]=='X'){
        verif_case(B,x,y-1,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x,y-1,nb_bat);
      }
    }
    if(B->grille[x+1][y]=='O' || B->grille[x+1][y]=='X' || B->grille[x+1][y]=='.' || B->grille[x+1][y]=='#'){
      if(B->grille[x+1][y]=='X' || B->grille[x+1][y]=='.' || B->grille[x+1][y]=='#'){
        verif_case(B,x+1,y,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x+1,y,nb_bat);
      }
    }
    if(B->grille[x-1][y]=='O' || B->grille[x-1][y]=='X' || B->grille[x-1][y]=='.' || B->grille[x-1][y]=='#'){
      if(B->grille[x-1][y]=='X' || B->grille[x-1][y]=='.' || B->grille[x-1][y]=='#'){
        verif_case(B,x-1,y,nb_bat);
        miss++;
      }
      else{
        verif_case(B,x-1,y,nb_bat);
      }
    }
    if(miss==9){
      printf("\nVous avez raté vos 9 tirs\n");
    }
    else{
      printf("\nVous avez touché un de vos 9 tirs \n");
    }

}

void jeu(joueur *A,joueur *B){
  int x,y,d,h=1,tire_spec=0,choix_tire,tir_prec_touche=0, xia, yia;
  int verif;
  int une_fois =0 ;
  int nb_batA= A->nb_bat, nb_batB=B->nb_bat;
  int ia_touche = 0;
  int tab_tir_touche_ia[10][10];
  for (int v = 0 ;  v < 10 ;  v++) { // init du tableau à 0
    for (int w =0 ; w < 10 ;  w++){
      tab_tir_touche_ia[v][w]=0;
    }
  }

  while (A->nb_bat > 0 && B->nb_bat > 0) {
    if(h==1){
      do{
        printf("\nEntrez un x et y valide: \n");
        verif=scanf("%d %d",&x,&y);
      }
      while(x<0 || x>9 || y<0 || y>9 && verif==1);
      if(tire_spec==0){
        printf("choisissez un tire \n" );
        int repet=0;
        for(int v=0;v<A->nb_bat;v++){
          if(A->navires[v].vie >0 && A->navires[v].taille==5){
            printf("Tapez %d pour un tire carré: \n",A->navires[v].taille );
          }
          if(A->navires[v].vie >0 && A->navires[v].taille==4){
            printf("Tapez 1 pour un tire en forme de plus: \nTapez 2 pour un tire en croix: \n");
          }
          if(A->navires[v].vie >0 && A->navires[v].taille==3  && repet==0){
            printf("Tapez %d pour un tire en ligne: \n",A->navires[v].taille );
            repet++;
          }
        }
        scanf("%d",&choix_tire);
        if(choix_tire==5){
          tire_specialcarre(B,x,y,nb_batB);
          tire_spec=1;
        }
        if(choix_tire==1){
          tire_specialplus(B,x,y,nb_batB);
          tire_spec=1;
        }
        if(choix_tire==2){
          tire_specialcroix(B,x,y,nb_batB);
          tire_spec=1;
        }
        if(choix_tire==3){
          tire_specialligne(B,x,y,nb_batB);
          tire_spec=1;
        }
      }
      else{
        if(verif_case(B,x,y,nb_batB)){
          tire_spec=0;
          printf("\n                               Touché vous pourrez faire un tir spécial au tour suivant\n");
        }
        else{
          printf("\n                               Vous n'avez pas touché\n");
        }
      }
      h=0;
    }
    else{

      if(ia_touche == 0){
        do{
          xia=rand()%10;
          yia=rand()%10;
        }
        while(tab_tir_touche_ia[xia][yia]!= 0 );
        tab_tir_touche_ia[xia][yia]=1;
      }
      else{
        if (A->grille[xia+1][yia] == 'O' && une_fois ==0 ){
          verif_case_ia(A,xia+1,yia,nb_batA);
          xia++;
          une_fois = 1;
        }
        if (A->grille[xia-1][yia] == 'O' && une_fois ==0 ){
          verif_case_ia(A,xia-1 , yia,nb_batA);
          xia--;
          une_fois = 1;
        }
        if (A->grille[xia][yia+1] == 'O'&& une_fois ==0 ){
          verif_case_ia(A,xia, yia+1,nb_batA);
          yia++;
          une_fois = 1;
        }
        if (A->grille[xia][yia-1] == 'O' && une_fois ==0  ){
          verif_case_ia(A,xia , yia-1,nb_batA);
          yia--;
          une_fois = 1;
        }

        if (A->grille[xia+1][yia] != 'O' && A->grille[xia-1][yia] != 'O'&& A->grille[xia][yia+1] != 'O'&& A->grille[xia][yia-1] != 'O'  ){
          ia_touche = 0;
        }
        une_fois =0;
      }

      if (ia_touche == 0){

        if (verif_case_ia(A,xia , yia, nb_batA)){
          ia_touche = 1;
        }
        else{
        ia_touche = 0;
        }
      }

      h=1;
      affiche_grille(A->grille, B->grilleIA);

    }
  }
  if(A->nb_bat ==0){
    printf("l'IA a gagné \n");
  }
  else{
    printf("Vous avez gagné \n");
  }
}



int main(){
  srand(time(NULL));
  joueur *joueurA, *ia;
  joueurA=(joueur*)malloc(sizeof(joueur));
  ia=(joueur*)malloc(sizeof(joueur));
  init_grille(ia->grilleIA);
  init_grille(joueurA->grille);
  init_bateau(joueurA);
  placer_bateau(joueurA,joueurA->grille);
  init_grille(ia->grille);
  init_bateau(ia);
  placer_bateau(ia,ia->grille);
  affiche_grille(joueurA->grille, ia->grilleIA);
  jeu(joueurA,ia);
  return 0;
}
