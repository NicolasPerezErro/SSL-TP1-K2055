#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* EJERCICIO 1*/

static int tt[8][7] = {
    // 0  [1-7] [8-9] [a-f] [xX]  [+-]
    /*q0-*/ {1,2,2,7,7,6,7},
    /*q1*/  {5,5,7,7,3,7,7},
    /*q2+*/ {2,2,2,7,7,7,7},
    /*q3*/  {4,4,4,4,7,7,7},
    /*q4+*/ {4,4,4,4,7,7,7},
    /*q5+*/ {5,5,7,7,7,7,7},
    /*q6*/  {2,2,2,7,7,7,7},
    /*q7*/  {7,7,7,7,7,7,7}
};

// mapeo de caracteres
int columna(int c) {
    if (c == '0') return 0;
    if (c >= '1' && c <= '7') return 1;
    if (c == '8' || c == '9') return 2;
    if (tolower(c) >= 'a' && tolower(c) <= 'f') return 3;
    if (c == 'x' || c == 'X') return 4;
    if (c == '-' || c == '+') return 5;
    return 7;
}

const char* esNumero(char *cadena) {
    int estado = 0;
    int i = 0;
    char c = cadena[i];

    while (c != '\0') {
        printf("Columna: %d\n",columna(c));
        printf("Estado incial %d\n",estado);
        estado = tt[estado][columna(c)];
        printf("Caracter: %c\n",c);
        printf("Estado final %d\n",estado);
        c = cadena[++i];
    }

    if (estado == 2 || estado == 1) return "Decimal";
    if (estado == 5) return "Octal";
    if (estado == 4) return "Hexadecimal";
    return "Error léxico";
}

void procesarCadena(char *cadena) {
    char *token = strtok(cadena, "#");
    int decimales = 0, octales = 0, hexadecimales = 0, erroresLexicos = 0;

    while (token != NULL) {
        const char* resultado = esNumero(token);

        if (strcmp(resultado, "Decimal") == 0) {
            decimales++;
        } else if (strcmp(resultado, "Octal") == 0) {
            octales++;
        } else if (strcmp(resultado, "Hexadecimal") == 0) {
            hexadecimales++;
        } else {
            erroresLexicos++;
        }

        printf("Cadena: %s -> %s\n", token, resultado);
        token = strtok(NULL, "#");
    }

    printf("\nResultados:\n");
    printf("Decimales: %d\n", decimales);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexadecimales);
    printf("Errores lexicos: %d\n", erroresLexicos);
}

/* EJERCICIO 2*/

int convertirCharANumero(char caracter){
    if (caracter >= 48 && caracter <= 57) return caracter - 48;
    return -1; // error
}

int main() {

    /* EJERCICIO 1 */

    FILE *archivo = fopen("cadena.txt", "r");
    char cadena[1024];

    if (archivo != NULL) {
        if (fgets(cadena, sizeof(cadena), archivo) != NULL) {
            procesarCadena(cadena);
        } else {
            printf("Error al leer el archivo.\n");
        }
        fclose(archivo);
    }

    /* EJERCICIO 2*/

    printf("Conversion char a int: %d\n",convertirCharANumero('5'));

    return 0;
}
