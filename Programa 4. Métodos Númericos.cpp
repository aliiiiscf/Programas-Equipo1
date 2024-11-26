/*
PROGRAMA 4. MÉTODOS NUMÉRICOS
INTEGRANTE:
    -) CAMACHO FLORES ALITZEL SOPHIA
    -) HERRERA HERNÁNDEZ DIEGO
    -) MEDINA HERNÁNDEZ RAMÓN
    -) VELÁZQUEZ MARTÍNEZ ANTONIO

GRUPO: 1301
FECHA: 25 DE NOVIEMBRE 2024

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float norma(float *vectorA, float *vectorAn, int n,float tol){
    float maximo = fabs(vectorA[0] - vectorAn[0]);
    for(int i = 1; i < n; i++){
        float diferencia = fabs(vectorA[i] - vectorAn[i]);
        if(diferencia > maximo){
            maximo = diferencia;
        }
    }
    if (fabs(maximo - 1.0) < tol) {
        printf("\nLa norma esta cerca de 1");
        } else {
            printf("\nLa norma no esta cerca de 1");
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
        float error = norma(aproximacionActual, aproximacionAnterior, n, tol);
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
                matriz[i][j] = 0.0;
            }
        }
    }
    printf("\n\tLectura del vector independiente.\n\n");

    for(int i = 0; i < n; i++){
        printf("\nIngrese el elemento [%d]: ", i + 1);
        if (scanf("%f", &vectorI[i]) != 1) {
            printf("Entrada invalida. Se asignara 0.\n");
            while (getchar() != '\n');
            vectorI[i] = 0.0; // Valor predeterminado
        }
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

void verificarDatos(float **matriz, float *vectorI, int n){
	char correcto;
	int fila, columna;

	while(1){
		printf("\n\nLos datos de la Matriz son correctos? (S/N): ");
		do{
				if (scanf("%c", &correcto)!=1) {
			        printf("Entrada invalida. Por favor, ingrese un caracter.\n");
			        while(getchar() != '\n');
			    	correcto = NULL;
				}
			}while(correcto != 'S' && correcto != 'N' && correcto != 's' && correcto != 'n');
		if(correcto == 's' || correcto == 'S'){
			break;
		}else{

			printf("\nIngrese el indice de la fila a modificar: ");
			do{
				if (scanf("%d", &fila)!=1) {
			        printf("Entrada invalida. Por favor, ingrese un numero entero.\n");
			        while(getchar() != '\n');
			    	fila = 0;
				}
			}while(fila <= 0);
			printf("\nIngrese el indice de la columna a modificar: ");
			do{
				if (scanf("%d", &columna)!=1) {
	        		printf("Entrada invalida. Por favor, ingrese un numero entero.\n");
	        		while(getchar() != '\n');
	    			columna = 0;
				}
			}while(columna <= 0);
			if(fila > n || columna > n){
				printf("\n\nEl elemento [%d][%d] no se encuentra en la Matriz.", fila, columna);
				continue;
			}

			printf("\nIngrese el nuevo dato para [%d][%d]: ", fila, columna);
			scanf("%f", &matriz[fila -1][columna - 1]);

			imprimeMatriz(matriz, vectorI, n);

		}
		break;
	}
}

void obtenerSubMatriz(float **A, float **subMat, int n, int fila, int columna) {
    int filaSub = 0, colSub = 0;

    for (int i = 0; i < n; i++) {
        if (i == fila) continue;

        colSub = 0; // Reset columna para cada nueva fila en subMatriz
        for (int j = 0; j < n; j++) {
            if (j == columna) continue;

            subMat[filaSub][colSub] = A[i][j];
            colSub++;
        }
        filaSub++;
    }
}

float calculaDeterminante(float **A, int n) {
    if (n == 1) {
        return A[0][0];
    }

    if (n == 2) {
        return A[0][0] * A[1][1] - A[1][0] * A[0][1];
    }

    float determinante = 0.0;
    float **subMat = (float **)malloc((n - 1) * sizeof(float *));
    for (int i = 0; i < n - 1; i++) {
        subMat[i] = (float *)malloc((n - 1) * sizeof(float));
    }

    for (int j = 0; j < n; j++) {
        obtenerSubMatriz(A, subMat, n, 0, j);
        determinante += A[0][j] * calculaDeterminante(subMat, n - 1) * ((j % 2 == 0) ? 1 : -1);
    }

    for (int i = 0; i < n - 1; i++) {
        free(subMat[i]);
    }
    free(subMat);

    return determinante;
}

void calcularCofactores(float **A, float **cofA, int n) {
    float **subMat = (float **)malloc((n - 1) * sizeof(float *));
    for (int i = 0; i < n - 1; i++) {
        subMat[i] = (float *)malloc((n - 1) * sizeof(float));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            obtenerSubMatriz(A, subMat, n, i, j);
            cofA[i][j] = calculaDeterminante(subMat, n - 1) * ((i + j) % 2 == 0 ? 1 : -1);
        }
    }

    for (int i = 0; i < n - 1; i++) {
        free(subMat[i]);
    }
    free(subMat);
}

void transpuesta(float **A, float **transpuesta, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transpuesta[j][i] = A[i][j];
        }
    }
}

int calcularInversa(float **A, float **inversa, int n) {
    float det = calculaDeterminante(A, n);
    if (fabs(det) < 1e-6) {
        printf("\nLa matriz es singular, no tiene inversa.\n");
        return 0; // No inversa
    }

    float **cofA = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        cofA[i] = (float *)malloc(n * sizeof(float));
    }

    calcularCofactores(A, cofA, n);

    float **adjunta = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        adjunta[i] = (float *)malloc(n * sizeof(float));
    }

    transpuesta(cofA, adjunta, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inversa[i][j] = adjunta[i][j] / det;
        }
    }

    for (int i = 0; i < n; i++) {
        free(cofA[i]);
        free(adjunta[i]);
    }
    free(cofA);
    free(adjunta);

    return 1; // Inversa calculada exitosamente
}


float** Inversa(float **A, int n) {//copia de la funcion calcular inversa que en este caso si devuelve una matriz
    float det = calculaDeterminante(A, n);
    if (fabs(det) < 1e-6) {
        printf("\nLa matriz es singular, no tiene inversa.\n");
        return 0; // No inversa
    }

    float **cofA = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        cofA[i] = (float *)malloc(n * sizeof(float));
    }

    calcularCofactores(A, cofA, n);

    float **adjunta = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        adjunta[i] = (float *)malloc(n * sizeof(float));
    }

    transpuesta(cofA, adjunta, n);

    float **inversa = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        inversa[i] = (float *)malloc(n * sizeof(float));
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inversa[i][j] = adjunta[i][j] / det;
        }
    }

    for (int i = 0; i < n; i++) {
        free(cofA[i]);
        free(adjunta[i]);
    }
    free(cofA);
    free(adjunta);

    return inversa; // regresa matriz inversa

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
        if(fabs(matriz[i][i]) <= suma){
            return 0;
        }
    }
    return 1;
}

void metodoPotencias(float **matriz, int n, float *vectorInicial, int iteracionesMaximas, float tolerancia) {
    float *vectorActual = (float *)malloc(n * sizeof(float)); // Vector actual
    float *vectorTemporal = (float *)malloc(n * sizeof(float)); // Vector temporal
    float valorPropio = 0.0, valorPropioAnterior = 0.0;
    int iteracion;

    // Inicializar el vector actual con el vector inicial
    for (int i = 0; i < n; i++) {
        vectorActual[i] = vectorInicial[i];
    }

    printf("\nMetodo de Potencias:\n");

    for (iteracion = 0; iteracion < iteracionesMaximas; iteracion++) {
        // Multiplicación matriz-vector: vectorTemporal = matriz * vectorActual
        for (int i = 0; i < n; i++) {
            vectorTemporal[i] = 0.0;
            for (int j = 0; j < n; j++) {
                vectorTemporal[i] += matriz[i][j] * vectorActual[j];
            }
        }

        // Normalizar vectorTemporal para obtener el nuevo vectorActual
        float normaVectorTemporal = 0.0;
        for (int i = 0; i < n; i++) {
            normaVectorTemporal += vectorTemporal[i] * vectorTemporal[i];
        }
        normaVectorTemporal = sqrt(normaVectorTemporal);

        for (int i = 0; i < n; i++) {
            vectorActual[i] = vectorTemporal[i] / normaVectorTemporal;
        }

        // Calcular el nuevo valor propio aproximado
        valorPropioAnterior = valorPropio;
        valorPropio = 0.0;
        for (int i = 0; i < n; i++) {
            valorPropio += vectorActual[i] * vectorTemporal[i]; // Producto escalar
        }

        // Imprimir estado de cada iteración
        printf("Iteracion %d:\n", iteracion + 1);
        printf("  Valor propio aproximado: %.8f\n", valorPropio);
        printf("  Vector propio aproximado: [");
        for (int i = 0; i < n; i++) {
            printf(" %.8f", vectorActual[i]);
            if (i < n - 1) printf(",");
        }
        printf(" ]\n");

        // Verificar convergencia
        if (fabs(valorPropio - valorPropioAnterior) < tolerancia) {
            printf("\nConvergencia alcanzada despues de %d iteraciones.\n", iteracion + 1);
            break;
        }
    }

    if (iteracion == iteracionesMaximas) {
        printf("\nEl metodo no alcanzo la convergencia en %d iteraciones.\n", iteracionesMaximas);
    }

    // Imprimir resultados finales
    printf("\nValor propio dominante: %.8f\n", valorPropio);
    printf("Vector propio asociado: [");
    for (int i = 0; i < n; i++) {
        printf(" %.8f", vectorActual[i]);
        if (i < n - 1) printf(",");
    }
    printf(" ]\n");

    free(vectorActual);
    free(vectorTemporal);
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

float valorpropiomin(float **matriz, int n, float *vectorInicial, int iteracionesMaximas, float tolerancia){
    float *vectorActual = (float *)malloc(n * sizeof(float)); // Vector actual
    float *vectorTemporal = (float *)malloc(n * sizeof(float)); // Vector temporal
    float valorPropio = 0.0, valorPropioAnterior = 0.0;
    int iteracion;

    matriz=Inversa(matriz, n);

    // Inicializar el vector actual con el vector inicial
    for (int i = 0; i < n; i++) {
        vectorActual[i] = vectorInicial[i];
    }

    printf("\nMetodo de Potencias:\n");

    for (iteracion = 0; iteracion < iteracionesMaximas; iteracion++) {
        // Multiplicación matriz-vector: vectorTemporal = matriz * vectorActual
        for (int i = 0; i < n; i++) {
            vectorTemporal[i] = 0.0;
            for (int j = 0; j < n; j++) {
                vectorTemporal[i] += matriz[i][j] * vectorActual[j];
            }
        }

        // Calcular norma 2 de vectorTemporal para normalizar
        float normaVectorTemporal = 0.0;
        for (int i = 0; i < n; i++) {
            normaVectorTemporal += vectorTemporal[i] * vectorTemporal[i];
        }
        normaVectorTemporal = sqrt(normaVectorTemporal);

        // Normalizar vectorTemporal para obtener el nuevo vectorActual
        for (int i = 0; i < n; i++) {
            vectorActual[i] = vectorTemporal[i] / normaVectorTemporal;
        }

        // Calcular el nuevo valor propio aproximado
        valorPropioAnterior = valorPropio;
        valorPropio = 0.0;
        for (int i = 0; i < n; i++) {
            valorPropio += vectorActual[i] * vectorTemporal[i]; // Aproximación del valor propio
        }



        // Verificar convergencia
        if (fabs(valorPropio - valorPropioAnterior) < tolerancia) {
            break;
        }
    }

    float valorPropioMin;

    valorPropioMin=1/valorPropio;

    // Imprimir resultados finales
    printf("\nValor propio minimo: %.8f\n", valorPropioMin);


    free(vectorActual);
    free(vectorTemporal);

}








int main() {
    int dimension, EDD;
    char opc;
    int countOnes = 0; // Para contar cuántos valores son 1

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
        verificarDatos(A, vector, dimension);

        if(funcEDD(A, dimension)){
            printf("\nLa matriz es Estrictamente Dominante Diagonal\n");
            EDD=1;
            // Verificar si el determinante es diferente de cero
		    det = determinanteTriangulacion(A, dimension); // Llama a la función para calcular el determinante
		    if (fabs(det) < 1e-6) { // Usa una tolerancia pequeña para evitar errores de precisión
		        printf("\nEl determinante de la matriz es %.8f. El sistema no tiene solucion unica.\n", det);
		        EDD = 0; // No aplicar Jacobi si el determinante es cero
		    } else {
		        printf("\nEl determinante de la matriz es %.8f. El sistema tiene solucion unica.\n", det);
		    }
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
            
            printf("\nObtencion de valores propios por Metodo de potencias\n");
            do {
			    printf("\nIngrese el vector inicial (debe contener un '1' y los demás valores deben ser '0'):\n");
			    //int countOnes = 0; // Para contar cuántos valores son 1
			    int valid = 1; // Bandera para saber si el vector es válido
			
			    for (int i = 0; i < dimension; i++) {
			        printf("x[%d]: ", i + 1);
			        if (scanf("%f", &vectorInicial[i]) != 1) {
			            printf("\nEntrada invalida. Por favor, ingrese un numero flotante.\n");
			            valid = 0; // Marcar como no válido si hay una entrada incorrecta
			            break;
			        }
			
			        if (fabs(vectorInicial[i] - 1.0) < 1e-6) { // Detectar un '1'
			            countOnes++;
			        } else if (fabs(vectorInicial[i]) > 1e-6) { // Detectar algo que no es '0' ni '1'
			            valid = 0;
			            break;
			        }
			    }
			
			    if (countOnes != 1) {
			        valid = 0; // El vector debe contener exactamente un '1'
			    }
			
			    if (!valid) {
			        printf("\nEl vector inicial es invalido. Asegúrate de que solo haya un '1' y los demás sean '0'.\n");
			    }
			} while (countOnes != 1);

			
            printf("\nIngrese el numero maximo de iteraciones: ");
            scanf("%d", &maxIter);
            printf("\nIngrese la tolerancia: ");
            scanf("%f", &tol);
            metodoPotencias(A, dimension, vectorInicial, maxIter, tol);
            valorpropiomin(A, dimension, vectorInicial, maxIter, tol);


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
