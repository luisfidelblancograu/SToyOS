#ifndef MODULE_BASIC_H
#define MODULE_BASIC_H

#include "cabeceras.h"

// TODO: DIR
void directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos);

// TODO: HELP
void ayuda() {

}

// TODO: EXIT
void salir() {

}

// TODO: CHECK COMMAND
int comprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2) {

}


// TODO: TODAS LAS FUNCIONES DE ABAJO IMPLICA EL COPIADO, BORRADO Y RENOMBRADO DE ARCHIVOS 
// TODO: (CREO QUE LA PRIMERA TAMBIEN IMPLICA EN ESO)

int BuscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre) {

}

// ! NOTA: SI SE REQUIERE HACER CODIGO INVIDUALMENTE PARA CASO, AVISAME POR MD PARA QUE LO PREPARE

void Grabarinodosydirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich) {
  
}
void GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich) {

}
void GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich) {

}
void GrabarDatos(EXT_DATOS *memdatos, FILE *fich) {

}

#endif



