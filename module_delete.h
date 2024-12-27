#ifndef MODULE_DELETE_H
#define MODULE_DELETE_H

#include "cabeceras.h"
#include <stdio.h>

int del(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos,
           EXT_BYTE_MAPS *ext_bytemaps, EXT_SIMPLE_SUPERBLOCK *ext_superblock,
           char *nombre, FILE *fich) {
    
    // Buscar el archivo en el directorio
    int inodo_index = buscaFich(directorio, inodos, nombre); 
    if (inodo_index == NULL_INODO) {
        printf("Error: El archivo '%s' no existe.\n", nombre);
        return -1;
    }

    // Liberar los bloques ocupados por el archivo
    EXT_SIMPLE_INODE *inodo = &inodos->blq_inodos[inodo_index];
    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        if (inodo->i_nbloque[i] != 0xFFFF) {
            // Liberar el bloque
            ext_bytemaps->bmap_bloques[inodo->i_nbloque[i]] = 0; 
            // Restablecer el bloque bloque
            inodo->i_nbloque[i] = 0xFFFF; 
        }
    }

    // Liberar el inodo (lo marca como libre)
    ext_bytemaps->bmap_inodos[inodo_index] = 0; 
    inodo->size_fichero = 0;

    // Eliminar del directorio
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo == inodo_index) {
            // Restablecer el inodo y el nombre del archivo
            directorio[i].dir_inodo = 0xFFFF; 
            strcpy(directorio[i].dir_nfich, "");
            break;
        }
    }

    // Persistencia
    grabarinodosydirectorio(directorio, inodos, fich); 
    grabarByteMaps(ext_bytemaps, fich); 
    grabarSuperBloque(ext_superblock, fich); 
    
    return 0;
}

#endif