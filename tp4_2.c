#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct TNodo{
    Tarea T;
    struct TNodo * Siguiente;
}TNodo;

TNodo * CrearLista();
Tarea * CrearTarea(int *id);
TNodo * NuevoNodo(Tarea nuevaTarea);
void AgregarALista(TNodo ** Lista, Tarea NuevaTarea);
void MostrarLista(TNodo *cabecera,const char *tituloLista); //doble puntero al que le mando la direccion de la cabecera
void TransferirTarea(TNodo **cabecera, TNodo **Realizadas);
TNodo * QuitarNodoPorID(TNodo **lista, int idBuscado);
void InsertarEnLista(TNodo **Lista, TNodo *Nodo);
void BuscarTarea(TNodo *ListaTP,TNodo *ListaTR);
void LiberarLista(TNodo *lista);

int main(){

    //Crear nodo tarea pendiente 
    TNodo * tareasPendientes;
    TNodo * tareasRealizadas;
    Tarea * temporal;
    tareasPendientes = CrearLista();
    tareasRealizadas = CrearLista();
    int continuar,marcar, *p_id;
    int id = 999; //Falta crear la variable y el puntery pasar por referencia en la funcion crear tarea, para que sea autoincremental el id
    p_id = &id;

    do
    {
        temporal = CrearTarea(p_id); 
        AgregarALista(&tareasPendientes,*temporal);
        printf("\nContinuar agregando tarea: 1 = SI, 0 = NO \n");
        scanf("%d",&continuar);

    } while (continuar);

    printf("\nMarcar tarea pendiente como realizada: 1 = SI, 0 = NO \n");
    scanf("%d",&marcar);
    if (marcar)
    {
        TransferirTarea(&tareasPendientes, &tareasRealizadas);
    } 

    MostrarLista(tareasPendientes,"TAREAS PENDIENTES");
    MostrarLista(tareasRealizadas,"TAREAS REALIZADAS");

    printf("\n");
 //   BuscarTarea(tareasPendientes,tareasRealizadas);
    LiberarLista(tareasPendientes) ; 
    LiberarLista(tareasRealizadas) ;
    MostrarLista(tareasPendientes,"TAREAS PENDIENTES");
    MostrarLista(tareasRealizadas,"TAREAS REALIZADAS");   

    return 0;
}

TNodo * CrearLista(){
    return NULL;
}

Tarea * CrearTarea(int *id){ 
    Tarea * Tarea = malloc (sizeof(Tarea));
    char *buff;
    (*id) =  (*id) + 1; //modifico la vaariable id 
    Tarea->TareaID = (*id); 
    buff = (char *) malloc(100 * sizeof(char));
    printf("\nIngresar descripcion de la tarea:"); 
    fflush(stdin);
    gets(buff);
    Tarea->Descripcion = (char *) malloc( (strlen(buff) + 1) * sizeof(char));
    strcpy(Tarea->Descripcion,buff);
    free(buff);
    Tarea->Duracion = rand() % 91 + 10 ; 

    return Tarea;
}

TNodo * NuevoNodo(Tarea nuevaTarea){
    TNodo * nuevoNodo = (TNodo *)malloc(sizeof(TNodo));
    nuevoNodo->T = nuevaTarea;
    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}


void AgregarALista(TNodo **cabecera, Tarea nuevaTarea) {
    TNodo * nuevo = NuevoNodo(nuevaTarea);

    // Si la lista está vacía, el nuevo nodo se convierte en la cabecera
    if (*cabecera == NULL) {
        * cabecera = nuevo;
        return;
    }

    // Buscamos el último nodo en la lista
    TNodo * aux = *cabecera;
    while (aux->Siguiente != NULL) {
        aux = aux->Siguiente;
    }

    // Enlazamos el nuevo nodo al final de la lista
    aux->Siguiente = nuevo;
}

void MostrarLista(TNodo *lista, const char *tituloLista)
{
    TNodo *aux = lista;
    printf("\n"); 
    printf("LISTA: %s\n", tituloLista);
    while (aux!=NULL)
    {
        printf("\nTarea ID: %d", aux->T.TareaID);
        printf("\nDescripcion:"); //%s", aux->T.Descripcion);
        puts(aux->T.Descripcion);
        printf("\nDuracion: %d", aux->T.Duracion);
        
        aux = aux->Siguiente;
    }
    printf("\n");
}

void TransferirTarea(TNodo **cabecera, TNodo **Realizadas){ 
    TNodo * Aux = *cabecera;
    TNodo * Amover;
    TNodo * proximo;
    int transferir;

    while (Aux != NULL)
    {
        printf("\nTarea ID: %d", Aux->T.TareaID);
        printf("\nDescripcion: %s", Aux->T.Descripcion);
        printf("\nDuracion: %d", Aux->T.Duracion);
        
        printf("\nTransferir esta tarea? 1 = SI, 0 = NO \n");
        scanf("%d",&transferir);
        if (transferir)
        {
            proximo = Aux->Siguiente;
            Amover = QuitarNodoPorID(cabecera,Aux->T.TareaID);
            InsertarEnLista(Realizadas,Amover);    
            Aux = proximo; 
        }else
        {
            Aux = Aux->Siguiente;
        }
    }
}

TNodo * QuitarNodoPorID(TNodo **lista, int idBuscado){ //EN TEMPLATE TENGO X DESCRIPCION
    TNodo *aux = *lista;
    TNodo *anterior = *lista;

    while (aux != NULL && aux->T.TareaID != idBuscado)
    {
        anterior = aux;
        aux = aux->Siguiente;
    }
    
    if (aux != NULL)
    {
        if (aux == (*lista))
        {
           *lista = aux->Siguiente;
        }else
        {
            anterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;
        
    }
    return aux;
}

void InsertarEnLista(TNodo **Lista, TNodo *Nodo) 
{
    if (*Lista == NULL) {
        *Lista = Nodo;
    } else {
        TNodo *temp = *Lista;
        while (temp->Siguiente != NULL) {
            temp = temp->Siguiente;
        }
        temp->Siguiente = Nodo;
    }
}

/*4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y
mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada.*/

void BuscarTarea(TNodo *ListaTP,TNodo *ListaTR){

    int encontrado, idBuscado, repetir;
    TNodo *Aux;
    do
    {
        encontrado = 0;
        puts("\nIngrese el id de la tarea a buscar: ");
        scanf("%d", &idBuscado);
        fflush(stdin);

        Aux = ListaTP;

        while (ListaTP != NULL)
        {
            if (ListaTP->T.TareaID == idBuscado)
            {
                printf("\nTarea ID: %d", ListaTP->T.TareaID);
                printf("\nDescripcion: %s", ListaTP->T.Descripcion);
                printf("\nDuracion: %d", ListaTP->T.Duracion);
                printf("\nEstado de la tarea: PENDIENTE");
                encontrado = 1;
            }
            if (encontrado)
            {
                break;
            }
            
            ListaTP = ListaTP->Siguiente;
        }   

        if (encontrado != 1) //Si no lo encuentra en la primera lista , busca en la segunda
        {
            while (ListaTR != NULL)
            if (ListaTR->T.TareaID == idBuscado)
            {
                printf("\nTarea ID: %d", ListaTR->T.TareaID);
                printf("\nDescripcion: %s", ListaTR->T.Descripcion);
                printf("\nDuracion: %d", ListaTR->T.Duracion);
                printf("\nEstado de la tarea: REALIZADA");                
            }
            ListaTR = ListaTR->Siguiente;
        }

        if(encontrado == 0)
        {
            puts("\n>>>>Tarea no encontrada\n");
        }

        puts("\nDesea buscar otra tarea?(s:1/n:0): \n");
        scanf("%d", &repetir);
        fflush(stdin);    
    } while (repetir);
}

void LiberarLista(TNodo *lista) {
    TNodo *Aux; // Designo nodo Aux

    while (lista != NULL) { // si la lista no está vacía
        // pongo el nodo en el lugar de la lista para liberarlo, y voy moviendo la lista
        Aux = lista;
        lista = lista->Siguiente; 
        free(Aux->T.Descripcion); // solo debo liberar este campo ya que es el unico con memo dinamica asignada
        free(Aux);
    }
}

