#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "Stack.h"
#include <time.h>



//Estructuras
typedef struct{
  int numero; //En caso de que la carta sea numérica, llevará su número, en de que no, será -1;
  int codigo; //Es el código específico para las cartas en general
  int color; //El color de la carta va de 100 en 100. En caso de que no tenga color, este será 0.
  int clave;
}tipoCarta;

typedef struct{
  int id;//NÚMERO QUE LE CORRESPONDE AL ORDEN DE INGRESO DE NOMBRE
  char jugador[100]; //NOMBRE DEL JUGADOR
  List* cartasJugador; // DE LA BARAJA DEL JUGADOR
}tipoJugador;

typedef struct{
  tipoCarta carta;
  int cont; //Contador de veces que la carta está en el mapa de cartas
}tipoMapa;


//Funciones secundarias
/*
int lower_than_int(void *key1, void *key2) {
  if (*(int *)key1 < *(int *)key2)
    return 1;
  return 0;
}
*/

int is_equal_int(void *key1, void *key2){
  if(*(int*)key1==*(int*)key2) return 1;
  return 0;
}

void mostrarMapa(Map* mapa) {
    // Obtener el primer elemento del mapa
    void* elemento = firstMap(mapa);

    // Recorrer el mapa e imprimir cada elemento
    while (elemento != NULL) {
        tipoMapa* cartaMapa = (tipoMapa*)elemento;
        tipoCarta carta = cartaMapa->carta;

        // Obtener el siguiente elemento del mapa
        elemento = nextMap(mapa);
    }
}


void mostrarListasJugadores(List* listaJugadores) {
    List* jugadorNode = firstList(listaJugadores);

    while (jugadorNode != NULL) {
        tipoJugador* jugador = (tipoJugador*)jugadorNode;

        printf("Jugador: %s\n", jugador->jugador);
        printf("Cartas:\n");

       if(firstList(jugador->cartasJugador) == NULL) printf("CARTAS NULL\n");
        tipoMapa* cartaNode = firstList(jugador->cartasJugador);
      
        while (cartaNode != NULL) {
            tipoMapa* cartaMapa = (tipoMapa*)cartaNode;
            tipoCarta carta = cartaMapa->carta;
            printf("Color: %d, Codigo: %d, Numero: %d\n", carta.color, carta.codigo, carta.numero);
            cartaNode = nextList(jugador->cartasJugador);
        }
        jugadorNode = nextList(listaJugadores);
        
    }
}



void rellenarMapaCartas(Map *mapa, int *vectorClaves){
  //Se define una carta auxiliar, el color que será 100 y se irá multiplicando y la posición del vector que 
  //se llenará que partirá en 0.
  tipoCarta cartaAux;
  int color=100;
  int posicion=0;

  /*Aquí se asignarán todas las cartas que tengan un color asignado, es decir, 
  si la carta tiene número, se le asignará y si no se le asigna -1, su código se le asigna por
  el tipo de carta que es, también se le asignará los colores correspondientes.
  */
  for(int i=0; i<=12; i++){
    if(i>=0 && i<=9) cartaAux.numero=i;
    else{
      cartaAux.numero=-1;
    }
    cartaAux.codigo=i;
    //Asignando colores
    for(int j=1; j<=4; j++){
      cartaAux.color=color*j;
      //Asignando la clave para el mapa de cartas.
      cartaAux.clave=cartaAux.color+cartaAux.codigo;
      tipoMapa *cartaMapa = malloc(sizeof(tipoMapa));
      cartaMapa->carta = cartaAux;

      int *clave = malloc(sizeof(int));
      *clave = cartaAux.clave;
      
      //Hay 2 cartas de cada una de estas en el mapa
      cartaMapa->cont = 2;
      //Se guarda la clave única en un vector para luego buscar estas cartas de manera random.
      vectorClaves[posicion]=cartaAux.clave;
      posicion++;

      //Se inserta la carta al mapa
      insertMap(mapa, clave, cartaMapa);
    }
  }

  //Lo mismo que con las cartas anteriores pero con el +4 y cambio color, que no poseen ni número ni color.
  for(int i=13; i<=14; i++){
    cartaAux.numero=-1;
    cartaAux.codigo=i;
    cartaAux.clave = cartaAux.codigo;
    cartaAux.color=0;
    tipoMapa *cartaMapa = malloc(sizeof(tipoMapa));;
    cartaMapa->carta = cartaAux;
    cartaMapa->cont = 4;
    vectorClaves[posicion]=cartaAux.clave;
    posicion++;
    
    int *clave = malloc(sizeof(int));
      *clave = cartaAux.clave;
    insertMap(mapa, clave, cartaMapa);
  }
}


/*
FUNCIÓN REPARTIR: La función saca una carta al azar del mapa de cartas (El que contiene todas las cartas) y la ingresa en el mazo, donde, a su vez, baja el contador de dicha carta en el mapa, para que indique que esa carta ya está ocupada.
*/

//Saca cartas del deposito global de cartas
tipoMapa *repartir(Map *mapa, int *vectorClaves){
  /*Extrae una carta al azar y la ingresa a la lista de cartas del jugador
  
  -Se genera un numero aleatorio
  -Se busca en el vector la carta cuyo indice coincide con el numero generado
  -Se verifica si esa carta esta disponible
    -En caso de estarlo se entrega y se reduce el contador
    -En caso de no estarlo se repite el proceso (A no ser de que se elimine del vector¿?)
  */
  //Generar numero aleatorio, usa la libreria time para obtener algo de una semilla basada en el tiempo actual
  //srand(time(NULL));
   printf("entro a repartir \n");
  int numeroAleatorio = rand() % 53;
//error en trabajo de punteros
  //Buscar numero en el vector  
  int claveCarta = vectorClaves[numeroAleatorio];
  tipoMapa *cartaEntregar = (tipoMapa *)searchMap(mapa, &claveCarta);
  if(cartaEntregar == NULL) printf("ESNULL2");
  //printf("Color: %d, Codigo: %d, Numero: %d\n", cartaEntregar->carta.color, cartaEntregar->carta.codigo, cartaEntregar->carta.numero);  
  
   while(true){
     //Verificar disponibilidad
    if(cartaEntregar->cont != 0) {
      cartaEntregar->cont--;
      return cartaEntregar;
    }
    printf("claveCarta = %i contador = %i \n",cartaEntregar->carta.clave, cartaEntregar->cont);
    numeroAleatorio = rand() % 53;
    claveCarta = vectorClaves[numeroAleatorio];
    cartaEntregar = (tipoMapa *)searchMap(mapa, &claveCarta);
    printf("claveCarta = %i contador = %i \n",cartaEntregar->carta.clave, cartaEntregar->cont);
  }
  
  //printf("cont = %d \n", cont);
  return cartaEntregar;
}

//Crear mazos iniciales 
void crearBaraja(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves){
  /*a función crear baraja llama a la función repartir 7 veces 
  por cada jugador, es decir que ingresa 7 cartas a cada listaJugadores de 
  jugador*/
  
  for(int i = 1 ; i <= *contJugadores ; i++) {
    //creo la listaJugadores de cartas del jugador i 
    tipoJugador *jugador=malloc(sizeof(tipoJugador));
    jugador->id=i;
    jugador->cartasJugador = createList();
    printf("ingrese el nickname del jugador: ");
    scanf("%[^\n]s", jugador->jugador);
    getchar();
    //se reparten las cartas al la lista de cartas del jugador
    for(int j=0; j<=6;j++){
      pushFront(jugador->cartasJugador, repartir(mapa, vectorClaves));
    }
    //se ingresa el jugador con su baraja creada en la lista de jugadores
    pushFront(listaJugadores, jugador);
  } 
}
/*
//Dar carta al jugador cuando no tenga que tirar y saque del mazo
void sacarCarta(List *listaJugadores, Map *mapa, int *contJugadores){
  La función sacarCarta, extrae una carta del mapa y la ingresa a la
  mano del jugador que está jugando*/

void theGameEnd(char *nombreJugador)
{
  printf("wena ganaste\n\n");
  return;
}

tipoMapa *puntocentral(List *barajajugador){
  int contcentro = 0;
  tipoMapa *aux = firstList(barajajugador);

  while(aux!=NULL){
    aux = nextList(barajajugador);
    contcentro++;
  }
  
  int centro = trunc(contcentro/2);
  
  aux = firstList(barajajugador);
  while(centro!=0){
    aux=nextList(barajajugador);
    centro--;
  }
  return aux;
}

tipoMapa *turnojugador(List *barajajugador, tipoCarta CartaArriba, int sumaDeCartas){ 
  
  tipoMapa *centro = puntocentral(barajajugador);
  tipoMapa *next = nextList(barajajugador);
  tipoMapa *verificarNext = nextList(barajajugador);
  centro = puntocentral(barajajugador);
  tipoMapa *prev = prevList(barajajugador); 
  tipoMapa *verificarPrev = prevList(barajajugador);
  tipoMapa *aux;
    

  centro = puntocentral(barajajugador);
  
  char vacio[4];
  strcpy(vacio,"xxx");
  int tecla;
  while(true){
    //El pato ve los prints

    printf("            \n\n\n==\n%i\n==\n\n\n\n", CartaArriba.clave);  
    printf("            %i\n       ", centro->carta.clave);  
    
    
    if(prev != NULL)printf("%i",prev->carta.clave);
    else {printf("X");}
    
    if(next!=NULL)printf("       %i\n   ", next->carta.clave);  
    else {printf("       X\n   ");  }
    //if(verificarPrev != NULL)printf("%s",vacio);
    //if(verificarNext != NULL)printf("               %s\n", vacio);

    scanf("%i", &tecla);
    
    switch(tecla){
  
      case 77:{//derecha
        if(next==NULL){
          break;
        }
        prev = centro;
        centro = nextList(barajajugador);
        next = nextList(barajajugador);
        if(next != NULL){
          aux = prevList(barajajugador);  
        }
        break;
      }
      
      case 75:{//izquierda
        if(prev == NULL){
          break;
        }
        next = centro;
        centro = prevList(barajajugador);
        prev =  prevList(barajajugador);
        if(prev != NULL){
          aux = nextList(barajajugador);
        }
        break;
      }
      
      case 32:{
        //Hay que hacer lo visual
      
        //voy a verificar si coinicide, en caso de no coincidir se devolvería a la seleccion de cartas
        //Comprobar si puede tirar la carta
      
        //comprobar si tiro un mas algo teniendo una suma pendiente
        if(sumaDeCartas > 0 ){
          if(centro->carta.codigo == 13 || centro->carta.codigo == 12){
            return centro;
          }
        }
      
        //comprobar si coincide el color
        if(centro->carta.color == CartaArriba.color){
          return centro;
        }
      
        //comprobar si coincide el numero/simbolo
        if(centro->carta.codigo == CartaArriba.codigo){
          return centro;
        }

        printf("tira otra carta\n\n");
        break;
      }

      case 22:{
        return NULL;
      }
      
    }
    //A estas alturas ya tenemos la carta que jugó el jugador
  }
  
}




void theGame(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves)
{
  //Si la dirección es hacia la derecha, que será al principio, valdrá 0, si es al otro lado, valdrá 1.
  int direccion = 0;
  int sumaDeCartas = 0;
  int color = 0;
  tipoMapa *CartaArribaMapa = repartir(mapa, vectorClaves);
  tipoCarta CartaArriba = CartaArribaMapa->carta;
  tipoMapa *CartaAbajo = malloc(sizeof(tipoCarta));
  
  tipoJugador *jugadorAct = firstList(listaJugadores);

  color=CartaArriba.color;

  //int vueltas = 30;
  while(true){//(true)
    //mostrarListasJugadores(listaJugadores);
    tipoMapa *cartaJugada = turnojugador(jugadorAct->cartasJugador, CartaArribaMapa->carta, sumaDeCartas); //aspecto: se muestran las cartas del jugador y la cartaArriba
    //Retornará la carta jugada, en caso de que el jugador no tenga una carta para jugar o
    //salte su turno, se retornará NULL.
    //tipoMapa *cartaJugada = firstList(jugadorAct->cartasJugador);
    
    if(cartaJugada == NULL && sumaDeCartas == 0){
      pushFront(jugadorAct->cartasJugador, repartir(mapa, vectorClaves));
    }

    if(cartaJugada == NULL && sumaDeCartas > 0){
        while(sumaDeCartas != 0){
          pushFront(jugadorAct->cartasJugador, repartir(mapa, vectorClaves));
          sumaDeCartas--;
        }
    }

    if(cartaJugada != NULL){
      
      if(cartaJugada->carta.codigo==12){
        sumaDeCartas=sumaDeCartas+2;
      }
      if(cartaJugada->carta.codigo==13){
        sumaDeCartas=sumaDeCartas+4;
      }
      if(cartaJugada->carta.codigo==11){
        if(direccion==0) direccion=1;
        if(direccion==1) direccion=0;
      }
      
      //vueltas--;
      
      CartaAbajo = CartaArribaMapa;
      CartaArribaMapa = cartaJugada;

      tipoMapa* cartaNode = firstList(jugadorAct->cartasJugador);
      while (cartaNode != cartaJugada) {
          cartaNode = nextList(jugadorAct->cartasJugador);
      }
      popCurrent(jugadorAct->cartasJugador);
      
      if(cartaJugada->carta.codigo==10){
        if(direccion==0){
          jugadorAct = nextList(listaJugadores);
          if(jugadorAct == NULL){
            jugadorAct = firstList(listaJugadores);
          }
        }
        else{
          jugadorAct = prevList(listaJugadores);
          if(jugadorAct == NULL){
            jugadorAct = lastList(listaJugadores);
          }
        }
      }      
      CartaAbajo->cont++;
    }
    
    if(firstList(jugadorAct->cartasJugador) == NULL) {
      theGameEnd(jugadorAct->jugador);
      return;
    }
    
    if(direccion==0){
      jugadorAct = nextList(listaJugadores);
      if(jugadorAct == NULL){
        jugadorAct = firstList(listaJugadores);
      }
    }
    else{
      jugadorAct = prevList(listaJugadores);
      if(jugadorAct == NULL){
        jugadorAct = lastList(listaJugadores);
      }
    }  
  }
}

void theGameBegins(List* listaJugadores, Map* mapa, int *contJugadores, int *vectorClaves){
  //mostrarMapa(mapa);
  crearBaraja(listaJugadores,mapa, contJugadores, vectorClaves);
  theGame(listaJugadores,mapa, contJugadores, vectorClaves);
  
  return;
}


/*Estructura del tipoCarta
- Int Numero //
- int codigo: Cada carta tendrá un código específico asociado. En caso de que sea
una carta de tipo numérica, será del 0 al 9, el cambio color valdrá 10, +4 valdrá 11,
bloqueo valdrá 12, reversa 13 y +2 14.
- Int color: Se utilizara un numero para identificar el color que le corresponde a la carta
100 rojo, 200 azul, 300 verde, 400 amarillo y 500 especial.
Estructura del tipoMapa
- tipoCarta carta
- Int Contador: Se contendrá un contador para ver cuantas cartas hay de esta misma
en el mapa.
Funciones:
- Repartir cartas: Esta opci
*/

//Funciones principales

void IniciarPartida(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves){
  int opcion = 1;
  while(opcion != 0){
    printf("\033[0;37m");

    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║  Ingrese una cantidad de jugadores entre 2 y 4              ║\n");
    printf("║  Presione 0 para volver al menu inicial                     ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    
    scanf("%d", contJugadores);
    opcion=(*contJugadores);
    getchar();
  
    if(opcion>=2 && opcion<=4) theGameBegins(listaJugadores,mapa, contJugadores,vectorClaves);   
  }
}

void menu(List * listaJugadores, Map* mapa, int *contJugadores,int*vectorClaves){
  //Se crea una variable "opcion" la cual será una condicionante para el ciclo "while" base de nuestro programa
  int opcion = 1;
  while(opcion != 0){
printf("\033[0;31m");
    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║                  DEFINITIVAMENTE UNON'T :D                 ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║  Presione 1 para iniciar partida                            ║\n");
    printf("║  Presione 0 para salir del juego                            ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    //Se cambia el valor de la variable "opcion" con un valor que desee el usuario realizar
    scanf("%d", &opcion);
    getchar();
    //Se utiliza un switch para acceder a las opciones de cada función
    switch(opcion){
      case 2: mostrarListasJugadores(listaJugadores);
      break;
      case 1: IniciarPartida(listaJugadores,mapa, contJugadores,vectorClaves);
      break; 

      //en caso de ser cero se imprime lo sgte. Para finalizar el programa
      case 0:
        printf("         by GG WP//");
        break;
    }
  }
}

int main(void) {
  List *listaJugadores = createList();
  Map *mapa = createMap(is_equal_int);
  int contJugadores;
  int *vectorClaves =(int*) malloc(54*sizeof(int));
  rellenarMapaCartas(mapa,vectorClaves);
  srand(time(NULL));
  
  menu(listaJugadores, mapa, &contJugadores,vectorClaves);
  free(vectorClaves);
  return 0;
}