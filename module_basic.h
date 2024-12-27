#ifndef MODULE_BASIC_H
#define MODULE_BASIC_H

#include "cabeceras.h"

char *comandos[] = {"exit", "dir", "rename", "remove", "copy", "info", "bytemaps", "print", "help", "debug"};


void dir(EXT_ENTRADA_DIR* directorio, EXT_BLQ_INODOS* inodos) {
  for (int i = 1; i < MAX_FICHEROS; i++) {
    if (directorio[i].dir_inodo != 0xFFFF) {
      
      EXT_SIMPLE_INODE* inodo = &inodos->blq_inodos[directorio[i].dir_inodo];
      printf("%s\t tamaño:%u\t inodo:%u bloques: ", directorio[i].dir_nfich, inodo->size_fichero, directorio[i].dir_inodo);

      for (int j = 0; j < MAX_NUMS_BLOQUE_INODO; j++) {
        if (inodo->i_nbloque[j] != 0xFFFF) {
            printf("%d ", inodo->i_nbloque[j]);
        }
      }
      printf("\n");
    }
  }
}


void help() {
  printf("Los comandos que puede utilizar son:\n");
  printf("dir: Muestra el contenido del directorio\n");
  printf("info: Muestra informacion sobre el sistema de ficheros\n");
  printf("bytemaps: Muestra el contenido del mapa de bits de bloques e inodos\n");
  printf("rename: Cambia el nombre de un fichero\n");
  printf("print: Muestra el contenido de un fichero\n");
  printf("remove: Elimina un fichero\n");
  printf("copy: Copia un fichero en otro\n");
  printf("exit: Cierra la aplicacion\n");
}

// TODO: CHECK COMMAND
int comprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2) {

  int codeOutput = -1;

  // RESET PARAMETROS POR NUEVO COMANDO EN COLA
  strcpy(orden, "");
  strcpy(argumento1, "");
  strcpy(argumento2, "");

  sscanf(strcomando, "%s %s %s", orden, argumento1, argumento2);
  
  /*
  printf("Orden: %s\n", orden);
  printf("Argumento 1: %s\n", argumento1);
  printf("Argumento 2: %s\n", argumento2);
  */

  // COMANDO ==> NUMERO
  // exit ==> 0
  // dir ==> 1
  // rename ==> 2
  // remove ==> 3
  // copy ==> 4
  // info ==> 5
  // bytemaps ==> 6
  // print ==> 7
  // help ==> 8
  // debug ==> 9

  for (int i = 0; i < 9; i++) {
    if (strcmp(orden, comandos[i]) == 0) codeOutput = i;
  }

  if (codeOutput == 2 || codeOutput == 4) { // COMANDOS CON DOS PARAAMETROS
    if (strcmp(argumento1, "") == 0 || strcmp(argumento2, "") == 0) {
      printf("Error: Faltan argumentos\n");
      codeOutput = -1;
    }

  }
  else if (codeOutput == 3 || codeOutput == 7) { // COMANDOS CON UN PARAMETRO
    if (strcmp(argumento1, "") == 0) {
      printf("Error: Faltan argumentos\n");
      codeOutput = -1;
    }
    else if (strcmp(argumento2, "") != 0) {
      printf("Error: Demasiados argumentos\n");
      codeOutput = -1;
    }

  }
  else if (codeOutput == 0 || codeOutput == 6 || codeOutput == 8 || codeOutput == 5 || codeOutput == 1 || codeOutput == 9) { // COMANDOS SIN PARAMETROS
    if (strcmp(argumento1, "") != 0 || strcmp(argumento2, "") != 0) {
      printf("Error: Demasiados argumentos\n");
      codeOutput = -1;
    }
  }
  else {
    printf("Error: Comando no reconocido\n");
  }

  return codeOutput;

}


// TODO: TODAS LAS FUNCIONES DE ABAJO IMPLICA EL COPIADO, BORRADO Y RENOMBRADO DE ARCHIVOS 
// TODO: (CREO QUE LA PRIMERA TAMBIEN IMPLICA EN ESO)

int buscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre) {

  for (int i = 0; i < MAX_FICHEROS; i++) { 
    if (directorio[i].dir_inodo != NULL_INODO && strcmp(directorio[i].dir_nfich, nombre) == 0) { 
      return directorio[i].dir_inodo; 
      } 
  } 
  return NULL_INODO;

}

// ! NOTA: SI SE REQUIERE HACER CODIGO INVIDUALMENTE PARA CASO, AVISAME POR MD PARA QUE LO PREPARE

void grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fent) {
  // Escribir los inodos
    fseek(fent, SIZE_BLOQUE * 2, SEEK_SET); // Bloque 2 contiene los inodos
    fwrite(inodos, SIZE_BLOQUE, 1, fent);

    // Escribir el directorio
    fseek(fent, SIZE_BLOQUE * 3, SEEK_SET); // Bloque 3 contiene el directorio
    fwrite(directorio, SIZE_BLOQUE, 1, fent);
}
void grabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fent) {
    fseek(fent, SIZE_BLOQUE, SEEK_SET); // Bloque 1 contiene los bytemaps
    fwrite(ext_bytemaps, SIZE_BLOQUE, 1, fent);
}
void grabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fent) {
  fseek(fent, 0, SEEK_SET); // Bloque 0 contiene el superbloque
  fwrite(ext_superblock, SIZE_BLOQUE, 1, fent);
}
void grabarDatos(EXT_DATOS *memdatos, FILE *fent) {
  fseek(fent, SIZE_BLOQUE * 4, SEEK_SET); // Bloques de datos comienzan en el bloque 4
  fwrite(memdatos, SIZE_BLOQUE, MAX_BLOQUES_DATOS, fent);
}

// TODO: EXIT
void salir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
           EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, FILE *fent) {
    // Guardar los cambios en el archivo binario
    grabarinodosydirectorio(directorio, inodos, fent);
    grabarByteMaps(ext_bytemaps, fent);
    grabarSuperBloque(ext_superblock, fent);
    grabarDatos(memdatos, fent);

    // Cerrar el archivo
    fclose(fent);

  exit(0);
}

#endif



