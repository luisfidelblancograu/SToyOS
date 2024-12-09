#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "module_basic.h"


#define LONGITUD_COMANDO 100

int main()
{

  char *comando[LONGITUD_COMANDO], *orden[LONGITUD_COMANDO], *argumento1[LONGITUD_COMANDO], *argumento2[LONGITUD_COMANDO];

  /*

  int i,j,entradadir, grabardatos;
  unsigned long int m;
  EXT_SIMPLE_SUPERBLOCK ext_superblock;
  EXT_BYTE_MAPS ext_bytemaps;
  EXT_BLQ_INODOS ext_blq_inodos;
  EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
  EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
  EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
  FILE *fent;

  */

  /*

  // Lectura del fichero completo de una sola vez
  fent = fopen("particion.bin","r+b");
  fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);
  memcpy(&ext_superblock,(EXT_SIMPLE_SUPERBLOCK *)&datosfich[0], SIZE_BLOQUE);
  memcpy(&directorio,(EXT_ENTRADA_DIR *)&datosfich[3], SIZE_BLOQUE);
  memcpy(&ext_bytemaps,(EXT_BLQ_INODOS *)&datosfich[1], SIZE_BLOQUE);
  memcpy(&ext_blq_inodos,(EXT_BLQ_INODOS *)&datosfich[2], SIZE_BLOQUE);
  memcpy(&memdatos,(EXT_DATOS *)&datosfich[4],MAX_BLOQUES_DATOS*SIZE_BLOQUE);

  */

  while (1) {
    printf(">> ");
    fflush(stdin);
    fgets(comando, LONGITUD_COMANDO, stdin);

    
  }
}