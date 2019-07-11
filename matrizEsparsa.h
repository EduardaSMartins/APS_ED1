#include <stdlib.h>

//VERSÃO COM SENTINELA
typedef struct node{
	int linha;
	int coluna;
	int valor;
	struct node *direita;
	struct node *baixo;
	struct node *esquerda;
	struct node *cima;
} Node;

typedef struct{
	Node **linhas;
	//ponteiro para o vetor cujas células são ponteiros de nós
	Node **colunas;
	//ponteiro para o vetor cujas células são ponteiros de nós
	int numLinhas;
	//Quantidade de linhas da matriz
	int numColunas;
	//Quantidade de colunas da matriz
} MatrizEsparsa;

Node* criaSentinela();
// --------------------- IMPLEMENTAÇÃO --------------------------- //
//Cria uma matriz vazia e devolve seu endereço de memória.
MatrizEsparsa *criarMatriz(int qtdeLinhas, int qtdeColunas){
	//Aloca a matriz por linhas e colunas
	MatrizEsparsa* m;
	m = (MatrizEsparsa *)malloc(sizeof(MatrizEsparsa));
	m->linhas = (Node **)calloc(qtdeLinhas, sizeof(Node*));
	m->colunas = (Node **)calloc(qtdeColunas, sizeof(Node*));
	for (int l = 0; l < qtdeLinhas; l++){
		m->linhas[l] = criaSentinela();
	}
	for (int c = 0; c < qtdeLinhas; c++){
		m->colunas[c] = criaSentinela();
	}
	return m;
}

Node* criaSentinela(){
	Node* novo = (Node*) malloc (sizeof(Node));
	novo->direita = novo->esquerda = novo;
	novo->cima = novo->baixo = novo;
	return novo;
}

int inserirEsquerda(Node* referencia, Node* novoNo){
	novoNo->direita = referencia;
	novoNo->esquerda = referencia->esquerda;
	referencia->esquerda->direita = novoNo;
	referencia->esquerda = novoNo;
	if(novoNo->direita==referencia	&& novoNo->esquerda==referencia->esquerda)
		return 1;
	else
		return -1;

}

int insereCima(Node* referencia, Node* novoNo){
	novoNo->baixo = referencia;
	novoNo->cima = referencia->cima;
	referencia->cima->baixo = novoNo;
	referencia->cima = novoNo;
	if(novoNo->baixo==referencia && novoNo->cima->baixo==novoNo)
		return 1;
	else
		return -1;
}


// Insere o <valor> na matriz <m> na linha <linha> e coluna <coluna>.
// Caso a posição já exista, substitua o valor da célula.

//int inserir(MatrizEsparsa *m, int linha, int coluna, int valor){
//	Node* temp;

//	return temp;
//}

int remover(MatrizEsparsa *m, int linha, int coluna);
// Remove o elemento da linha <linha> e coluna <coluna> na matriz <m> .
// Devolva 1 caso a remoção seja efetivada e 0 caso contrário.

int acessar(MatrizEsparsa *m, int linha, int coluna);
// Devolve o valor correspondente a linha e coluna solicitada.
// Faça a validação dos índices. Caso a posição solicitada esteja fora do intervalo, devolva zero.

void imprimir(MatrizEsparsa *m){
	int l,c;
  	Node* aux;
  	for(l = 0; l < m->numLinhas; l++) {    
    	aux = m->linhas[l]->direita; 
    for(c = 0; c < m->numColunas; c++){
      	if(aux->coluna == c){
        	printf("%03d ", aux->valor);
        	aux = aux->direita;
      	}else{
        	printf("%03d ", 0);
      }
    }
    printf("\n");
  }   
  printf("\n");

}
// Imprime os valores da matriz na tela. Cada linha deve ser impressa em uma linha diferente
// e os elementos separados por espaço ou tabulação. Os elementos não representados na matriz (valor zero),
// também devem ser impressos.

void desalocar(MatrizEsparsa *m);
// Libera toda memória alocada dinamicamente para a matriz.
