/*********************************************
Qian Zhang June 5, 2009
Updated program to make it compile and run.
Header changed, %ld and %lf changed to %d and %f, and removed "typedef" from "typedef struct info".


Catherine Bourgain 12/1/2003 
  Computes inbreeding and kinship coefficients for pedigrees using KARIGL algorithm (1981,Ann. Hum Genet 45:299-305)
  Usage : ./KinInbcoef pedigreefile listname outputfile
where 
- pedigreefile has 4 col. Fam indId fatherId motherId
- listname is a file with the list of the individuals for whom computation of the coefficients is required. Should have 2 columns : Fam indId
- outputfile has four col: Fam Id1 Id2 kinship/inbreeding coef
for all possible pairs of indiv listed in the listname file

Inbreeding and Kinship coefficients are computed only for individuals from the same family.

MAXFAM is the maximum number of families to be analyzed at the same time. Can be changed
MAXIND is the maximum number of individuals in each family for whom inbreeding/kinship coefficients are to be computed. Can be changed.

g++ should be used for compilation (to allow use of map class)
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;

#define MAXFAM 100
#define MAXIND 1000
typedef struct data {
  int father;
  int mother;
  int generation;
}parents;

struct info {
 map<int,parents> ped;
 int Nsize;   
};

struct info Global[MAXFAM+1];
void check(long *x, long *y,int boolfix);
void create_generation(int fam,struct info *Global);
double phi2(int i, int j,int fam);
int make_generation(int ind,int per,int mer,struct info G);


int keep[MAXFAM+1];
int list[MAXFAM+1][MAXIND+1];
int  i,j,F,fam=0;
FILE *infile;
FILE *listfile;
FILE *outfile;
map<int,parents>::iterator iter,iterend;

int main(int argc, char *argv[])
{
  int NbInd=0,Nblist=0;
  int famold=1;

  if (argc!=4) {
    printf("wrong usage. Should be ./idcoef pedfile listfile outfile\n");
    exit(1);}

  if ((infile=fopen(argv[1],"r"))==NULL)
   {printf("Can't open pedigree file\n");
   exit(1);}

  if ((listfile=fopen(argv[2],"r"))==NULL)
   {printf("Can't open file with the list of individuals\n");
   exit(1);}

    if ((outfile=fopen(argv[3],"w"))==NULL)
   {printf("Can't open outfile\n");
   exit(1);}

for (fam=1;fam<=MAXFAM;fam++) Global[fam].Nsize=0;
   
    NbInd++;
    fscanf(infile,"%d ",&fam);  
    fscanf(infile, "%d", &i);
    Global[fam].Nsize++;
    Global[fam].ped[i].mother=0;
    Global[fam].ped[i].father=0;
	Global[fam].ped[i].generation=0;
    fscanf(infile,"%d%d\n", &Global[fam].ped[i].father, &Global[fam].ped[i].mother);   

  while (!feof(infile)) {
     fscanf(infile,"%d ",&fam);
     if (fam>MAXFAM) {
       printf("number of families exceeds the maximum.\n Change the value of MAXFAM in the source file and recompile\n");
       exit(1);
   }

     if (fam!=famold) {
	 if  (fam!=(famold+1)) {printf("families should have following Id's from 1 to F\n\n");
	     exit(1);}
	 else 
	     famold=fam;
	     
	    	 
     }
   Global[fam].Nsize++;
   if (Global[fam].Nsize>MAXIND) {
	printf("number of individuals in family %d exceeds the maximum.\n Change the value of MAXIND in the source file and recompile\n",fam);
		 exit(1);
	     }

   NbInd++;  
   
    fscanf(infile, "%d", &i);
    Global[fam].ped[i].mother=0;
    Global[fam].ped[i].father=0;
Global[fam].ped[i].generation=0;

    fscanf(infile,"%d%d\n", &Global[fam].ped[i].father, &Global[fam].ped[i].mother);   

      }    

 	  
   F=famold;

   fclose(infile);

   
   for (fam=1;fam<=F;fam++)
   {
      create_generation(fam,Global);
      keep[fam]=0;
      for (j=0;j<=Global[fam].Nsize;j++)
	  list[fam][j]=0;
  }
  
  while (!feof(listfile)) {
      fscanf(listfile,"%d\n",&fam);
      fscanf(listfile,"%d\n",&i);
      if (Global[fam].ped.find(i)==Global[fam].ped.end()) 
	  printf("Individual %d not in pedigree file...\n Skipped\n",i);
      else {
	  Nblist++;
	  if (Nblist<=NbInd)
	  {
	      keep[fam]++;
	      list[fam][keep[fam]-1]=i;
	  }
	  else {
	      printf("too many individuals in the list file\n");
	      exit(1);
	  }
	  
      }
  }

  
   for (fam=1;fam<=F;fam++)
       if (keep[fam]>0)
       {
  	for (i=0;i<=keep[fam]-1;i++) 
	{  

	    fprintf(outfile,"%d %d %d %f\n",fam,list[fam][i],list[fam][i],phi2(Global[fam].ped[list[fam][i]].father,Global[fam].ped[list[fam][i]].mother,fam));
    for (j=i+1;j<=keep[fam]-1;j++)
    {
    fprintf(outfile,"%d %d %d %f\n",fam,list[fam][i],list[fam][j],phi2(list[fam][i],list[fam][j],fam));
    }  
	}
       }
}

/*----------------------------------*/

void check(int *x, int *y,int fam)
{
    int z;

if (Global[fam].ped[*x].generation>=Global[fam].ped[*y].generation)
    return;
    else
    	{
		z = *x;
		*x = *y;
		*y = z;
    	}
}
/*------------------------------------- */
double phi2(int i, int j,int fam)
{

  if (i * j == 0)
  {         return 0.0;
  }
  else if (i == j)
  {    return ((1 + phi2(Global[fam].ped[i].father, Global[fam].ped[i].mother,fam)) / 2);

  }
  else {
      check(&i, &j,fam);
    return ((phi2(Global[fam].ped[i].father, j,fam) + phi2(Global[fam].ped[i].mother, j,fam)) / 2);

  }
}

/*--------------------------------------*/
void create_generation(int fam,struct info *Global)
{
    int i=0,per=0,mer=0,generation=0,pas=0,ind=0;
    map<int,parents>::iterator iter,iterend;

    iter=Global[fam].ped.begin();
    iterend=Global[fam].ped.end();
    
    while (iter!=iterend)
    {
	
	ind=iter->first;
	per=iter->second.father;
	mer=iter->second.mother;

	if (iter->second.generation==0)
	{ 	
	    iter->second.generation=make_generation(ind,per,mer,Global[fam]);
	}
	++iter;
    }
}
/*  -------------------------------------  */
int make_generation(int ind,int per,int mer,struct info G)
{ 

    if (per!=0 && G.ped[per].generation==0)
	G.ped[per].generation=make_generation(per,G.ped[per].father,G.ped[per].mother,G);
    if (mer!=0 && G.ped[mer].generation==0)
	G.ped[mer].generation=make_generation(mer,G.ped[mer].father,G.ped[mer].mother,G);

    if (per==0 && mer==0)
    	return(1);
    
    else {
	if (G.ped[per].generation>=G.ped[mer].generation)
	    return(G.ped[per].generation+1);

	else return(G.ped[mer].generation+1);
    }

}
