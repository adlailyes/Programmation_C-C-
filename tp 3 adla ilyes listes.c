#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct et *pet;
typedef struct sp *psp;
typedef struct dep *pdep;
typedef struct fac *pfac;
typedef struct t *pt;
typedef struct et {pet suivant ;
                    char val[30];
                   
}et;
typedef struct sp {psp suivant ;
                  char val[30];
                   pet precedent;
}sp;
typedef struct dep {pdep suivant;
                    char val[30];
                    psp precedent ;
}dep;
typedef struct fac {pfac suivant ;
                    char val[30];
                    pdep precedent;
}fac;
typedef struct t {pt suivant ;
                 char val[30];
                  pfac precedent;
}t;

void creer_univ (pt *ptr)
{
	printf("creation UNIV\n");
	(*ptr)=(pt)malloc(sizeof(struct t));
	(*(*ptr)).suivant=NULL;
	(*(*ptr)).precedent=NULL;
    printf("entrer le nom de l universite\n");
	scanf ("%s",&((*(*ptr)).val));
    printf ("la creation de %s est terminer\n",(*(*ptr)).val);
    printf("\n________________________________________________________________\n");
}
void creer_fac (pt *ptr,pfac *pred1 ) 
{
	pfac x;
    printf("creation FAC\n");
	printf ("il faut cree d\'abord UNIV\n");
	if (ptr != NULL){
	x=(pfac)malloc(sizeof(struct fac));
	printf("entrer le nom de la faculte\n");
	scanf("%s",&((*x).val));
	(*x).suivant=NULL;
	(*x).precedent=NULL;
	if ((*(*ptr)).precedent==NULL) { (*(*ptr)).precedent=x;
	                                 (*pred1)=x;
	                               } 
    else { (*(*pred1)).suivant=x;
           (*pred1)=x;  
	}
     printf("la creation de %s est termine\n",(*x).val);
     printf("l\'universite: %s",(*(*ptr)).val);
     printf("| FAC: %s",(*x).val);
     printf("\n________________________________________________________________\n");
}
else printf("creer d\'abord UNIV \n");

}

void creer_departement (pt ptr,pdep *pred2)
{
	
	char rep[30];
	pdep y;
	pfac x;
	printf("creation departement\n");
	printf("il faut d'abord cree UNIV et FAC\n");
	if ( ptr != NULL)
	{
	printf("entrer le nom de la faculte\n");
	scanf("%s",&rep);
	x=(*ptr).precedent;
	while ((x != NULL) && (strcmp((*x).val,rep)!=0)){x=(*x).suivant;}
	if (x==NULL){ printf("votre faculte n\'existe pas\n");}
	else { y=(pdep)malloc(sizeof( struct dep));
	       printf("entrer le nom de departement\n");
		   scanf("%s",&((*y).val));
	      (*y).suivant=NULL;
	      (*y).precedent=NULL;
	      if((*x).precedent==NULL) { (*x).precedent=y;
		                              (*pred2)=y;}
           	else { (*(*pred2)).suivant=y;
           	(*pred2)=y;
			   }
	  printf("la creation de %s est termine\n",(*y).val);
      printf("l\'universite: %s",(*ptr).val);     
      printf("  |FAC: %s",(*x).val);
      printf("  | dep: %s",(*y).val);
	}
	
   }else printf ("UNIV n\'existe pas\n");

printf("\n________________________________________________________________\n");	
}


void creer_specialite (pt ptr,psp *pred3)
{
	pfac x;
	pdep y;
	psp z;
	char nom1[30],nom2[30];
    printf("creation specialite\n");
	printf("il faut d\'abord cree UNIV FAC et departement\n");
if (ptr!= NULL)
{
	printf("entrer le nom de la fac\n");
	scanf("%s",&nom1);
	x=(*ptr).precedent;
	while ((x!=NULL) && (strcmp((*x).val, nom1) != 0)) { x=(*x).suivant;}
	if (x == NULL) { printf("votre fac n\'existe pas\n");}
    else
	{ printf("entrer le nom de departement\n");
	  scanf("%s",&nom2);
	  y=(*x).precedent;
	  while( (y != NULL) && (strcmp((*y).val,nom2) != 0)) { y=(*y).suivant;}
	  if(y == NULL) { printf("votre departement n\'existe pas\n");}
	  else
	  {printf("entrer le nom de specialte\n");
		z=(psp)malloc(sizeof ( struct sp));
		scanf("%s",&((*z).val));
		(*z).suivant=NULL;
		(*z).precedent=NULL;
		if ((*y).precedent==NULL) { (*y).precedent=z;
		                            (*pred3)=z;}
	    else 
		{(*(*pred3)).suivant=z;
		(*pred3)=z;
		}
	     printf("la creation de %s est termine\n",(*z).val);
        printf("l\'universite: %s",(*ptr).val);
        printf(" |FAC: %s",(*x).val);
        printf("  | DEP: %s",(*y).val);
        printf("  | SP: %s",(*z).val);
    
	
	 } 
    
    }
    
	}
else printf ("UNV n\'existe pas\n");
 printf("\n________________________________________________________________\n");
}
  

	void creer_etudiant (pt ptr, pet *pred4)
	{
		pfac x;
		pdep y;
		psp z;
		pet k;
		char v[30],nom1[30],nom2[30],nom3[30];
	    printf("il faut d\'abord cree UNIV FAC et departement et specialite\n");
		if (ptr != NULL)
		{
		
		 printf("entrer le nom de la fac \n");
		 scanf("%s",&nom1);
	  	 x=(*ptr).precedent;
		 while ((x !=NULL) && (strcmp((*x).val,nom1) != 0)) { x=(*x).suivant;}
	    if (x== NULL) { printf ("votre fac n\'existe pas\n");}
	    else 
	    {
	    	printf("entrer le nom de departement\n");
	    	scanf("%s",&nom2);
	    	y=(*x).precedent;
	    	while ((y != NULL) && (strcmp((*y).val,nom2) != 0)) { y=(*y).suivant;}
			if (y == NULL) { printf("votre departement n\'existe pas\n");}                 
			else 
			{ printf ("entrer le nom de la specialite\n");
			 scanf("%s",&nom3);
			 z=(*y).precedent;
			 while ((z!=NULL) && (strcmp((*z).val,nom3) != 0)) { z=(*z).suivant;}
			if (z == NULL) {printf(" votre specialite n\'existe pas\n");}
			else 
			{ printf ("entrer le nom de l\'etudiant\n") ;
			 k =(pet)malloc(sizeof( struct et));
			 scanf("%s",&v);
			  strcpy((*k).val,v);
			 (*k).suivant=NULL;
			 if ((*z).precedent==NULL) { (*z).precedent=k;
			                             (*pred4)=k;}
			 else
			 {
			 	(*(*pred4)).suivant=k;
			 	(*pred4)=k;
			 }
		     	printf("la creation de %s est termine\n",(*k).val);
              printf("l\'universite: %s",(*ptr).val);
             printf(" |FAC: %s",(*x).val);
              printf("| DEP: %s",(*y).val);
               printf("| SP: %s",(*z).val);
			  printf ("| ET: %s\n ",(*k).val);
			
			}
			} 
		    
		
		
		}
	
	}
	else printf ("UNV n\'existe pas\n");
	
	printf ("_____________________________________________________\n");
	}
	
	
int rech_fac (pt ptr,char nom1[30])
{ 
    pfac x;
	if (ptr != NULL)
	{
	x=(*ptr).precedent;
	while ((x!= NULL) && (strcmp((*x).val,nom1) != 0)) { x=(*x).suivant;}
	if (x == NULL) { return 0;}
	else return 1;
	 } 
	 else return 0;
}
int rech_dep ( pt ptr,char nom[30])
{
     pfac x;
     pdep y;
	int rep; rep=0;
if (ptr != NULL)
{
	x= (*ptr).precedent;
	while ((x!=NULL) && (rep == 0)) 
	{
		y=(*x).precedent;
		while ((y !=NULL) && (strcmp((*y).val, nom) != 0)) { y=(*y).suivant;}
		if (y != NULL) { rep=1;
		                     printf("%s / %s / %s \n",(*ptr).val,(*x).val,(*y).val);}
	  else 	x=(*x).suivant;
	}
return rep;
}
else return 0;

}

int rech_sp (pt ptr,char nom[30])
{
	pfac x;
	int rep;rep=0;
	pdep y;
	psp z;
if (ptr != NULL)
{
  x=(*ptr).precedent;
  while ((x != NULL) && (rep == 0))
{
	y=(*x).precedent;
	while ((y!=NULL) && (rep == 0))
	{ z=(*y).precedent;
	 while( (strcmp((*z).val,nom) != 0) && (z != NULL)) { z=(*z).suivant;}
	 if (z != NULL) { rep =1;
	                     printf("%s / %s / %s / %s\n",(*ptr).val,(*x).val,(*y).val,(*z).val);}
     else	y=(*y).suivant;
	}
if (rep ==0) x=(*x).suivant;
}
return rep ;
}
else return 0;
}

int rech_etd (pt ptr,char nom[30])
{
	pfac x;
	int rep;rep =0;
	pdep y;
	psp z;
	pet k;
   if (ptr != NULL)
   {
    x=(*ptr).precedent; 
    while ((x!=NULL) && (rep ==0) ) 
    {
    	y=(*x).precedent;
    	while ( (y!=NULL) && (rep ==0))
    	{
		 z=(*y).precedent;
	      while ( (z != NULL) && (rep==0))
	      {
	     	k= (*z).precedent;
	     	while( (strcmp((*k).val,nom) != 0) && (k !=NULL)) { k=(*k).suivant;}
	     	if (k != NULL) { rep =1;
			                       printf("%s / %s / %s / %s / %s \n",(*ptr).val,(*x).val,(*y).val,(*z).val,(*k).val);}
		    else z=(*z).suivant;
		 }
		  if (rep == 0) y=(*y).suivant;
		 }
     if (rep == 0) x=(*x).suivant;
	}
     return rep;
}
else return 0;
}

void sup_fac (pt *ptr,char nom[30])
{
	pfac a,pred,x;
	pdep sv1,y;
	psp sv2,z;
	pet sv3,k;
printf ("supresion d\'une fac\n");
	x=(*(*ptr)).precedent; pred=NULL;
	if (rech_fac(*ptr,nom) == 1)          
	{ 
		while ((x != NULL) && (strcmp((*x).val,nom) != 0)) { pred=x;
		                                           x=(*x).suivant;}
    y=(*x).precedent;
    if ( y != NULL) sv1=(*y).suivant;
     while (y != NULL)
     {
     	z=(*y).precedent;
     	if (z != NULL) sv2=(*z).suivant;
     	while (z !=NULL)
     	{
     		k=(*z).precedent;
     	  if ( k != NULL)	sv3=(*k).suivant;
     		while (k != NULL)
     		{
     			free(k);
     			k=sv3;
     			if (sv3 != NULL) sv3=(*sv3).suivant;
			 }
		 (*z).precedent=NULL;
		 free(z);
		 z=sv2;
		   if (sv2 != NULL) sv2=(*sv2).suivant;
		 }
	 (*y).precedent=NULL;
	 free(y);
	 y=sv1;
	 if (sv1 != NULL) sv1=(*sv1).suivant;
	 }
    		if (strcmp((*((*(*ptr)).precedent)).val,nom) == 0) { a=(*(*ptr)).precedent;
    		                                        (*(*ptr)).precedent=(*a).suivant;
    		                                        (*a).precedent=NULL;
													free(a);
			}
			else{
				(*x).precedent=NULL;
		         (*pred).suivant=(*x).suivant;
		         (*x).suivant=NULL;
		         free(x);
		       }
    		
    		printf("votre fac %s a ete suprime\n",nom);
	}
   else printf ("votre fac n\'existe pas\n");
    printf("________________________________________________________________\n");
}

void sup_dep (pt ptr,char nom[30])
{
	pfac x;
	pdep a,y,pred;
	psp z,sv2;
	pet k,sv3;
	int rep;
    sv2=NULL;sv3=NULL;
	if (rech_dep (ptr,nom)==1)
	{
		x=(*ptr).precedent;
		if (x !=NULL)
		{
	    	rep =0;
	    	while ((x !=NULL) && (rep == 0))
		   {
			   y=(*x).precedent;pred =NULL;
			   while ((strcmp((*y).val,nom) != 0) && (y != NULL)) { pred =y;
			                                                         y=(*y).suivant;}
	           if (y != NULL) { printf("dep trouve\n");
			                   rep=1;}
			   else x=(*x).suivant;
		   }
	       z=(*y).precedent;
	       if (z != NULL) sv2=(*z).suivant;              /*sv2 = null*/
    	   while (z !=NULL)
	       {
		      k=(*z).precedent;
	          if ( k != NULL)	sv3=(*k).suivant;          /* sv3 = null*/
		      while (k != NULL)
		      {
			   free(k);
			    k=sv3;
		       if (sv3 != NULL)	sv3=(*sv3).suivant;
		      }
	            (*z).precedent=NULL;
	            free(z);
	            z=sv2;
	            if (sv2 != NULL) sv2=(*sv2).suivant;
           }
    	   if (strcmp((*((*x).precedent)).val,nom) == 0)
    	   { printf("votre departement est en tete de fac\n");
    		 a=(*x).precedent;
	     	 (*x).precedent=(*a).suivant;
	    	 (*a).precedent=NULL;
	    	 (*a).suivant=NULL;
	    	 free(a);
	       }
	     else
	     {
		  (*pred).suivant=(*y).suivant;
		  (*y).suivant=NULL;
		  (*y).precedent=NULL;
		  free(y);
	     }
	      printf("votre DEP %s a ete suprime\n",nom);
	
    	} 
	}
	else printf("votre votre departement n\'existe pas\n");
	 printf("________________________________________________________________\n");
}

void sup_sp (pt ptr,char nom[30])
{
	
	pfac x;
	pdep y;
	psp pred,z;
	pet k,sv;
	int rep;rep=0;
	sv=NULL;
	x=(*ptr).precedent;
	if (rech_sp(ptr,nom)==1)
	{
		while ((x != NULL) && (rep == 0))
		{
			y=(*x).precedent;
			while ((y !=NULL) && (rep ==0))
			{
				pred =NULL;
				z=(*y).precedent;
				while( (strcmp((*z).val,nom) != 0) &&  (z != NULL)) { pred=z;
				                                                      z=(*z).suivant;}
			    if (z == NULL) y=(*y).suivant;
			    else rep =1;
			}
		if (rep == 0) x=(*x).suivant;
		}
	   k=(*z).precedent;
	   if (k != NULL) sv=(*k).suivant;
	   while (k != NULL)
	   {free(k);
	    k=sv;
	    if (sv != NULL) sv=(*sv).suivant;
	   }
	   (*z).precedent=NULL;
	   if(strcmp(( *((*y).precedent)).val,nom) == 0) { (*y).precedent=(*((*y).precedent)).suivant;}
       else { (*pred).suivant=(*z).suivant;}
	   (*z).suivant=NULL;
	   free(z);
		printf("votre SP %s a ete suprime\n",nom);
	}
else printf ("votre specialite n\'existe pas\n");
printf("________________________________________________________________\n");
}
void sup_etd (pt ptr,char nom[30])
{
	pfac x;
	pdep y;
	psp z;
	pet k,pred;
	int rep;rep=0;
	x=(*ptr).precedent;
	if (rech_etd(ptr,nom)==1)
	{
		while ((x != NULL) && (rep==0))
		{
			y=(*x).precedent;
			while ((y != NULL) && (rep==0))
			{
				z=(*y).precedent;
				while ((z != NULL) && (rep==0))
				{
					k=(*z).precedent;pred=NULL;
					while ((strcmp((*k).val,nom) != 0) && (k!= NULL)){ pred =k;
					                                                   k=(*k).suivant;}
			       if (k == NULL) z=(*z).suivant;
				   else rep =1; 
				}
			 if (rep == 0) y=(*y).suivant;
			}
			if (rep ==0) x=(*x).suivant;
		}
	
     if (strcmp((*((*z).precedent)).val,nom) == 0){ (*z).precedent=(*k).suivant;}
     else (*pred).suivant=(*k).suivant;
     (*k).suivant=NULL;
     free(k);
   	 printf("votre ET %s a ete suprime\n",nom);
    }
    else printf ("votre etudiant n\'existe pas\n");
printf("________________________________________________________________\n");
}

void trie_fac(pt ptr)
{
   pfac a,x,y,pred1,pred2;
   x=(*ptr).precedent; pred1=NULL;
  printf("le trie des FAC\n");
  if (x != NULL){
   while ((*x).suivant != NULL)
   {
   	y=(*x).suivant; pred2=x;
   	while (y != NULL)
   	{
   		if ((*x).val > (*y).val)
   		{
   			a=(*x).suivant;
   			(*x).suivant=(*y).suivant;
   			(*y).suivant=a;
   			(*pred2).suivant=x;
   			if ((*ptr).precedent==x) (*ptr).precedent=y;
   			else (*pred1).suivant=y;
		   }
	    pred2=y;
	    y=(*y).suivant;
	}
    pred1=x;
    x=(*x).suivant;
   }
  printf("le trie est termine\n");
  }
else printf ("votre faculte est vide\n");
}

void trie_dep (pt ptr)
{                                                 
	pfac x;
	pdep y,z,pred1,pred2,a;
	char nom[30];
	printf ("le trie des departements\n");
	printf("entrer le nom de la FAC\n");
	scanf("%s",&nom);
	if (rech_fac(ptr,nom)==1) 
	{
		x=(*ptr).precedent;
		while (strcmp((*x).val,nom) !=0) { x=(*x).suivant;}
	    y=(*x).precedent;
	    pred1=NULL;
	    if (y != NULL){
		 while ((*y).suivant != NULL)
	     {
	    	z=(*y).suivant;pred2=y;
	    	while (z !=NULL)
	    	{
	    		if ((*y).val > (*z).val) 
			    {
			    	a=(*z).suivant;
			    	(*z).suivant=(*y).suivant;
			    	(*y).suivant=a;
			    	(*pred2).suivant=y;
			    	if ((*x).precedent==y) (*x).precedent=z;
			    	else (*pred1).suivant=z;
				}
			pred2=z;
			z=(*z).suivant;
			}
		  pred1=y;
		  y=(*y).suivant;
		 }
	      printf("le trie est termine\n");
		}
		else printf (" votre departements est vide\n");
	}
	else printf ("votre fac n\'existe pas\n");
}

void trie_sp (pt ptr)
{
	char nom1[30],nom2[30];
pfac x;
pdep y;
psp z,k,a,pred1,pred2;
printf ("le trie des specialites\n");
printf ("entrer le nom de la fac\n");
scanf("%s",&nom1);
if (rech_fac(ptr,nom1)==1)
{ x=(*ptr).precedent;
  while (strcmp((*x).val,nom1) != 0) { x=(*x).suivant;}
  printf("entrer le nom de departement\n");
  scanf("%s",&nom2);
   if (rech_dep(ptr,nom2)==1)
  {
 	 y=(*x).precedent;
	 while (strcmp((*y).val,nom2) != 0) {y=(*y).suivant;}
	 z=(*y).precedent;
	 pred1=NULL;
	 if (z != NULL){
	   while((*z).suivant != NULL)
	   {
		 k=(*z).suivant;pred2=z;
		 while (k !=NULL)
		 {
			if ((*z).val > (*k).val)
			{
				a=(*k).suivant;
				(*k).suivant=(*z).suivant;
				(*z).suivant=a;
				(*pred2).suivant=z;
				if((*y).precedent==z)	{ (*y).precedent=k;}
				else (*pred1).suivant=k;
			}
		   pred2=k;
		   k=(*k).suivant;
		 }
	    pred1=z;
	    z=(*z).suivant;
	   }
       printf ("le trie est termine\n");
     }
     else printf ("votre specialites est vide \n");
}
	else printf("votre departement n\'existe pas\n");
}
else printf("votre fac n\'existe pas\n");


}
void trie_etd (pt ptr)
{
	char nom1[30],nom2[30],nom3[30];
	pfac x;
	pdep y;
	psp z;
	pet i,j,a,pred1,pred2;
	printf("entrer le nom de la fac\n");
	scanf("%s",&nom1);
	if (rech_fac(ptr,nom1)==1)
	{
		x=(*ptr).precedent;
		while (strcmp((*x).val,nom1) != 0) {x=(*x).suivant; }
		printf("entrer le nom de departement\n");
		scanf("%s",&nom2);
		if (rech_dep(ptr,nom2)==1)
		{
			y=(*x).precedent;
			while (strcmp((*y).val,nom2) != 0) {y=(*y).suivant;}
			printf("entrer le nom de specialite\n");
			scanf("%s",&nom3);
			if (rech_sp (ptr,nom3)==1)
			{
				z=(*y).precedent;
				while (strcmp((*z).val,nom3) != 0 ) {z=(*z).suivant;}
				i=(*z).precedent;pred1=NULL;
			 if (i != NULL){
				while ((*i).suivant != NULL)
				{
					j=(*i).suivant;pred2=i;
					while (j != NULL)
					{
						if ((*i).val > (*j).val)
						{
							a=(*i).suivant;
							(*i).suivant=(*j).suivant;
							(*j).suivant=a;
							(*pred2).suivant=i;
							if ((*z).precedent==i) {(*z).precedent=j;}		
						    else (*pred1).suivant=j;
						}
					pred2=j;
					j=(*j).suivant;
					}
				 pred1=i;
				 i=(*i).suivant;
				}
				printf ("le trie est termine \n");
			 }
			 else printf ("votres etudiants est vide \n");
		    }
			else printf ("votre specialite n\'existe pas");
		}
	   else printf ("votre departement n\'existe pas");
	}
else printf ("votre fac n\'existe pas");
}

main()
{
	char nom[30]; 
	int op;
	pfac pred1;
	pdep pred2;
	psp pred3;
	pet pred4;
	pt  ptr;
	pred1=NULL;
	pred2=NULL;
	pred3=NULL;
	pred4=NULL;
    ptr=NULL;
	do {
		printf ("entrer une operation\n");
    printf ("entrer 0 pour exit\n");
	scanf("%d",&op);
    switch (op)
    {
    	case(1):{creer_univ(&(ptr));
			break;
		}
	    case (2):{ creer_fac(&(ptr),&(pred1));
			break;
		}
	    case (3):{ creer_departement(ptr,&(pred2));
			break;
		}
        case (4): {creer_specialite(ptr,&(pred3));
			break;
		}
	    case (5):{creer_etudiant(ptr,&(pred4));
			break;
		}
	    case (6):{printf("entrer le nom de FAC\n");
		scanf("%s",&nom);
	             if (rech_fac(ptr,nom)==0) {printf("%s n\'existe pas\n",nom); }
	             else printf("%s existe\n",nom);
			 printf("________________________________________________________________\n");
			break;
		}
	    case (7):{printf("entrer le nom de DEP\n");
	    scanf("%s",&nom);
	    if (rech_dep(ptr,nom)==0) {printf("%s n\'existe pas\n",nom); }
	             else printf("%s existe\n",nom);
		 printf("________________________________________________________________\n");
			break;
		}
	    case (8):{printf("entrer le nom de SP\n");
	    scanf("%s",&nom);
	    if (rech_sp(ptr,nom) == 0) {printf("%s n\'existe pas\n",nom); }
	             else printf("%s existe\n",nom);
		 printf("________________________________________________________________\n");
			break;
		}
	   case (9):{printf("entrer le nom de ET\n");
	    scanf("%s",&nom);
	   if (rech_etd(ptr,nom) == 0) {printf("%s n\'existe pas\n",nom); }
	             else printf("%s existe\n",nom);
		 printf("________________________________________________________________\n");
		break;
	   }
	  case (10):{printf("entrer le nom de FAC\n");
		scanf("%s",&nom);
		sup_fac(&(ptr),nom);
		break;
	  }
	 case (11):{printf("entrer le nom de DEP\n");
		scanf("%s",&nom);
		sup_dep(ptr,nom);break;
	 }
	 case (12):{printf("entrer le nom de SP\n");
		scanf("%s",&nom);
		sup_sp(ptr,nom);
		break;
	 }
	 case (13):{printf("entrer le nom de ETD\n");
		scanf("%s",&nom);
		sup_etd(ptr,nom);
		break;
	 }
	 case (14):{trie_fac(ptr);
	 printf("________________________________________________________________\n");
		break;
	 }
	 case (15):{trie_dep(ptr);
	 printf("________________________________________________________________\n");
		break;
	 }
	case (16):{trie_sp(ptr);
	printf("________________________________________________________________\n");
		break;
	 }
	case (17):{trie_etd(ptr);
	printf("________________________________________________________________\n");
		break;
	 }
     default: { printf("erreur\n");
		break;
	 }

	}
	
	
	}
	while (op !=0);
}

