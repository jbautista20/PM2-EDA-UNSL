#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

/**
PMI 2 - GRUPO 3
INTEGRANTES:
 Rio, Sofia
 Montenegro, Juan Bautista

Conclusión:
Para finalizar, la mejor opción entre las estructuras evaluadas es sin dudas el Árbol Binario de Búsqueda.
Si bien los costos de evocacion son un poco superiores a los de la Lista con Busqueda Binaria,
los costos medios y máximos en altas y bajas son significativamnete menores al de las demás estructuras,
lo que lo hace más adecuado para optimizar el rendimiento de estas operaciones.

Esta conclusión esta respaldada por los resultados obtenidos en el siguiente cuadro:
##==========================================================================##
||                      COMPARACION DE ESTRUCTURAS                          ||
##==========================================================================##
||                      ||  COSTOS LSO  ||  COSTOS LSO.BB ||   COSTOS ABB   ||
##==========================================================================##
|| MAX. ALTA            ||     108.000  ||      107.000   ||      0.500     ||
|| MEDIO ALTA           ||     27.711   ||      26.711    ||      0.500     ||
|| MAX. BAJA            ||     97.000   ||      96.000    ||      1.500     ||
|| MEDIO BAJA           ||     30.594   ||      29.594    ||      0.799     ||
|| MAX. EVOC. EX.       ||     99.000   ||      13.000    ||      27.000    ||
|| MED. EVOC. EX.       ||     37.787   ||      9.643     ||      11.428    ||
|| MAX. EVOC. NO EX.    ||     84.000   ||      14.000    ||      24.000    ||
|| MED. EVOC. NO EX.    ||     32.930   ||      11.513    ||      13.047    ||
||==========================================================================||

CORRECIONES REALIZADAS (CONDICIONAL)

1: Se corrigio la llamada a evocacion para la LSO con +infinito (estaba mal la condicion del if antes
de llamar a evocar)

2: Se corrigio la devolucion del prestador para LSO y LSOBB, en caso que fracase la localizacion, evocar
devuelve un prestador 'invalido'

*/

#define MAX 111
#define INFINITO 99999999

typedef struct
{
    int DNI;
    char nombreApellido[81];
    char servicios[121];
    char domicilio[81];
    char mail[51];
    char telefono[31];
} Prestadores;

typedef struct NodoABB
{
    Prestadores dato;
    struct NodoABB* izq;
    struct NodoABB* der;
} NodoABB;

typedef struct
{
    NodoABB* dato;
    struct NodoPila *sig;
} NodoPila;

typedef struct
{
    NodoPila *tope;
} Pila;

typedef struct
{
    NodoABB* raiz;  // Puntero a la raiz del arbol
    NodoABB* ant;   // Puntero al padre de cur
    NodoABB* cur;   // Puntero para navegar en el ABB
} ABB;

/**VARIABLES PARA COSTOS*/
float maxaltalso=0;
float maxaltalsobb=0;
float maxaltaabb=0;

float medioaltalso=0;
float medioaltalsobb=0;
float medioaltaabb=0;

float maxbajalso=0;
float maxbajalsobb=0;
float maxbajaabb=0;

float mediobajalso=0;
float mediobajalsobb=0;
float mediobajaabb=0;

float maxevElso=0;
float maxevElsobb=0;
float maxevEabb=0;

float medioevElso=0;
float medioevElsobb=0;
float medioevEabb=0;

float maxevNElso=0;
float maxevNElsobb=0;
float maxevNEabb=0;

float medioevNElso=0;
float medioevNElsobb=0;
float medioevNEabb=0;

float sumaAltalso=0;
float sumaAltalsobb=0;
float sumaAltaabb=0;

float sumaBajalso=0;
float sumaBajalsobb=0;
float sumaBajaabb=0;

float sumaEvElso=0;
float sumaEvElsobb=0;
float sumaEvEabb=0;

float sumaEvNElso=0;
float sumaEvNElsobb=0;
float sumaEvNEabb=0;

float cantAltalso=0;
float cantAltalsobb=0;
float cantAltaabb=0;

float cantBajalso=0;
float cantBajalsobb=0;
float cantBajaabb=0;

float cantEvElso=0;
float cantEvElsobb=0;
float cantEvEabb=0;

float cantEvNElso=0;
float cantEvNElsobb=0;
float cantEvNEabb=0;

/**PROTOTIPOS*/
int localizarABB();
int localizarLSOBB ();
int localizarLSO();

int altaABB();
int altaLSOBB();
int altaLSO();

int eliminarABB();
int eliminarLSOBB();
int eliminarLSO();

Prestadores evocacionABB();
Prestadores evocacionLSOBB();
Prestadores evocacionLSO();

NodoABB* crearNodo(Prestadores p);

void mostrarLista();
void mostrarABB();

void cuadroComp();


int main()
{
    Prestadores lso[MAX];   //111 elementos maximo. (ultimo elemento INFINITO)
    lso[0].DNI=INFINITO;
    int cantCargadosLSO=0;

    Prestadores lsoBB[MAX-1];   //110 elementos maximo.
    int cantCargadosLSOBB=0;

    ABB arbol;
    arbol.raiz = NULL;
    arbol.cur = NULL;
    arbol.ant = NULL;
    int cantCargadosABB = 0;

    int op;
    do
    {
        system("cls");
        system("color F");
        printf("##==========================================================================##\n");
        printf("||                PM2 - ESTRUCTURA DE DATOS Y ALGORITMOS 1                  ||\n");
        printf("||==========================================================================||\n");
        printf("||     1 - COMPARAR ESTRUCTURAS                                             ||\n");
        printf("||                                                                          ||\n");
        printf("||     2 - MOSTRAR LSO                                                      ||\n");
        printf("||                                                                          ||\n");
        printf("||     3 - MOSTRAR LSO BB                                                   ||\n");
        printf("||                                                                          ||\n");
        printf("||     4 - MOSTRAR ABB                                                      ||\n");
        printf("||                                                                          ||\n");
        printf("||     5 - SALIR                                                            ||\n");
        printf("##==========================================================================##\n");
        printf("Seleccione una opcion (1-5): ");

        scanf("%d", &op);
        switch(op)
        {
        case 1:
            limpiarABB(&arbol,&cantCargadosABB);
            cantCargadosLSO = 0;
            lso[0].DNI=INFINITO;
            cantCargadosLSOBB = 0;

            maxaltalso=0;
            maxaltalsobb=0;
            maxaltaabb=0;

            medioaltalso=0;
            medioaltalsobb=0;
            medioaltaabb=0;

            maxbajalso=0;
            maxbajalsobb=0;
            maxbajaabb=0;
            mediobajalso=0;
            mediobajalsobb=0;
            mediobajaabb=0;

            maxevElso=0;
            maxevElsobb=0;
            maxevEabb=0;

            medioevElso=0;
            medioevElsobb=0;
            medioevEabb=0;

            maxevNElso=0;
            maxevNElsobb=0;
            maxevNEabb=0;
            medioevNElso=0;
            medioevNElsobb=0;
            medioevNEabb=0;

            sumaAltalso=0;
            sumaAltalsobb=0;
            sumaAltaabb=0;

            sumaBajalso=0;
            sumaBajalsobb=0;
            sumaBajaabb=0;

            sumaEvElso=0;
            sumaEvElsobb=0;
            sumaEvEabb=0;

            sumaEvNElso=0;
            sumaEvNElsobb=0;
            sumaEvNEabb=0;

            cantAltalso=0;
            cantAltalsobb=0;
            cantAltaabb=0;

            cantBajalso=0;
            cantBajalsobb=0;
            cantBajaabb=0;

            cantEvElso=0;
            cantEvElsobb=0;
            cantEvEabb=0;

            cantEvNElso=0;
            cantEvNElsobb=0;
            cantEvNEabb=0;
            leerArchivoOperaciones(lso,lsoBB,&arbol,&cantCargadosLSO,&cantCargadosLSOBB,&cantCargadosABB);
            system("pause");
            cuadroComp();
            break;
        case 2:
            if(cantCargadosLSO <1)
            {
                printf("Lista vacia\n");
                system("pause");
            }
            else
            {
                mostrarLSO(lso,cantCargadosLSO);
            }
            break;
        case 3:
            if(cantCargadosLSOBB <1)
            {
                printf("Lista vacia\n");
                system("pause");
            }
            else
            {
                mostrarLSOBB(lsoBB,cantCargadosLSOBB);
            }
            break;
        case 4:
            if(arbol.raiz != NULL)
            {
                printf("cargados: %d\n",cantCargadosABB);
                mostrarABB(&arbol);
            }
            else
            {
                printf("Arbol vacio\n");
                system("pause");
            }
            break;
        case 5:
            printf("Saliendo del programa...\n");
            exit(0);
        default:
            printf("Opcion invalida. Por favor, intente de nuevo.\n");
            getch();
            break;
        }/**FIN SWITCH*/

    }
    while(op!=5);
    return 0;
}

/**--------------------------------FUNCIONES PARA ABB----------------------------------*/
int localizarABB(ABB *arbol, int dni, float *costo)
{
    (arbol->cur) = (arbol->raiz);
    arbol->ant = arbol->cur;
    while(arbol->cur != NULL)
    {

        *costo = *costo + 1;    //primer comparacion ((arbol->cur)->dato).DNI != dni

        if(((arbol->cur)->dato).DNI != dni)
        {

            *costo+=1;          //segunda comparacion dni < ((arbol->cur)->dato).DNI

            arbol->ant = arbol->cur; //actualizo el cursor del anterior
            if(dni < ((arbol->cur)->dato).DNI)
            {
                arbol->cur = (arbol->cur)->izq;
            }
            else
            {
                arbol->cur = (arbol->cur)->der;
            }
        }
        else
        {
            break;
        }
    }
    if (arbol->cur == NULL)
    {
        return 0;  // fracaso
    }
    return 1; //exito
}

//RETORNA 1 SI TUVO EXITO, 0 SI YA EXISTIA EL PRESTADO, O -1 EN OTRO CASO.
int altaABB(ABB* arbol, Prestadores nuevo_dato, int *cantCargadosABB)
{
    float costo=0, a=0;
    if(arbol->raiz == NULL)
    {
        NodoABB* nodo = crearNodo(nuevo_dato);
        if (nodo != NULL)
        {
            costo=costo+0.5;
            arbol->raiz = nodo;
            *cantCargadosABB+=1;
            return 1;
        }
    }
    else
    {
        if(localizarABB(arbol,nuevo_dato.DNI,&a)==1)
        {
            return 0;
        }
        NodoABB* nodo = crearNodo(nuevo_dato);

        if(((arbol->ant)->dato).DNI < nuevo_dato.DNI)
        {
            costo=costo+0.5;
            (arbol->ant)->der = nodo;
        }
        else
        {
            costo=costo+0.5;
            (arbol->ant)->izq = nodo;
        }
        if (nodo != NULL)
        {
            *cantCargadosABB+=1;
            if(maxaltaabb<costo)
            {
                maxaltaabb=costo;
            }
            sumaAltaabb+=costo;
            cantAltaabb++;
            return 1;
        }
    }
    return -1;
}

int eliminarABB(ABB* arbol, Prestadores p, int *cantCargadosABB)
{
    float a=0, costo =0;

    if (localizarABB(arbol, p.DNI,&a) == 0)
    {
        return 0;
    }

    if(compararPrestador(p,(arbol->cur)->dato)==1)
    {
        // Caso sin hijos
        if ((arbol->cur)->izq == NULL && (arbol->cur)->der == NULL)
        {
            if(arbol->cur == arbol->raiz)
            {
                arbol->raiz = NULL;
            }
            else
            {
                if(arbol->ant->der == arbol->cur)
                {
                    arbol->ant->der = NULL;
                }
                else
                {
                    arbol->ant->izq = NULL;
                }
            }
            free((void*)arbol->cur);
            costo+=0.5;
            *cantCargadosABB-=1;
        }
        // Caso con solo hijo derecho
        else if ((arbol->cur)->izq == NULL)
        {
            if (arbol->cur == arbol->raiz)
            {
                arbol->raiz = arbol->cur->der;
            }
            else if(arbol->ant->der == arbol->cur)
            {
                arbol->ant->der = arbol->cur->der;
            }
            else
            {
                arbol->ant->izq = arbol->cur->der;
            }

            free((void*)arbol->cur);
            costo+=0.5;
            *cantCargadosABB-=1;
        }
        // Caso con solo hijo izquierdo
        else if ((arbol->cur)->der == NULL)
        {
            if (arbol->cur == arbol->raiz)
            {
                arbol->raiz = arbol->cur->izq;
            }
            else if(arbol->ant->der == arbol->cur)
            {
                arbol->ant->der = arbol->cur->izq;
            }
            else
            {
                arbol->ant->izq = arbol->cur->izq;
            }

            free((void*)arbol->cur);
            costo+=0.5;
            *cantCargadosABB-=1;
        }
        // Caso con dos hijos
        else
        {
            NodoABB* actual = (arbol->cur)->izq;
            NodoABB* padre = (arbol->cur);
            while (actual->der != NULL)
            {
                padre = actual;
                actual = actual->der;
            }

            // Si el nodo mayor de los menores tiene un hijo izquierdo:
            if (actual->izq != NULL)
            {
                if (padre->der == actual)
                {
                    padre->der = actual->izq;
                }
                else
                {
                    padre->izq = actual->izq;
                }
            }
            else
            {
                if (padre->der == actual)
                {
                    padre->der = NULL;
                }
                else
                {
                    padre->izq = NULL;
                }
            }

            (arbol->cur)->dato = actual->dato;
            free((void*)actual);
            costo += 1.5;
            *cantCargadosABB -= 1;
        }

        if(costo > maxbajaabb)
        {
            maxbajaabb = costo;
        }
        sumaBajaabb+=costo;
        cantBajaabb++;
        return 1;
    }
    return 0;
}

void push(Pila *p, NodoABB* nodo)
{
    NodoPila* nuevoNodo = (NodoPila*) malloc(sizeof(NodoPila));
    if (nuevoNodo == NULL){
        printf("Error: No se pudo asignar memoria para el nuevo nodo\n");
        exit(1);
    }
    nuevoNodo->dato = nodo;
    nuevoNodo->sig = p->tope;              // El siguiente del nuevo nodo es el antiguo tope
    p->tope = nuevoNodo;
}

NodoABB* pop(Pila *pila)
{
    if (pila->tope == NULL)
    {
        return NULL;
    }
    NodoABB* elemento = pila->tope->dato;
    NodoPila* nodoAEliminar = pila->tope;
    pila->tope = pila->tope->sig;
    free(nodoAEliminar);
    return elemento;
}

/**Verificar que no sea nulo antes de llamar a la función*/
void mostrarABB(ABB* arbol)
{
    Pila pila;
    pila.tope = NULL;
    int contdenodo=0;
    NodoABB* cursor=arbol->raiz;
    push(&pila,cursor);
    while((pila.tope)!=NULL)
    {
        contdenodo+=1;
        printf("\n-----------------------------------------------------------------\n");
        printf("Nodo numero %d:\n", contdenodo);
        printf("DATOS:\n   DNI: %d\n", (cursor->dato).DNI);
        printf("   Nombre: %s\n", (cursor->dato).nombreApellido);
        printf("   Servicios: %s\n", (cursor->dato).servicios);
        printf("   Domicilio: %s\n", (cursor->dato).domicilio);
        printf("   Mail: %s\n", (cursor->dato).mail);
        printf("   Telefono: %s\n", (cursor->dato).telefono);
        if(cursor->der != NULL)
        {
            printf("   DNI hijo derecho: %d\n", ((cursor->der)->dato).DNI);
            push(&pila, cursor->der);
        }
        if(cursor->izq != NULL)
        {
            printf("   DNI hijo izquierdo: %d", ((cursor->izq)->dato).DNI);
            cursor=cursor->izq;
        }
        else
        {
            cursor=pop(&pila);
        }
    }
    system("pause");
}

Prestadores evocacionABB(ABB* arbol, int dni)
{
    if(arbol->raiz==NULL)
    {
        Prestadores r;
        return r;
    }
    float costo = 0;
    if(localizarABB(arbol, dni, &costo))
    {
        if(maxevEabb < costo)
        {
            maxevEabb = costo;
        }
        sumaEvEabb+=costo;
        cantEvEabb++;
        return (arbol->cur)->dato;

    }
    else
    {
        if(maxevNEabb < costo)
        {
            maxevNEabb = costo;
        }
        sumaEvNEabb+=costo;
        cantEvNEabb++;
        return (arbol->ant)->dato;
    }
}

void limpiarNodos(NodoABB* nodo)
{
    if(nodo != NULL)
    {
        limpiarNodos(nodo->izq);
        limpiarNodos(nodo->der);
        free((void*)nodo);
    }
}

void limpiarABB(ABB *arbol, int *cantCargadosABB)
{
    limpiarNodos(arbol->raiz);
    arbol->raiz = NULL;
    arbol->cur = NULL;
    arbol->ant = NULL;
    *cantCargadosABB = 0;
}

/**-------------------------------------FUNCIONES PARA LSO-------------------------------------------------

LOCALIZAR: retorna 1 si lo encontro y 0 si no*/
int localizarLSO(int dni, Prestadores lso[],int *pos, float *costo)
{
    int i=0;
    while ((lso[i].DNI)<dni)
    {
        i=i+1;
        *costo+=1;
    }
    *costo+=2;
    *pos=i;
    if ((lso[i].DNI)==dni)
    {
        return 1;
    }
    return 0;
}

/**Retorna 1 si se insertó, -1 si está llena y 0 si ya estaba*/
int altaLSO(Prestadores lso[], Prestadores elem, int *cargados)
{
    float costo=0;
    if(*cargados==MAX-1)
    {
        return -1;
    }
    int pos=0;
    float nadaquever;
    if ((localizarLSO(elem.DNI, lso, &pos, &nadaquever))==1)
    {
        return 0;
    }
    int i;
    for(i=*cargados; i>=pos; i--)
    {
        costo++;
        lso[i+1]=lso[i];
    }
    if(maxaltalso<costo)
    {
        maxaltalso=costo;
    }
    sumaAltalso+=costo;
    lso[pos]=elem;
    *cargados+=1;
    cantAltalso++;
    return 1;
}

/**Retorna 1 si se pudo eliminar y 0 si no se pudo*/
int eliminarLSO(Prestadores lso[], Prestadores p, int *cargados)
{
    int pos;
    float costo=0;
    float nadaquever;
    if(localizarLSO(p.DNI, lso, &pos, &nadaquever))
    {
        if(compararPrestador(p,lso[pos])==1)
        {
            int i=pos;
            for(i; i<(*cargados); i++)
            {
                costo++;
                lso[i]=lso[i+1];
            }
            if(maxbajalso<costo)
            {
                maxbajalso=costo;
            }
            sumaBajalso+=costo;
            cantBajalso++;
            *cargados-=1;
            return 1;
        }
    }
    return 0;
}

Prestadores evocacionLSO(Prestadores lso[], int dni)
{
    int pos;
    float costo=0;
    int e=localizarLSO(dni, lso,&pos, &costo);
    if(e==1)
    {
        sumaEvElso+=costo;
        if(maxevElso<costo)
        {
            maxevElso=costo;
        }
        cantEvElso++;
        return lso[pos];
    }
    else
    {
        sumaEvNElso+=costo;
        if(maxevNElso<costo)
        {
            maxevNElso=costo;
        }
        cantEvNElso++;
        Prestadores p = {0};
        return p;  //prestador inválido
    }
}

void mostrarLSO(Prestadores lista[], int cargados)
{
    int i, mod;
    /*PARA QUE VAYA MOSTRANDO DE A 5*/
    for(i=0; i<cargados; i+=5)
    {
        system("cls");
        printf("LISTA SECUENCIAL ORDENADA CON TERMINACION DADA POR INFINITO\n");
        printf("--------------AGENDA DE PRESTADORES--------------\n");
        for(mod=i; mod<i+5 && mod<cargados; mod++)
        {
            printf("Prestador %d:\n", mod+1);
            printf("DNI: %d\n", lista[mod].DNI);
            printf("Nombre y Apellido: %s\n", lista[mod].nombreApellido);
            printf("Servicio: %s\n", lista[mod].servicios);
            printf("Domicilio: %s\n", lista[mod].domicilio);
            printf("Correo electronico: %s\n", lista[mod].mail);
            printf("Telefono: %s\n", lista[mod].telefono);
            printf("-------------------------------------------------\n");
        }
        system("pause");
    }
}

/**---------------------------------------FUNCIONES PARA LSOBB------------------------------------------------------

Triseccion: LI inclusivo, LS exclusivo, segmento mayor a izquierda
Retorna 1 si es exitoso, 0 si fracasa*/
int localizarLSOBB(int dni, Prestadores lso[], int *pos, int cargados, float *costo)
{
    int li = 0;
    int ls = cargados;
    int medio = cargados/2;
    while(li <= ls-1)
    {
        *costo+=1;
        if((lso[medio].DNI != dni))
        {
            *costo+=1;
            if(lso[medio].DNI > dni)
            {
                ls = medio;
            }
            else
            {
                li = medio+1;
            }
            medio = (li+ls) / 2;
        }
        else
        {
            break;
        }
    }
    *pos = medio;
    if (li<=ls-1)
    {
        return 1;
    }
    return 0;
}

/**Retorna 1 si se insertó, -1 si está llena y 0 si ya estaba*/
int altaLSOBB(Prestadores lso[], Prestadores elem, int *cargados)
{
    float costo=0, a=0;
    if(*cargados==MAX-1)
    {
        return -1;
    }
    int pos=0;
    if ((localizarLSOBB(elem.DNI, lso, &pos, *cargados, &a))==1)
    {
        return 0;
    }
    int i;
    for(i=*cargados-1; i>=pos; i--)
    {
        costo++;
        lso[i+1]=lso[i];
    }
    if(maxaltalsobb<costo)
    {
        maxaltalsobb=costo;
    }
    sumaAltalsobb+=costo;
    cantAltalsobb++;
    lso[pos]=elem;
    *cargados+=1;
    return 1;
}

/*Retorna 1 si se pudo eliminar, 0 si no se elimino.*/
int eliminarLSOBB(Prestadores lso[], Prestadores p, int *cargados)
{
    int pos = 0;
    float costo=0, a =0;
    if(localizarLSOBB(p.DNI, lso, &pos, *cargados,&a) == 1)
    {
        if(compararPrestador(p,lso[pos])==1)
        {
            int i=pos;
            for(i; i<(*cargados)-1; i++)
            {
                lso[i]=lso[i+1];
                costo++;
            }
            if(maxbajalsobb<costo)
            {
                maxbajalsobb = costo;
            }
            sumaBajalsobb += costo;
            cantBajalsobb++;
            *cargados-=1;
            return 1;
        }
    }
    return 0;
}

Prestadores evocacionLSOBB(Prestadores lso[], int dni, int cargados)
{
    int pos;
    float costo=0;
    if(localizarLSOBB(dni, lso,&pos, cargados, &costo)==1)
    {
        if(maxevElsobb < costo)
        {
            maxevElsobb = costo;
        }
        sumaEvElsobb+=costo;
        cantEvElsobb++;
        return lso[pos];
    }
    else
    {
        if(maxevNElsobb < costo)
        {
            maxevNElsobb = costo;
        }
        sumaEvNElsobb+=costo;
        cantEvNElsobb++;
        Prestadores p = {0};
        return p; //prestador invalido
    }
}

void mostrarLSOBB(Prestadores lista[], int cargados)
{
    int i, mod;
    /*PARA QUE VAYA MOSTRANDO DE A 5*/
    for(i=0; i<cargados; i+=5)
    {
        system("cls");
        printf("LISTA SECUENCIAL ORDENADA CON BUSQUEDA BINARIA\n");
        printf("--------------AGENDA DE PRESTADORES--------------\n");
        for(mod=i; mod<i+5 && mod<cargados; mod++)
        {
            printf("Prestador %d:\n", mod+1);
            printf("DNI: %d\n", lista[mod].DNI);
            printf("Nombre y Apellido: %s\n", lista[mod].nombreApellido);
            printf("Servicio: %s\n", lista[mod].servicios);
            printf("Domicilio: %s\n", lista[mod].domicilio);
            printf("Correo electronico: %s\n", lista[mod].mail);
            printf("Telefono: %s\n", lista[mod].telefono);
            printf("-------------------------------------------------\n");
        }
        system("pause");
    }
}

void leerArchivoOperaciones(Prestadores lso[], Prestadores lsoBB[], ABB* arbol, int *cantCargadosLSO, int *cantCargadosLSOBB, int *cantCargadosABB)
{
    FILE* archivo;
    archivo = fopen("Operaciones-Prestadores.txt", "r");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo\n");
        system("pause");
        return;
    }
    int codigoOperacion;
    Prestadores prestador;
    int dni;
    while (!feof(archivo))
    {
        fscanf(archivo, "%d", &codigoOperacion);
        switch (codigoOperacion)
        {
        case 1: // Alta de prestador
            fscanf(archivo, "%d",&prestador.DNI);
            fscanf(archivo, " %[^\n]", prestador.nombreApellido);
            fscanf(archivo, " %[^\n]", prestador.servicios);
            fscanf(archivo, " %[^\n]", prestador.domicilio);
            fscanf(archivo, " %[^\n]", prestador.mail);
            fscanf(archivo, " %[^\n]", prestador.telefono);

            if(prestador.DNI < INFINITO)
            {
                altaLSO(lso,prestador,cantCargadosLSO);
            }
            altaABB(arbol,prestador,cantCargadosABB);
            altaLSOBB(lsoBB,prestador,cantCargadosLSOBB);
            break;
        case 2: // Baja de prestador
            fscanf(archivo, "%d",&prestador.DNI);
            fscanf(archivo, " %[^\n]", prestador.nombreApellido);
            fscanf(archivo, " %[^\n]", prestador.servicios);
            fscanf(archivo, " %[^\n]", prestador.domicilio);
            fscanf(archivo, " %[^\n]", prestador.mail);
            fscanf(archivo, " %[^\n]", prestador.telefono);

            if(prestador.DNI < INFINITO)
            {
                eliminarLSO(lso, prestador, cantCargadosLSO);
            }
            eliminarLSOBB(lsoBB, prestador, cantCargadosLSOBB);
            eliminarABB(arbol, prestador,cantCargadosABB);
            break;
        case 3: // Evocar prestador
            fscanf(archivo, "%d", &dni);

            if(dni < INFINITO)
            {
                evocacionLSO(lso,dni);
            }
            evocacionLSOBB(lsoBB,dni,*cantCargadosLSOBB);
            evocacionABB(arbol,dni);
            break;
        default:
            printf("Codigo de operacion no reconocido: %d\n", codigoOperacion);
            break;
        }
    }
    fclose(archivo);
}

NodoABB* crearNodo(Prestadores p)
{
    NodoABB* nuevoNodo = (NodoABB*)malloc(sizeof(NodoABB));
    if (!nuevoNodo)
    {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        exit(1);
    }
    nuevoNodo->dato = p;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

int compararPrestador(Prestadores a, Prestadores b)
{
    if (a.DNI == b.DNI && strcasecmp(a.domicilio,b.domicilio)==0 && strcasecmp(a.mail,b.mail)==0 && strcasecmp(a.nombreApellido,b.nombreApellido)==0 && strcasecmp(a.servicios,b.servicios)==0 && strcasecmp(a.telefono,b.telefono)==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void cuadroComp(void)
{
    system("cls");
    system("color 03");
    printf("##==========================================================================##\n");
    printf("||                      COMPARACION DE ESTRUCTURAS                          ||\n");
    printf("##==========================================================================##\n");
    printf("||                      ||  COSTOS LSO  ||  COSTOS LSO.BB ||   COSTOS ABB   ||\n");
    printf("##==========================================================================##\n");
    printf("|| MAX. ALTA            ||     %.3f  ||      %.3f   ||      %.3f     ||\n",maxaltalso, maxaltalsobb, maxaltaabb);
    if(cantAltalso==0 && cantAltalsobb==0 && cantAltaabb==0)
    {
        printf("|| MEDIO ALTA           ||     0.000   ||      0.000    ||      0.000     ||\n");
    }
    else
    {
        printf("|| MEDIO ALTA           ||     %.3f   ||      %.3f    ||      %.3f     ||\n",(sumaAltalso/cantAltalso),(sumaAltalsobb/cantAltalsobb),(sumaAltaabb/cantAltaabb));
    }
    printf("|| MAX. BAJA            ||     %.3f   ||      %.3f    ||      %.3f     ||\n",maxbajalso, maxbajalsobb, maxbajaabb);
    if(cantBajalso==0  && cantBajalsobb==0 && cantBajaabb==0)
    {
        printf("|| MEDIO BAJA           ||     0.000   ||      0.000    ||      0.000     ||\n");
    }
    else
    {
        printf("|| MEDIO BAJA           ||     %.3f   ||      %.3f    ||      %.3f     ||\n",(sumaBajalso/cantBajalso),(sumaBajalsobb/cantBajalsobb),(sumaBajaabb/cantBajaabb));
    }
    printf("|| MAX. EVOC. EX.       ||     %.3f   ||      %.3f    ||      %.3f    ||\n",maxevElso, maxevElsobb, maxevEabb);
    if(cantEvElso==0 && cantEvElsobb==0 && cantEvEabb==0)
    {
        printf("|| MED. EVOC. EX.       ||     0.000   ||      0.000    ||      0.000     ||\n");
    }
    else
    {
        printf("|| MED. EVOC. EX.       ||     %.3f   ||      %.3f     ||      %.3f    ||\n",(sumaEvElso/cantEvElso),(sumaEvElsobb/cantEvElsobb),(sumaEvEabb/cantEvEabb));
    }
    printf("|| MAX. EVOC. NO EX.    ||     %.3f   ||      %.3f    ||      %.3f    ||\n",maxevNElso, maxevNElsobb, maxevNEabb);
    if(cantEvNElso==0 && cantEvNElsobb==0 && cantEvNEabb==0)
    {
        printf("|| MED. EVOC. NO EX.    ||     0.000   ||      0.000    ||      0.000     ||\n");
    }
    else
    {
        printf("|| MED. EVOC. NO EX.    ||     %.3f   ||      %.3f    ||      %.3f    ||\n",(sumaEvNElso/cantEvNElso),(sumaEvNElsobb/cantEvNElsobb),(sumaEvNEabb/cantEvNEabb));
    }
    printf("||==========================================================================||\n");
    system("pause");
    system("cls");
}
