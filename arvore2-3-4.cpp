/*trabalho Estruturtra de dados 2
arvore 2-3-4*/

#include <stdlib.h>
#include <stdio.h>
#include "arvore2-3-4.h"
#define TRUE (1==1)
#define FALSE (1==0)

// Função para criar um nó
No *criarNo(No *ptr){
    
    if(ptr == NULL){
        ptr = (No*) malloc( sizeof(No) );
        if(ptr != NULL){
		    ptr->pai = ptr;
		    ptr->ptrEsquerdo = NULL;
		    ptr->ptrMeioE = NULL;
		    ptr->ptrMeioD = NULL;
		    ptr->ptrDireito = NULL;
		    ptr->ptrAux = NULL;
		    ptr->contador = 0;
		    ptr->altura = 0;
		    ptr->valor0 = NULL;
	        ptr->valor1 = NULL;
	        ptr->valor2 = NULL;
		    ptr->valor3 = NULL;
	    }
	    else{
	    	printf("perdeu play.");
		}
    }
    return ptr;    
}

Arvore* criarArvore(){
    Arvore *arv = (Arvore*) malloc(sizeof(Arvore));
    if(arv != NULL){
	
    arv->raiz = criarNo(NULL);
	}
	else{
		printf("perdeu play, so q na arv");
	}
    return arv;
}

//função que acha uma folha 
No *acharFolha(Arvore* ptr, int valor){
	// (ptr->raiz->ptrEsquerdo) == NULL && (ptr->raiz->ptrMeioE) == NULL && (ptr->raiz->ptrMeioD) == NULL && (ptr->raiz->ptrDireito) == NULL
	if((ptr->raiz->ptrEsquerdo) == NULL){
		return (ptr->raiz);
	}
	
	Arvore *aux = criarArvore();
	
    // Se valor < A
    if((ptr->raiz->valor0) > valor){
    	if((ptr->raiz) == NULL){
    		No *auxNo;
    		auxNo = criarNo(NULL);
    		ptr->raiz->ptrEsquerdo = auxNo;
		}
    	aux->raiz = ptr->raiz->ptrEsquerdo;
    	return acharFolha(aux, valor);
	}
	
	// Se A > valor < B
	//else
	if((ptr->raiz->valor0) < valor && (ptr->raiz->contador) == 1 || 
			(ptr->raiz->valor0) < valor && (ptr->raiz->valor1) > valor){
				if((ptr->raiz) == NULL){
    				No *auxNo;
    				auxNo = criarNo(NULL);
    				ptr->raiz->ptrMeioE = auxNo;
				}
				aux->raiz = ptr->raiz->ptrMeioE;
				return acharFolha(aux, valor);
	}
		   
	// Se B > valor < C
	//else
	if((ptr->raiz->valor1) < valor && (ptr->raiz->contador) == 2 ||
			(ptr->raiz->valor1) < valor && (ptr->raiz->valor2) > valor){
				if((ptr->raiz) == NULL){
    				No *auxNo;
    				auxNo = criarNo(NULL);
    				ptr->raiz->ptrMeioD = auxNo;
    			}
				aux->raiz = ptr->raiz->ptrMeioD;
				return acharFolha(aux, valor);
	}
	
    // Se C > valor
	//else
	if((ptr->raiz->valor2) < valor){
		if((ptr->raiz) == NULL){
    		No *auxNo;
    		auxNo = criarNo(NULL);
    		ptr->raiz->ptrDireito = auxNo;
    	}
		aux->raiz = ptr->raiz->ptrDireito;
		return acharFolha(aux, valor);
	}
}


// Função de inserção [ A, B, C ]
void inserir(Arvore *arv, int valor){
    
    if(valorExistente(arv, valor)){
    	printf("Valor j%c existente.\n", 160);
    	return;
	}
    No *teste = criarNo(NULL);
    teste = acharFolha(arv, valor); // retorna ptr->raiz
    
    // Nó = [ A, B, C ]
    if((teste->contador) != 3){
    	
    	// 1º Caso   [ NULL, NULL, NULL ]
    	
    	if((teste->contador) == 0){      // Valor = A
    		teste->valor0 = valor;
    		teste->contador++;
    		return;
    	}
    	
    	// 2º Caso   [ A, NULL, NULL ]
    	
		else if((teste->contador) == 1){ // Valor = B
    		if((teste->valor0) < valor){
    			teste->valor1 = valor;
    			teste->contador++;
    			return;
			}else{
				teste->valor1 = teste->valor0;  // Valor = A
				teste->valor0 = valor;
				teste->contador++;
				return;
			}
		}
		
		// 3º Caso   [ A, B, NULL ] 
		
		else if((teste->contador) == 2){
			if((teste->valor1) < valor){   // Valor = C
				teste->valor2 = valor;
    			teste->contador++;
    			return;
			}
			else if((teste->valor1) > valor && (teste->valor0) < valor){ // Valor = B
				teste->valor2 = teste->valor1;
				teste->valor1 = valor;
    			teste->contador++;
    			return;
			}
			else if((teste->valor0) > valor){
				teste->valor2 = teste->valor1;
				teste->valor1 = teste->valor0;
				teste->valor0 = valor;
				teste->contador++;
				return;
			}
			else{
				printf("Erro antes do contador=3\n");
			}
		}
    }else if((teste->contador) == 3){
    	
    	Arvore *aux = criarArvore();
    	aux->raiz = teste;
    	// 4º Caso | Valor < A |   [ Aux, A, B, C ]
    	
    	if((teste->valor0) > valor){
    		teste->valor3 = teste->valor2;
    		teste->valor2 = teste->valor1;
    		teste->valor1 = teste->valor0;
    		teste->valor0 = valor;
    		balancear(aux);
    		return;
		}
		
		// 5º Caso | Valor A > valor < B |   [ A, Aux, B, C ]
		
		else if((teste->valor0) < valor && (teste->valor1) > valor){
			teste->valor3 = teste->valor2;
			teste->valor2 = teste->valor1;
			teste->valor1 = valor;
			balancear(aux);
			return;
		}
		
		// 6º Caso | Valor B > valor < C |   [ A, B, Aux, C ]
		
		else if((teste->valor1) < valor && (teste->valor2) > valor){
			teste->valor3 = teste->valor2;
			teste->valor2 = valor;
			balancear(aux);
			return;
		}
		
		// 7º Caso | Valor C > valor |   [ A, B, C, Aux ]
		
		else if((teste->valor2) < valor){
			teste->valor3 = valor;
			balancear(aux);
    		return;
		}
		else{
			printf("erro na funcao inserir 1.\n");
			return;
		}
		
	}
	else{
		printf("erro na funcao inserir 2.\n");
		return;
	}
    
}


// Função de balanceamento [ A, B, C, D]
void balancear(Arvore *arv){
	
	// Se já balanceado
	if((arv->raiz->valor3) == NULL){
		return;
	}
			
	// Se não tiver pai e nem filho
	if((arv->raiz->pai) == (arv->raiz) && (arv->raiz->ptrEsquerdo) == NULL){
		// Cria o nó esquerdo e insere os valores
		No *noEsq = criarNo(NULL);
		arv->raiz->ptrEsquerdo = noEsq;
		arv->raiz->ptrEsquerdo->valor0 = arv->raiz->valor0;
		arv->raiz->ptrEsquerdo->contador = 1;
		arv->raiz->ptrEsquerdo->pai = arv->raiz;
		// Cria o nó direito e insere os valores
		No *noDir = criarNo(NULL);
		arv->raiz->ptrMeioE = noDir;
		arv->raiz->ptrMeioE->valor0 = arv->raiz->valor2;
		arv->raiz->ptrMeioE->valor1 = arv->raiz->valor3;
		arv->raiz->ptrMeioE->contador = 2;
		arv->raiz->ptrMeioE->pai = arv->raiz;
		// Arruma os valores do nó pai
		arv->raiz->valor0 = arv->raiz->valor1;
		arv->raiz->valor1 = NULL;
		arv->raiz->valor2 = NULL;
		arv->raiz->valor3 = NULL;
		arv->raiz->contador = 1;
		return;
	}
	// Se não tiver pai e tiver filho
	else if((arv->raiz) == (arv->raiz->pai) && (arv->raiz->ptrEsquerdo) != NULL){
		
		// Cria nó esquerdo e insere os valores e filhos
		No *noEsq = criarNo(NULL);
		noEsq->valor0 = arv->raiz->valor0;
		noEsq->contador = 1;
		noEsq->ptrEsquerdo = arv->raiz->ptrEsquerdo;
		noEsq->ptrMeioE = arv->raiz->ptrMeioE;
		// Cria nó ptrMeioE e insere os valores e filhos
		No *noDir = criarNo(NULL);
		noDir->valor0 = arv->raiz->valor2;
		noDir->valor1 = arv->raiz->valor3;
		noDir->contador = 2;
		noDir->ptrEsquerdo = arv->raiz->ptrMeioD;
		noDir->ptrMeioE = arv->raiz->ptrDireito;
		noDir->ptrMeioD = arv->raiz->ptrAux;
		// Arruma os nós (pais e valores)
		arv->raiz->ptrEsquerdo = noEsq;
		arv->raiz->ptrMeioE = noDir;
		arv->raiz->ptrEsquerdo->pai = arv->raiz;
		arv->raiz->ptrMeioE->pai = arv->raiz;
		arv->raiz->valor0 = arv->raiz->valor1;
		arv->raiz->valor1 = NULL;
		arv->raiz->valor2 = NULL;
		arv->raiz->valor3 = NULL;
		arv->raiz->contador = 1;
		arv->raiz->ptrMeioD = NULL;
		arv->raiz->ptrDireito = NULL;
		arv->raiz->ptrAux = NULL;
		// Arrumando o pai dos filhos dos nós
		arv->raiz->ptrEsquerdo->ptrEsquerdo->pai = arv->raiz->ptrEsquerdo;
		arv->raiz->ptrEsquerdo->ptrMeioE->pai = arv->raiz->ptrEsquerdo;
		arv->raiz->ptrMeioE->ptrEsquerdo->pai = arv->raiz->ptrMeioE;
		arv->raiz->ptrMeioE->ptrMeioE->pai = arv->raiz->ptrMeioE;
		arv->raiz->ptrMeioE->ptrMeioD->pai = arv->raiz->ptrMeioE;
		return;
	}
	// Se tiver pai
	else if((arv->raiz) != (arv->raiz->pai)){
		// 1º Caso (2-node)
		if((arv->raiz->pai->ptrMeioD) == NULL){
			// Se raiz == ptrMeioE
			if((arv->raiz) == (arv->raiz->pai->ptrMeioE)){
				// Cria um nó para o ptrMeioD
				No *noAux = criarNo(NULL);
				noAux->valor0 = arv->raiz->valor2;
				noAux->valor1 = arv->raiz->valor3;
				noAux->contador = 2;
				noAux->pai = arv->raiz->pai;
				arv->raiz->pai->ptrMeioD = noAux;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor1 = arv->raiz->valor1;
				arv->raiz->pai->contador = 2;
				// Splita o nó atual
				arv->raiz->pai->ptrMeioD->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrMeioD->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrMeioD->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				return;
			}
			// Se raiz == ptrEsquerdo
			else if((arv->raiz) == (arv->raiz->pai->ptrEsquerdo)){
				// Cria o nó ptrMeioD e empurra o nó ptrMeioE para a direita
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrMeioD = arv->raiz->pai->ptrMeioE;
				arv->raiz->pai->ptrMeioE = noAux;
				arv->raiz->pai->ptrMeioE->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor1 = arv->raiz->pai->valor0;
				arv->raiz->pai->valor0 = arv->raiz->valor1;
				arv->raiz->pai->contador = 2;
				// Splita o nó atual
				arv->raiz->pai->ptrMeioE->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrMeioE->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrMeioE->contador = 2;
				arv->raiz->pai->ptrMeioE->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrMeioE->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrMeioE->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				return;
			}
			else{
				return;
			}
		}
		// 2º caso (3-node)
		else if((arv->raiz->pai->ptrDireito) == NULL){
			// Se raiz == ptrEsquerdo
			if((arv->raiz) == (arv->raiz->pai->ptrEsquerdo)){
				// Cria o nó ptrDireito e empurra os nós para a direita
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrDireito = arv->raiz->pai->ptrMeioD;
				arv->raiz->pai->ptrMeioD = arv->raiz->pai->ptrMeioE;
				arv->raiz->pai->ptrMeioE = noAux;
				arv->raiz->pai->ptrMeioE->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor2 = arv->raiz->pai->valor1;
				arv->raiz->pai->valor1 = arv->raiz->pai->valor0;
				arv->raiz->pai->valor0 = arv->raiz->valor1;
				arv->raiz->pai->contador = 3;
				// Splita o nó atual
				arv->raiz->pai->ptrMeioE->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrMeioE->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrMeioE->contador = 2;
				arv->raiz->pai->ptrMeioE->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrMeioE->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrMeioE->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				return;
			}
			// Se raiz == ptrMeioE
			else if((arv->raiz) == (arv->raiz->pai->ptrMeioE)){
				// Cria o nó ptrDireito e empurra os nós para a direita
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrDireito = arv->raiz->pai->ptrMeioD;
				arv->raiz->pai->ptrMeioD = noAux;
				arv->raiz->pai->ptrMeioD->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor2 = arv->raiz->pai->valor1;
				arv->raiz->pai->valor1 = arv->raiz->valor1;
				arv->raiz->pai->contador = 3;
				// Splita o nó atual
				arv->raiz->pai->ptrMeioD->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrMeioD->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrMeioD->contador = 2;
				arv->raiz->pai->ptrMeioD->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrMeioD->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrMeioD->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				return;
			}
			// Se raiz == ptrMeioD
			else if((arv->raiz) == (arv->raiz->pai->ptrMeioD)){
				// Cria o nó ptrDireito
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrDireito = noAux;
				arv->raiz->pai->ptrDireito->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor2 = arv->raiz->valor1;
				arv->raiz->pai->contador = 3;
				// Splita o nó atual
				arv->raiz->pai->ptrDireito->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrDireito->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrDireito->contador = 2;
				arv->raiz->pai->ptrDireito->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrDireito->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrDireito->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				return;
			}
			else{
				return;
			}
		}
		// 3º caso (4-node)
		else if((arv->raiz->pai->ptrDireito) != NULL){
			// Se raiz == ptrEsquerdo
			if((arv->raiz) == (arv->raiz->pai->ptrEsquerdo)){
				// Cria o nó ptrAux e empurra os nós para a direita
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrAux = arv->raiz->pai->ptrDireito;
				arv->raiz->pai->ptrDireito = arv->raiz->pai->ptrMeioD;
				arv->raiz->pai->ptrMeioD = arv->raiz->pai->ptrMeioE;
				arv->raiz->pai->ptrMeioE = noAux;
				arv->raiz->pai->ptrMeioE->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor3 = arv->raiz->pai->valor2;
				arv->raiz->pai->valor2 = arv->raiz->pai->valor1;
				arv->raiz->pai->valor1 = arv->raiz->pai->valor0;
				arv->raiz->pai->valor0 = arv->raiz->valor1;
				// Splita o nó
				arv->raiz->pai->ptrMeioE->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrMeioE->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrMeioE->contador = 2;
				arv->raiz->pai->ptrMeioE->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrMeioE->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrMeioE->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				// Chama recursividade no nó pai
				Arvore *aux = criarArvore();
				aux->raiz = arv->raiz->pai;
				return balancear(aux);
			}
			// Se raiz == ptrMeioE
			else if((arv->raiz) == (arv->raiz->pai->ptrMeioE)){
				// Cria o nó ptrAux e empurra os nós para a direita
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrAux = arv->raiz->pai->ptrDireito;
				arv->raiz->pai->ptrDireito = arv->raiz->pai->ptrMeioD;
				arv->raiz->pai->ptrMeioD = noAux;
				arv->raiz->pai->ptrMeioD->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor3 = arv->raiz->pai->valor2;
				arv->raiz->pai->valor2 = arv->raiz->pai->valor1;
				arv->raiz->pai->valor1 = arv->raiz->valor1;
				// Splita o nó
				arv->raiz->pai->ptrMeioD->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrMeioD->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrMeioD->contador = 2;
				arv->raiz->pai->ptrMeioD->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrMeioD->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrMeioD->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				// Chama recursividade no nó pai
				Arvore *aux = criarArvore();
				aux->raiz = arv->raiz->pai;
				return balancear(aux);
			}
			// Se raiz == ptrMeioD
				else if((arv->raiz) == (arv->raiz->pai->ptrMeioD)){
				// Cria o nó ptrAux e empurra o nó para a direita
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrAux = arv->raiz->pai->ptrDireito;
				arv->raiz->pai->ptrDireito = noAux;
				arv->raiz->pai->ptrDireito->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor3 = arv->raiz->pai->valor2;
				arv->raiz->pai->valor2 = arv->raiz->valor1;
				// Splita o nó
				arv->raiz->pai->ptrDireito->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrDireito->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrDireito->contador = 2;
				arv->raiz->pai->ptrDireito->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrDireito->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrDireito->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				// Chama recursividade no nó pai
				Arvore *aux = criarArvore();
				aux->raiz = arv->raiz->pai;
				return balancear(aux);
			}
			// Se raiz == ptrDireito
			else if((arv->raiz) == (arv->raiz->pai->ptrDireito)){
				// Cria o nó ptrAux
				No *noAux = criarNo(NULL);
				arv->raiz->pai->ptrAux = noAux;
				arv->raiz->pai->ptrAux->pai = arv->raiz->pai;
				// Sobe o valor1 para o pai
				arv->raiz->pai->valor3 = arv->raiz->valor1;
				// Splita o nó
				arv->raiz->pai->ptrAux->valor0 = arv->raiz->valor2;
				arv->raiz->pai->ptrAux->valor1 = arv->raiz->valor3;
				arv->raiz->pai->ptrAux->contador = 2;
				arv->raiz->pai->ptrAux->ptrEsquerdo = arv->raiz->ptrMeioD;
				arv->raiz->pai->ptrAux->ptrMeioE = arv->raiz->ptrDireito;
				arv->raiz->pai->ptrAux->ptrMeioD = arv->raiz->ptrAux;
				arv->raiz->valor1 = NULL;
				arv->raiz->valor2 = NULL;
				arv->raiz->valor3 = NULL;
				arv->raiz->contador = 1;
				arv->raiz->ptrMeioD = NULL;
				arv->raiz->ptrDireito = NULL;
				arv->raiz->ptrAux = NULL;
				// Chama recursividade no nó pai
				Arvore *aux = criarArvore();
				aux->raiz = arv->raiz->pai;
				return balancear(aux);
			}
		}
		else{
			printf("erro nas funcoes casos\n");
		}
	}
	else{
		printf("erro na funcao se pai\n");
	}
}

// Função de busca [ A, B, C ]
void procurarElemento(Arvore *arv, int valor){
	
	if(arv->raiz == NULL){
		printf("\nRaiz nula.\n");
		return;
	}
	else if(arv->raiz != NULL){
		
		// Se valor = A
	
		if((arv->raiz->valor0) == valor){   // Crash
			printf("N%cmero %d encontrado no valor (valor0)!\n", 163, valor);
			return;
		}
		
		// Se valor = B
		if((arv->raiz->valor1) == valor){
			printf("N%cmero %d encontrado no valor (valor1)!\n", 163, valor);
			return;
		}
		
		// Se valor = C
		if((arv->raiz->valor2) == valor){
			printf("N%cmero %d encontrado no valor (valor2)!\n", 163, valor);
			return;
		}
		
		Arvore *aux = criarArvore();
		
		// Se valor < A
		if((arv->raiz->valor0) > valor){
			if((arv->raiz->ptrEsquerdo) == NULL){
				printf("Valor n%co existe (a)).\n",198);
				return;
			}
			else{
				aux->raiz = arv->raiz->ptrEsquerdo;
				procurarElemento((aux), valor);
				return;
			}
			
		}
		
		// Se A > valor < B
		if((arv->raiz->valor0) < valor && (arv->raiz->contador) == 1 ||
		   (arv->raiz->valor0) < valor && (arv->raiz->valor1) > valor){
			if((arv->raiz->ptrMeioE) == NULL){
				printf("Valor n%co existe (b).\n",198);
				return;
			}
			else{
				aux->raiz = arv->raiz->ptrMeioE;
				procurarElemento((aux), valor);
				return;
			}
		}
		
		// Se B > valor < C
		if((arv->raiz->valor1) < valor && (arv->raiz->contador) == 2 ||
			(arv->raiz->valor1) < valor && (arv->raiz->valor2) > valor){
			if((arv->raiz->ptrMeioD) == NULL){
				printf("Valor não existe (c)).\n", 198);
				return;
			}
			else{
				aux->raiz = arv->raiz->ptrMeioD;
				procurarElemento((aux), valor);
				return;
			}
		}
		
		// Se C > valor
		if((arv->raiz->valor2) < valor){
			if((arv->raiz->ptrEsquerdo) == NULL){
				printf("Valor não existe (d)).\n",198);
				return;
			}
			else{
				aux->raiz = arv->raiz->ptrDireito;
				procurarElemento((aux), valor);
				return;
			}
		}
		
		{
			printf("Valor %d não encontrado na %crvore.\n", valor, 198, 160);
			return;
		}

	}
	
	// Caso acima nao funcione
	else{
		printf("Erro na fun%c%co.\n", valor ,135, 198);
		return;
	}
	
}

// Função de verificação de duplicidade [ A, B, C ]
int valorExistente(Arvore *arv, int valor){
	
	if(arv->raiz == NULL){
		//Raiz nula
		return FALSE;
	}
	else if(arv->raiz != NULL){
		
		// Se valor = A
	
		if((arv->raiz->valor0) == valor){
			return TRUE;
		}
		
		// Se valor = B
		if((arv->raiz->valor1) == valor){
			return TRUE;
		}
		
		// Se valor = C
		if((arv->raiz->valor2) == valor){
			return TRUE;
		}

		Arvore *aux = criarArvore();
		
		// Se valor < A
		if((arv->raiz->valor0) > valor){
			if((arv->raiz->ptrEsquerdo) == NULL){
				return FALSE;
			}
			else{
				aux->raiz = arv->raiz->ptrEsquerdo;
				return valorExistente((aux), valor);;
			}
			
		}
		
		// Se A > valor < B
		if((arv->raiz->valor0) < valor && (arv->raiz->contador) == 1 ||
		   (arv->raiz->valor0) < valor && (arv->raiz->valor1) > valor){
			if((arv->raiz->ptrMeioE) == NULL){
				return FALSE;
			}
			else{
				aux->raiz = arv->raiz->ptrMeioE;
				return valorExistente((aux), valor);
			}
		}
				
		// Se B > valor < C
		if((arv->raiz->valor1) < valor && (arv->raiz->contador) == 2 ||
			(arv->raiz->valor1) < valor && (arv->raiz->valor2) > valor){
			if((arv->raiz->ptrMeioD) == NULL){
				return FALSE;
			}
			else{
				aux->raiz = arv->raiz->ptrMeioD;
				return valorExistente((aux), valor);
			}
		}
		
		// Se C > valor
		if((arv->raiz->valor2) < valor){
			if((arv->raiz->ptrEsquerdo) == NULL){
				return FALSE;
			}
			else{
				aux->raiz = arv->raiz->ptrDireito;
				return valorExistente((aux), valor);
			}
		}
		return FALSE;
	}
	
	// Caso acima nao funcione
	else{
		printf("Erro na fun%c%co valorExistente().\n", valor, 135, 198);
		return FALSE;
	}
	
}

// função para imprimir na tela
void printTree(Arvore *arv, int i){
    
    
	
    if(arv->raiz != NULL && arv->raiz->altura == i ){
     
        
        printf("[%d-%d-%d- %d]\t  ", arv->raiz->valor0, arv->raiz->valor1, arv->raiz->valor2, arv->raiz->altura);
	}
    if(arv->raiz != NULL){
	
    	if(arv->raiz->ptrEsquerdo != NULL){
    	    Arvore *aux = criarArvore();
        	aux->raiz = arv->raiz->ptrEsquerdo;
        	printTree(aux,i);
    	}

    	if(arv->raiz->ptrMeioE != NULL){
        	Arvore *aux1 = criarArvore();
        	aux1->raiz = arv->raiz->ptrMeioE;
        	printTree(aux1,i);
    	}

    	if(arv->raiz->ptrMeioD != NULL){
        	Arvore *aux2 = criarArvore();
        	aux2->raiz = arv->raiz->ptrMeioD;
        	printTree(aux2,i);
    	}

    	if(arv->raiz->ptrDireito != NULL){
        	Arvore *aux3 = criarArvore();
        	aux3->raiz = arv->raiz->ptrDireito;
        	printTree(aux3,i);
    	}
    }
   
    return;
 
}

//função para colocar altura
void altura1(Arvore *arv, int valor){
    
    if((arv->raiz) != NULL){
        
        valor++;
        arv->raiz->altura = valor;
        
        if((arv->raiz->ptrEsquerdo) != NULL){
            Arvore *aux = criarArvore();
            aux->raiz = arv->raiz->ptrEsquerdo;
            altura1(aux, valor);
            aux->raiz = arv->raiz->ptrMeioE;
            altura1(aux, valor);
            aux->raiz = arv->raiz->ptrMeioD;
            altura1(aux, valor);
            aux->raiz = arv->raiz->ptrDireito;
            altura1(aux, valor);
            return;
        }
        return;
        
    }
    return;
    
    
}

//função para zerar altura
void altura2(Arvore *arv){
    
    if((arv->raiz) != NULL){
        
        arv->raiz->altura = 0;
        
        if((arv->raiz->ptrEsquerdo) != NULL){
            Arvore *aux = criarArvore();
            aux->raiz = arv->raiz->ptrEsquerdo;
            altura2(aux);
            aux->raiz = arv->raiz->ptrMeioE;
            altura2(aux);
            aux->raiz = arv->raiz->ptrMeioD;
            altura2(aux);
            aux->raiz = arv->raiz->ptrDireito;
            altura2(aux);
            return;
        }
        return;
        
    }
    return;
    
    
}

// função para ver a altura max da arvore
int alturaArvore(Arvore *arv){
	No *aux = criarNo(NULL);
	aux = acharFolha(arv,-10000);
	arv->altura = aux->altura;	
	return arv->altura;
}
