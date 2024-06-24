#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
typedef struct Voiture{
  int idVoiture;
  char marque[15];
  char nomVoiture[15];
  char couleur[7];
  int nbplaces;
  int prixJour;
  char EnLocation[4];
}voiture;
/**********************************/
typedef struct date{
  int jour;
}date;
typedef struct contratLocation{
  float numContrat;
  int idVoiture;
  int idClient;
  date debut;
  date fin;
  int cout;
}contrat;
/*********************************/
typedef struct Client{
  int idClient;
  char nom[20];
  char prenom[20];
  int cin;
  char adresse[15];
  int telephone;
}client;
/**********************************************/
int retourMenu(){
  return 9;
}
/**********************************************/
int afficherListVoiture(){
  FILE *f;
  f=fopen("Voitures.bin","rb");
  fseek(f,0,SEEK_SET);
  if(!f){
    puts("ereur a l'ouverture de fichier");
  }
  else{
    voiture temp;
    int x=0;
    printf("\xba id voiture\t\xba marque\t\xba nom voiture\t\xba couleur\t\xba nb places\t\xba prix voiture\t\xba Enlocation\n");
    while(fread(&temp,sizeof(temp),1,f)){
      x=1;
      printf("\xba %d\t\t  %s\t\t  %s\t\t  %s\t\t  %d\t\t  %d\t\t  %s\n",temp.idVoiture,temp.marque,temp.nomVoiture,temp.couleur,temp.nbplaces,temp.prixJour,temp.EnLocation);
    }
    if(x==0){
      puts("il n'ya pas de voiture enregistrer\n");
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    }
    else{
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    }
  }
  fclose(f);
}
/*************************************************/
int ajouterNouvelVoiture(){
  voiture new;
  printf("\xc9\xcd\n");
  printf("\xba entrer id de voiture : ");scanf("%d",&new.idVoiture);
  printf("\xba entrer marque : ");scanf("%s",new.marque);
  printf("\xba entrer nom de voiture : ");scanf("%s",new.nomVoiture);
  printf("\xba entrer couleur : ");scanf("%s",new.couleur);
  printf("\xba entrer nombre de place : ");scanf("%d",&new.nbplaces);
  printf("\xba entrer prix par jour : ");scanf("%d",&new.prixJour);
  strcpy(new.EnLocation,"Non");
  printf("\xc8\xcd\n");
  printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  FILE *fichier=fopen("Voitures.bin","ab");
  fwrite(&new,sizeof(new),1,fichier);
  fclose(fichier);
}
/**************************************************************/
int modifierInfoVoiture(){
  int id,trouve=0;
  voiture temp;
  printf("l 'id des voiture qui sont enregistrer : \n");
  FILE *fichier=fopen("Voitures.bin","rb");
  fseek(fichier,0,SEEK_SET);
  int i=0;
  printf("\xc9\n");
  while(fread(&temp,sizeof(temp),1,fichier)){
    i++;
    printf("\xba\tvoiture nom : %s ==> id : %d\n",temp.nomVoiture,temp.idVoiture);
  }
  printf("\xc8\n");
  if(i==0){
    printf("il n'ya pas de voiture a modifier\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  printf("entre l'id de voiture que tu veut modifier ses information : ");
  scanf("%d",&id);
  fseek(fichier,0,SEEK_SET);
  int taille=i;
  voiture current[taille];
  i=0;
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
  fclose(fichier);
  while(trouve == 0 && i<taille){
    if(current[i].idVoiture == id){
      trouve=1;
      printf("\xc9\xcd\n");
      printf("\xba entrer nouveau id : "),scanf("%d",&current[i].idVoiture);
      printf("\xba entrer nouveau marque : "),scanf("%s",current[i].marque);
      printf("\xba entrer nouveau nom : "),scanf("%s",current[i].nomVoiture);
      printf("\xba entrer nouveau couleur : "),scanf("%s",current[i].couleur);
      printf("\xba entrer nouveau nombre de place : "),scanf("%d",&current[i].nbplaces);
      printf("\xba entrer nouveau prixJour : "),scanf("%d",&current[i].prixJour);
      printf("\xc8\xcd\n");
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
      fichier=fopen("voitures.bin","wb+");
      fwrite(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
      fclose(fichier);
    }
    i++;
  }
  if(trouve == 0){
    printf("il n'exist pas voiture avec ce id : %d\n",id);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
}
/*************************************************************/
int supprimerVoiture(){
  voiture temp;
  printf("l 'id des voiture qui sont enregistrer : \n");
  FILE *fichier=fopen("Voitures.bin","rb");
  int i=0;
  printf("\xc9\n");
  while(fread(&temp,sizeof(temp),1,fichier)){
    i++;
    printf("\xba\tvoiture nom : %s ==> id : %d\n",temp.nomVoiture,temp.idVoiture);
  }
  printf("\xc8\n");
  if(i==0){
    printf("il n'y a pas de voiture a supprimer\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  int id;
  printf("entrer l'id de voiture que tu veux supprimer : ");
  scanf("%d",&id);
  fseek(fichier,0,SEEK_SET);
  int taille=i;
  voiture current[taille];
  i=0;
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
  fclose(fichier);
  fichier=fopen("Voitures.bin","wb+");
  i=0;
  int trouve=0;
  while(i<taille){
    if(current[i].idVoiture == id){
      i++;
      trouve=1;
    }
    else{
      fwrite(&current[i],sizeof(current[0]),1,fichier);
      i++;
    }
  }
  if(trouve==0){
    printf("il n'exist pas de voiture avec ce id : %d\n",id);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else{
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  fclose(fichier);
}
/***********************************************************/
int (* gestionVoiture[5])(void)={afficherListVoiture,ajouterNouvelVoiture,modifierInfoVoiture,supprimerVoiture,retourMenu};
/***********************************************************/
int (* MenuGestionVoiture(void))(void){
  int choix;
  printf("\n\n\n\n\n");
  printf("\033[1;34m\t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
  printf("\t\t\t\t\xba\t Gestion des voiture \t    \xba\n");
  printf("\t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n\n");
  printf("\t\t\033[0;34m\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
  printf("\t\t\xba\tListe des voitures...............................1     \xba\n");
  printf("\t\t\xba\tAjouter voiture..................................2     \xba\n");
  printf("\t\t\xba\tModifier voiture.................................3     \xba\n");
  printf("\t\t\xba\tSupprimer voiture................................4     \xba\n");
  printf("\t\t\xba\tRetour...........................................5     \xba\n");
  printf("\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n");
  printf("\t\t\t\tvotre choix : ");  
  do{
    scanf("%d",&choix);
  }while(choix>5 || choix<1);
  return gestionVoiture[choix-1];
}
/*********************************************************
 * ************************************************************
 * *************************************************************/
int afficherListClient(){
  FILE *f;
  f=fopen("Clients.bin","rb");
  fseek(f,0,SEEK_SET);
  if(!f){
    puts("ereur a l'ouverture de fichier");
  }
  else{
    client temp;
    int x=0;
    printf("\xba id client\t\xba nom\t\t\xba prenom\t\xba cin\t\t\xba adresse\t\xba telephone\t\n");
    while(fread(&temp,sizeof(temp),1,f)){
      x=1;
      printf("\xba %d\t\t  %s\t\t  %s\t\t  %d\t\t  %s\t\t  %d\n",temp.idClient,temp.nom,temp.prenom,temp.cin,temp.adresse,temp.telephone);
    }
    if(x==0){
      puts("il n'ya pas de client enregistrer\n");
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    }
    else{
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    }
  }
  fclose(f);
}
/*************************************************/
int ajouterNouvelClient(){
  client new;
  printf("\xc9\xcd\n");
  printf("\xba entrer id de client : ");scanf("%d",&new.idClient);
  printf("\xba entrer nom : ");scanf("%s",new.nom);
  printf("\xba entrer prenom : ");scanf("%s",new.prenom);
  printf("\xba entrer cin : ");scanf("%d",&new.cin);
  printf("\xba entrer adresse : ");scanf("%s",new.adresse);
  printf("\xba entrer numero de telephone : ");scanf("%d",&new.telephone);
  printf("\xc8\xcd\n");
  printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  FILE *fichier=fopen("Clients.bin","ab");
  fwrite(&new,sizeof(new),1,fichier);
  fclose(fichier);
}
/**************************************************************/
int modifierInfoClient(){
  int id,trouve=0;
  client temp;
  printf("l 'id des clients qui sont enregistrer : \n");
  FILE *fichier=fopen("Clients.bin","rb");
  fseek(fichier,0,SEEK_SET);
  int i=0;
  printf("\xc9\n");
  while(fread(&temp,sizeof(temp),1,fichier)){
    i++;
    printf("\xba\tclient nom : %s ==> id : %d\n",temp.nom,temp.idClient);
  }
  printf("\xc8\n");
  if(i==0){
    printf("il n'ya pas de client a modifier\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  printf("entre l'id de client que tu veut modifier ses information : ");
  scanf("%d",&id);
  fseek(fichier,0,SEEK_SET);
  int taille=i;
  client current[taille];
  i=0;
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
  fclose(fichier);
  while(trouve == 0 && i<taille){
    if(current[i].idClient == id){
      trouve=1;
      printf("\xc9\xcd\n");
      printf("\xba entrer nouveau id : "),scanf("%d",&current[i].idClient);
      printf("\xba entrer nouveau nom : "),scanf("%s",current[i].nom);
      printf("\xba entrer nouveau prenom : "),scanf("%s",current[i].prenom);
      printf("\xba entrer nouveau cin : "),scanf("%d",&current[i].cin);
      printf("\xba entrer nouveau adresse : "),scanf("%s",current[i].adresse);
      printf("\xba entrer nouveau telephone : "),scanf("%d",&current[i].telephone);
      printf("\xc8\xcd\n");
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
      fichier=fopen("Clients.bin","wb+");
      fwrite(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
      fclose(fichier);
    }
    i++;
  }
  if(trouve == 0){
    printf("il n'exist pas client avec ce id : %d\n",id);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
}
/*************************************************************/
int supprimerClient(){
  client temp;
  printf("l 'id des clients qui sont enregistrer : \n");
  FILE *fichier=fopen("Clients.bin","rb");
  int i=0;
  printf("\xc9\n");
  while(fread(&temp,sizeof(temp),1,fichier)){
    i++;
    printf("\xba\tclient nom : %s ==> id : %d\n",temp.nom,temp.idClient);
  }
  printf("\xc8\n");
  if(i==0){
    printf("il n'y a pas de client a supprimer\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  int id;
  printf("entrer l'id de client que tu veux supprimer : ");
  scanf("%d",&id);
  fseek(fichier,0,SEEK_SET);
  int taille=i;
  client current[taille];
  i=0;
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
  fclose(fichier);
  fichier=fopen("Clients.bin","wb+");
  i=0;
  int trouve=0;
  while(i<taille){
    if(current[i].idClient == id){
      i++;
      trouve=1;
    }
    else{
      fwrite(&current[i],sizeof(current[0]),1,fichier);
      i++;
    }
  }
  if(trouve==0){
    printf("il n'exist pas de client avec ce id : %d\n",id);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else{
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  fclose(fichier);
}
/***********************************************************/
int (* gestionClient[5])(void)={afficherListClient,ajouterNouvelClient,modifierInfoClient,supprimerClient,retourMenu};
/***********************************************************/
int (* MenuGestionClients(void))(void){
  int choix;
  printf("\n\n\n\n\n");
  printf("\033[1;35m\t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
  printf("\t\t\t\t\xba\t Gestion des clients \t    \xba\n");
  printf("\t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n\n");
  printf("\t\t\033[0;35m\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
  printf("\t\t\xba\tListe des clients................................1     \xba\n");
  printf("\t\t\xba\tAjouter client...................................2     \xba\n");
  printf("\t\t\xba\tModifier client..................................3     \xba\n");
  printf("\t\t\xba\tSupprimer client.................................4     \xba\n");
  printf("\t\t\xba\tRetour...........................................5     \xba\n");
  printf("\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n");
  printf("\t\t\t\tvotre choix : ");  
  do{
    scanf("%d",&choix);
  }while(choix>5 || choix<1);
  return gestionClient[choix-1];
}
/*************************************************************************************
 * ************************************************************************************
 * *********************************************************************************************/
int visualiserContrat(){
  FILE *fichier=fopen("ContratsLocations.bin","rb");
  int taille,i=0,trouve=0;
  float choix;
  contrat temp;
  while(fread(&temp,sizeof(temp),1,fichier)){
    i++;
  }
  if(i==0){
    printf("il n'y a pas de contrat enregistrer\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  taille=i;
  contrat current[taille];
  fseek(fichier,0,SEEK_SET);
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
  fclose(fichier);
  printf("les numero des contrats qui existes : \n");
  printf("\xc9\xcd\n");
  for(i=0;i<taille;i++){
    printf("\xba\tnumero de contrat ==> %.2f\n",current[i].numContrat);
  }
  printf("\xc8\xcd\n");
  printf("entrer le numero de contrat que tu veut afficher : ");
  scanf("%f",&choix);
  i=-1;
  do{
    i++;
    if(current[i].numContrat == choix){
      trouve=1;
    }
  }while(trouve == 0 && i < taille);
  if(trouve == 1){
    printf("\xc9\xcd\n");
    printf("\xba\t\t\t contrat numero %.2f\n",current[i].numContrat);
    printf("\xba\t idVoiture : %d\n",current[i].idVoiture);
    printf("\xba\t idClient : %d\n",current[i].idClient);
    printf("\xba\t date debut : %d\n",current[i].debut.jour);
    printf("\xba\t date fin : %d\n",current[i].fin.jour);
    printf("\xba\t cout : %d\n",current[i].cout);
    printf("\xc8\xcd\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else{
    printf("il n'y a pas un contrat avec ce numero : %.2f\n",choix);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
}
/***********************************************************/
int louerVoiture(){
  char nom[20],prenom[20];
  int idVoiture;
  printf("entrer votre nom : ");scanf("%s",nom);
  printf("entrer votre prenom : ");scanf("%s",prenom);
  printf("entre l'id de voiture que tu veut louer : ");scanf("%d",&idVoiture);
  FILE *fichier1,*fichier2;
  int trouve1=0,trouve2=0;
  voiture temp1;
  int i=0,tailleV,tailleC;
  fichier1 = fopen("Voitures.bin","rb");
  while(fread(&temp1,sizeof(temp1),1,fichier1)){
    i++;
  }
  tailleV=i;
  voiture currentV[tailleV];
  fseek(fichier1,0,SEEK_SET);
  fread(currentV,sizeof(currentV[0]),sizeof(currentV)/sizeof(currentV[0]),fichier1);
  fclose(fichier1);
  i=0;
  fichier2 = fopen("Clients.bin","rb");
  client temp2;
  while(fread(&temp2,sizeof(temp2),1,fichier2)){
    i++;
  }
  tailleC=i;
  client currentC[tailleC];
  fseek(fichier2,0,SEEK_SET);
  fread(currentC,sizeof(currentC[0]),sizeof(currentC)/sizeof(currentC[0]),fichier2);
  fclose(fichier2);
  i=0;
  while(i<tailleV && trouve1==0){
    if(currentV[i].idVoiture == idVoiture){
      trouve1=i+1;
    }
    else i++;
  }
  i=0;
  while(i<tailleC && trouve2==0){
    if(strcmp(currentC[i].nom,nom)==0 && strcmp(currentC[i].prenom,prenom)==0){
      trouve2=i+1;
    }
    else i++;
  }
  if(trouve1==0 && trouve2==0){
    printf("\xc9\xcd\n");
    printf("\xba\tle client %s :: %s ne se trouve pas\n",nom,prenom);
    printf("\xba\taussi la voiture d'id %d ne se trouve pas\n",idVoiture);
    printf("\xba\tallez au menu principal / gestion client et gestion voiture pour saisir ces information\n");
    printf("\xc8\xcd\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else if(trouve1 == 0 && trouve2 != 0){
    printf("\xc9\xcd\n");
    printf("\xba\tla voiture d'id %d ne se trouve pas\n",idVoiture);
    printf("\xba\tallez au menu principal / gestion voiture pour saisir ces information\n");
    printf("\xc8\xcd\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else if(trouve1 != 0 && trouve2 == 0){
    printf("\xc9\xcd\n");
    printf("\xba\tle client %s :: %s ne se trouve pas\n",nom,prenom);
    printf("\xba\tallez au menu principal / gestion clients pour saisir ces information\n");
    printf("\xc8\xcd\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else{
    if(strcmp(currentV[trouve1-1].EnLocation,"Oui")==0){
      printf("cette voiture est deja louee par une autre personne\n");
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    }
    else{
      fichier1 = fopen("Voitures.bin","wb+");
      strcpy(currentV[trouve1-1].EnLocation,"Oui");
      fwrite(currentV,sizeof(currentV[0]),sizeof(currentV)/sizeof(currentV[0]),fichier1);
      fclose(fichier1);
      fichier2 = fopen("ContratsLocations.bin","ab");
      contrat new;
      new.idVoiture = idVoiture;
      new.idClient  = currentC[trouve2-1].idClient;
      printf("\xc9\xcd\n");
      printf("\xba\tentrer numero de contrat : ");scanf("%f",&new.numContrat);
      printf("\xba\tle jour de debut == 1 \n");
      new.debut.jour=1;
      do{
        printf("\xba\tentrer le jour de fin : ");scanf("%d",&new.fin.jour);
      }while(new.debut.jour > new.fin.jour);
      int coute;
      coute = new.fin.jour;
      new.cout = coute * currentV[trouve1-1].prixJour;
      printf("\xba\tle prix totale est %d * %d = %d\n",coute,currentV[trouve1-1].prixJour,new.cout);
      printf("\xc8\xcd\n");
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
      fwrite(&new,sizeof(new),1,fichier2);
      fclose(fichier2);
    }
  }
}
/********************************************************************************/
int retournerVoiture(){
  FILE *fichier1;
  fichier1 = fopen("ContratsLocations.bin","rb");
  int i=0;
  contrat temp;
  while(fread(&temp,sizeof(temp),1,fichier1)){
    i++;
  }
  if(i==0){
    printf("il n'y a pas de contrat enregistrer \n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  contrat current[i];
  fseek(fichier1,0,SEEK_SET);
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier1);
  fclose(fichier1);
  int taille=i;
  printf("les numero de contrat existant : \n");
  printf("\xc9\xcd\n");
  for(i=0;i<taille;i++){
    printf("\xba\tnumero contrat : %f\n",current[i].numContrat);
  }
  printf("\xc8\xcd\n");
  float choix;
  printf("entrer votre numero de contrat : ");
  scanf("%f",&choix);
  int trouve=0;
  i=0;
  while(i<taille && trouve==0){
    if(current[i].numContrat == choix){
      trouve=1;
    }
    else{
      i++;
    }
  }
  if(trouve == 0){
    printf("il n'exist pas ce numero de contrat : %f\n",choix);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else{
    fichier1 = fopen("Voitures.bin","rb");
    voiture v;
    int j=0,tailleV;
    while(fread(&v,sizeof(v),1,fichier1)){
      j++;
    }
    tailleV=j;
    voiture vt[tailleV];
    fseek(fichier1,0,SEEK_SET);
    fread(vt,sizeof(vt[0]),sizeof(vt)/sizeof(vt[0]),fichier1);
    fclose(fichier1);
    j=0;
    while(vt[j].idVoiture != current[i].idVoiture){
      j++;
    }
    strcpy(vt[j].EnLocation,"Non");
    fichier1=fopen("Voitures.bin","wb+");
    fwrite(vt,sizeof(vt[0]),sizeof(vt)/sizeof(vt[0]),fichier1);
    fclose(fichier1);
    printf("\n\n\n\t\t\t (press any key)");
    getch();
    system("cls");
  }
}
/********************************************************/
int modifierContrat(){
  FILE *fichier1;
  fichier1 = fopen("ContratsLocations.bin","rb");
  int i=0;
  contrat temp;
  while(fread(&temp,sizeof(temp),1,fichier1)){
    i++;
  }
  if(i==0){
    printf("il n'y a pas de contrat enregistrer \n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  contrat current[i];
  fseek(fichier1,0,SEEK_SET);
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier1);
  fclose(fichier1);
  int taille=i;
  printf("les numero de contrat existant : \n");
  printf("\xc9\xcd\n");
  for(i=0;i<taille;i++){
    printf("\xba\tnumero contrat : %f\n",current[i].numContrat);
  }
  printf("\xc8\xcd\n");
  float choix;
  printf("entrer le numero de contrat que tu veut changer ses info : ");
  scanf("%f",&choix);
  int trouve=0;
  i=0;
  while(i<taille && trouve==0){
    if(current[i].numContrat == choix){
      trouve=1;
      printf("\xc9\xcd\n");
      printf("\xba\tentrer nouveau date de retour : ");
      do{
        scanf("%d",&current[i].fin.jour);
      }while(current[i].debut.jour >= current[i].fin.jour);
      fichier1 = fopen("Voitures.bin","rb");
      int j=0,taille;
      voiture v;
      while(fread(&v,sizeof(v),1,fichier1)){
        j++;
      }
      taille=j;
      voiture vt[taille];
      fseek(fichier1,0,SEEK_SET);
      fread(vt,sizeof(vt[0]),sizeof(vt)/sizeof(vt[0]),fichier1);
      fclose(fichier1);
      j=0;
      while(j<taille && current[i].idVoiture != vt[j].idVoiture){
        j++;
      }
      current[i].cout = current[i].fin.jour * vt[j].prixJour;
      printf("\xba\tnouveau prix %d * %d = %d\n",current[i].fin.jour,vt[j].prixJour,current[i].cout);
      printf("\xc8\xcd\n");
      fichier1 = fopen("ContratsLocations.bin","wb+");
      fwrite(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier1);
      fclose(fichier1);
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    }
    else{
      i++;
    }
  }
  if(trouve == 0){
    printf("il n'y a pas ce numero de contrat %f\n",choix);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
}
/********************************************************/
int supprimerContrat(){
  FILE *fichier=fopen("ContratsLocations.bin","rb");
  int taille,i=0,trouve=0;
  float choix;
  contrat temp;
  while(fread(&temp,sizeof(temp),1,fichier)){
    i++;
  }
  if(i==0){
    printf("il n'y a pas de contrat enregistrer\n");
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    return 0;
  }
  taille=i;
  contrat current[taille];
  fseek(fichier,0,SEEK_SET);
  fread(current,sizeof(current[0]),sizeof(current)/sizeof(current[0]),fichier);
  fclose(fichier);
  printf("les numero des contrats qui existes : \n");
  printf("\xc9\xcd\n");
  for(i=0;i<taille;i++){
    printf("\xba\tnumero de contrat ==> %.2f\n",current[i].numContrat);
  }
  printf("\xc8\xcd\n");
  printf("entrer le numero de contrat que tu veut supprimer : ");
  scanf("%f",&choix);
  i=-1;
  do{
    i++;
    if(current[i].numContrat == choix){
      trouve=1;
    }
  }while(trouve == 0 && i < taille);
  if(trouve==0){
    printf("\til n'ya a pas ce numero de contrat : %.2f\n",choix);
    printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
  }
  else{
    FILE *fichier1;
    voiture temp1;
    fichier1 = fopen("Voitures.bin","rb");
    int j=0,tailleV;
    while(fread(&temp1,sizeof(temp1),1,fichier1)){
      j++;
    }
    tailleV=j;
    voiture currentV[tailleV];
    fseek(fichier1,0,SEEK_SET);
    fread(currentV,sizeof(currentV[0]),sizeof(currentV)/sizeof(currentV[0]),fichier1);
    fclose(fichier1);
    trouve=0;j=0;
    while(j<tailleV && trouve==0){
      if(currentV[j].idVoiture == current[i].idVoiture){
        trouve=1;
      }
      else{
        j++;
      }
    }
    if(strcmp(currentV[j].EnLocation,"Oui")==0){
      printf("la voiture est deja louee \n");
      printf("\n\n\n\t\t\t (press any key)");getch();system("cls");
    }
    else{
      fichier1 = fopen("ContratsLocations.bin","wb+");
      j=0;
      while(j<taille){
        if(j==i){
          j++;
        }
        else{
          fwrite(&current[j],sizeof(current[j]),1,fichier1);
        }
      }
      fclose(fichier1);
    }
  }
}
/**********************************************************/
int (* location[6])(void)={visualiserContrat,louerVoiture,retournerVoiture,modifierContrat,supprimerContrat,retourMenu};
/******************************************************************/
int (* MenuGestionLocation(void))(void){
  int choix;
  printf("\n\n\n\n\n");
  printf("\033[1;31m\t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
  printf("\t\t\t\t\xba\t Location d'une voiture \t  \xba\n");
  printf("\t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n\n");
  printf("\t\t\033[0;31m\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
  printf("\t\t\xba\tVisualiser contrat...............................1     \xba\n");
  printf("\t\t\xba\tLouer voiture....................................2     \xba\n");
  printf("\t\t\xba\tRetourner voiture................................3     \xba\n");
  printf("\t\t\xba\tModifier contrat.................................4     \xba\n");
  printf("\t\t\xba\tSupprimer contrat................................5     \xba\n");
  printf("\t\t\xba\tRetour...........................................6     \xba\n");
  printf("\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n");
  printf("\t\t\t\tvotre choix : ");  
  do{
    scanf("%d",&choix);
  }while(choix>6 || choix<1);
  return location[choix-1];
}
/********************************************************************************/
void menuPrincipale(){
  int choix,retour;
  do{
    printf("\n\n\n\n\n");
    printf("\033[1;33m\t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
    printf("\t\t\t\t\xba\t Menu Principal \t    \xba\n");
    printf("\t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n\n");
    printf("\033[1;31m\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
    printf("\t\t\xba\tLocation.........................................1     \xba\033[0m\n");
    printf("\033[1;34m\t\t\xba\tGestion Voitures.................................2     \xba\n\033[0m ");
    printf("\033[1;35m\t\t\xba\tGestient Clients.................................3     \xba\n\033[0m ");
    printf("\033[1;32m\t\t\xba\tQuitter..........................................4     \xba\n");
    printf("\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\033[0m\n");
    printf("\t\t\t\tvotre choix : ");  
    do{
      scanf("%d",&choix);
    }while(choix<1 || choix>4);
    system("cls");
    if(choix == 1){
      do{
        retour = -1;
        int (* menuLocation)();
        menuLocation=MenuGestionLocation();   
        retour=(* menuLocation)();   
        system("cls");
      }while(retour != 9);
    }
    if(choix == 2){
      do{
        retour = -1;
        int (* menuVoiture)();
        menuVoiture=MenuGestionVoiture();   
        retour=(* menuVoiture)();   
        system("cls");
      }while(retour != 9);
    }
    else if(choix == 3){
      do{
        retour = -1;
        int (* menuClients)();
        menuClients=MenuGestionClients();   
        retour=(* menuClients)();  
        system("cls"); 
      }while(retour != 9);
    }
  }while(choix != 4);
}
/***********************************************/
void timeFun(char txt[]){
  time_t currentTime;
  struct tm *m = localtime(&currentTime);
  printf("\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb\n");
  printf("\xba\t\tdate  %s : \t\t%i / %02i / %i\t\t\xba\n\xba\t\ttime %s : \t\t%02d : %02d : %02d\t\t\xba\n",txt,m->tm_mday,m->tm_mon+1,1900+m->tm_year,txt,m->tm_hour,m->tm_min,m->tm_sec);
  printf("\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc\n");
  printf("\n\n\n\t\t\t (press any key to continue)");
  getch();
  system("cls");
}
/********************************************/
int main(int argc,char const *argv[]){
  system("cls");
  timeFun("debut");
  system("cls");
  system("cls");
  menuPrincipale();
  timeFun("fin..");
  return 0;
}
