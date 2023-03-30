#ifndef __PRODUCTOS_H__
#define __PRODUCTOS_H__
#include "global.h"

typedef struct
{
    int id;
    char nombre[40];
    float precio;
    float cant;
} tproducto;

int buscarIdProducto(int codigo, tproducto *pro);
RET buscarPosicion(int codigo, tproducto *pro);

void crearProducto();
void listadoProductos();

RET ExisteProducto(FILE *archNombre, char* nombre, tproducto* pro);

#endif