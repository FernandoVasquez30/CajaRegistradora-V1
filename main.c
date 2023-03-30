#include "global.h"
#include "productos.h"
#include "venta.h"

void inventario()
{
    LIMPIAR
    int op;

    do{
        printf("INVENTARIO.\n");
        printf("1-Crear Producto.\n");
        printf("2-Listar Productos.\n");
        printf("3-Regresar.\n");
        printf("Ingrese su opcion:");
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            LIMPIAR
            crearProducto();
            break;

        case 2:
            LIMPIAR
            listadoProductos();
            break;

        case 3:
            LIMPIAR
            break;
        }
    } while (op != 3);
}

int main()
{
    int op;
    LIMPIAR

    do
    {
        printf("MENU PRINCIPAL.\n");
        printf("1-Registrar Venta.\n");
        printf("2-Inventario de los productos.\n");
        printf("3-Listar Ventas.\n");
        printf("4-Salir.\n");
        printf("Ingrese su opcion:");
        scanf("%i", &op);

        switch (op){
        case 1:
            LIMPIAR
            crearVenta();
            break;

        case 2:
            LIMPIAR
            inventario();
            break;

        case 3:
            LIMPIAR
            imprimirVentas();
            break;

        default:
            LIMPIAR
            break;
        }
    } while (op != 4);
    return 0;
}
