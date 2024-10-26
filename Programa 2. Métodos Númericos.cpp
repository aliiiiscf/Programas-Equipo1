/*
PROGRAMA 2. MÉTODOS NÚMERICOS
INTEGRANTE:
	-) CAMACHO FLORES ALITZEL SOPHIA
	-) HERRERA HERNÁNDEZ DIEGO
	-) MEDINA HERNÁNDEZ RAMÓN
	-) VELÁZQUEZ MARTÍNEZ ANTONIO

GRUPO: 1301
FECHA: 26 OCTUBRE 2024 

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	
	/*printf("\n\tVector Independiente: \n\n");
	for(int i = 0; i < n; i++){
		printf("[%.2f]", vectorI[i]);
	}*/
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

int funcEDD(float **matriz, int n){
	float max,suma;
	for(int i = 0; i < n; i++){
		suma = 0.0;
		for(int k = 0; k < n; k++){
			if(matriz[i][i] != matriz[i][k]){
				suma = suma + fabs(matriz[i][k]);	
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

main(){
	int dimension,EDD;
	//float *A = (float *) malloc(dimension * sizeof(float *));
	char opc;
	
	printf("\t\tPROGRAMA 2. METODOS NUMERICOS.\n\n");
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
		}else{
			printf("\nLa matriz no es Estrictamente Dominante Diagonal\n");
			EDD=0;
		}
		if(EDD!=1){
			det = determinanteTriangulacion(A, dimension);
			printf("\nDeterminante de la matriz: %.2f", det);
			
			if(det != 0){
				printf("\nEl sistema de ecuaciones tiene solucion\n");
			}else{
				printf("\nEl sistema de ecuaciones no tiene solucion\n");
			}
			
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
	
}
