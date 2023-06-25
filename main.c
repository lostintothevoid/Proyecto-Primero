#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "Stack.h"
#include <time.h>
#include <conio.h>
#include <math.h>
#include "gotoxy.h"
#include <stdbool.h>


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
  //int numeroAleatorio = rand() % 53;
  int numeroAleatorio = rand() % 54;
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
    numeroAleatorio = rand() % 54;
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
    gotoxy(15,8);printf("ingrese el nickname del jugador%i: ", i);
    scanf("%[^\n]s", jugador->jugador);
    getchar();
    //se reparten las cartas al la lista de cartas del jugador
    for(int j=0; j<=6;j++){
      pushFront(jugador->cartasJugador, repartir(mapa, vectorClaves));
    }
    //se ingresa el jugador con su baraja creada en la lista de jugadores
    pushFront(listaJugadores, jugador);
    system("cls");
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

tipoMapa *turnojugador(List *barajajugador, tipoCarta CartaArriba, int sumaDeCartas, int *color){

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
    
    if(kbhit()){
      gotoxy(30,50);tecla = getch();
      system("cls");

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
          if(centro->carta.color == CartaArriba.color && sumaDeCartas == 0){
            return centro;
          }
        
          //comprobar si coincide el numero/simbolo
          if(centro->carta.codigo == CartaArriba.codigo && sumaDeCartas == 0){
            return centro;
          }

          if(sumaDeCartas==0 && centro->carta.codigo==14){
            printf("¿A que color quieres cambiar?\n");
            printf("1. Rojo\n");
            printf("2. Azul\n");
            printf("3. Verde\n");
            printf("4. Amarillo\n");
            int opcion;
            scanf("%d", &opcion);
            switch(opcion){
              case 1: *color=100;

              case 2: *color=200;

              case 3: *color=300;

              case 4: *color=400;
            }
            
          }
          
          gotoxy(30,4);printf("tira otra carta\n\n");
          break;
        }

        case 122:{
          return NULL;
        }
        case 120:{
          tipoMapa* cartaBool = malloc(sizeof(tipoMapa));
          cartaBool->carta.clave=999;
          return cartaBool;
        }
      }

      gotoxy(37,10);printf("===\n");
      gotoxy(37,11);printf("%i\n", CartaArriba.clave); 
      gotoxy(37,12);printf("===\n");   
      gotoxy(29,20);printf("            %i\n       ", centro->carta.clave);  
      
      
      if(prev != NULL){
        gotoxy(35,22);printf("%i",prev->carta.clave);
      } 
      else {
        gotoxy(35,22);printf("X");
      }
      
      if(next!=NULL){
        gotoxy(40,22);printf("       %i\n   ", next->carta.clave); 
      }   
      else {
        gotoxy(40,22);printf("       X\n   ");  
      }


    }
    //A estas alturas ya tenemos la carta que jugó el jugador
  }
  
}



void exportarDatos(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves, int direccion, int sumaDeCartas, tipoMapa *CartaArribaMapa, tipoMapa *CartaAbajo, tipoJugador *jugadorAct){
  //Se crea una string estática para dar un nombre al archivo qsue exportará a los jugadores
  
  char archivo[100];
  printf("Escribe el nombre con el que guardarás tu partida:\n");
  getchar();
  //scanf("%s",archivo);
  scanf("%[^\n]s",archivo);
  getchar();
  FILE *fp = fopen(archivo, "w");


  fprintf(fp, "Datos de partida: contJugadores, Direccion, sumDeCartas, CartaArribaMapa.numero, CartaArribaMapa.codigo, CartaArribaMapa.color, CartaArribaMapa.clave, CartaArribaMapa.cont, CartaAbajo.numero, CartaAbajo.codigo, CartaAbajo.color, CartaAbajo.clave, CartaAbajo.cont, jugadorAct.id\n");

  fprintf(fp, "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n", *contJugadores, direccion, sumaDeCartas, CartaArribaMapa->carta.numero, CartaArribaMapa->carta.codigo, CartaArribaMapa->carta.color, CartaArribaMapa->carta.clave, CartaArribaMapa->cont, CartaAbajo->carta.numero, CartaAbajo->carta.codigo, CartaAbajo->carta.color, CartaAbajo->carta.clave, CartaAbajo->cont, jugadorAct->id);
  
  
  fprintf(fp, "NombreJugador,ID jugador,Carta 1,numero, codigo, color, clave,Carta 2,Carta 3,Carta 4,Carta 5,Carta 6,Carta 7,Carta ...\n");
  //Se comienza a recorrer la lista jugaadores para imprimir los datos al archivo que se exportará todo
  for (tipoJugador *player = firstList(listaJugadores) ; player != NULL ; player = nextList(listaJugadores)){
    fprintf(fp, "%s,%d,", player->jugador, player->id);
    
    //Dentro de la iteración "for", se entra a otra, ya que puede existir el caso de que hayan más de un item
    for(tipoMapa* carta=firstList(player->cartasJugador) ; carta!=NULL; carta=nextList(player->cartasJugador)){
      
      fprintf(fp, "%i,%i,%i,%i,%i,", carta->cont, carta->carta.numero, carta->carta.codigo, carta->carta.color, carta->carta.clave);
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "Map: contador,numero, codigo, color, clave\n");
  
  void* elemento = firstMap(mapa);

  while (elemento != NULL) {
      tipoMapa* cartaMapa = (tipoMapa*)elemento;
      
       fprintf(fp, "%i,%i,%i,%i,%i,", cartaMapa->cont, cartaMapa->carta.numero, cartaMapa->carta.codigo, cartaMapa->carta.color, cartaMapa->carta.clave);
       fprintf(fp, "\n");
    
      elemento = nextMap(mapa);
  }
  
  
  //De no haber errores, se muestra el siguiente mensaje por pantalla 
  gotoxy(30,1);printf("===============================================================\n");
  gotoxy(30,2);printf("       Partida guardada con éxito\n");
  gotoxy(30,3);printf("                   ▒▒▒▒▒▒▒▒▒▄▄▄▄▒▄▄▄▒▒▒\n");
  gotoxy(30,4);printf("                   ▒▒▒▒▒▒▄▀▀▓▓▓▀█░░░█▒▒\n");
  gotoxy(30,5);printf("                   ▒▒▒▒▄▀▓▓▄██████▄░█▒▒\n");
  gotoxy(30,6);printf("                   ▒▒▒▄█▄█▀░░▄░▄░█▀▀▄▒▒\n");
  gotoxy(30,7);printf("                   ▒▒▄▀░██▄░░▀░▀░▀▄▓█▒▒\n");
  gotoxy(30,8);printf("                   ▒▒▀▄░░▀░▄█▄▄░░▄█▄▀▒▒\n");
  gotoxy(30,9);printf("                   ▒▒▒▒▀█▄▄░░▀▀▀█▀▓█▒▒▒\n");
  gotoxy(30,10);printf("                   ▒▒▒▄▀▓▓▓▀██▀▀█▄▀▒▒▒▒\n");
  gotoxy(30,11);printf("                   ▒▒█▓▓▄▀▀▀▄█▄▓▓▀█▒▒▒▒\n");
  gotoxy(30,12);printf("                   ▒▒▀▄█░░░░░█▀▀▄▄▀█▒▒▒\n");
  gotoxy(30,13);printf("                   ▒▒▒▄▀▀▄▄▄██▄▄█▀▓▓█▒▒\n");
  gotoxy(30,14);printf("                   ▒▒█▀▓█████████▓▓▓█▒▒\n");
  gotoxy(30,15);printf("                   ▒▒█▓▓██▀▀▀▒▒▒▀▄▄█▀▒▒\n");
  gotoxy(30,16);printf("                   ▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");
  gotoxy(30,17);printf("                           Oki doki!\n");
  gotoxy(30,18);printf("===============================================================\n");
  fclose(fp);
  
}


bool cargarDatos(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves, int *direccion, int *sumaDeCartas, tipoMapa *CartaArribaMapa, tipoMapa *CartaAbajo, int *turnoDe){
  char archivo[100];
  //Se le pide al usuario que ingrese el nombre del archivo de donde desea importar las tareas
  printf("Ingresa el nombre de la partida que quieras cargar:\n");
  //fflush(stdin);
  scanf("%[^\n]s",archivo);
  getchar();
  gotoxy(30,1);printf("                                                                \n");
  gotoxy(30,2);printf("                                                               \n");
  gotoxy(30,3);printf("                                                                 \n\n");
  gotoxy(30,4);printf("                                                               \n");
  gotoxy(30,5);printf("                                                                \n");
  gotoxy(30,6);printf("                                                               \n");
  gotoxy(30,7);printf("                                                                \n");
  gotoxy(30,8);printf("                                                                \n\n");

  //Se abre el archivo
  FILE *fp=fopen(archivo, "r");
  if(fp==NULL){
    gotoxy(30,1);printf("\n===============================================================\n");
    gotoxy(30,2);printf("                   Error al importar archivo...\n");
    gotoxy(30,3);printf("     Asegúrese de importar al programa con el mismo nombre\n");
    gotoxy(30,4);printf("===============================================================\n\n");
    return false;
  }
  char linea[300];
  //Se obtiene la primera línea (Que no nos sirve porque son las descripciones de las columnas)
  fgets(linea,301,fp);

  int j=0;
  //A partir de aqui las lineas son importante porque tienen la información que necesitamos
  while(fgets(linea,301,fp)!=NULL){
    //Es una tarea por linea, por lo que aquí se crea
    tipoJugador *player;
    player=malloc(sizeof(tipoJugador));
    //Se empieza a obtener cada parámetro a través de strtok, asi guardandose en sus variables correspondientes
    linea[strlen(linea)-1] = 0;
    
    char *ch = strtok(linea, ",");
    
    if(j==0){
      
      *contJugadores = atoi(ch);

      ch = strtok(NULL,",");
      *direccion= atoi(ch);

      ch = strtok(NULL,",");
      *sumaDeCartas= atoi(ch);
    
      ch = strtok(NULL,",");
      CartaArribaMapa->carta.numero = atoi(ch);
        
      ch = strtok(NULL,",");
      CartaArribaMapa->carta.codigo = atoi(ch);

      ch = strtok(NULL,",");
      CartaArribaMapa->carta.color = atoi(ch);

      ch = strtok(NULL,",");
      CartaArribaMapa->carta.clave = atoi(ch);

      ch = strtok(NULL,",");
      CartaArribaMapa->cont = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->carta.numero = atoi(ch);
        
      ch = strtok(NULL,",");
      CartaAbajo->carta.codigo = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->carta.color = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->carta.clave = atoi(ch);

      ch = strtok(NULL,",");
      CartaAbajo->cont = atoi(ch);

      ch = strtok(NULL,",");
      *turnoDe = atoi(ch);
      j++;
    }

    if(j==1){
      fgets(linea,301,fp);
      fgets(linea,301,fp);  
      linea[strlen(linea)-1] = 0;
    }
  
    if(j<=*contJugadores){
      tipoMapa *carta = malloc(sizeof(tipoMapa));
      if(j<2){
        ch = strtok(linea,",");  
      }
      strcpy(player->jugador,ch);        

      ch = strtok(NULL,",");
      player->id = atoi(ch);

      player->cartasJugador=createList();
    
      ch = strtok(NULL,",");

      while(ch != NULL){

      tipoMapa* carta = malloc(sizeof(tipoCarta));
      carta->cont = atoi(ch);   

      ch = strtok(NULL,",");
      carta->carta.numero = atoi(ch);   
      
      ch = strtok(NULL,",");
      carta->carta.codigo =atoi(ch);   
      
      ch = strtok(NULL,",");
      carta->carta.color = atoi(ch);   
        
      ch = strtok(NULL,",");
      carta->carta.clave = atoi(ch);
      
      pushBack(player->cartasJugador, carta);
      
      ch = strtok(NULL,",");
      }
      pushBack(listaJugadores, player);
    }
    
    if(j==*contJugadores){
      fgets(linea,301,fp);
      linea[strlen(linea)-1] = 0;
    }

    if(j>*contJugadores){
      tipoMapa *carta = malloc(sizeof(tipoMapa));
    
      //ch = strtok(NULL,",");
      carta->cont = atoi(ch);   
  
  
      ch = strtok(NULL,",");
      carta->carta.numero = atoi(ch);   
        
      ch = strtok(NULL,",");
      carta->carta.codigo =atoi(ch);   
        
      ch = strtok(NULL,",");
      carta->carta.color = atoi(ch);   
          
      ch = strtok(NULL,",");
      carta->carta.clave = atoi(ch);
        
      int *clave = malloc(sizeof(int));
        *clave = carta->carta.clave;
      insertMap(mapa, clave, carta);
    }
    j++;
  }

    gotoxy(30,1);printf("                                                                \n");
    gotoxy(30,2);printf("                                                               \n");
    gotoxy(30,3);printf("                                                                 \n\n");
    gotoxy(30,4);printf("                                                               \n");
    gotoxy(30,5);printf("                                                                \n");
    gotoxy(30,6);printf("                                                               \n");
    gotoxy(30,7);printf("                                                                \n");
    gotoxy(30,8);printf("                                                                \n\n");
  
  
  gotoxy(30,1);printf("\n===============================================================\n");
  gotoxy(30,2);gotoxy(30,1);printf("        La importación de tareas fue hecha con éxito\n");
  gotoxy(30,3);printf("===============================================================\n\n");
  fclose(fp);

  return true;
}


void theGame(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves,bool cargar)
{
  //Si la dirección es hacia la derecha, que será al principio, valdrá 0, si es al otro lado, valdrá 1.
  int direccion = 0;
  int sumaDeCartas = 0;
  int color = 0;
  int turnoDe = 0;
  tipoMapa *CartaArribaMapa = malloc(sizeof(tipoMapa));
  system("cls");
  if(cargar==false){
    CartaArribaMapa = repartir(mapa, vectorClaves);
    while(CartaArribaMapa->carta.codigo==13 || CartaArribaMapa->carta.codigo==14){
      CartaArribaMapa = repartir(mapa, vectorClaves);
    }
  }
  tipoCarta CartaArriba = CartaArribaMapa->carta;
  tipoMapa *CartaAbajo = malloc(sizeof(tipoCarta));
   
  tipoJugador *jugadorAct = firstList(listaJugadores);
   
  
  
  if(cargar==true){
   if(cargarDatos(listaJugadores, mapa, contJugadores, vectorClaves, &direccion, &sumaDeCartas, CartaArribaMapa, CartaAbajo, &turnoDe) == false) return;
    //hay que vincular turnoDe con el jugador actual
    for(jugadorAct=firstList(listaJugadores); jugadorAct!=NULL ; jugadorAct=nextList(listaJugadores)){
      if(turnoDe==jugadorAct->id) break;
    }
  }
  //mostrarListasJugadores(listaJugadores);
  if(CartaArriba.codigo!=13 && CartaArriba.codigo){
    color=CartaArriba.color;  
  }
  //int vueltas = 30;
  while(true){//(true)
    //mostrarListasJugadores(listaJugadores);
    gotoxy(30,4);printf("==============================\n");
    gotoxy(30,5);printf("       TURNO DE: %s \n", jugadorAct->jugador);
    gotoxy(30,6);printf("==============================\n"); 
    tipoMapa *cartaJugada = turnojugador(jugadorAct->cartasJugador, CartaArribaMapa->carta, sumaDeCartas, &color); //aspecto: se muestran las cartas del jugador y la cartaArriba

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

      if(cartaJugada->carta.clave == 999){
        exportarDatos(listaJugadores, mapa, contJugadores, vectorClaves, direccion, sumaDeCartas, CartaArribaMapa, CartaAbajo,  jugadorAct);
        return;
      }
      
      if(cartaJugada->carta.codigo==12){
        sumaDeCartas=sumaDeCartas+2;
      }
      if(cartaJugada->carta.codigo==13){
        sumaDeCartas=sumaDeCartas+4;
      }
      if(CartaArriba.codigo!=13 && CartaArriba.codigo){
        color=CartaArriba.color;  
      }
      //vueltas--;
      
      CartaAbajo = CartaArribaMapa;
      CartaArribaMapa = cartaJugada;

      tipoMapa* cartaNode = firstList(jugadorAct->cartasJugador);
      while (cartaNode != cartaJugada) {
          cartaNode = nextList(jugadorAct->cartasJugador);
      }
      popCurrent(jugadorAct->cartasJugador);

      if(cartaJugada->carta.codigo==11){
        if(direccion==0) direccion=1;
        if(direccion==1) direccion=0;
        if(*contJugadores == 2){
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
  theGame(listaJugadores,mapa, contJugadores, vectorClaves,false);
  
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

void IniciarPartida(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves) {
  int opcion = 1;
  system("cls");
  while (opcion != 0) {
    system("cls");
    
    gotoxy(30, 3);
    printf("Ingrese una cantidad de jugadores entre 2 y 4 \n");
    gotoxy(30, 4);
    printf("2 jugadores\n");
    gotoxy(30, 5);
    printf("3 jugadores\n");    
    gotoxy(30, 6);
    printf("4 jugadores\n\n");

    int flecha = 1;
    int tecla;
    while (true) {
      gotoxy(28, flecha + 3);
      printf(">");
      tecla = getch();
      gotoxy(28, flecha + 3);
      printf(" ");

      if (tecla == 13) {
        break;  // Presionar Enter para seleccionar la opción
      } else if (tecla == 224) {
        tecla = getch();  // Leer la tecla de flecha
        if (tecla == 72) {
          // Flecha hacia arriba
          if (flecha > 1) {
            flecha--;
          }
        } else if (tecla == 80) {
          // Flecha hacia abajo
          if (flecha < 3) {
            flecha++;
          }
        }
      }
    }

    system("cls");  // Limpiar la pantalla

    switch (flecha) {
      case 1:
        *contJugadores = 2;
        break;
      case 2:
        *contJugadores = 3;
        break;
      case 3:
        *contJugadores = 4;
        break;
    }

    if (*contJugadores >= 2 && *contJugadores <= 4) {
      theGameBegins(listaJugadores, mapa, contJugadores, vectorClaves);
    }
    
    printf("\nPresione Enter para continuar...");
    getchar();
  }
}

/*
void exportarDatos(List *listaJugadores, Map *mapa, int *contJugadores, int *vectorClaves, int direccion, int sumaDeCartas, tipoMapa *CartaArribaMapa, tipoMapa *CartaAbajo, tipoJugador *jugadorAct){
  //Se crea una string estática para dar un nombre al archivo qsue exportará a los jugadores


  fprintf(fp, "Datos de partida: contJugadores, Direccion, sumDeCartas, CartaArribaMapa.numero, CartaArribaMapa.codigo, CartaArribaMapa.color, CartaArribaMapa.clave, CartaArribaMapa.cont, CartaAbajo.numero, CartaAbajo.codigo, CartaAbajo.color, CartaAbajo.clave, CartaAbajo.cont, jugadorAct.id\n");

  fprintf(fp, "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",contJugadores, direccion, sumaDeCartas, CartaArribaMapa->carta.numero, CartaArribaMapa->carta.codigo, CartaArribaMapa->carta.color, CartaArribaMapa->carta.clave, CartaArribaMapa->cont, CartaAbajo->carta.numero, CartaAbajo->carta.codigo, CartaAbajo->carta.color, CartaAbajo->carta.clave, CartaAbajo->cont, jugadorAct->id);

  
  fprintf(fp, "NombreJugador,ID jugador,Carta 1,cont, numero, codigo, color, clave,Carta 2,Carta 3,Carta 4,Carta 5,Carta 6,Carta 7,Carta ...\n");
  //Se comienza a recorrer la lista jugaadores para imprimir los datos al archivo que se exportará todo
  for (tipoJugador *player = firstList(listaJugadores) ; player != NULL ; player = nextList(listaJugadores)){
    fprintf(fp, "%s,%d,", player->jugador, player->id);
    
    //Dentro de la iteración "for", se entra a otra, ya que puede existir el caso de que hayan más de un item
    for(tipoMapa* carta=firstList(player->cartasJugador) ; carta!=NULL; carta=nextList(player->cartasJugador)){
      
      fprintf(fp, "%i,%i,%i,%i,%i, ", carta->cont, carta->carta.numero, carta->carta.codigo, carta->carta.color, carta->carta.clave);
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "Map: contador,numero, codigo, color, clave\n");
  
  void* elemento = firstMap(mapa);

  while (elemento != NULL) {
      tipoMapa* cartaMapa = (tipoMapa*)elemento;
      
       fprintf(fp, "%i,%i,%i,%i,%i,", cartaMapa->cont, cartaMapa->carta.numero, cartaMapa->carta.codigo, cartaMapa->carta.color, cartaMapa->carta.clave);
       fprintf(fp, "\n");
    
      elemento = nextMap(mapa);
  }

}
*/

void menu(List * listaJugadores, Map* mapa, int *contJugadores,int*vectorClaves) {
  int opcion = 1;
  while (opcion != 0) {
    system("cls");  // Limpiar la pantalla
    gotoxy(32, 2);
    printf("DEFINITIVAMENTE UNON'T :D\n");
    gotoxy(32, 4);
    printf("\n");
    gotoxy(32, 5);
    printf("iniciar partida\n");
    gotoxy(32, 6);
    printf("cargar partida\n");
    gotoxy(32, 7);
    printf("salir del juego\n");


    int flecha = 1;
    int tecla;
    while (true) {
      gotoxy(30, flecha + 4);
      printf(">");
      tecla = getch();
      gotoxy(30, flecha + 4);
      printf(" ");

      if (tecla == 13) {
        break;  // Presionar Enter para seleccionar la opción
      } else if (tecla == 224) {
        tecla = getch();  // Leer la tecla de flecha
        if (tecla == 72) {
          // Flecha hacia arriba
          if (flecha > 1) {
            flecha--;
          }
        } else if (tecla == 80) {
          // Flecha hacia abajo
          if (flecha < 3) {
            flecha++;
          }
        }
      }
    }

    system("cls");  // Limpiar la pantalla

    switch (flecha) {
      case 1:
        IniciarPartida(listaJugadores,mapa, contJugadores,vectorClaves);
        break;
      case 2:
        bool cargar = true;
        theGame(listaJugadores, mapa, contJugadores, vectorClaves, cargar);      
        break;
      case 3:
        printf("         by GG WP//");
        return;  
        break;
    }
    
    printf("\nPresione Enter para continuar...");
    getchar();
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
  free(listaJugadores);
  free(mapa);
  return 0;
}