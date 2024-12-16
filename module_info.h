#ifndef MODULE_INFO_H
#define MODULE_INFO_H

#include "cabeceras.h"

// Esta funcion muestra la informacion del superbloque por pantalla
void info(EXT_SIMPLE_SUPERBLOCK *extSuperBlock) {
  printf("Bloque %d Bytes\n", extSuperBlock->s_block_size);
  printf("Inodos particion: %d\n", extSuperBlock->s_inodes_count);
  printf("Bloques particion: %d\n", extSuperBlock->s_blocks_count);
  printf("Bloques libres: %d\n", extSuperBlock->s_free_blocks_count);
  printf("Inodos libres: %d\n", extSuperBlock->s_free_inodes_count);
  printf("Primer bloque de datos: %d\n", extSuperBlock->s_first_data_block);
}

#endif