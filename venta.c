#include "venta.h"
#include "productos.h"

void crearVenta(){
    FILE *archProducto = fopen("productos.txt", "r+t");
    tventa venta;
    tproducto producto;
    if (archProducto == NULL){
        printf("No hay productos registrados\n");
        system("pause");
        LIMPIAR
        return;
    }

    FILE *archVentas = fopen("ventas.txt", "r+t");
    if (archVentas == NULL){
        archVentas = fopen("ventas.txt", "a+t");
        if (archVentas == NULL){
            printf("no hay ventas registradas\n");
            system("pause");
            LIMPIAR
            return;
        }else{
            fseek(archVentas, 0, SEEK_END);
        }
    }

    int cantPro = 0;
    int codigo;
    float precio, precio_total;
    int cantidad, i = 1;
    char listado;
    tproducto prod, aux;

    printf("VENTA\n");

    int ultimoID = 0;
    while (fscanf(archVentas, "%d %s %s", &venta.codigo, venta.fecha, venta.nombreC) == 3){
        ultimoID = venta.codigo;
    }
    ultimoID++;
    venta.codigo = ultimoID;
    printf("ID = %d\n", venta.codigo);
    printf("sig ID = %d\n", ultimoID);

    fflush(stdin);
    memset(venta.fecha, 0x00, sizeof(venta.fecha));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(venta.fecha, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    printf("fecha: %s\n", &venta.fecha);

    printf("Ingrese el nombre del Cliente:");
    gets(venta.nombreC);
    if (strcmp(venta.nombreC, "") == 0){
        printf("No debe estar vacio\n");
        system("pause");
        LIMPIAR
        return;
    }

    fseek(archVentas, 0, SEEK_END);
    fprintf(archVentas, "\n%d %s %s\n", venta.codigo, venta.fecha, venta.nombreC);

    printf("---PRODUCTOS DISPONIBLES---\n");
    while (!feof(archProducto)){
        fscanf(archProducto, "%i %s %f %f\n", &producto.id, &producto.nombre, &producto.precio, &producto.cant);
        if (producto.cant <= 0) continue;
        printf("%i %s %.f %.f\n", producto.id, producto.nombre, producto.precio, producto.cant);
    }

    printf("Cuantos productos va llevar:");
    scanf("%d", &cantPro);

    for (int f = 0; f < cantPro; f++){
        printf("Ingrese el ID del producto:");
        scanf("%i", &codigo);

        if (codigo == 0)
        {
            printf("El 0 no es valido.\n");
            f--;
            continue;
        }else if (buscarIdProducto(codigo, &prod) <= 0){
            printf("No se encontro el producto.\n");
            f--;
            continue;
        }else if (prod.cant <= 0){
            printf("No se encontro el producto.\n");
            f--;
            continue;
        }

        printf("El producto es: %s\n", prod.nombre);
        printf("Su precio es: %.f\n", prod.precio);

        printf("Ingrese la cantidad que desea comprar:");
        scanf("%d", &cantidad);
        fflush(stdin);

        if (cantidad <= 0)
        {
            printf("la cantidad no es valida.\n");
            f--;
            continue;
            return;
        }
        else if (cantidad > prod.cant)
        {
            printf("Cantidad no disponible\n");
            f--;
            continue;
        }

        if (!buscarPosicion(codigo, &aux) >= 0)
        {
            prod.cant -= cantidad;

            char lenPrecio[100];
            sprintf(lenPrecio, "%.f", prod.precio);

            fseek(archProducto, aux.id + 2 + strlen(prod.nombre) + 1 + strlen(lenPrecio) + 1, SEEK_SET);
            fprintf(archProducto, " %1.f", prod.cant);
            printf("Quedan en total %.f\n", prod.cant);
        }
        fprintf(archVentas, "%i %s %.f %i %d\n", prod.id, prod.nombre, prod.precio, cantidad, cantPro);
        getch();
    }
    fclose(archProducto);
    fclose(archVentas);
    LIMPIAR
    return;
}

void imprimirVentas()
{
    FILE *fp;
    tventa venta[100];
    int contador = 0;
    int cantProductos = 0;
    int i;
    float precio;

    fp = fopen("ventas.txt", "r");
    if (fp == NULL){
        printf("No existen ventas\n");
        system("pause");
        LIMPIAR
        return;
    }

    char linea[100], buffer[100];
    char *token;
    int valide = 0;

    while (fgets(linea, 100, fp))
    {
        strcpy(buffer, linea);
        char *token = strtok(linea, " ");
        int count = 0;
        while (token != NULL)
        {
            count++;
            token = strtok(NULL, " ");
        }
        if (count == 3)
        {
            if (valide == 1)
            {
                valide = 0;
                contador++;
            }
            sscanf(buffer, "\n%d %s %s\n", &venta[contador].codigo, venta[contador].fecha, venta[contador].nombreC);
        }
        else if (count == 5)
        {
            sscanf(buffer, "%d %s %f %f %d", &venta[contador].lista[cantProductos].id, venta[contador].lista[cantProductos].nombre, &venta[contador].lista[cantProductos].precio, &venta[contador].lista[cantProductos].cant, &venta[contador].numProductos);
            cantProductos++;
        }
        else if (contador != 0)
        {
            cantProductos = 0;
            contador++;
        }
        else
        {
            valide = 1;
        }
    }
    for (i = 1; i < contador + 1; i++)
    {
        precio = 0;
        printf("Venta # %d - Cliente: %s - Fecha: %s\n", venta[i].codigo, venta[i].nombreC, venta[i].fecha);

        for (int j = 0; j < venta[i].numProductos; j++)
        {
            venta[i].lista[j].precio *= venta[i].lista[j].cant;
            printf("\tProducto #%d: %s, Cantidad: %.f, Precio Unitario: %.f\n",
                    venta[i].lista[j].id, venta[i].lista[j].nombre, venta[i].lista[j].cant, venta[i].lista[j].precio);
            precio += venta[i].lista[j].precio;
        }
        printf("\t-----------------------------");
        printf("\n\tPrecio Total: %.f\n", precio);
        printf("\t-----------------------------\n");
    }

    printf("Presione una tecla para continuar");
    fclose(fp);
    getch();
    LIMPIAR
    return;
}