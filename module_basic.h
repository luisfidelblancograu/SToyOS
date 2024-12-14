#ifndef MODULE_BASIC_H
#define MODULE_BASIC_H

#include "cabeceras.h"

// TODO: DIR
void dir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos) {
  
}

// TODO: HELP
void help() {
  
}

// TODO: EXIT
void salir(EXT_DATOS* memDatos, FILE* fent) {


  //TODO: Si el comando es salir se habrán escrito todos los metadatos
  //TODO: faltan los datos y cerrar
  grabarDatos(&memDatos, fent);
  fclose(fent);

  exit(0);
}

// TODO: CHECK COMMAND
int comprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2) {

}


// TODO: TODAS LAS FUNCIONES DE ABAJO IMPLICA EL COPIADO, BORRADO Y RENOMBRADO DE ARCHIVOS 
// TODO: (CREO QUE LA PRIMERA TAMBIEN IMPLICA EN ESO)

int buscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre) {

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

#endif



