#include<stdlib.h>
#include<stdio.h> 
#include<string.h>
#include<gmp.h>


/******************************************
 *                                        *
 * Alhadj Adam Mamadou && Malick Laye Sy  *
 *                                        *
 ******************************************/




void notre_pow_mod_ui( mpz_t res,mpz_t var,mpz_t n);

void square_and_multiply(mpz_t res, mpz_t a, mpz_t expo, mpz_t n);

int test_de_Miller_Rabin(mpz_t n, int k);

int test_de_fermat(mpz_t n, long k);

void AfficheTest(int test);

int main(int argc, char const *argv[])
{

	 mpz_t n; long int k ; 


    if(argc == 3){

    /*On récupère l'argument qui se trouve a la position 2 on le stocke dans K (l'index commence par 0 ) s'il est a l'entre par l'utilisateur*/

     k = atoi(argv[2]); 

    /*On récupère l'argument qui se trouve a la position 1 on le stocke dans n (l'index commence par 0 ) , il est toujours donné dans notre systeme*/

     mpz_init_set_str(n, argv[1], 10); 
    }
     
    else if (argc == 2){

     mpz_init_set_str(n ,argv[1] ,10);

     gmp_printf(" \n* Donnez le nombre de fois que ce test sera répété  ==> K : ");

     scanf("%ld", &k);
    }

    else
    {
     gmp_printf("\nassurez vous que que le format soit aisni:\n ./DM2  n k\n {avec n valeur à tester}\n et k {nbre d'iteration} .\n");
     gmp_printf("\nOubien de cette format :\n ./DM2  n \n {avec n valeur à tester} \n   Puis vous donnez  k {nbre d'iteration} .\n");        
     return -1;
    }

   gmp_printf("\npour n : %Zd\n",n);//Test qui affiche les deux parametres
   
   gmp_printf("\n et k : %d\n", k);

   gmp_printf("\n** Test de Fermat **  :\n");
   
   AfficheTest(test_de_fermat(n,k));

   gmp_printf("\n** Test de Miller-Rabin ** : \n");

   AfficheTest(test_de_Miller_Rabin(n,k));
 
   mpz_clears(n, NULL);

   return 0;

  
}


/************************************************* METHODE AFFICHETEST ******************************************************/


void AfficheTest(int test)
{

  switch(test)
  {
    case 0:gmp_printf(" \nnous donne avec certitude que ce nombre est Composé !\n\n"); break;
    case 1:gmp_printf(" \nnous dit que ce nombre est  probablement Premier  !\n\n");break;
    case 2:gmp_printf ("\ndemande a ce que n soit positif  !\n\n");break;
    //default: gmp_printf ("\nNEUTRE\n");break;
      

   }

}


/************************************************* TEST DE FERMAT  **********************************************************/

int test_de_fermat(mpz_t n, long k)
{


 /* 
  * Pour eviter de tester des entier negatif et des perte de temps et de performance 
  * On teste d'abord si n inferieur  a 1.
  * Avant l'initialisation de variable.
  */

    if ( mpz_cmp_ui(n,0) < 0 )  return 2; 

    //Cas ou si la valeur de n = 2 car on a un problème quand on essaye de trouver un a car on essaie de le générer 1 < a < 1
    if(mpz_cmp_ui(n, 2) == 0) return 1;

    //pareil pour n=1
	  if(mpz_cmp_ui(n, 1) == 0)  return 0;
 
   
  /* Declaration et initialisation des variables*/

	mpz_t  y , a,limite, nMoinsUn;
	
	mpz_inits(y, a, NULL); long int i;

	mpz_init_set(nMoinsUn, n); 

	mpz_sub_ui(nMoinsUn, nMoinsUn, 1);

    gmp_randstate_t state;

    gmp_randinit_mt(state);

	mpz_init_set(limite, n); 
	
	mpz_sub_ui(limite,limite,2);


/*
 * pour i = 1 jusqu’à k 
 * À chaque itération on effectue le test avec des a differents
 */
 
	for(i = 0 ; i < k; i++)
	{
	   
	 
   //Generer aleatoirement a compris  entre 0 < a < n-2
		mpz_urandomm(a, state, limite);
   //Genere l'entier a aleatoirement entre 1 < a < n-1
		mpz_add_ui(a, a, 1); 
     
	    // Effectue a^n-1 mod n
		square_and_multiply(y, a, nMoinsUn, n); 
	    // verifie si le resultat est different de 1
	    if(mpz_cmp_ui(y, 1) != 0)
	    { 
	      mpz_clears(y, a, nMoinsUn, NULL);
	      return 0;
	    }
      
	}
  mpz_clears(limite, y, a, nMoinsUn, NULL);

  return 1;
}	




/************************************************* TEST DE MILLER-RABIN ****************************************************/

/*Le test de Miller-Rabin est lui aussi basé sur le Petit Théorème de Fermat, mais exploite quant à lui
*quelques propriétés supplémentaires.
*Si n est un nombre impair dont on souhaite tester la primalité, on peut écrire n − 1 = 2^s * t, où t est
*un nombre impair.
*/


int test_de_Miller_Rabin(mpz_t n, int k)
{


/* 
  * Pour evider des perte de temps et de performance 
  * On teste d'abord si n est positif.
  * Avant initialisation varible dans la methode.
  */

 if ( mpz_cmp_ui(n,0) < 0 )   return 2; 
 
 if ( mpz_cmp_ui(n,1) == 0)   return 0;

 if ( mpz_cmp_ui(n,2) == 0)   return 1;

/*
  * pour ne prendre que des nombre impaire. 
  * Si mpz_even_p renvoi 1 dans ce cas n est paire on renvoie 0
  * sinon l'execution continue.
  */

  int nIP=mpz_even_p(n);  if(nIP==1) return 0 ;

     
 /*
  *  Declarartion et initialisation des variables
  */

   int s = 0 ,iSuivant = 0;

   mpz_t a, t, t_temp, reste, limite, y, nMoinsUn;
   
   mpz_inits (a, t, t_temp, reste, limite , y , nMoinsUn, NULL);

   mpz_init_set(nMoinsUn, n); 

   mpz_sub_ui(nMoinsUn, nMoinsUn, 1);
   
   mpz_init_set(limite, n); 

   mpz_sub_ui(limite,limite,2);

   gmp_randstate_t state;
	
   gmp_randinit_default(state);
  
  
  /*
   *  Décomposition   : 
   *  On fait la décomposition de l'ordre du groupe multiplicatif 
   *  des residus mod n ===>  n - 1 = 2^s*t, t impair
   *
   *  Puisque t est par definition impaire on verifie si t est divisible par 2.
   *  2^s est la plus grande puissance de 2 qui divise n-1 ==> t=(n-1)/ 2^s
   */    
  
    mpz_sub_ui(t, n, 1);
 
    mpz_mod_ui(reste, t, 2);

    while( mpz_cmp_ui(reste, 0) == 0)
    {
      //t = t/2
      mpz_div_ui(t, t, 2);
      s++;
      //reste = t%2
      mpz_mod_ui(reste, t, 2);
    }

   /*
    * On répète le test k fois 
    */
   
   for (long int i = 0; i < k ; i++)
   {

      //Generer aleatoirement l'entier compris entre 0 < a < n-1

    	 mpz_urandomm(a, state, limite);
                  
    	 mpz_add_ui(a, a, 1); 
        
      // y = a^t mod n
       mpz_set(t_temp, t);
        
      //methode de square and multiply
	     square_and_multiply(y, a, t_temp, n);

	     mpz_set(t_temp, t);
	  
      
	    /* 
       * Debut du temoin de miller 
       *
	     * Si y /≡ 1 mod n et y /≡ −1 mod n alors
	     */
       
	     if ((mpz_cmp_ui(y,1) != 0)  &&  (mpz_cmp(y,nMoinsUn) != 0) )
	     {
	      
	       //Pour j = 1 jusqu’à s−1 faire	
	      
	       for (long int j = 1 ; j <= (s-1) ; j++ )
	       {
	        
	        //y = y^2 mod n
	         notre_pow_mod_ui(y, y, n);

	        //si y = 1 
	        if (mpz_cmp_ui(y,1) == 0) {
	           mpz_clears(a, t, t_temp, reste, y, state, nMoinsUn, NULL);
	         // renvoye composee
	          return 0; 
	        }
	        
          //si y = n-1 alors
           if (mpz_cmp(y,nMoinsUn) == 0) {
          /*
           *arrêter la boucle de j. Continuer avec le i suivant 
           */	
           iSuivant = 1;
          break;
        }

      }
      
     /*
      * Dans le cas où toute la boucle du j a été itérée 
      * On libere quand meme l'espace et renvoye  (0) composee.
      */
      if( ! iSuivant ) {
        mpz_clears(a, t, t_temp, reste, y,state, nMoinsUn, NULL);
        // renvoye composee
        return 0;
      }
    }
  }//fin du temoin
  
  mpz_clears(a, t, t_temp, reste, y, state, nMoinsUn, NULL);

 /*Arriver a ce stade on dit que n est Probablement premier <ie> renvoyer (1) */
  return 1; 
}



/************************************************* METHODE EXPONENTIATION MODULAIRE  ****************************************************/

/*
 *Un algorithme qui permet de calculer l’exponentiation modulaire efficacement est la méthode square
 *and multiply, qui utilise la décomposition binaire de l’exposant. Cette méthode, pour le cas de
 *l’exponentiation modulaire est décrite par l’algorithme suivant.
 */
void square_and_multiply(mpz_t res, mpz_t a, mpz_t expo, mpz_t n)
{
  /*
   *  Declarartion et initialisation des variables
   */
	 mpz_t r; long long int i;
	 char* expo_bin;
	 mpz_init_set(r, a);

   /*
	*  Grace a mpz_get-str on recupere l'exposand puis on 
	*  le dransforme  en  formad binaire  exemple si expo=5 
	*  la chaine de caracdere expo_bin="101"
	*/
	expo_bin = mpz_get_str(NULL, 2, expo); 

   /*
	* Boucle pour le tableau Binaire et calcul 
	*/
	for(i=1 ; i<strlen(expo_bin); i++)
	{

		 
	  // r = (r*r) mod n ;  avec l'aide de notre fonction  notre_pow_mod_ui
		
	  notre_pow_mod_ui(r,r,n);
	 
	  //si h[i] = 1 alors  r = r · a mod n ;
		  
	  if(expo_bin[i] == '1'){
		
		mpz_mul(r, r, a);
		
		mpz_mod(r, r, n);
	 }

	}

   /*
    *  en sordie on a notre resutat grace a mpz_set(res, r);
    */

    mpz_set(res, r);

   /* puis liberadion de l'espace memoire occuper par r */
    mpz_clear(r);    


}




/************************************************* METHODE NOTRE_POW_MOD_UI ****************************************************/

/*
 *   Cette est methode fait la meme chose que pow_mod_ui (qui fait partie des interdits dans ce Dm)
 *   D' ou le nom notre_pow_mod_ui
 */

void notre_pow_mod_ui( mpz_t res,mpz_t var,mpz_t n)
{
		mpz_mul(var,var,var);
		mpz_mod(res,var , n);
}


// point final




