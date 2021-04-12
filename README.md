
                           💻️# PROJET D'IMPLÉMENTATION DES TESTS DE PRIMALITÉS DE FERMAT ET MILLER-RABIN #💻️
                                          # DM2 de cryptographie  L3 Informatique 29 Avril 2020



# Realiser par:

 Sy Malick Laye
 Alhadj Adam Mamadou

# Dirigé par:

 Madame Christina Boura

#CONDITION D'UTILISATION !

✔️installé la bibliothèque GNU MP 

✔️compililation:
   
 Pour compiler notre programme il faut utiliser la commande suivante :   gcc  DM2.c -o DM2  -lgmp 

✔️Execution du projet:

 Pour executer vous avez deux choix:

 Avant tout le programme veut que vous lui passer exactement comme nous allons decrire le format de test mais tout de même on a facilité l'utilisation en ajoutant quelques guide. Supposons que tu donne juste le nom du fichier sans argument comme ./DM2 ou accompagné de n mais sans la valeur de l'iteration, à chaque fois il vous aide à bien faire ton test sans interruption.
      
   *soit vous executer avec ce format :     ./DM2    n    k 

             exemple:   ./DM2 6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151=n   2=k
   
   *ou bien vous executer avec ce format:   ./DM2   n 
    en suite le programme vous demande de donner K. 
 
             exemple:   ./DM2 n=(6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151) 
             Donnez le nombre de tour  K : 2

Pour un nombre très grand  si t'es pressé evite de prendre un K tres grand ca risque de prendre enormement de temps mais plus k (le nombre d'iteration) est grand plus le resultat est sûr.


# Explications des algorithmes :

Ce programme en general  permet de tester si un nombre est problablement premier ou non selon le test de fermat et de miller Rabin.

Notre programme est compose de 5 methodes  dont 2 sont complementaires:
 
Les deux premiéres methodes sont respectivement test de Fermat et test de miller-Rabin .
          
        int test_de_fermat(mpz_t n, long k);
        
        int test_de_Miller_Rabin(mpz_t n, int k);

        void square_and_multiply(mpz_t res, mpz_t a, mpz_t expo, mpz_t n);
      
        void  notre_pow_mod_ui( mpz_t res,mpz_t var,mpz_t n);

        void AfficheTest(int test);


       
Tout d'abord il faut savoir que le test de Fermat et celui de Miller Rabin sont des tests probabilistes. 

C'est dans la methode principale (main) qu'on demande à l'utilisateur de donner l'entier n  (l'entier à tester)
 et k (le nombre de fois que le test sera répété) 

qui sont les deux parametres de nos deux methodes test.

Pour afficher le resultat retourner par les deux tests tout en évitant  une répétition nous avons implementer la methode  
 #void AfficheTest(int test); 

Puis nous avons ajouter la methode   
 #void  notre_pow_mod_ui( mpz_t res,mpz_t var,mpz_t n) 
 pour remplacer la methode #pow_mod_ui qui fait partie des methode interdit dans ce DM. 

+Pour les valeurs de retour : 
       
        0 quand n est compose;
        1 quand n est probablement premeier.
        

# int test_de_fermat(mpz_t n, int k);`

   Cette methode prend en paramètres un entier de type mpz_t de la bibliothèque GMP  et un entier k et exécute k fois le test de Fermat sur l'entier.

   Pour des raison de performance nous au debut de chacune des methodes (avant méme de declarer et initialiser nos variables) tester 

        si n est positif
        si n est egal à 1
        si n est egal à 2

    Puis on declare nos variables ( variable temporaire, variable pour generer les valeurs aleatoire ).Puis on les initialise.

  


# int test_de_Miller_Rabin(mpz_t n, int k);

  Cette methode prend en paramètres un entier de type mpz_t de la bibliothèque GMP 
   et un entier k et exécute k fois le test de Fermat sur l'entier.

  Pour des raison de performance au debut de chacune des methodes (avant méme de declarer et initialiser nos variables) on a testé 

        si n est positif
        si n est egal à 1
        si n est egal à 2
        si n est impaire.

  Puis nous avons declarer variables qu'on va utilise dans le corps de la 
  fonction ( variable temporaire, variable pour generer les valeurs aleatoire ).

  Apres declaration  on  :
   
  On decompose n comme suit: 
        n-1 = 2^s * t 
  Puis pour chaque  iteration  pour les k répétition : on choisit un nombre aleatoire a compris entre 0 et n
        0 < a < n
  en suite avec la fonction  square_and_multiply on calcule 
        y ← a^t mod n ;
  on compare y avec 1 et avec n-1 / 
      si y=1 ou y=n-1 on renvoie 1(probablement premier)
      sinon on execute le temoin.
  
         
        
# square_and_multiply(mpz_t res, mpz_t a, mpz_t exp, mpz_t mod);`

    Cet algorithme va calculer l'exponentiation modulaire en utilisant la décomposition binaire de l'exposant. 
    Il a une boucle de t-1 à 0 avec 
    t le nombre de d'éléments dans la décomposition binaire de l'exposant. La complexité de cet algorithme 
    est donc O(log_2(e)) avec e l'exposant en base de 10 puisque cela correspond au nombre d'éléments dans sa représentation binaire. 



    
























