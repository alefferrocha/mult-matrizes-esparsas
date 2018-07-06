#include "lib.h"

int main(void){

    matriz_esparsa *matrizA = NULL;
    matriz_esparsa *matrizB = NULL;
	matriz_esparsa *matrizC = NULL;
    matrizA = carregaMatriz("matriz-a.txt");
    printf("-> Matriz A\n");
    imprimeMatriz(matrizA);

    matrizB = carregaMatriz("matriz-b.txt");
    printf("\n-> Matriz B\n");
    imprimeMatriz(matrizB);

	printf("\n-> Matriz C\n");
    matrizC = multiplicaMatriz(matrizA, matrizB);
    imprimeMatriz(matrizC);

    return 0;
}
