#ifndef MODULE_PRINT_H
#define MODULE_PRINT_H

#include "module_basic.h"

int print(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, 
             EXT_DATOS *memdatos, char *nombre) {

}

void printByteMaps(EXT_BYTE_MAPS *ext_bytemaps) {

  printf("Bloques: ");
  for (int i = 0; i < MAX_BLOQUES_PARTICION; i++) {
    printf("%d", ext_bytemaps->bmap_bloques[i]);
  }
  printf("\n");
  
  printf("Inodos: ");
  for (int i = 0; i < MAX_INODOS; i++) {
    printf("%d", ext_bytemaps->bmap_inodos[i]);
  }
  printf("\n");

}

void readSuperBlock(EXT_SIMPLE_SUPERBLOCK *psup) {
  
}

#endif