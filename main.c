#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define DECIMAL 1
#define OCTAL 2
#define HEXADECIMAL 3
#define ERROR_LEXICO 4

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
    return 7;
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

void procesarCadena(char *cadena) {
    char *token = strtok(cadena, "#");
    int decimales = 0, octales = 0, hexadecimales = 0, erroresLexicos = 0;

    while (token != NULL) {
        const char resultado = obtenerTipoNumero(token);

             if (resultado == DECIMAL)      decimales++;
        else if (resultado == OCTAL)        octales++;
        else if (resultado == HEXADECIMAL)  hexadecimales++;
        else if (resultado == ERROR_LEXICO) erroresLexicos++;

        printf("Cadena: %s -> %c\n", token, resultado);
        token = strtok(NULL, "#");
    }

    printf("Resultados:\n");
    printf("Decimales: %d\n", decimales);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexadecimales);
    printf("Errores Léxicos: %d\n", erroresLexicos);
}

// EJERCICIO 2

int convertirCharANumero(char caracter)
{
    if (caracter >= 48 && caracter <= 57)
        return caracter - 48;
    return -1; // error
}

int main() {
    printf("Test de columna:\n");
    printf("Columna 0: %d\n", columna('0'));
    printf("Columna 1: %d\n", columna('1'));
    printf("Columna 2: %d\n", columna('8'));
    printf("Columna 3: %d\n", columna('a'));
    printf("Columna 4: %d\n", columna('x'));
    printf("Columna 5: %d\n", columna('-'));
    printf("Columna 6: %d\n", columna('G'));

    // EJERCICIO 1

    FILE *archivo = fopen("cadena.txt", "r");
    char cadena[1024];

    if (archivo != NULL)
    {
        if (fgets(cadena, sizeof(cadena), archivo) != NULL) {
            procesarCadena(cadena);
        } else {
            printf("Error al leer el archivo.\n");
        }
        fclose(archivo);
    }

    // EJERCICIO 2

    printf("Conversion char a int: %d\n", convertirCharANumero('5'));

    return 0;
}
