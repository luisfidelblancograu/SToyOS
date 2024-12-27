#ifndef MODULE_BASIC_H
#define MODULE_BASIC_H

#include "cabeceras.h"

char *comandos[] = {"exit", "dir", "rename", "remove", "copy", "info", "bytemaps", "print", "help"};

// TODO: DIR
void dir(EXT_ENTRADA_DIR* directorio, EXT_BLQ_INODOS* inodos) {
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo != 0xFFFF) {
            EXT_SIMPLE_INODE* inodo = &inodos->blq_inodos[directorio[i].dir_inodo];
            printf("Nombre: %s, Tamaño: %u bytes, Bloques: ", directorio[i].dir_nfich, inodo->size_fichero);
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

  for (int i = 0; i < sizeof(comandos) / sizeof(comandos[0]); i++) {
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

void grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich) {
  
}
void grabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich) {

}
void grabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich) {

}
void grabarDatos(EXT_DATOS *memdatos, FILE *fich) {

}

// TODO: EXIT
void salir(EXT_DATOS* memDatos, FILE* fent) {


  //TODO: Si el comando es salir se habrán escrito todos los metadatos
  //TODO: faltan los datos y cerrar
  // grabarDatos(memDatos, fent);
  fclose(fent);

  exit(0);
}

#endif



