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
#include "matrizEsparsa.h"

int main(){
    
    MatrizEsparsa* mat = criarMatriz(4,4);
    
    inserir(mat, 3,0,8);
    imprimir(mat);
    return 0;
}