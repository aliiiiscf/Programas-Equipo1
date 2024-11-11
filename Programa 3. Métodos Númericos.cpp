/*
PROGRAMA 3. MÉTODOS NUMÉRICOS
INTEGRANTE:
    -) CAMACHO FLORES ALITZEL SOPHIA
    -) HERRERA HERNÁNDEZ DIEGO
    -) MEDINA HERNÁNDEZ RAMÓN
    -) VELÁZQUEZ MARTÍNEZ ANTONIO

GRUPO: 1301
FECHA: 11 DE NOVIEMBRE 2024

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float norma(float *vectorA, float *vectorAn, int n){
    float maximo = fabs(vectorA[0] - vectorAn[0]);
    for(int i = 1; i < n; i++){
        float diferencia = fabs(vectorA[i] - vectorAn[i]);
        if(diferencia > maximo){
            maximo = diferencia;
        }
    }
    return maximo;
}

void metodoJacobi(float **A, float *vector, int n, float *vectorInicial, int maxIter, float tol) {
    float *aproximacionAnterior = (float *)malloc(n * sizeof(float));
    float *aproximacionActual = (float *)malloc(n * sizeof(float));

    // Inicializar la aproximación con el vector inicial
    for (int i = 0; i < n; i++) {
        aproximacionAnterior[i] = vectorInicial[i];
    }

    // Bucle de iteración
    for (int iter = 0; iter < maxIter; iter++) {
        // Para cada fila, calcular la nueva aproximación
        for (int i = 0; i < n; i++) {
            float suma = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    suma += A[i][j] * aproximacionAnterior[j];
                }
            }
            aproximacionActual[i] = (vector[i] - suma) / A[i][i];
        }

        // Calcular el error y mostrar el vector actual y el error en cada iteración
        float error = norma(aproximacionActual, aproximacionAnterior, n);
        printf("Iteracion %d:\n", iter + 1);
        printf("Vector actual: [");
        for (int i = 0; i < n; i++) {
            printf(" %.8f", aproximacionActual[i]);
            if (i < n - 1) printf(",");
        }
        printf(" ]\n");
        printf("Error: %.8f\n\n", error);

        // Verificar si se ha alcanzado la tolerancia para detener las iteraciones
        if (error < tol) {
            printf("Convergencia alcanzada despues de %d iteraciones.\n\n", iter + 1);
            break;
        }

        // Copiar la aproximación actual para usarla en la siguiente iteración
        for (int i = 0; i < n; i++) {
            aproximacionAnterior[i] = aproximacionActual[i];
        }
    }

    // Imprimir la solución final obtenida
    printf("Solucion aproximada por Jacobi:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.8f\n", i, aproximacionActual[i]);
    }

    free(aproximacionAnterior);
    free(aproximacionActual);
}

void leerMatriz(float **matriz, float *vectorI, int n){
    printf("\n\tLectura de Matriz\n\n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("\nIngrese el elemento [%d][%d]: ", i + 1, j + 1);

            if (scanf("%f", &matriz[i][j])!=1) {
                printf("Entrada invalida. Por favor, ingrese un numero flotante.\n");
                while(getchar() != '\n');
                matriz[i][j] = 0;
            }
        }
    }
    printf("\n\tLectura del vector independiente.\n\n");

    for(int i = 0; i < n; i++){
        printf("\nIngrese el elemento [%d]: ", i + 1);
        scanf("%f", &vectorI[i]);
    }
}

void imprimeMatriz(float **matriz, float *vectorI, int n){
    printf("\n\tMatriz:\n\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("[%.2f]", matriz[i][j]);
        }
        printf(" | [%.2f]\n", vectorI[i]);
    }
}

int funcEDD(float **matriz, int n){
    float max, suma;
    for(int i = 0; i < n; i++){
        suma = 0.0;
        for(int k = 0; k < n; k++){
            if(matriz[i][i] != matriz[i][k]){
                suma += fabs(matriz[i][k]);
            }
        }
        if(matriz[i][i] < suma){
            return 0;
        }
    }
    return 1;
}

float determinanteTriangulacion(float **matriz, int n){
	float determinante = 1.0;
	float temporal = 0.0;
	float factor = 0.0;

	for(int i = 0; i < n; i++){
		if(matriz[i][i] == 0.0){
			for(int j = i+1; j < n; j++){
				if(matriz[j][i]  != 0.0){
					for(int k = 0; k < n; k++){
						temporal = matriz[i][k];
						matriz[i][k] = matriz[j][k];
						matriz[j][k] = temporal;
					}
					determinante *= -1.0;
					break;
				}
			}
		}

		if(matriz[i][i] == 0.0){
			return 0.0;
		}

		for(int j = i+1; j < n; j++){
			factor = matriz[j][i] / matriz[i][i];
			for(int k = 0; k < n; k++){
				matriz[j][k] -= factor * matriz[i][k];
			}
		}
	}

	for(int i = 0; i < n; i++){
		determinante *= matriz[i][i];
	}

	return determinante;
}

int main() {
    int dimension, EDD;
    char opc;

    printf("\t\tPROGRAMA 3. METODOS NUMERICOS.\n\n");
    do{
        float det = 0.0;
        printf("\nIngrese la dimension de la matriz: ");
        do{
            if (scanf("%d", &dimension)!=1) {
                printf("Entrada invalida. Por favor, ingrese un numero entero.\n");
                while(getchar() != '\n');
                dimension = 0;
            }
        }while(dimension <= 0);

        float **A = (float **) malloc(dimension * sizeof(float *));
        for(int i = 0; i < dimension; i++){
            A[i] = (float *) malloc(dimension * sizeof(float));
        }
        float *vector = (float *) malloc(dimension * sizeof(float));

        leerMatriz(A, vector, dimension);
        imprimeMatriz(A, vector, dimension);

        if(funcEDD(A, dimension)){
            printf("\nLa matriz es Estrictamente Dominante Diagonal\n");
            EDD=1;
        } else {
            printf("\nLa matriz no es Estrictamente Dominante Diagonal\n");
            EDD=0;
        }

        if(EDD == 1){
            int maxIter;
            float tol;
            float *vectorInicial = (float *)malloc(dimension * sizeof(float));
            printf("\nSolucion del sistema por medio del metodo de Jacobi\n");
            printf("\nIngrese el vector inicial:\n");
            for(int i = 0; i < dimension; i++){
                printf("x[%d]: ", i + 1);
                scanf("%f", &vectorInicial[i]);
            }
            printf("\nIngrese el numero maximo de iteraciones: ");
            scanf("%d", &maxIter);
            printf("\nIngrese la tolerancia: ");
            scanf("%f", &tol);

            metodoJacobi(A, vector, dimension, vectorInicial, maxIter, tol);

            free(vectorInicial);
        }

        for(int i = 0; i < dimension; i++){
            free(A[i]);
        }
        free(A);
        free(vector);

        printf("\n%cQuieres ingresar otra matriz? [S / N]: ", 191);
        do{
            if (scanf(" %c", &opc)!=1) {
                printf("Entrada invalida. Por favor, ingrese un caracter.\n");
                while(getchar() != '\n');
                opc = 0;
            }
        }while(opc != 'S' && opc != 'N' && opc != 's' && opc != 'n');

    }while(opc == 'S' || opc == 's');

    return 0;
}

