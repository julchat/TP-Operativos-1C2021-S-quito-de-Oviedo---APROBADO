#ifndef I_MONGO_STORE_H
#define I_MONGO_STORE_H

#include "i-mongo-store-lib.h"
// Funciones Auxiliares
bool reparar_block_count();
bool reparar_sabotaje_md5();
bool reparar_size();

// Funciones de sabotaje
bool sabotaje_block_count();
bool sabotaje_superbloque();
bool sabotaje_md5();
bool sabotaje_size();

#endif /* I_MONGO_STORE_H */