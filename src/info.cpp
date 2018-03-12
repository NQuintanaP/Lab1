/*
  Modulo de implementacion de info_t
  Se implementa struct rep_info como un registro
   con dos campos, uno numerico y otro de texto
*/

#include "../include/info.h"

#include <string.h>
#include <stdio.h>
#include <limits.h>

struct rep_info {
  int num;
  //arreglo cuyo tama;o se determina en
  //tiempo de ejecucion
  char *frase;
};

info_t crear_info(int num, char *frase) {
  //obtener memoria para el struct
  info_t nueva = new rep_info;
  nueva->num = num;
  //comparte memoria con el parametro
  nueva->frase = frase;
  return nueva;
}

info_t copia_info(info_t info) {
  info_t copia = new rep_info;
  copia->num = info->num;
  //obtiene memoria para el arreglo
  //NO comparte memoria con info
  copia->frase = new char[strlen(info->frase) + 1];
  strcpy(copia->frase, info->frase);
  return copia;
}

void liberar_info(info_t &info) {
  //devuelve la memoria del arreglo
  delete[] info->frase;
  //devuelve la memoria del struct
  delete info;
}

int numero_info(info_t info) {
  return info->num;
}

char *frase_info(info_t info) {
  return info->frase;
}

bool son_iguales(info_t i1, info_t i2) {
  if ((i1->num == i2->num) && (strcmp(i1->frase,i2->frase) == false))
    return true;
  else
    return false;
}

bool es_valida_info(info_t info) {
  return (info->num != INT_MAX);
}

char *info_a_texto(info_t info) {
  char copia_num[11];
  sprintf(copia_num, "%d", info->num);
  char *texto = new char[strlen(copia_num) +
                         strlen(info->frase) + 4];
  strcpy(texto, "(");
  strcat(texto, copia_num);
  strcat(texto, ",");
  strcat(texto, info->frase);
  strcat(texto, ")");
  return texto;
}

info_t combinar_info(info_t i1, info_t i2) {
  info_t info;
  int numero = i1->num + i2->num;
  char *fraseI1;
  fraseI1 = new char[strlen(i1->frase)+1];
  // fraseI1[strlen(i1->frase)+1] = '\0';
  char *fraseI2;
  fraseI2 = new char[strlen(i2->frase)+1];
  // fraseI2[strlen(i2->frase)+1] = '\0';
  strcpy(fraseI1, i1->frase);
  strcpy(fraseI2, i2->frase);
  char *fraseTotal = new char [strlen(i1->frase)+strlen(i2->frase)+1];
  strcat(fraseTotal,fraseI1);
  strcat(fraseTotal,fraseI2);
  fraseTotal[strlen(i1->frase)+strlen(i2->frase)+1]='\0';
  info = crear_info(numero, fraseTotal);
  return info;
}

info_t leer_info(int max) {
  info_t leido;
  int num;
  char *cadena = new char[max + 1];
  char simbolo;
  bool error = false;
  scanf(" %c", &simbolo);
  if (simbolo != '(')
    error = true;
  else {
    scanf("%d", &num);
    scanf(" %c", &simbolo);
    if (simbolo != ',')
      error = true;
    else {
      int pos = 0;
      int c = getchar();
      while ((c != ')') && (c != '\n')) {
        cadena[pos] = c;
        pos++;
        c = getchar();
      }
      cadena[pos] = '\0';
      if (c == '\n') {
        error = true;
        ungetc('\n', stdin);
      }
    }
  }
  if (error) {
    char *nulo = new char[1];
    nulo[0] = '\0';
    leido = crear_info(INT_MAX, nulo);
  } else {
    char *frase = new char[strlen(cadena) + 1];
    strcpy(frase, cadena);
    leido = crear_info(num, frase);
  }
  delete[] cadena;
  return leido;
}
