#include "productos.h"

void crearProducto()
{
    tproducto producto;
    memset(&producto,0x00,sizeof(tproducto*));
    fflush(stdin);
    printf("Ingrese el nombre del producto:");
    char nombreAux[40];
    gets(nombreAux);
    if (strcmp(nombreAux,"")==0) {
        printf("No debe estar vacio\n");
        system("pause");
        LIMPIAR
        return;
    }

    FILE *arch;
    FILE *archNombre;
    arch = fopen("productos.txt", "a+t");
    if (arch == NULL){
        printf("Error al escribir en el archivo\n");
        system("pause");
        fclose(arch);
        LIMPIAR
        return;
    }

    int ultimoID = 0;
    while (fscanf(arch, "%d %s %f %f", &producto.id, producto.nombre, &producto.precio, &producto.cant) == 4) {
        ultimoID = producto.id;
    }
    producto.id = ultimoID + 1;

    float cantAgregar = 0;
    tproducto prodNombre;
    archNombre = fopen("productos.txt", "r+t");
    char respuesta;
    if (ExisteProducto(archNombre,nombreAux, &prodNombre) == RET_OK){
        printf("El producto %s ya se encuentra en el registro.\n", prodNombre.nombre);
        printf("La cantidad actual del producto es %.f, Desea agregar mas cantidad? (s/n)", prodNombre.cant);
        scanf(" %c", &respuesta);
        if (respuesta == 's'){
            printf("Ingrese la cantidad:");
            scanf("%f", &cantAgregar);
            if(producto.cant <= 0 || producto.cant>= 1000){
                printf("cantidad no disponible\n");
                system("pause");
                LIMPIAR
                fclose(archNombre);
                fclose(arch);
                return;
            }
            prodNombre.cant += cantAgregar;

            char charPrecio[10];
            sprintf(charPrecio, "%.f", prodNombre.precio);

            fseek(archNombre, prodNombre.id + 2 + strlen(prodNombre.nombre) + 1 + strlen(charPrecio) + 1, SEEK_SET);
            fprintf(archNombre, "%.f", prodNombre.cant);
        }
    }else{
        printf("El producto no existe, quiere agregar uno nuevo? (s/n)");
        scanf(" %c", &respuesta);
        if (respuesta == 's' || respuesta == 'S'){
            printf("Ingrese precio:");
            scanf("%f", &producto.precio);

            printf("Ingrese La cantidad disponible:");
            scanf("%f", &producto.cant);
            if(producto.cant <= 0 || producto.cant>= 1000){
                printf("cantidad no disponible\n");
                system("pause");
                LIMPIAR
                fclose(archNombre);
                fclose(arch);
                return;
            }
            fseek(archNombre, 0, SEEK_END);
            fprintf(archNombre, "%i %s %.f %.f\n", producto.id, nombreAux, producto.precio, producto.cant);
        }
    }
    fclose(archNombre);
    fclose(arch);
    LIMPIAR
    return;
}

int buscarIdProducto(int codigo, tproducto *pro){
    FILE *arch = fopen("productos.txt", "r+t");
    while (!feof(arch))
    {
        fscanf(arch, "%i %s %f %f\n", &pro->id, &pro->nombre, &pro->precio, &pro->cant);
        if (pro->id == codigo){
            return 1;
        }
    }
    return 0;
}

RET buscarPosicion(int codigo, tproducto *pro){
    FILE *arch = fopen("productos.txt", "r+t");
    if(arch == NULL)
        return RET_FAIL;

    while (!feof(arch)){
        fscanf(arch, "%i %s %f %f\n", &pro->id, &pro->nombre, &pro->precio, &pro->cant);
        if (pro->id == codigo){
            pro->id = ftell(arch);
            char lenPrecioBuscar[10];
            sprintf(lenPrecioBuscar,"%.f",pro->precio);
            char lenCantBuscar[10];
            sprintf(lenCantBuscar,"%.f",pro->cant);
            char lenIdBuscar[10];
            sprintf(lenIdBuscar,"%d",pro->id);
            int lenGeneral = strlen(pro->nombre) + strlen(lenCantBuscar) + strlen(lenIdBuscar) + strlen(lenPrecioBuscar) + 4;
            pro->id -= lenGeneral;
            return RET_OK;
        }
    }
    return RET_FAIL;
}

void listadoProductos()
{
    FILE *arch;
    tproducto producto;

    arch = fopen("productos.txt", "r");
    if (arch == NULL){
        printf("No hay productos disponibles\n");
        system("pause");
        LIMPIAR
        return;
    }

    while (!feof(arch))
    {
        fscanf(arch, "%i %s %f %f\n", &producto.id, &producto.nombre, &producto.precio, &producto.cant);
        if(producto.cant <= 0) continue;
        printf("%i %s %.f %.f\n", producto.id, producto.nombre, producto.precio, producto.cant);
    }

    printf("Ingrese una tecla para continuar");
    fclose(arch);
    getch();
    LIMPIAR
    return;
}

RET ExisteProducto(FILE *archNombre, char* nombre, tproducto* pro) {
    if(archNombre == NULL)
        return RET_FAIL;

    while (fscanf(archNombre, "%d %s %f %f\n", &pro->id, pro->nombre, &pro->precio, &pro->cant) == 4) {
        if (strcmp(pro->nombre, nombre) == 0) {
            pro->id = ftell(archNombre);
            char lenPrecioBuscar[10];
            sprintf(lenPrecioBuscar, "%.f", pro->precio);
            char lenCantBuscar[10];
            sprintf(lenCantBuscar, "%.f", pro->cant);
            char lenIdBuscar[10];
            sprintf(lenIdBuscar, "%d", pro->id);
            int lenGeneral = strlen(pro->nombre) + strlen(lenCantBuscar) + strlen(lenIdBuscar) + strlen(lenPrecioBuscar) + 4;
            pro->id -= lenGeneral;
            return RET_OK;
        }
    }
    return RET_FAIL;
}