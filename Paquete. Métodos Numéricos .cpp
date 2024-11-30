#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>

float funcion1(float x){
    return x*x*cos(x)-2*x;
}

float funcion2(float x) {
    return (6 - (2 / (x * x))) * (exp(2 + x) / 4) + 1;
}

float funcion3(float x){
    return pow(x,3) - 3*sin(pow(x,2)) + 1;
}

float funcion4(float x){
    return pow(x,3) + 6*pow(x,2) + 9.4*x + 2.5;
}

void biseccion(float (*funcion)(float), float a, float b, float tolerancia, int maxIteraciones){

    float errorRelativo = tolerancia + 1; // Inicializar para entrar al bucle
    float p, fp, fa; // p, f(p), f(a)
    int iteracion = 0;
    float pO = a; // Valor anterior de p

    if(funcion(a) * funcion(b) > 0){
        printf("Las funciones no son de signos opuestos, no hay raices.\n");
        return;
    }

    printf("\nIteracion | a         | b         | c         | f(c)      | Error Relativo\n");
    printf("-------------------------------------------------------------------------\n");

    while(errorRelativo > tolerancia && iteracion < maxIteraciones){
        p = (a + b)/2;
        fp = funcion(p);
        fa = funcion(a);

        if(iteracion > 0){
            errorRelativo = fabs((p - pO)/p);
        }

        printf("%9d | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f\n", iteracion, a, b, p, fp, errorRelativo);

        if(fp == 0 || errorRelativo < tolerancia){
            printf("Raíz encontrada: %f en la iteracion %d con tolerancia %f\n", p, iteracion, tolerancia);
            return;
        }

        if(fa * fp < 0){
            b = p;
        } else{
            a = p;
        }



        pO = p;
        iteracion++;
    }

    printf("Se alcanzo el maximo de iteraciones (%d) sin encontrar una raiz con la tolerancia deseada. \n", maxIteraciones);
}

void secante(float (*funcion)(float), float x0, float x1, float tolerancia, int maxIteraciones){
    float fx0, fx1, x2;
    float errorRelativo = tolerancia + 1; // Inicializar para entrar al bucle
    int iteracion = 0;

    printf("\nIteracion | x0        | x1        | x2        | f(x2)     | Error Relativo\n");
    printf("-------------------------------------------------------------------------\n");

    while(errorRelativo > tolerancia && iteracion < maxIteraciones){
        fx0 = funcion(x0);
        fx1 = funcion(x1);

        if(fx1 - fx0 == 0){
            printf("ERROR. Division entre 0.\n");
            return;
        }

        x2 = x1 - fx1 * (x1 - x0)/(fx1 - fx0);

        if(tolerancia > 0){
            errorRelativo = fabs((x2 - x1) / x2);
        }


        printf("%9d | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f\n", iteracion, x0, x1, x2, funcion(x2), errorRelativo);

        if (fabs(funcion(x2)) < tolerancia) {
            printf("Raiz encontrada: %f en la iteracion %d con tolerancia %f\n", x2, iteracion, tolerancia);
            return;
        }


        x0 = x1;
        x1 = x2;

        iteracion++;
    }

    printf("Se alcanzo el maximo de iteraciones (%d) sin encontrar una raiz con la tolerancia deseada.  \n", maxIteraciones);
}

void leerMatriz(float **matriz, float *vectorI, int n){
    printf("\n\tLectura de Matriz\n\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("\nIngrese el elemento [%d][%d]: ", i + 1, j + 1);
            if (scanf("%f", &matriz[i][j]) != 1) {
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
    float suma;
    for(int i = 0; i < n; i++){
        suma = 0.0;
        for(int k = 0; k < n; k++){
            if(i != k){
                suma += fabs(matriz[i][k]);
            }
        }
        if(fabs(matriz[i][i]) <= suma){
            return 0; // No es estrictamente dominante diagonal
        }
    }
    return 1; // Es estrictamente dominante diagonal
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
        subMat[i] = (float *)malloc((n - 1) * sizeof(float *));
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

float determinanteTriangulacion(float **matriz, int n){
    float determinante = 1.0;
    float temporal = 0.0;
    float factor = 0.0;

    for(int i = 0; i < n; i++){
        if(matriz[i][i] == 0.0){
            for(int j = i+1; j < n; j++){
                if(matriz[j][i] != 0.0){
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
            return 0.0; // Determinante es cero
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

float calNorma(float vector[], int dimension) {
    float suma = 0.0;
    for (int i = 0; i < dimension; i++) {
        suma += vector[i] * vector[i];
    }
    return sqrt(suma);
}

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

int main(){
	int opcion = 0;
	int rep;
	printf("\tPAQUETE\n");
	printf("Metodos Numericos I\n");

	do{
		printf("\n\tMenu de Opciones\n\n");
		printf("1. Solucion de ecuaciones.\n");
		printf("2. Solucion a sistemas de ecuaciones.\n");
		printf("3. Metodo de Potencias. (Obtencion de valores propios).");

		do{
			printf("\n\nElija la opcion deseada: ");
			scanf("%d", &opcion);
			system("cls");
		}while(opcion < 1);

		switch(opcion){
			case 1:
				{
					int funcion, metodo;
				    int otra = 0; // Inicializar para entrar al bucle
				    float a, b, tolerancia;
				    int iteraciones;
				    float (*funcion_ptr)(float) = NULL;

				    while (otra != 2) {
				        // Selección de función
				        do {
				            printf("\n\n-------------Menu de funciones-------------");
				            printf("\n1. f(x) = x^2 * cos(x) - 2x");
				            printf("\n2. f(x) = (6 - 2x^2) * e^(2 + x^4) + 1");
				            printf("\n3. f(x) = x^3 - 3 * sin(x^2) + 1");
				            printf("\n4. f(x) = x^3 + 6x^2 + 9.4x + 2.5");

				            //Protocolo para verificar si el dato ingresado se trata de un entero y no provocar un error con el programa
				            printf("\n\nElegir una funcion: ");
				            if (scanf("%d", &funcion) != 1) {
				                printf("No te quieras pasar de listo usuario, ya se que no ingresaste un numero entero - _-\n");
				                while(getchar() != '\n'); // Limpiar el buffer
				                funcion = 0;
				            }

				            if (funcion < 1 || funcion > 4) {
				                printf("\nNo es una opcion valida.\n");
				            }
				        } while (funcion < 1 || funcion > 4);

				        // Asignar el puntero a la función seleccionada
				        switch (funcion) {
				            case 1:
				                funcion_ptr = funcion1;
				                break;
				            case 2:
				                funcion_ptr = funcion2;
				                break;
				            case 3:
				                funcion_ptr = funcion3;
				                break;
				            case 4:
				                funcion_ptr = funcion4;
				                break;
				            default:
				                printf("Funcion no valida.\n");
				                exit(1); // Salir del programa
				        }

				        // Selección de método
				        do {
				            printf("\n\n-------------Menu de metodos-------------");
				            printf("\n1. Metodo de biseccion");
				            printf("\n2. Metodo de la secante");

				            printf("\n\nElegir un metodo: ");
				            if (scanf("%d", &metodo) != 1) {
				                printf("Iralo te estoy diciendo que no metas caracteres usuario, si seras si seras!!\n");
				                while(getchar() != '\n'); // Limpiar el buffer
				                metodo = 0;
				            }

				            if (metodo < 1 || metodo > 2) {
				                printf("\nNo es una opcion valida, ingresala de nuevo.\n");
				            }

				        } while (metodo < 1 || metodo > 2);

				        do{
				        	printf("\n\nIngrese valores para el intervalo");
					        printf("\na: ");
					        scanf("%f", &a);

					        printf("b: ");
					        scanf("%f", &b);

					        printf("\nIngrese un maximo de iteraciones: ");
					        if (scanf("%d", &iteraciones) != 1) {
					                printf("nomas no te doy una porque soy un ente virtual usuario . _.\n");
					                while(getchar() != '\n'); // Limpiar el buffer
					                iteraciones = 0;
					            }

					        if(iteraciones <= 0){
					        	printf("\nIteraciones invalidas.");
								continue;
							}
					        printf("\nIngrese una tolerancia: ");
					        scanf("%f", &tolerancia);
					        if(tolerancia <= 0){
					        	printf("\nTolerancia invalida.");
					        	continue;
							}

					        // Ejecutar el método seleccionado
					        if(metodo == 1){
					            biseccion(funcion_ptr, a, b, tolerancia, iteraciones);
					        } else if(metodo == 2){
					            secante(funcion_ptr, a, b, tolerancia, iteraciones);
					        }

					        printf("\n\nDesea obtener otra raiz?\n\n  1 = Si\t2 = No:  ");
				            if (scanf("%d", &otra) != 1) {
				                printf("Entrada invalida. Por favor, ingrese 1 o 2.\n");
				                while(getchar() != '\n');
				                otra = 0; // Forzar reintento
				            }
				            if (otra != 1 && otra != 2) {
				                printf("Opción no valida. Por favor, ingrese 1 o 2.\n");
				            }
						}while(otra == 1);


				        // Preguntar al usuario si desea continuar
				        do {
				            printf("\n\nDesea regresar al menu principal de funciones?\n\n  1 = Si\t2 = No:  ");
				            if (scanf("%d", &otra) != 1) {
				                printf("Entrada invalida. Por favor, ingrese 1 o 2.\n");
				                while(getchar() != '\n');
				                otra = 0; // Forzar reintento
				            }
				            if (otra != 1 && otra != 2) {
				                printf("Opción no valida. Por favor, ingrese 1 o 2.\n");
				            }
				        } while (otra != 1 && otra != 2);
				    }
				}
				break;
			case 2:
				{
					int dimension, EDD;
		            char opc;
		            int otra;

		            printf("\t** SOLUCION A SISTEMAS DE ECUACIONES ** \n\n");

		            printf("\nIngrese la dimension de la matriz: ");
		            do {
		                if (scanf("%d", &dimension) != 1) {
		                    printf("Entrada invalida. Por favor, ingrese un numero entero.\n");
		                    while(getchar() != '\n');
		                    dimension = 0;
		                }
		            } while(dimension <= 0);

		            float **A = (float **)malloc(dimension * sizeof(float *));
		            for(int i = 0; i < dimension; i++){
		                A[i] = (float *)malloc(dimension * sizeof(float));
		            }
		            float *vector = (float *)malloc(dimension * sizeof(float));

		            leerMatriz(A, vector, dimension);
		            imprimeMatriz(A, vector, dimension);

		            if(funcEDD(A, dimension)){
		                printf("\nLa matriz es Estrictamente Dominante Diagonal\n");
		                EDD = 1;
		            } else {
		                printf("\nLa matriz no es Estrictamente Dominante Diagonal\n");
		                EDD = 0;
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
		            } else {
		                float det = determinanteTriangulacion(A, dimension);
		                printf("\nDeterminante de la matriz: %.2f\n", det);
		                if(det != 0){
		                    printf("El sistema tiene solución.\n");
		                } else {
		                    printf("El sistema no tiene solución.\n");
		                }
		            }

		            for(int i = 0; i < dimension; i++){
		                free(A[i]);
		            }
		            free(A);
		            free(vector);

		            do {
				            printf("\n\nDesea ingresar otra matriz?\n\n  1 = Si\t2 = No:  ");
				            if (scanf("%d", &otra) != 1) {
				                printf("Entrada invalida. Por favor, ingrese 1 o 2.\n");
				                while(getchar() != '\n');
				                otra = 0; // Forzar reintento
				            }
				            if (otra != 1 && otra != 2) {
				                printf("Opción no valida. Por favor, ingrese 1 o 2.\n");
				            }
				    } while (otra != 1 && otra != 2);
	    		}
			case 3:
			    int otra;
				do{
                	int dimension, EDD;
		            char opc;

		            printf("\nIngrese la dimension de la matriz: ");
		            do {
		                if (scanf("%d", &dimension) != 1) {
		                    printf("Entrada invalida. Por favor, ingrese un numero entero.\n");
		                    while(getchar() != '\n');
		                    dimension = 0;
		                }
		            } while(dimension <= 0);

		            float **A = (float **)malloc(dimension * sizeof(float *));
		            for(int i = 0; i < dimension; i++){
		                A[i] = (float *)malloc(dimension * sizeof(float));
		            }
		            float *vector = (float *)malloc(dimension * sizeof(float));

		            leerMatriz(A, vector, dimension);
		            imprimeMatriz(A, vector, dimension);
                    verificarDatos(A, vector, dimension);

		            if(funcEDD(A, dimension)){
		                printf("\nLa matriz es Estrictamente Dominante Diagonal\n");
		                EDD = 1;
		            } else {
		                printf("\nLa matriz no es Estrictamente Dominante Diagonal\n");
		                EDD = 0;
		            }
		            if(EDD == 1){
		                int maxIter;
		                float tol;
		                float *vectorInicial = (float *)malloc(dimension * sizeof(float));

		                printf("\nObtencion de valores propios por Metodo de potencias\n");
                        int cuentaUnos;
			            do {
			                cuentaUnos = 0;
						    printf("\nIngrese el vector inicial (debe contener un '1' y los demás valores deben ser '0'):\n");
						    //int cuentaUnos = 0; // Para contar cuántos valores son 1
						    int valid = 1; // Bandera para saber si el vector es válido

						    for (int i = 0; i < dimension; i++) {
						        printf("x[%d]: ", i + 1);
						        if (scanf("%f", &vectorInicial[i]) != 1) {
						            printf("\nEntrada invalida. Por favor, ingrese un numero flotante.\n");
						            valid = 0; // Marcar como no válido si hay una entrada incorrecta
						            break;
						        }

						        if (fabs(vectorInicial[i] - 1.0) < 1e-6) { // Detectar un '1'
						            cuentaUnos++;
						        } else if (fabs(vectorInicial[i]) > 1e-6) { // Detectar algo que no es '0' ni '1'
						            valid = 0;
						            break;
						        }
						    }

						    if (cuentaUnos != 1) {
						        valid = 0; // El vector debe contener exactamente un '1'
						    }

						    if (!valid) {
						        printf("\nEl vector inicial es invalido. Asegúrate de que solo haya un '1' y los demás sean '0'.\n");
						    }
						    float vecINorm=calNorma(vectorInicial,dimension);
						    printf("\nEl vector tiene una norma de: %.2f",vecINorm);

						} while (cuentaUnos != 1);


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
        			do {
				        printf("\n\nDesea ingresar otra matriz?\n\n  1 = Si\t2 = No:  ");
				        if (scanf("%d", &otra) != 1) {
				            printf("Entrada invalida. Por favor, ingrese 1 o 2.\n");
				            while(getchar() != '\n');
				            otra = 0; // Forzar reintento
				        }
				        if (otra != 1 && otra != 2) {
				            printf("Opción no valida. Por favor, ingrese 1 o 2.\n");
				        }
				    } while (otra != 1 && otra != 2);
				}while(otra==1 && otra !=2);

				break;
			default:

				break;
		}

		do {
            printf("\n\nDesea regresar al menu principal?\n\n  1 = Si\t2 = No: ");
            if (scanf("%d", &rep) != 1) {
                printf("Entrada invalida. Por favor, ingrese 1 o 2.\n");
                while (getchar() != '\n');
                rep = 0;
            } else if (rep != 1 && rep != 2) {
                printf("Opción no valida. Por favor, ingrese 1 o 2.\n");
            }
            system("cls");
        } while (rep != 1 && rep != 2);

    } while (rep == 1);

	return 0;
}
