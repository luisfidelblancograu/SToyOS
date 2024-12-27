#ifndef MODULE_RENAME_H
#define MODULE_RENAME_H

#include "module_basic.h"

int renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreAntiguo, char *nombreNuevo) {
    
    // Buscar el archivo en el directorio
    int dir_index_antiguo = buscaFich(directorio, inodos, nombreAntiguo);
    if (dir_index_antiguo == NULL_INODO) {
        printf("Error: El archivo '%s' no existe.\n", nombreAntiguo);
        return -1;
    }

    // Verificar ue no hayan dos archivos con mismo nombre 
    int dir_index_nuevo = buscaFich(directorio, inodos, nombreNuevo);
    if (dir_index_nuevo != NULL_INODO) {
        printf("Error: Ya existe un archivo con el nombre '%s'.\n", nombreNuevo);
        return -1;
    }

    // Renombrar el archivo
    for (int i = 0; i < MAX_FICHEROS; i++) {
        if (directorio[i].dir_inodo == dir_index_antiguo) {
            strncpy(directorio[i].dir_nfich, nombreNuevo, LEN_NFICH);
            directorio[i].dir_nfich[LEN_NFICH - 1] = '\0'; // Asegurar terminación nula
            printf("El archivo '%s' ha sido renombrado a '%s'.\n", nombreAntiguo, nombreNuevo);
            return 0;
        }
    }
    
    return 0;
}

#endif