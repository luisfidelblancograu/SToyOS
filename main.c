#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "cabeceras.h"
#include "module_basic.h"
#include "module_copy.h"
#include "module_delete.h"
#include "module_info.h"
#include "module_print.h"
#include "module_rename.h"


#define LONGITUD_COMANDO 100

int main()
{

  char* comando = malloc(sizeof(char) * LONGITUD_COMANDO);
  char* orden = malloc(sizeof(char) * LONGITUD_COMANDO);
  char* argumento1 = malloc(sizeof(char) * LONGITUD_COMANDO);
  char* argumento2 = malloc(sizeof(char) * LONGITUD_COMANDO);


  int i,j,entradadir, grabardatos, codeOutput;
  unsigned long int m;
  EXT_SIMPLE_SUPERBLOCK ext_superblock;
  EXT_BYTE_MAPS ext_bytemaps;
  EXT_BLQ_INODOS ext_blq_inodos;
  EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
  EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
  EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
  FILE *fent;

  // Lectura del fichero completo de una sola vez
  fent = fopen("particion.bin","r+b");
  fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);
  memcpy(&ext_superblock,(EXT_SIMPLE_SUPERBLOCK *)&datosfich[0], SIZE_BLOQUE);
  memcpy(&directorio,(EXT_ENTRADA_DIR *)&datosfich[3], SIZE_BLOQUE);
  memcpy(&ext_bytemaps,(EXT_BLQ_INODOS *)&datosfich[1], SIZE_BLOQUE);
  memcpy(&ext_blq_inodos,(EXT_BLQ_INODOS *)&datosfich[2], SIZE_BLOQUE);
  memcpy(&memdatos,(EXT_DATOS *)&datosfich[4],MAX_BLOQUES_DATOS*SIZE_BLOQUE);

  while (1) {
    printf(">> ");
    fflush(stdin);
    fgets(comando, LONGITUD_COMANDO, stdin);

    codeOutput = comprobarComando(comando, orden, argumento1, argumento2);

    switch (codeOutput) {
      case 0: // ORDEN SALIR
        printf("Apagando el equipo...\n");
        salir(memdatos, fent);
        break;

      case 1: // ORDEN DIRECTORIO
        // dir(directorio,&ext_blq_inodos);
        break;

      case 2: // ORDEN RENAME
      case 3: // ORDEN REMOVE
      case 4: // ORDEN COPY

        // Escritura de metadatos en comandos rename, remove, copy  
        /*   
        grabarinodosydirectorio(&directorio,&ext_blq_inodos,fent);
        grabarByteMaps(&ext_bytemaps,fent);
        grabarSuperBloque(&ext_superblock,fent);
        if (grabardatos){
          grabarDatos(&memdatos,fent);
        }
        grabardatos = 0;
        */
        break;

      case 5: // ORDEN INFO
        info(&ext_superblock);
        break;

      case 6: // ORDEN BYTEMAPS
        printByteMaps(&ext_bytemaps);
        break;

      case 7: // ORDEN PRINT
        print(directorio, &ext_blq_inodos, memdatos, argumento1);
        break;

      case 8: // ORDEN HELP
        help();
        break;

      case 9: // ORDEN DEBUG (SOLO PARA DESARROLLADORES) (EDITA EL CODIGO PARA LLAMAR LA FUNCION DESEADA)
        printMemDatos(memdatos);
        break;
      }

    printf("\n");

  }
}