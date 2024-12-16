#ifndef MODULE_PRINT_H
#define MODULE_PRINT_H

#include "module_basic.h"

int print(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, 
             EXT_DATOS *memdatos, char *nombre) {

}

void printByteMaps(EXT_BYTE_MAPS *ext_bytemaps) {

  printf("Inodos: ");
  for (int i = 0; i < MAX_INODOS; i++) {
    printf("%d ", ext_bytemaps->bmap_inodos[i]);
  }
  printf("\n");

  printf("Bloques: ");
  for (int i = 0; i < 25; i++) {
    printf("%d ", ext_bytemaps->bmap_bloques[i]);
  }
  printf("\n");

}

void readSuperBlock(EXT_SIMPLE_SUPERBLOCK *psup) {
  
}

#endif