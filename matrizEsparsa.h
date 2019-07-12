/************************************
Algoritmos e Estrutura de Dados 1
Prof. Rafael Liberato
-----------------------------------
Exercício: APS Matriz Esparsa
Alunos: Caio Cintra, Eduarda Martins
Data: 11/07/19
*************************************/

#include <stdio.h>
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

// -------------------- PROTÓTIPOS DAS FUNÇÕES -------------------- //

Node *criaSentinela();
Node *criarNo(int linha, int coluna, int valor);
MatrizEsparsa *criarMatriz(int qtdeLinhas, int qtdeColunas);
Node* posicaoLinha(Node *sentinela, int coluna);
Node* posicaoColuna(Node *sentinela, int linha);
int insereEmCima(Node* auxColuna, Node* novo);
int insereEsquerda(Node* auxLinha, Node* novo);
int verifica(MatrizEsparsa *m, int linha, int coluna, int valor);
int inserir(MatrizEsparsa *m, int linha, int coluna, int valor);
int remover(MatrizEsparsa *m, int linha, int coluna);
int acessar(MatrizEsparsa *m, int linha, int coluna);
void imprimir(MatrizEsparsa *m);
void desalocar(MatrizEsparsa *m);

// --------------------- IMPLEMENTAÇÃO --------------------------- //

//Cria um nó do tipo sentinela
Node *criaSentinela(){
	Node *novo = (Node *)malloc(sizeof(Node));
	novo->direita = novo->esquerda = novo;
	novo->cima = novo->baixo = novo;
	return novo;
}

//Cria uma matriz vazia e devolve seu endereço de memória.
//Aloca a matriz por linhas e colunas
MatrizEsparsa *criarMatriz(int qtdeLinhas, int qtdeColunas){
	// Ponteiro do tipo MatrizEsparsa
	MatrizEsparsa *m;
	//Aloca uma matriz com <qtdeLinhas> e <qtdeColunas>
	m = (MatrizEsparsa *)malloc(sizeof(MatrizEsparsa));
	m->linhas = (Node **)calloc(qtdeLinhas, sizeof(Node *));
	m->colunas = (Node **)calloc(qtdeColunas, sizeof(Node *));
	for (int l = 0; l < qtdeLinhas; l++){
		m->linhas[l] = criaSentinela();
	}
	for (int c = 0; c < qtdeColunas; c++){
		m->colunas[c] = criaSentinela();
	}
	//Recebe a quantidade de linhas e colunas que a matriz possui
	m->numLinhas = qtdeLinhas;
	m->numColunas = qtdeColunas;
	// Retorna o endereço de ponteiro para a matriz
	return m;
}

// Função que encontra em qual linha o nó está
Node *posicaoLinha(Node *sentinela, int coluna){
	// Variável auxiliar no processo de percorrer as linhas até encontrar o nó
	Node *aux = sentinela;
	// Procura na matriz (por linhas) aonde o nó está
	while (aux->direita != sentinela && coluna > aux->coluna){
		// aux recebe o endereço do próximo nó à direita dele
		aux = aux->direita;
	}
	//Retorna o endereço de qual é o nó à direita do nó de desejava-se encontrar
	return aux;
}

//Funçao que devolve a posição da coluna desejada
Node *posicaoColuna(Node *sentinela, int linha){
	// 	// Variável auxiliar no processo de percorrer as colunas até encontrar o nó
	Node *aux = sentinela->baixo;
	// Procura na matriz (por colunas) aonde o nó está
	while (aux != sentinela && linha > aux->linha){
		// aux recebe o endereço do próximo nó abaixo dele
		aux = aux->baixo;
	}
	//Retorna o endereço de qual é o nó abaixo do nó de desejava-se encontrar
	return aux;
}

// Insere o <valor> na matriz <m> na linha <linha> e coluna <coluna>.
// Caso a posição já exista, substitua o valor da célula.
// Recebe o endereço da matriz, a linha e coluna nas quais o valor deve ser inserido

Node *criarNo(int linha, int coluna, int valor){
	Node* novo = (Node *)malloc(sizeof(Node));
  novo->linha = linha;
  novo->coluna = coluna;  
  novo->valor = valor;  
	return novo;
}

// Refaz o apontamento dos ponteiros da coluna em que o nó está sendo inserido
int insereEmCima(Node* auxColuna, Node* novo){
	novo->baixo = auxColuna;
	novo->cima = auxColuna->cima;
	auxColuna->cima->baixo = novo;
	auxColuna->cima = novo;
	return 1;
}

// Refaz o apontamento dos ponteiros da linha em que o nó está sendo inserido
int insereEsquerda(Node* auxLinha, Node* novo){
	novo->direita = auxLinha;
	novo->esquerda = auxLinha->esquerda;
	auxLinha->esquerda->direita = novo;
	auxLinha->esquerda = novo;
	return 1;
}

int inserir(MatrizEsparsa *m, int linha, int coluna, int valor){
	//Caso a matriz não esteja alocada ou a coluna na qual deseja inserir o valor
	//seja maior ou menor do que a quantidade de colunas que a matriz possui, a função não 
	//efetua nenhuma operação e retorna 0
	if(linha<0 || coluna<0 || linha>=m->numLinhas || coluna>=m->numColunas){
        return 0;
    }else{
		// Encontra a linha em que está o nó desejado e retorna o valor existente nele
      
      Node* auxColuna = posicaoColuna(m->colunas[coluna], linha);
      if(auxColuna->linha == linha && auxColuna->coluna == coluna){
        auxColuna->valor = valor;
      }else{
        Node* auxLinha = posicaoLinha(m->linhas[linha], coluna);
        Node* novo = criarNo(linha, coluna, valor);
        insereEmCima(auxColuna, novo);
        insereEsquerda(auxLinha, novo);
      }
        return 1;
    }
}

// Remove o elemento da linha <linha> e coluna <coluna> na matriz <m> .
// Devolva 1 caso a remoção seja efetivada e 0 caso contrário.
int remover(MatrizEsparsa *m, int linha, int coluna){
		Node* linhas;
//	int result = acessar(m, linha, coluna);
	//Remove o elemento
	if(linha<0 || coluna<0 || linha>=m->numLinhas || coluna>=m->numColunas){
        return 0;
    }else{
		// Encontra a linha em que está o nó desejado e muda seu valor para NULL
        linhas = posicaoLinha(m->linhas[linha], coluna+1);
        linhas->valor = NULL;
    }
	if(linhas->valor == NULL)
		return 1;
	else
		return 0;
}


int acessar(MatrizEsparsa *m, int linha, int coluna){
	// Devolve o valor correspondente a linha e coluna solicitada.
	// Faça a validação dos índices. Caso a posição solicitada esteja fora do intervalo, devolva zero.
	// No caso da posição estar fora do intervalo a função retornará 0
	if(linha<0 || coluna<0 || linha>=m->numLinhas || coluna>=m->numColunas){
        return 0;
    }else{
		// Encontra a linha em que está o nó desejado e retorna o valor existente nele
        Node* linhas = posicaoLinha(m->linhas[linha], coluna+3);
        return linhas->valor;
    }
}
// Imprime os valores da matriz na tela. Cada linha deve ser impressa em uma linha diferente
// e os elementos separados por espaço ou tabulação. Os elementos não representados na matriz (valor zero),
// também devem ser impressos.
void imprimir(MatrizEsparsa *m){
	Node *aux;
	// Percorre toda a matriz para imprimir cada um de seus elementos
	for (int l = 0; l < m->numLinhas; l++){
		aux = m->linhas[l]->direita;
		for (int c = 0; c < m->numColunas; c++){
			if (aux->coluna == c){
				printf("%3d ", aux->valor);
				aux = aux->direita;
			}else{
				printf("%3d ", 0);
			}
		}
		printf("\n");
	}
	printf("\n");
}

	// Libera toda memória alocada dinamicamente para a matriz.
void desalocar(MatrizEsparsa *m){
	// Percorre cada nó desalocando-os
	for (int l = 0; l < m->numLinhas; l++){
		free(m->linhas[l]->direita);
	}
	for (int c = 0; c < m->numColunas; c++){
		free(m->colunas[c]->direita);
	}
	// Desaloca a quantidade de linhas e colunas antes alocadas
	free(m->linhas);
	free(m->colunas);
	// Desaloca a estrutura MatrizEsparsa
	free(m);
}