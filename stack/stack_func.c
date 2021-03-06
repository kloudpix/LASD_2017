#include "stack_func.h"

//Funzione prinicpale degli Stack
void stack_func_main()  {
	STACK pila = stack_init();	//inizializzazione della struttura

	int choiceMenu;
	do	{
		io_clearScreen();
		switch(choiceMenu = stack_func_menu(stack_isEmpty(pila)))	{	//chiamata del menu principale con scelta dell'albero con controllo di esistenza della pila
			case 1:
				printf("GENERAZIONE STACK\n\n");
				stack_func_generate(pila);
				break;
			case 2:
				printf("INSERIMENTO NUOVO ELEMENTO NELLO STACK\n\n");
                stack_func_insertKey(pila);
				break;
			case 3:
				printf("STAMPA STACK\n\n");
                stack_func_print(pila);
				break;
			case 4:
				printf("ESTRAZIONE ELEMENTO IN TESTA\n\n");
				stack_func_extract(pila);
				break;
            case 5:
				printf("CANCELLAZIONE STACK\n\n");
				stack_func_delete(pila);
				break;
            case 6:
				printf("SESSIONE TERMINATA\n\n");
		}
		io_pressKey();
	}while(choiceMenu != 6);

	pila = stack_free(pila, 1); //con il parametro '1', dealloco completamente lo stack
}

//Interfaccia utente
int stack_func_menu(int isEmpty)	{
	int choiceMenu;
	printf("\t\t\tStack - MENU PRINCIPALE\n");
	printf("1. Genera Stack\n");
	printf("2. Inserisci nuovo elemento\n");
    if(!isEmpty)    {   //se lo Stack esiste, mostro gli altri elementi del menu
        printf("3. Stampa Stack\n");
        printf("4. Estrai elemento in testa\n");
        printf("5. Cancella lo Stack");
    }
    printf("\n");
    printf("6. Esci\n");
    printf("\n\n");
	do {
		printf("SCELTA: ");
		if(((choiceMenu = io_getInteger()) < 1 || choiceMenu > 6) || (isEmpty && (choiceMenu > 2 && choiceMenu < 6))) //nel caso l'utente inserisca una scelta del menu non presente
			printf("ATTENZIONE: Valore non valido\n\n");
	}while((choiceMenu < 1 || choiceMenu > 6) || (isEmpty && (choiceMenu > 2 && choiceMenu < 6)));
    io_clearScreen();   //pulizia dello schermo del terminale
	return choiceMenu;
}

//Generazione di uno Stack con valori randomici
void stack_func_generate(STACK pila) {
    int idx, n_elem;
    if(!stack_isEmpty(pila))	{	//se è già presente, chiedo al'utente quale operazione effettuare sullo Stack
        int choice;
        printf("ATTENZIONE: Stack già presente. Cosa preferisci fare?\n\t1. Generazione nuovo Stack\t2. Inserimento nuovi elementi\n\n");
        do  {
            printf("SCELTA: ");
            if((choice = io_getInteger()) < 1 || choice > 2)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(choice < 1 || choice > 2);
        if(choice == 1) {
            pila = stack_free(pila, 0);   //con '0' in parametro non elimino completamente lo Stack ma solo tutti i puntatori al suo interno
            printf("\n");
            if(stack_isEmpty(pila))
                printf("Stack eliminato\n\n");
        }
    }
    
    do  {
        printf("Quanti elementi vuoi inserire nello Stack? (1-%d): ", MAX_stack-*(pila[0]));
        if((n_elem = io_getInteger()) < 1 || n_elem > MAX_stack-*(pila[0]))
			printf("ATTENZIONE: Valore non valido\n\n");
	}while(n_elem < 1 || n_elem > MAX_stack-*(pila[0]));

    for(idx=0;idx<n_elem;idx++)
        stack_push(pila, random_num(1, MAX_stack));	//inserisce un numero casuale compreso fra 1 e MAX_stack
    printf("\n");
    stack_func_print(pila);
}

//Inserimento in input del valore nello Stack
void stack_func_insertKey(STACK pila)   {
    if(!stack_isFull(pila)) {
        int val;
        do  {
            printf("Quale valore vuoi inserire nello Stack? (1-%d): ", MAX_stack);
            if((val = io_getInteger()) < 1 || val > MAX_stack)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(val < 1 || val > MAX_stack);

        stack_push(pila, val);
        printf("\n");
        stack_func_print(pila);
    } else
        printf("ATTENZIONE: lo Stack è pieno\n\n");
}

//Estrazione con conferma dell'elemento dello Stack
void stack_func_extract(STACK pila) {
    printf("Valore in testa nello Stack: %d\n", stack_top(pila));
    char choice;
    do  {
        printf("Desideri estrarlo? (S/N): ");
        choice = toupper(io_getChar());
        if(choice != 'S' && choice != 'N')
            printf("ATTENZIONE: comando non riconosciuto\n\n");
    }while(choice != 'S' && choice != 'N');
    printf("\n");
    if(choice == 'S')   {
        printf("Valore estratto: %d\n\n", stack_pop(pila));
        if(!stack_isEmpty(pila))
            stack_func_print(pila);
        else
            printf("ATTENZIONE: Stack svuotato\n\n");
    }
}

//Eliminazione con conferma dello Stack
void stack_func_delete(STACK pila)  {
    char choice;
    do  {
        printf("Sei sicuro di voler eliminare lo Stack? (S/N): ");
        choice = toupper(io_getChar()); //se metto un carattere minuscolo, lo rende maiuscolo
        if(choice != 'S' && choice != 'N')
            printf("ATTENZIONE: scelta non valida\n\n");
    }while(choice != 'S' && choice != 'N');

    if(choice == 'S')   {
        pila = stack_free(pila, 0);   //con '0' in parametro non elimino completamente lo Stack ma solo tutti i puntatori al suo interno
        printf("\n");
        if(stack_isEmpty(pila))
            printf("Stack eliminato\n\n");
    }
}

//Stampa dello Stack
void stack_func_print(STACK pila)  {
    stack_print(pila);
    printf("\tNumero elementi: %d\n", *(pila[0]));
}