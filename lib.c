#include "lib.h"

matriz_esparsa *carregaMatriz(char *nome){ //nome ou endereco do arquivo
    matriz_esparsa *mat;

    char linha[TAM_BUFFER];

    int m=0, n=0;
    int l=0, c=0;
    float valor=0.0;

    FILE *arquivo;

    arquivo = fopen(nome,"r");
    if (!arquivo){
      arquivo = fopen("arquivo.txt","w");
      fprintf(arquivo, "Erro ao abrir arquivo\n");
      fclose(arquivo);
      return NULL;
    }

    fgets(linha, TAM_BUFFER, arquivo); //le primeira linha
    sscanf(linha, "%d %d", &m, &n);

    if (m<=0 || n<=0){
        return 0;
    }

    mat = cria_matriz_esparsa(m, n);

    while(fgets(linha, TAM_BUFFER, arquivo)){
        sscanf(linha, "%d %d %f", &l, &c, &valor);
        if (valor){
            insereElemento(mat, l, c, valor);
        }
    }
    fclose(arquivo);
    return mat;
}

int salvaMatriz(matriz_esparsa *mat){ //nome ou endereco do arquivo
    int m= mat->m;
	int n= mat->n;

	 int i, j;
    tipo_celula *apontaCelula;

    if (!mat || !mat->m || !mat->n){
        return 0;
    }

    FILE *arquivo;

    arquivo = fopen("resultado.txt","w");
    if (!arquivo){
      arquivo = fopen("arquivo.txt","w");
      fprintf(arquivo, "Erro ao abrir arquivo\n");
      fclose(arquivo);
      return 0;
    }
    apontaCelula = mat->inicio->abaixo;
	fprintf(arquivo,"%d %d\n", m, n);
    for (i = 1; i <= mat->m; i++){
        for (j = 1; j <= mat->n; j++){
            if (apontaCelula->direita->linha == i && apontaCelula->direita->coluna == j){
                apontaCelula = apontaCelula->direita;
                fprintf(arquivo, "%d %d %0.2f\n",apontaCelula->linha, apontaCelula->coluna, apontaCelula->valor);
            }
        }

        apontaCelula = apontaCelula->direita->abaixo;
    }

    fclose(arquivo);

    return 1;
}

matriz_esparsa *cria_matriz_esparsa(int m, int n){
    matriz_esparsa *mat;
	mat = (matriz_esparsa *)malloc(sizeof(matriz_esparsa));

	if (!mat || m<=0 || n<=0){
        return 0;
	}

	//inicia as variaveis da struct
	mat->inicio = NULL;
	mat->fimLinha = NULL;
	mat->fimColuna = NULL;
	mat->m = m;
	mat->n = n;

	iniciaCabecas(mat);

	return mat;
}

int iniciaCabecas(matriz_esparsa *mat){ //cria a estrutura
    int i=0;

    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0; //erro
    }

    //celula principal
    cabeca->coluna = -1;
    cabeca->linha = -1;

    mat->inicio = cabeca;
    mat->fimLinha = cabeca;
    mat->fimColuna = cabeca;

    for (i = 1; i <= mat->n; i++){ //cria celulas cabecas das colunas
        insereCabecaColuna(mat);
    }
    for (i = 1; i <= mat->m; i++){ //cria celulas cabecas das linhas
        insereCabecaLinha(mat);
    }
    return 1;
}
int insereCabecaColuna(matriz_esparsa *mat){
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0;
    }

    cabeca->coluna = -1;
    cabeca->linha = 0;

    mat->fimColuna->direita = cabeca;
    mat->fimColuna = cabeca;

    cabeca->direita = mat->inicio;
    cabeca->abaixo = cabeca;
    return 1;
}

int insereCabecaLinha(matriz_esparsa *mat){
    tipo_celula *cabeca;
    cabeca = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!cabeca){
        return 0;
    }

    cabeca->coluna = 0;
    cabeca->linha = -1;

    mat->fimLinha->abaixo = cabeca;
    mat->fimLinha = cabeca;

    cabeca->abaixo = mat->inicio;
    cabeca->direita = cabeca;

    return 1;
}

int insereElemento(matriz_esparsa *mat, int linha, int coluna, float valor){
    int i;

    if (!mat || mat->m <= 0 || mat->n <= 0 || !valor){ //verifica restricoes dos parametros recebidos
        return 0;
    }
    if (linha>mat->m || coluna>mat->n || !valor || linha < 1 || coluna < 1){
        return 0;
    }

    tipo_celula *novaCelula; //ponteiro para celula a ser inserida
    tipo_celula *ponteiroColuna; //ponteiro para controle da coluna
    tipo_celula *ponteiroLinha; //ponteiro para controle da linha

    novaCelula = (tipo_celula*)malloc(sizeof(tipo_celula));

    if (!novaCelula){
        return 0;
    }

    novaCelula->linha = linha;
    novaCelula->coluna = coluna;
    novaCelula->valor = valor;

    ponteiroLinha = mat->inicio->abaixo; // aponta para a primeira cabeca so de linha
    ponteiroColuna = mat->inicio->direita; // aponta para a primeira cabeca so de coluna

    //Percorre nas cabecas ate a linha do elemento
    for (i=1; i<linha; i++){
        ponteiroLinha = ponteiroLinha->abaixo;
    }
    i=1;
    while (i<coluna && ponteiroLinha->direita->linha != -1){
        if (ponteiroLinha->direita->coluna > novaCelula->coluna){ //se a celula inserida esta a esquerda
            novaCelula->direita = ponteiroLinha->direita;
            ponteiroLinha->direita = novaCelula;
        }
        else{
            ponteiroLinha = ponteiroLinha->direita; //anda pelas celulas a direita
        }
        i++;
    }
    if (ponteiroLinha->direita->linha == -1){ //a celula esta mais a direita
        novaCelula->direita = ponteiroLinha->direita; //aponta para a cabeca
        ponteiroLinha->direita = novaCelula; //ultima celula ou cabeca, senao tiver celulas, aponta para a celula
    }

    //Percorre nas cabecas ate a coluna do elemento
    for (i = 1; i < coluna; i++){
        ponteiroColuna = ponteiroColuna->direita;
    }
    i=1;
    while (i<linha && ponteiroColuna->abaixo->coluna != -1){
        if (ponteiroColuna->abaixo->linha > novaCelula->linha){
            novaCelula->abaixo = ponteiroColuna->abaixo;
            ponteiroColuna->abaixo = novaCelula;
        }
        else{
            ponteiroColuna = ponteiroColuna->abaixo; //anda pelas celulas abaixo
        }
        i++;
    }
    if (ponteiroColuna->abaixo->coluna == -1){
        novaCelula->abaixo = ponteiroColuna->abaixo; //aponta para a cabeca
        ponteiroColuna->abaixo = novaCelula; //ultima celula ou cabeca, senao tiver celulas, aponta para a celula
    }
    return 1;
}

int imprimeMatriz(matriz_esparsa *mat){
    int i, j;
    tipo_celula *apontaCelula;

    if (!mat || !mat->m || !mat->n){
        return 0;
    }

    apontaCelula = mat->inicio->abaixo;

    printf("\n");

    for (i = 1; i <= mat->m; i++){
        for (j = 1; j <= mat->n; j++){
            if (apontaCelula->direita->linha == i && apontaCelula->direita->coluna == j){
                apontaCelula = apontaCelula->direita;
                printf("  \t%0.2f   ", apontaCelula->valor);
            }
            else{
                printf("  \t%0.2f   ", 0.0F);
            }
        }
        printf("\n");
        apontaCelula = apontaCelula->direita->abaixo;
    }

    return 1;
}

float obtemElementoPeloIndice(matriz_esparsa *mat, int linha, int coluna){
    tipo_celula *apontaCelula;
    int i = 0;

    apontaCelula = mat->inicio->direita;

    for (i = 1; i < coluna; i++){ //chega na coluna desejada
        apontaCelula = apontaCelula->direita;
    }

    do{
        apontaCelula = apontaCelula->abaixo;
        if (apontaCelula->linha == linha){
            return apontaCelula->valor;
        }
    }while(apontaCelula->coluna != -1);

    return 0; //elemento nao encontrado
}

matriz_esparsa *multiplicaMatriz(matriz_esparsa *matA, matriz_esparsa *matB){
    int i=0, j=0, k=0;
    float total;
    matriz_esparsa *matC;

    if (matA->n != matB->m){ //so pode multiplicar se o numero de colunas de A eh igual ao numero de linhas de B
        printf("\nNao foi possivel multiplicar as matrizes\nnumero de colunas de A eh diferente do numero de linhas de B\n");
        return NULL;
    }

    if (!matA || !matB || !matA->m || !matA->n || !matB->n){
        return NULL;
    }

    matC = cria_matriz_esparsa(matA->m, matB->n); //C � formada pelo numero de linhas de A e de colunas de B

    for (i = 1; i <= matA->m; i++){
        for (j = 1; j <= matB->n; j++){
            total = 0;
            for (k = 1; k <= matA->n; k++){
                total += obtemElementoPeloIndice(matA,i,k) * obtemElementoPeloIndice(matB,k,j);
            }
            if (total){
                insereElemento(matC,i,j,total);
            }
        }
    }
    return matC;
}
