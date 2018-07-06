#include "lib.h"

int main(void){

    matriz_esparsa *matrizA = NULL;
    matriz_esparsa *matrizB = NULL;
    matriz_esparsa *matrizC = NULL;
    char nome_arquivo_matriz_A[100], nome_arquivo_matriz_B[100];

    puts("Digite o nome do arquivo da primeira matriz:");
    puts("Exemplo: matriz_A.txt");
    scanf("%[^\n]s", nome_arquivo_matriz_A);
    setbuf(stdin, NULL);

    matrizA = carregaMatriz(nome_arquivo_matriz_A);
    if (matrizA == NULL){
    	return 0;
	}

    puts("\nDigite o nome do arquivo da segunda matriz:");
    puts("Exemplo: matriz_B.txt");
    scanf("%[^\n]s", nome_arquivo_matriz_B);
    setbuf(stdin, NULL);

    matrizB = carregaMatriz(nome_arquivo_matriz_B);
    if (matrizB == NULL){
    	return 0;
	}

    printf("-----------------------------------------------------\n");
    printf("\n\n-> Matriz A\n");
    imprimeMatriz(matrizA);
    printf("-----------------------------------------------------\n");
    printf("\n-> Matriz B\n");
    imprimeMatriz(matrizB);
    printf("-----------------------------------------------------\n");
    printf("\nMultiplicando Matrizes...\n");
    printf("\nmatriz_C = matriz_A * matriz_B\n\n");
    matrizC = multiplicaMatriz(matrizA, matrizB);
    printf("-----------------------------------------------------\n");
    printf("\n-> Matriz C\n");
    imprimeMatriz(matrizC);
    printf("-----------------------------------------------------\n");
    salvaMatriz(matrizC);
    printf("Resultado salvo no arquivo \" resultado.txt\"");
    return 1;
}
