/*trabalho Estruturtra de dados 2
arvore 2-3-4*/

struct No {
    
    int n;
    
    int valor0;
    int valor1;
    int valor2;
    int valor3;
    int contador;
    int altura;
    
    struct No *pai;
    struct No *ptrEsquerdo;
    struct No *ptrMeioE;
    struct No *ptrMeioD;
    struct No *ptrAux;
    struct No *ptrDireito;
    
};
typedef struct No No;

struct Arvore{
    No *raiz;
    int altura = 0;
};
typedef struct Arvore Arvore;

No* criarNo(No *ptr);
Arvore* criarArvore();

void inserir(Arvore *arv, int valor);
void procurarElemento(Arvore *arv, int valor);
void printTree(Arvore *arv, int i);

void balancear(Arvore *arv);
void altura1(Arvore *arv, int valor);
void altura2(Arvore *arv);

int valorExistente(Arvore *arv, int valor);
int alturaArvore(Arvore *arv);
