#include <stdio.h>
#include <math.h>
#include <stdlib.h> // Para usar exit()
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
        printf("Las funciones no son de signos opuestos, no hay raíces.\n");
        return;
    }
    
    printf("\nIteracion | a         | b         | c         | f(c)      | Error Relativo\n");
    printf("-------------------------------------------------------------------------\n");
    
    while(errorRelativo > tolerancia && iteracion < maxIteraciones){
        p = (a + b)/2;
        fp = funcion(p);
        fa = funcion(a);
        
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
        
        if(iteracion > 0){
            errorRelativo = fabs((p - pO)/p);
        }
        
        pO = p;
        iteracion++;
    }

    printf("Se alcanzo el maximo de iteraciones (%d) sin encontrar una raiz con la tolerancia deseada.\n", maxIteraciones);
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
        
        printf("%9d | %10.6f | %10.6f | %10.6f | %10.6f | %10.6f\n", iteracion, x0, x1, x2, funcion(x2), errorRelativo);
        
        if (fabs(funcion(x2)) < tolerancia) {
            printf("Raiz encontrada: %f en la iteracion %d con tolerancia %f\n", x2, iteracion, tolerancia);
            return;
        }
        
        errorRelativo = fabs((x2 - x1) / x2);
        x0 = x1;
        x1 = x2;
        
        iteracion++;
    }
    
    printf("Se alcanzo el maximo de iteraciones (%d) sin encontrar una raiz con la tolerancia deseada.\n", maxIteraciones);
}

int main() {
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
        
        // Entrada de parámetros
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
        
        // Preguntar al usuario si desea continuar
        do {
            printf("\n\nDesea obtener otra raiz?\n\n  1 = Si\t2 = No:  ");
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
    
    return 0;
}
