#ifndef MODULE_INFO_H
#define MODULE_INFO_H

#include "cabeceras.h"
#include "module_print.h"

// Esta funcion muestra la informacion del superbloque por pantalla
void info(EXT_SIMPLE_SUPERBLOCK *extSuperBlock) {
  readSuperBlock(extSuperBlock);
}

#endif