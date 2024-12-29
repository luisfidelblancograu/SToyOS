#ifndef MODULE_COPY_H
#define MODULE_COPY_H

#include "cabeceras.h"
#include "module_basic.h"
#include <stdio.h>

// FUNCION COPIAR
int copy(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps, 
            EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, 
            char *nombredestino) 
{
    //Buscar archivo origen
    int inodo_origen = buscaFich(directorio, inodos, nombreorigen);
    if (inodo_origen == NULL_INODO) {
        printf("Error: El archivo de origen '%s' no existe.\n", nombreorigen);
        return -1;
    }

    // Verificar nombre de destino (y que no exista ya)
    if (buscaFich(directorio, inodos, nombredestino) != NULL_INODO) {
        printf("Error: El archivo de destino '%s' ya existe.\n", nombredestino);
        return -1;
    }

    // Encontrar inodo libre
    int inodo_destino = -1;
    for (int i = 0; i < MAX_INODOS; i++) {
        if (ext_bytemaps->bmap_inodos[i] == 0) {
            inodo_destino = i;
            ext_bytemaps->bmap_inodos[i] = 1; // Marcar inodo como ocupado
            break;
        }
    }
    if (inodo_destino == -1) {
        printf("Error: No hay inodos libres disponibles.\n");
        return -1;
    }

    // Copiar los bloques 
    EXT_SIMPLE_INODE *inodo_src = &inodos->blq_inodos[inodo_origen];
    EXT_SIMPLE_INODE *inodo_dest = &inodos->blq_inodos[inodo_destino];
    inodo_dest->size_fichero = inodo_src->size_fichero;

    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++) {
        if (inodo_src->i_nbloque[i] != 0xFFFF) {
            int bloque_destino = -1;
            for (int j = 0; j < MAX_BLOQUES_DATOS; j++) {
                if (ext_bytemaps->bmap_bloques[j] == 0) {
                    bloque_destino = j;
                    ext_bytemaps->bmap_bloques[j] = 1; // Marcar bloque como ocupado
                    break;
                }
            }
            if (bloque_destino == -1) {
                printf("Error: No hay bloques libres disponibles.\n");
                return -1;
            }
            inodo_dest->i_nbloque[i] = bloque_destino;
            memcpy(&memdatos[bloque_destino - 4], &memdatos[inodo_src->i_nbloque[i]] - 4, SIZE_BLOQUE); // Hay un .dato en source
        } else {
            inodo_dest->i_nbloque[i] = 0xFFFF;
        }
    }

    // Actualizar el directorio
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo == 0xFFFF) {
            directorio[i].dir_inodo = inodo_destino;
            strcpy(directorio[i].dir_nfich, nombredestino);
            break;
        }
    }

    return 0;
}

#endif