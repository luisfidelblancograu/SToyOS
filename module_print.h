#ifndef MODULE_PRINT_H
#define MODULE_PRINT_H

#include "module_basic.h"

// ! DEBUGGING --> VER EL CONTENIDO DE CADA BLOQUE DE DATOS
void printMemDatos(EXT_DATOS *memdatos) {
  for (int i = 0; i < MAX_BLOQUES_DATOS; i++) {
    printf("Bloque de datos %d\n", i);
    for (int j = 0; j < SIZE_BLOQUE; j++) {
      printf("%c", memdatos[i].dato[j]);
    }
    printf("\n");
  }
}

int print(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, 
             EXT_DATOS *memdatos, char *nombre) {

  int inodo = buscaFich(directorio, inodos, nombre);
  if (inodo == NULL_INODO) {
    printf("Error: Fichero no encontrado\n");
    return -1;
  }
  else {
      printf("Contenido del fichero %s:\n", nombre);
      
      /*
      NOTAS:
      - El tamaño del fichero se encuentra en el inodo
      - Los bloques de datos se encuentran en el inodo
      - Los datos se encuentran en los bloques de datos
      ! El fichero HOLA.txt por ejemplo, ocupa 11 bytes, por ende solo tiene un bloque de datos
      ! El fichero BelloGal.txt ocupa mas de 1000 bytes, por ende tiene 3 bloques de datos
      ! Esto se debe a que el tamaño de un bloque es de 512 bytes
      ? En cuestion: Bloques reservados 4, Bloques de datos 96
      ? Operacion final: Bloque de datos seleccionado - 4 (FUNCIONA)
      */

      EXT_SIMPLE_INODE inodo_fichero = inodos->blq_inodos[inodo];
      int tam = inodo_fichero.size_fichero;

      int bloqueActual = 0; // Esta variable se usara como calculo del bloque de datos exacto ya que son 96 bloques de datos y 4 reservados por ende i_nbloque - 4;

      for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        if (inodo_fichero.i_nbloque[i] != NULL_BLOQUE) {
          bloqueActual = inodo_fichero.i_nbloque[i] - 4;
          printf("Debug: Bloque de Datos Logico: %d\n", inodo_fichero.i_nbloque[i]);
          printf("Debug: Bloque de Datos Real: %d\n", bloqueActual);
          for (int j = 0; j < SIZE_BLOQUE; j++) {

            if (tam != 0) {
              printf("%c", memdatos[bloqueActual].dato[j]);
              tam--;
            }
          }

        }
      }

      return 1;
    
  }

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
  printf("Bloque %d Bytes\n", psup->s_block_size);
  printf("Inodos particion: %d\n", psup->s_inodes_count);
  printf("Bloques particion: %d\n", psup->s_blocks_count);
  printf("Bloques libres: %d\n", psup->s_free_blocks_count);
  printf("Inodos libres: %d\n", psup->s_free_inodes_count);
  printf("Primer bloque de datos: %d\n", psup->s_first_data_block);
}

#endif