#ifndef _H_SPARSEM_
#define _H_SPARSEM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 255

#ifndef _H_NO_CELULA_
#define _H_NO_CELULA_

typedef struct t_celula{
    struct t_celula *direita, *abaixo;
    int linha, coluna;
    float valor;
}tipo_celula;
#endif


#ifndef _H_NO_SPARSEM_
#define _H_NO_SPARSEM_

typedef struct{
    int m, n;
    tipo_celula *inicio, *fimLinha, *fimColuna;
}tipo_matriz_esparsa;

#endif

typedef tipo_matriz_esparsa matriz_esparsa;

matriz_esparsa *carregaMatriz(char *nome);
matriz_esparsa *cria_matriz_esparsa(int m, int n);

int iniciaCabecas(matriz_esparsa *mat);
int insereCabecaLinha(matriz_esparsa *mat);
int insereCabecaColuna(matriz_esparsa *mat);

int salvaMatriz(matriz_esparsa *mat);

int insereElemento(matriz_esparsa *mat, int linha, int coluna, float valor);

matriz_esparsa *multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB);

float obtemElementoPeloIndice(matriz_esparsa *mat, int linha, int coluna);

int imprimeMatriz(matriz_esparsa *mat);

#endif
