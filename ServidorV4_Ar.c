#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>

//Variables globales
MYSQL *conn;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//int i;

//Estructuras
typedef struct{
	char nombre[20];
	int socket;
	int partida;
} Conectado;

typedef struct{
	Conectado conectados[100];
	int num;
} ListaConectados;

//Variable global
ListaConectados lista;

typedef struct{
	Conectado jugadores[4];
	char equipo[50];
	int numJugadores;
	int pruebas[4];
	int aciertos; //Se pasará de prueba cuando todos los jugadores hayan acertado, o sea numero de aciertos = numero de jugadores  
	int estado; //0 si está vacio, 1 lleno, -1 no esta completo
}Partida;

//Variable global
Partida tablas[100]; 

void PonNombre (ListaConectados *lista, char nombre[20], int s){ //Pone nombre a un socket de la lista de conectados	
	int i = 0;
	int encontrado = 0;
	
	while ((i < lista->num) && encontrado == 0){
		if (lista->conectados[i].socket == s)
			encontrado = 1;
		if (encontrado == 0)
			i++;
	}
	
	strcpy(lista->conectados[i].nombre, nombre);	
}


int PonSocket(ListaConectados *lista, int socket){ //Asigna un socket cuando se conecta una persona
	if (lista->num == 100)
		return -1;
	else{
		lista->conectados[lista->num].socket = socket;
		strcpy(lista->conectados[lista->num].nombre, "");
		lista->num++;
		return 0;
	}
}


int DamePosicion (ListaConectados *lista, char nombre[20]){ //Devuelve la posición de una persona, a partir de su nombre, dentro de la lista
	int i = 0;
	int encontrado = 0;
	
	while ((i < lista->num) && !encontrado){
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
			encontrado = 1;
		if (!encontrado)
			i++;
	}
	
	if (encontrado)
		return i;
	else
		return -1;
}


int CreaPartida (Partida Ttabla[100], char nombre[20], int s) //Se asigna una posición de la tabla de partidas
{
	int t = 0;
	
	while (t < 100){
		if (Ttabla[t].estado == 0){		
			strcpy (Ttabla[t].jugadores[0].nombre, nombre);
			Ttabla[t].jugadores[0].socket = s;
			Ttabla[t].estado = -1;
			Ttabla[t].numJugadores = 1;
			lista.conectados[DamePosicion(&lista, nombre)].partida = t;
			return t;
		}
		t ++;
	}
	return -1;
}


int SalaDeEspera (Partida tabla[100], char nombre[20], int s, int id) //Une a un jugador a una partida 
{
	if (tabla[id].numJugadores < 4){
		int numero = tabla[id].numJugadores;
		lista.conectados[DamePosicion(&lista, nombre)].partida = id;
		tabla[id].jugadores[numero] = lista.conectados[DamePosicion(&lista, nombre)];
		tabla[id].numJugadores ++;
	}
	
	if (tabla[id].numJugadores == 4){
		tabla[id].estado = 1;
	}
	
	return tabla[id].estado;
}



int Salir (Partida tabla[100], char nombre[20], int id) //Salir de una partida
{
	int j = 0;
	int encontrado = 0;
	
	while (j < tabla[id].numJugadores && encontrado == 0){
		if (strcmp(tabla[id].jugadores[j].nombre, nombre) == 0)
			encontrado = 1;
		else
			j++;
	}	
	
	int i;
	for (i=j; i < tabla[id].numJugadores-1; i++){
		tabla[id].jugadores[i] = tabla[id].jugadores[i+1];
	}
	
	lista.conectados[DamePosicion(&lista, nombre)].partida = -1;
	tabla[id].numJugadores--;
	
	if (tabla[id].numJugadores == 0){ //Si la partida se queda sin jugadores, se "desocupa" la posicion de esa partida en la tabla
		tabla[id].estado = 0;
	}
}



void BorrarPartida (Partida tabla[100], int id){
	for (int i = 0; i < tabla[id].numJugadores; i++){
		lista.conectados[DamePosicion(&lista, tabla[id].jugadores[i].nombre)].partida = -1;
		strcpy(tabla[id].jugadores[i].nombre, "");
	}
	tabla[id].estado = 0;
	tabla[id].numJugadores = 0;
}


int Eliminar (ListaConectados *lista, char nombre[20]) //Eliminar a una conectado de la lista de conectados
{
	int pos = DamePosicion (lista, nombre);
	if (pos == -1)
		return -1;
	else{
		int i;
		for (i=pos; i < lista->num-1; i++){
			lista->conectados[i] = lista->conectados[i+1];
		}
		
		lista->num--;
		return 0;
	}
}
 

void DameConectados (ListaConectados *lista, char conectados[500]) //Devuelve un char con la lista de los conectados
{
	int i;
	for (i=0; i < lista->num; i++){
		if (strcmp(lista->conectados[i].nombre, "") != 0) //Si alguno se conectó y se le asignó un socket pero aun no ha introducido su nombre no se incluye en esta lista de conectados
			sprintf (conectados, "%s%s,", conectados, lista->conectados[i].nombre);
	}
	conectados[strlen(conectados) - 1] = '\0';
}


void DameJugadores (Partida tabla[100], char invitados[500], int id) //Devuelve los jugadores de una partida a partir de su id de partida
{
	int w;
	for (w=0; w < tabla[id].numJugadores; w++){
		sprintf (invitados, "%s%s,", invitados, tabla[id].jugadores[w].nombre);
	}
	invitados[strlen(invitados) - 1] = '\0';
}


int GuardarTodo (Partida tabla[100], char duracion[20], char fecha[20], int id) //Guarda los datos de las partidas en la base de datos
{
	
	char consulta [500];
	char con [500];
	char consu [500];
	char ganador[20];
	int err;
	int idP;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	if(strcmp(duracion, "20:00") != 0)
	{
		strcpy (ganador, "si");
	}
	else
	   strcpy (ganador, "no");
	
	sprintf(consulta, "INSERT INTO partida(ganador, fecha, duracion, equipo) VALUES ('%s','%s','%s','%s')", ganador, fecha, duracion, tabla[id].equipo);
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 0;
	}
	else{
		printf ("funciona\n");
	}
	
	int er = mysql_query (conn, "SELECT idP FROM partida ORDER BY idP DESC liMIT 1");
	// Recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial 
	row = mysql_fetch_row (resultado);
	
	idP = atoi(row[0]);
	
	for (int i = 0; i<tabla[id].numJugadores; i++)
	{
		sprintf(consu, "SELECT idJ FROM jugador WHERE nombre = '%s'", tabla[id].jugadores[i].nombre);
		err=mysql_query (conn, consu);
		// Recogemos el resultado de la consulta
		resultado = mysql_store_result (conn);
		// El resultado es una estructura matricial 
		row = mysql_fetch_row (resultado);
		int idJ = atoi(row[0]);
		sprintf(con, "INSERT INTO historial VALUES ('%d','%d')", idJ, idP);
		err=mysql_query (conn, con);
	}	
}


int insertar(char nombre[20], char password[20]){ //Registro de una persona, se introducen sus datos en la base de datos

	char consulta [500];
	int err;
	
	sprintf(consulta, "INSERT INTO jugador(nombre, contraseña) VALUES ('%s','%s')", nombre, password);
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 0;
	}
	else{
		printf ("funciona\n");
		return 1;
	}
}


int borrar(char nombre[20], char password[20]) //Se borran los datos de la persona con el nombre y contresña que se pasa por parámetro de la base de datos
{
	
	char consulta [500];
	char consul [500];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int id;
	sprintf(consul,  "SELECT idJ FROM jugador WHERE nombre = '%s' AND contraseña = '%s'", nombre, password);
	
	int er = mysql_query (conn, consul);
	if (er!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	// Recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial 
	row = mysql_fetch_row (resultado);
	// Recorremos una a una cada fila del resultado
	
	if (row == NULL){ //si no existe nadie con este nombre devuelve 0, porque dara error. Si funciona significa que lo ha borrado.
		return 0;
	}
	else{
		id = atoi(row[0]);
		sprintf(consulta, "DELETE FROM jugador WHERE idJ ='%d'", id);
		err=mysql_query (conn, consulta);
		if (err!=0)
		{
			printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
			return 0;
		}
		else{
			printf ("funciona\n");
			return 1;
		}
	}
}


int buscar(char nombre[20], char password[20]){ //Busca en la base de datos un jugador con el nombre y contraseña que se pasa por parámetro, si la encuentra el login será correcto
	
	char consulta [500];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int id;
	
	sprintf(consulta, "SELECT * FROM jugador WHERE contraseña = '%s' AND nombre = '%s'", password, nombre);
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		return 0;
	}
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial 
	row = mysql_fetch_row (resultado);
	// Recorremos una a una cada fila del resultado
	if (row == NULL)
		return 0;
	else
		return 1;
}


int Historial(char nombre[20], char result[1000]){ //Consulta 1: muestra el historial de una personal
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[500];
	int i;
	
	sprintf(consulta, "SELECT partida.duracion, partida.fecha, partida.equipo, partida.ganador  FROM (historial, jugador, partida) WHERE jugador.nombre = '%s' AND jugador.idJ = historial.idJ AND historial.idP = partida.idP", nombre);
	
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial 
	
	row = mysql_fetch_row (resultado);
	// Recorremos una a una cada fila del resultado
	if (row == NULL)
		return 0;
	else{

		while (row !=NULL){
		
			sprintf (result, "%s%s_%s_%s_%s,", result, row[2], row[1], row[0], row[3]);
				
			// Obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
		}
		result[strlen(result) - 1] = '\0';
		return 1;
	}
}


int Ranking(char equipos[1000]) //Consulta 2: Muestra el top 10 de las mejores partidas jugadas
{	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[500];
	int i;
	
	sprintf(consulta, "SELECT partida.duracion, partida.equipo FROM (partida) ORDER BY partida.duracion DESC LIMIT 10");
	
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial 
	
	row = mysql_fetch_row (resultado);
	// Recorremos una a una cada fila del resultado
	if (row == NULL)
		return 0;
	else
	{
		while (row !=NULL){
			
			sprintf (equipos, "%s%s_%s,", equipos, row[1], row[0]);
			row = mysql_fetch_row (resultado);
		}
		
		equipos[strlen(equipos) - 1] = '\0';
		return 1;
	}
}


void MiembrosEquipo(char equipo[100], char nombres[500]) //Consulta 3: Muestra el nombre de los jugadores que formaron un equipo
{
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[500];
	int i;
	
	sprintf(consulta, "SELECT jugador.nombre FROM (partida, jugador, historial) WHERE partida.equipo = '%s' AND partida.idP = historial.idP AND historial.idJ = jugador.idJ", equipo);
	
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial 
	
	row = mysql_fetch_row (resultado);
	// Recorremos una a una cada fila del resultado
	
	while (row !=NULL){
			
			sprintf (nombres, "%s %s,", nombres, row[0]);
			
			row = mysql_fetch_row (resultado);
	}
	nombres[strlen(nombres) - 1] = '\0';	
}


void FechaRanking (char fecha[20], char ranking[3000])
{
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[500];
	int i;
	
	sprintf(consulta, "SELECT equipo, duracion, fecha FROM partida WHERE fecha = '%s'", fecha);
	
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial 
	
	row = mysql_fetch_row (resultado);
	// Recorremos una a una cada fila del resultado
	if (row == NULL){
		sprintf (ranking, "1");
	}
	else{
		while (row !=NULL){
			
			sprintf (ranking, "%s%s_%s_%s,", ranking, row[0], row[1], row[2]);
			
			row = mysql_fetch_row (resultado);
		}
		ranking[strlen(ranking) - 1] = '\0';
	}	
}



void *AtenderCliente(void *socket)
{
	int sock_conn;
	int *s;
	s = (int *)socket;
	sock_conn = *s;
	
	char nombre[20];
	char peticion[512];
	char respuesta[512];
	int ret;
	
	int terminar = 0;
	// Entramos en un bucle para atender todas las peticiones de este cliente
	//hasta que se desconecte
	while (terminar == 0)
	{
		// Ahora recibimos la petición
		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibido\n");
		// Tenemos que añadirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret] = '\0';
		
		printf("Peticion: %s\n", peticion);
		
		// vamos a ver que quieren
		char *p = strtok(peticion, "/");
		int codigo = atoi(p);
		// Ya tenemos el código de la peticion
		
		if (codigo == 0) //Peticion de desconexion
		{	
			int pos = DamePosicion(&lista, nombre);
			int id = lista.conectados[pos].partida;
			
			terminar = 1;
			pthread_mutex_lock(&mutex);
			Eliminar(&lista, nombre);
			pthread_mutex_unlock(&mutex);
			
			//Se actualiza la lista de conectados para todos los conectados
			char conect[500];
			conect[0] = '\0';
			char conectados[500];
			
			DameConectados(&lista, conect);
			sprintf(conectados, "%s", conect);
			
			char notificacion[200];
			sprintf (notificacion, "7/%s", conectados);
			
			int j;
			for (j=0; j< lista.num; j++){
				write (lista.conectados[j].socket, notificacion, strlen(notificacion));
			}
			
			if (id != -1){ //El jugadores estaba dentro de una partida (no tiene porqué ser jugando)
				
				pthread_mutex_lock(&mutex);
				Salir(tablas, nombre, id);
				pthread_mutex_unlock(&mutex);
				
				if(tablas[id].numJugadores == 1){					
					char aviso[20];
					aviso[0] = '\0';
					sprintf(aviso, "18/%s", tablas[id].jugadores[0].nombre);
					
					write (tablas[id].jugadores[0].socket, aviso, strlen(aviso));
					
					printf("%s\n", aviso);
					
					
				}
				else{
					//Se actualiza la lista de jugadores de una partida "sala de espera"
					char jugadores[500];
					jugadores[0] = '\0';
					
					DameJugadores(tablas, jugadores, id);
					printf("%s\n", jugadores);
					
					char actualizar[200];
					sprintf (actualizar, "12/%s", jugadores);
					printf("%s\n", actualizar);
					
					int t;
					for (t=0; t< tablas[id].numJugadores; t++){
						write (tablas[id].jugadores[t].socket, actualizar, strlen(actualizar));
					}
					
					printf("%d\n", tablas[id].numJugadores);
				}
				
			}
		}
		
		else if (codigo == 1) //Registrarse
		{
			char password[20];
			char nom[20];
			
			p = strtok(NULL, "/");
			strcpy(nom, p);
			p = strtok(NULL, "/");
			strcpy(password, p);
			if (insertar(nom, password) == 1)
			{
				strcpy(respuesta, "1/Registrado");
			}
			else
				strcpy(respuesta, "1/Error 1");
		}
		
		else if (codigo == 2) //Loguearse
		{
			char password[20];
			
			p = strtok(NULL, "/");
			strcpy(nombre, p);
			p = strtok(NULL, "/");
			strcpy(password, p);
			
			if (buscar(nombre, password) == 1)
			{
				pthread_mutex_lock(&mutex);
				PonNombre(&lista, nombre, sock_conn);
				pthread_mutex_unlock(&mutex);
				printf("%d\n", sock_conn);
				int posi = DamePosicion(&lista, nombre);
				printf("%d\n", lista.conectados[posi].socket);
				printf("%s\n", lista.conectados[DamePosicion(&lista, nombre)].nombre);
								
				strcpy(respuesta, "2/SI");
				printf ("Añadido a la lista\n");
					
				char conect[500];
				conect[0] = '\0';
					
				char conectados[500];
					
				DameConectados(&lista, conect);
				sprintf(conectados, "%s", conect);
					
				char notificacion[200];
				sprintf (notificacion, "7/%s", conectados);
					
				int j;
				for (j=0; j< lista.num; j++){
					write (lista.conectados[j].socket, notificacion, strlen(notificacion));
				}
			}
			else
				strcpy(respuesta, "2/Error 2");
		}
		
		else if (codigo == 3) //Nombre de jugadores de un equipo
		{
			char nombres[500];
			nombres[0] = '\0';
			char equipo[100];
			
			p = strtok(NULL, "/");
			strcpy(equipo, p);
			
			MiembrosEquipo(equipo, nombres);
			
			sprintf(respuesta, "3/El equipo %s son: %s", equipo, nombres);
		}
		
		if (codigo == 4) //Historial
		{
			char historial[1000];
			historial[0] = '\0';
			
			if (Historial(nombre, historial) == 0){
				sprintf(respuesta, "4/No has jugado aun");
			}
			else
				sprintf(respuesta, "4/%s", historial);;
		}
		
		else if (codigo == 5) //fecha y duracion de ganadas
		{
			char equipos[1000];
			equipos[0] = '\0';
			
			if (Ranking(equipos) == 0){
				sprintf(respuesta, "5/No se ha jugado aun");
			}
			else
				sprintf(respuesta, "5/%s", equipos);
		}
		
		else if (codigo == 6) //Invitar
		{
			int partida;
			
			//Si la persona que hizo la invitación no está en una partida, crea una
			if (lista.conectados[DamePosicion(&lista, nombre)].partida == -1)
			{
				pthread_mutex_lock(&mutex);
				partida = CreaPartida(tablas, nombre, sock_conn);
				pthread_mutex_unlock(&mutex);
			}
			//Si ya esta, se busca la posición de la partida en la tabla, es decir su id de partida
			else
				partida = lista.conectados[DamePosicion(&lista, nombre)].partida;
				
			if (tablas[partida].estado == 1){ //La partida ya tiene el máximo de jugadores
				char completo [100];
				sprintf(completo, "6/Ya estáis completos, no se puede invitar a más gente");
				
				write (sock_conn, completo, strlen(completo));
			}	
			else
			{	
				char invitado [100];
				p = strtok(NULL, "/");
				strcpy(invitado, p);
				
				int pos = DamePosicion(&lista, invitado);
				int s = lista.conectados[pos].socket;
				
				char invitacion [500];
				sprintf(invitacion, "8/%s-%d", nombre, partida);				
				
				write(s, invitacion, strlen(invitacion));
			}
		}
		
		else if (codigo == 7) // Aceptar invitacion
		{
			p = strtok(NULL, "/");
			int id = atoi(p);
			printf("%d\n", id);
			
			int est = SalaDeEspera(tablas, nombre, sock_conn, id);
			
			char jugadores[500];
			jugadores[0] = '\0';
			char notificacion[200];
			
			DameJugadores(tablas, jugadores, id);
			printf("%s\n", jugadores);
			
			sprintf (notificacion, "10/%s", jugadores);
			printf("%s\n", notificacion);
			
			int j;
			for (j=0; j< tablas[id].numJugadores; j++){
				write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
			}
			
			if (est == 1){
				char completo [100];
				sprintf(completo, "6/Ya estais completos");
				for (int y =0 ; y< tablas[id].numJugadores; y++){
					write (tablas[id].jugadores[y].socket, completo, strlen(completo));
				}
			}
		}
		
		else if (codigo == 8) //Rechazar invitación
		{
			char rechazado [100];
			p = strtok(NULL, "/");
			strcpy(rechazado, p);
			
			int pos = DamePosicion(&lista, rechazado);
			int s = lista.conectados[pos].socket;
			
			char rechazo [500];
			sprintf(rechazo, "9/%s no quiere ser tu amigo", nombre);
			printf("%s\n", rechazo);
			
			write(s, rechazo, strlen(rechazo));
		}
		
		else if (codigo == 9) //Enviar mensaje en el chat
		{
			char chat [500];
			p = strtok(NULL, "/");
			strcpy(chat, p);
			
			int pos = DamePosicion(&lista, nombre);
			int id = lista.conectados[pos].partida;
			
			char enviado [500];
			sprintf(enviado, "11/%s: %s", nombre, chat);
			printf("%s\n", enviado);
			
			int j;
			for (j=0; j< tablas[id].numJugadores; j++){
				write (tablas[id].jugadores[j].socket, enviado, strlen(enviado));
			}
		}
		
		else if (codigo == 10) //Salir sala de espera
		{
			int pos = DamePosicion(&lista, nombre);
			int id = lista.conectados[pos].partida;
			
			pthread_mutex_lock(&mutex);
			Salir(tablas, nombre, id);
			pthread_mutex_unlock(&mutex);
			
			//Se actualiza la lista de jugadores de una partida
			char jugadores[500];
			jugadores[0] = '\0';
			char notificacion[200];
			
			DameJugadores(tablas, jugadores, id);
			sprintf (notificacion, "12/%s", jugadores);
			printf("%s\n", notificacion);
			
			int j;
			for (j=0; j< tablas[id].numJugadores; j++){
				write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
			}
		}
		
		else if (codigo == 11) //Eligir nombre equipo y iniciar partida
		{
			
			char nombreEquipo [50];
			p = strtok(NULL, "/");
			strcpy(nombreEquipo, p);
			
			int pos = DamePosicion(&lista, nombre);
			int id = lista.conectados[pos].partida;
			
			pthread_mutex_lock(&mutex);
			strcpy(tablas[id].equipo, nombreEquipo);
			pthread_mutex_unlock(&mutex);
			
			srand (time(NULL));
			int t = 0;
			int numero;
			
			while (t < 4){ //Secuencia random de las 4 pruebas
				numero = rand() % 8;
				if (numero != tablas[id].pruebas[0] && numero != tablas[id].pruebas[1] && numero != tablas[id].pruebas[2] && numero != tablas[id].pruebas[3]){
					pthread_mutex_lock(&mutex);
					tablas[id].pruebas[t] = numero;
					pthread_mutex_unlock(&mutex);
					t ++;
				}
			}
			
			printf("%d,%d,%d,%d\n", tablas[id].pruebas[0],tablas[id].pruebas[1], tablas[id].pruebas[2], tablas[id].pruebas[3]);
			
			char notificacion[200];
			int i;
			int j = 0;
			
			//Se envía en codigo de la primera prueba y el código de jugador a todos los jugadores de la partida
			if (tablas[id].numJugadores == 4){
				i = 0;
				while (j < 4){
					sprintf (notificacion, "13/%d-%d", tablas[id].pruebas[0], i);
					write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
					i ++;
					j ++;
				}
			}
			
			else if (tablas[id].numJugadores == 3){
				i = 4;
				while (j < 3){
					sprintf (notificacion, "13/%d-%d", tablas[id].pruebas[0], i);
					write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
					i ++;
					j ++;
				}
			}
			
			else if (tablas[id].numJugadores == 2){
				i = 7;
				while (j < 2){
					sprintf (notificacion, "13/%d-%d", tablas[id].pruebas[0], i);
					printf("%s\n", notificacion);
					write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
					i ++;
					j ++;
				}
			}	
			
			pthread_mutex_lock(&mutex);
			tablas[id].aciertos = 0;
			pthread_mutex_unlock(&mutex);			
			
			char timer[200];
			sprintf (timer, "14/"); //Código par activar timer
			
			int z;
			for (z=0; z < tablas[id].numJugadores; z++){
				write (tablas[id].jugadores[z].socket, timer, strlen(timer));
			}
		}
		
		else if (codigo == 12){ //Pasar de prueba
			
			int pos = DamePosicion(&lista, nombre);
			int id = lista.conectados[pos].partida;
			
			pthread_mutex_lock(&mutex);
			tablas[id].aciertos ++; 
			pthread_mutex_unlock(&mutex);
			
			if (tablas[id].aciertos == tablas[id].numJugadores){
				
				if (tablas[id].pruebas[3] == -1){ //Ya se pasaron las 4 pruebas y se guardan los datos de la partida en la base de datos
					
					char fin[20];
					sprintf (fin, "15/");
					
					int z;
					for (z=0; z< tablas[id].numJugadores; z++){
						write(tablas[id].jugadores[z].socket, fin, strlen(fin));
					}
					
					char tiempo[20];
					char fecha[20];
					char duracion[20];
				
					p = strtok(NULL, "/");
					strcpy(tiempo, p);
					p = strtok(NULL, "/");
					strcpy(fecha, p);

					char *u = strtok(tiempo, ":");
					int min = atoi(u);
					u = strtok(NULL, ":");
					int seg = atoi(u);
					min = 19 - min;
					seg = 60 - seg;
					if (seg < 10)
						sprintf(duracion, "%d:0%d", min, seg);
					else
						sprintf(duracion, "%d:%d", min, seg);
					
					//Se guarda los datos de la partida en la base de datos y se borra la partida de la tabla
					pthread_mutex_lock(&mutex);
					GuardarTodo(tablas, duracion, fecha, id);
					pthread_mutex_unlock(&mutex);
					
					pthread_mutex_lock(&mutex);
					BorrarPartida(tablas, id);
					pthread_mutex_unlock(&mutex);
				}
				
				else
				{
					int prueba;
					int t = 0;
					int encontrado = 0;
					
					while (encontrado == 0){
						t ++;
						if (tablas[id].pruebas[t] != -1){
							prueba = tablas[id].pruebas[t];
							encontrado = 1;
						}
					}
					
					char notificacion[200];
					int i;
					int j = 0;
					
					printf("%d\n", tablas[id].numJugadores);
					
					//Además del código de las pruebas se manda un codigo para diferenciar a cada jugador 
					//0, 1, 2, 3 para 4 jugadores
					//4, 5, 6 para 3 jugadores
					//7, 8 para 2 jugadores
					
					if (tablas[id].numJugadores == 4){
						i = 0;
						while (j < 4){
							sprintf (notificacion, "13/%d-%d", prueba, i);
							write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
							i ++;
							j ++;
						}
					}
					
					
					else if (tablas[id].numJugadores == 3){
						i = 4;
						while (j < 3){
							sprintf (notificacion, "13/%d-%d", prueba, i);
							write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
							i ++;
							j ++;
						}
					}
					
					
					else if (tablas[id].numJugadores == 2){
						i = 7;
						while (j < 2){
							sprintf (notificacion, "13/%d-%d", prueba, i);
							
							printf("%s\n", notificacion);
							write (tablas[id].jugadores[j].socket, notificacion, strlen(notificacion));
							i ++;
							j ++;
						}
					}
					
					pthread_mutex_lock(&mutex);
					tablas[id].aciertos = 0;
					pthread_mutex_unlock(&mutex);
					
					
					pthread_mutex_lock(&mutex);
					tablas[id].pruebas[t] = -1;
					pthread_mutex_unlock(&mutex);
				}				
			}
		}
		
		else if (codigo == 13) // Desregistrarse
		{
			char password[20];
			char nom[20];
			
			p = strtok(NULL, "/");
			strcpy(nom, p);
			p = strtok(NULL, "/");
			strcpy(password, p);
			
			if (borrar(nom, password) == 1) 
			{
				strcpy(respuesta, "16/0/Se te ha borrado del registro!\n(Ten en cuenta que tus partidas siguen apareciendo en el historial de aquellos con los que jugaste alguna partida)");
			}
			else
				strcpy(respuesta, "16/1/No se ha podido desregistrar al usuario.");
		}
		
		else if (codigo == 14) //Codigo para tiempo finalizado.
		{
			int pos = DamePosicion(&lista, nombre);
			int id = lista.conectados[pos].partida;
			char fecha[20];
			
			pthread_mutex_lock(&mutex);
			tablas[id].aciertos++;
			pthread_mutex_unlock(&mutex);
			
			if(tablas[id].aciertos == tablas[id].numJugadores) {
				p = strtok(NULL, "/");
				strcpy(fecha, p);
				
				//Se guarda los datos de la partida en la base de datos
				pthread_mutex_lock(&mutex);
				GuardarTodo(tablas, "20:00", fecha, id);
				pthread_mutex_unlock(&mutex);
				
				char acabar[20];
				strcpy(acabar, "17/");
				
				for(int i=0; i < tablas[id].numJugadores; i++){
					write (tablas[id].jugadores[i].socket, acabar, strlen(acabar));
				}
				
				//Borramos la partida de la tabla 
				pthread_mutex_lock(&mutex);
				BorrarPartida(tablas, id);
				pthread_mutex_unlock(&mutex);
			}
		}
		
		else if (codigo == 15) //Historial de una fecha concreta
		{
			char fecha[20];
			p = strtok(NULL, "/");
			strcpy(fecha, p);
			
			char historial[3000];
			historial[0] = '\0';
			FechaRanking(fecha, historial);
			
			sprintf(respuesta, "19/%s", historial);
		}
		
		if (codigo != 0 && codigo !=6 && codigo !=7 && codigo !=8 && codigo !=9 && codigo !=10  && codigo !=11  && codigo !=12 && codigo != 14)
		{
			printf("Respuesta: %s\n", respuesta);
			// Enviamos respuesta
			write(sock_conn, respuesta, strlen(respuesta));
		}
	}
	close(sock_conn);
}


int main(int argc, char **argv)
{
	lista.num = 0;
	
	for (int u = 0; u < 100; u++)
	{
		tablas[u].numJugadores = 0;
		tablas[u].estado = 0;
	}
	for (int v = 0; v < 100; v++)
	{
		lista.conectados[v].partida = -1;
	}
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Inicializar la conexion
	conn = mysql_real_connect (conn, "shiva2.upc.es","root", "mysql", "T7_BBDDJuego",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	int puerto = 50071;
	
	// INICIALITZACIONS
	// Obrim el socket
 	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// establecemos el puerto de escucha
	serv_adr.sin_port = htons(puerto);
	
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");	
	
	pthread_t *thread;
//	i = 0;
	
	// Bucle infinito
	for (;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		
		
		pthread_mutex_lock(&mutex);
		PonSocket(&lista, sock_conn);		
		pthread_create(&thread, NULL, AtenderCliente, &lista.conectados[lista.num-1].socket);		
		pthread_mutex_unlock(&mutex);
		//i = i + 1;
		// Cerrar la conexion con el servidor MYSQL
	}
	mysql_close (conn);
}



