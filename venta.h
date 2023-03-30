#ifndef __VENTA_H__ 
#define __VENTA_H__
#include "global.h"
#include "productos.h"

typedef struct
{
    int codigo;
    char fecha[100];
    char nombreC[50];
    tproducto lista[10];
    int numProductos;
} tventa;

void crearVenta();
void imprimirVentas();

#endif //__VENTA_H__ 