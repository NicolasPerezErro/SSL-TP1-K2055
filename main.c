#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define DECIMAL 1
#define OCTAL 2
#define HEXADECIMAL 3
#define ERROR_LEXICO 4


// UTILIDADES

void leerArchivo(const char *nombreArchivo, void (procesarCadena)(char *)) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    char cadena[1024];
    while (fgets(cadena, sizeof(cadena), archivo) != NULL) {
        procesarCadena(cadena);
    }

    fclose(archivo);
}

// EJERCICIO 1

// Tabla de transiciones
static int tt[8][7] = {
    //           0  [1-7] [8-9] [a-f] [xX]  [+-] [Otro]
    /* q0 - */ { 1,  2,    2,    7,    7,    6,  7 },
    /* q1   */ { 5,  5,    7,    7,    3,    7,  7 },
    /* q2 + */ { 2,  2,    2,    7,    7,    7,  7 },
    /* q3   */ { 4,  4,    4,    4,    7,    7,  7 },
    /* q4 + */ { 4,  4,    4,    4,    7,    7,  7 },
    /* q5 + */ { 5,  5,    7,    7,    7,    7,  7 },
    /* q6   */ { 2,  2,    2,    7,    7,    7,  7 },
    /* q7   */ { 7,  7,    7,    7,    7,    7,  7 }
};

// Carácter a columna de la tabla de transiciones
int columna(char c) {
    if (c == '0') return 0;
    if (c >= '1' && c <= '7') return 1;
    if (c == '8' || c == '9') return 2;
    if (tolower(c) >= 'a' && tolower(c) <= 'f') return 3;
    if (c == 'x' || c == 'X') return 4;
    if (c == '-' || c == '+') return 5;
    return 6;
}

const int obtenerTipoNumero(char *cadena) {
    int estado = 0;
    int i = 0;
    char c = cadena[i];

    while (c != '\0') {
        estado = tt[estado][columna(c)];
        c = cadena[++i];
    }

    if (estado == 2 || estado == 1) return DECIMAL;
    if (estado == 5) return OCTAL;
    if (estado == 4) return HEXADECIMAL;
    return ERROR_LEXICO;
}

char * debugResultado(int resultado) {
    switch (resultado) {
        case DECIMAL: return "Decimal";
        case OCTAL: return "Octal";
        case HEXADECIMAL: return "Hexadecimal";
        case ERROR_LEXICO: return "Error léxico";
        default: return "Desconocido";
    }
}

void procesarCadena(char *cadena) {
    char *token = strtok(cadena, "#");
    int decimales = 0, octales = 0, hexadecimales = 0, erroresLexicos = 0;

    while (token != NULL) {
        const int resultado = obtenerTipoNumero(token);

             if (resultado == DECIMAL)      decimales++;
        else if (resultado == OCTAL)        octales++;
        else if (resultado == HEXADECIMAL)  hexadecimales++;
        else if (resultado == ERROR_LEXICO) erroresLexicos++;

        printf("Cadena: %s\t->\t%s\n", token, debugResultado(resultado));
        token = strtok(NULL, "#");
    }

    printf("Resultados:\n");
    printf("Decimales: %d\n", decimales);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexadecimales);
    printf("Errores Léxicos: %d\n", erroresLexicos);
}

// EJERCICIO 2

int convertirCharANumero(char caracter) {
    // Si el caracter es un número, se le resta el valor ASCII de '0' para obtener el número entero
    if (caracter >= '0' && caracter <= '9') return caracter - '0';
    // Si no es un número, se retorna -1 para indicar un error
    return -1;
}

// EJERCICIO 3

void obtenerResultadoDeOperacion(char *cadena) {
    int resultado = 0; // Acumulador de la operación
    int estado = 0; // Operador
    
    int i = 0;
    char c = cadena[i];
    while (c != '\0') {
        estado = tt[estado][columna(c)];

        // TODO

        // Seguir leyendo el número
        c = cadena[++i];
    }

    printf("Resultado de la operación: %s = %d\n", cadena, resultado);
}

int main() {
    // EJERCICIO 1
    printf("\nEJERCICIO 1\n");
    leerArchivo("cadenaPunto1.txt", procesarCadena);

    // EJERCICIO 2
    printf("\nEJERCICIO 2\n");
    printf("Conversion char '%c' a int: %d\n", '5', convertirCharANumero('5'));

    // EJERCICIO 3
    printf("\nEJERCICIO 3\n");
    leerArchivo("cadenaPunto3.txt", obtenerResultadoDeOperacion);

    return 0;
}
