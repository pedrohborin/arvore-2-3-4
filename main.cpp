#include <stdio.h>
#include <stdlib.h>
#include "arvore2-3-4.cpp"

// Á = 181
// á = 160
// ç = 135
// ã = 198
// ó = 162
// ú = 163
// é = 130

/*??????????????????????????????????
|               Menu                |
__________________________________*/

void menu(void){
	
	int choice, num, x;
	Arvore *ptr = criarArvore();
	Arvore *aux = criarArvore();
	
	do{
		//system("cls");
		printf("\n-----------Menu-----------\n\n");
		printf(" 1. Inserir elemento\n");
		printf(" 2. Buscar elemento\n");
		printf(" 3. Printar %crvore \n", 160, 130);
		printf(" 4. Gera 30 valores para inserir\n");
		printf(" 5. Sair.\n");
		printf("\n--------------------------\n");
		printf("\nOp%c%co: ", 135, 198);
		scanf("%d",&choice);
		
		switch(choice){
			// Inserir elemento
			case 1: {system("cls");
				printf(" Elemento a ser inserido: ");
				scanf("%d", &x);
				inserir(ptr, x);
				altura2(ptr);
				altura1(ptr,0);
				
				printf(" Valores da raiz:\n");
				printf("\n Valor 0: %d", ptr->raiz->valor0);
				printf("\n Valor 1: %d", ptr->raiz->valor1);
				printf("\n Valor 2: %d", ptr->raiz->valor2);
				printf("\n Valor 3: %d", ptr->raiz->valor3);
				printf("\n Contador: %d\n\n", ptr->raiz->contador);
				system("pause");
				system("cls");
				break;}
			// Buscar um valor
			case 2: {system("cls");
				printf("\n----------Buscar----------\n\n");
				printf(" Valor a ser buscado: \n", 181);
				scanf(" %d", &x);
				procurarElemento(ptr, x);
				system("pause");
				system("cls");
				break;}
			// Printar a árvore método 1
		
			case 3:{system("cls");
			
				printf("---------arvore---------\n");
				printf(" Raiz  ");
				int a = alturaArvore(ptr);
				int i = 0;
				
				while(i <= a){
				
				printTree(ptr,i);
				
				printf("\n");
				
				i++;
				}
				system("pause");
				system("cls");
				break;}
			
			//Gera valores
			case 4: {system("cls");
				
				int i = 0;
				
				for(i=0; i<= 15; i++){
					int r = rand() % 500;
					r++;
					inserir(ptr,r);
					altura2(ptr);
					altura1(ptr,0);
					
				}
					
				system("pause");
				system("cls");
				break;}
				
			//Sair do programa
			case 5:{system("cls");
				printf(" Saindo... \n");
				
				break;}
			
			
			default:{ system("cls");
				printf("\n Escolha inv%clida.\n", 160);
				system("pause");
				system("cls");
				break;}
		}
	} while (choice != 5);
	
}

int main()
{
    
    menu();

  	return 0;
}
