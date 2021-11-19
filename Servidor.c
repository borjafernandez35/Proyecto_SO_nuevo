#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>

MYSQL *conn;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int i;
int sockets[100];

typedef struct{
	char nombre[20];
	int socket;
} Conectado;

typedef struct{
	Conectado conectados[100];
	int num;
} ListaConectados;

ListaConectados lista;

int Pon (ListaConectados *lista, char nombre[20], int scoket){
	if (lista->num == 100)
		return -1;
	else{
		strcpy (lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		return 0;
	}
}

int DamePosicion (ListaConectados *lista, char nombre[20]){
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

int Eliminar (ListaConectados *lista, char nombre[20])
{
	int pos = DamePosicion (lista, nombre);
	if (pos == -1)
		return -1;
	else{
		int i;
		for (i=pos; i < lista->num-1; i++){
			lista->conectados[i] = lista->conectados[i+1];
			//strcpy (list->conectados[i].nombre, lista->conectados[i+1].nombre;
			//lista->conectados[i].socket = lista->conectados[i+1].socket;
		}
		lista->num--;
		return 0;
	}
}

void DameConectados (ListaConectados *lista, char conectados[500])
{
	int i;
	for (i=0; i < lista->num; i++){
		sprintf (conectados, "%s %s,", conectados, lista->conectados[i].nombre);
	}
	conectados[strlen(conectados) - 1] = '\0';
}

int insertar(char nombre[20], char password[20]){
	
	char consulta [500];
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int id;
	
	int er = mysql_query (conn, "SELECT idJ FROM jugador ORDER BY idJ DESC liMIT 1");
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
	if (row == NULL)
		id = 1;
	else
		id = atoi(row[0]) + 1;
	
	sprintf(consulta, "INSERT INTO jugador VALUES ('%d','%s','%s')", id, nombre, password);
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


int buscar(char nombre[20], char password[20]){
	
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



int Nombre(int idp, char nombre[200]){
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[200];
	int i;
	
	
	sprintf(consulta, "SELECT jugador.nombre FROM (historial, jugador, partida) WHERE partida.idP = '%d' AND historial.idP = partida.idP AND historial.idJ = jugador.idJ", idp );
	
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
		i = 0;
	else{
		i = 0;
		while (row !=NULL) {
			
			sprintf(nombre,"%s %s,", nombre, row[0]);
			
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
			i ++;
		}
		nombre[strlen(nombre) - 1] = '\0';
	}
	return i;
}



int Ultimas(char result[500], char nom[100]){
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta [500];
	
	strcpy (consulta,"SELECT historial.idP, historial.puntuacion, partida.ganador FROM (historial, jugador, partida) WHERE jugador.nombre = '"); 
	strcat (consulta, nom);
	strcat (consulta,"' AND jugador.idJ = historial.idJ AND historial.idP = partida.idP ORDER BY historial.idP DESC LIMIT 3");
	
	// Hacemos la consulta 
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
			if (strcmp(row[2], nom) == 0){
				sprintf (result, "%s ha ganado la partida %s con %s puntos,", result, row[0], row[1]);
				// Las columnas 0,1,2 contienen (idP,puntuacion,ganador);
			}
			else{
				sprintf (result, "%s ha perdido la partida %s con %s puntos,", result, row[0], row[1]);
			}
			
			// Obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
		}
		result[strlen(result) - 1] = '\0';
		return 1;
	}
}

int Ganador(char nombre[20], char result[500])
{
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta [80];
	int i;
	
	
	sprintf(consulta, "SELECT partida.fecha, partida.duracion FROM (partida) WHERE partida.ganador = '%s'", nombre);
	

	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	resultado = mysql_store_result (conn);
	
	
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		i=0;
	
	else{
		
		while(row !=NULL){
		// Convertimos las columnas 0 y 1 las cuales contienen la palabra fecha y duracion
		
		sprintf(result, "%s la partida del %s que ha durado %s min,", result, row[0], row[1]);

		i++;
		
		// obtenemos la siguiente fila
		row = mysql_fetch_row (resultado);
		}
		
		result[strlen(result) - 1] = '\0';
	}
	
	return i;
}

int PruebasPartida(char prueba[100])
{
	
	int err;
	
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int i;
	

	//"SELECT Pruebas.Nombre, Juegos.Cantidad, Pruebas.Puntos FROM (Juegos, Pruebas) WHERE Juegos.idP = SELECT MAX(Historial.idP) FROM (Historial) AND Juegos.idPb = Pruebas.idPb"
	
	err=mysql_query (conn, "SELECT pruebas.nombre, juego.cantidad, pruebas.puntos FROM (juego, pruebas, historial) WHERE juego.idPb = pruebas.idPb AND juego.idP = historial.idP ORDER BY historial.idP DESC LIMIT 1");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	
	resultado = mysql_store_result (conn);
	
	// El resultado es una estructura matricial en memoria
	
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	
	row = mysql_fetch_row (resultado);
	
	// En una fila hay tantas columnas como datos tiene una
	// la busqueda que queremos. En nuestro caso hay tres columnas: cuantas pruebas(row[0]),
	// nombre de la prueba(row[1]) y cuantos puntos(row[2]).
	
	if (row == NULL)
		i=0;
	else{
		i=1;
		
		sprintf(prueba, "La prueba %s se ha jugado %s veces y da %s puntos", row[0], row[1], row[2]);
		
	return i;
	}
}

void *AtenderCliente(void *socket)
{
	int sock_conn;
	int *s;
	s = (int *)socket;
	sock_conn = *s;
	
	//int socket_conn = * (int *) socket;
	
	char nombre[20];
	char peticion[512];
	char respuesta[512];
	int ret;
	
	int terminar = 0;
	// Entramos en un bucle para atender todas las peticiones de este cliente
	//hasta que se desconecte
	while (terminar == 0)
	{
		
		// Ahora recibimos la petici?n
		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibido\n");
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret] = '\0';
		
		printf("Peticion: %s\n", peticion);
		
		// vamos a ver que quieren
		char *p = strtok(peticion, "/");
		int codigo = atoi(p);
		// Ya tenemos el c?digo de la petici?n
		
		if (codigo == 0) //petici?n de desconexi?n
		{	
			terminar = 1;
			pthread_mutex_lock(&mutex);
			Eliminar(&lista, nombre);
			pthread_mutex_unlock(&mutex);
			
			char conect[500];
			conect[0] = '\0';
			
			char conectados[500];
			
			pthread_mutex_lock(&mutex);
			DameConectados(&lista, conect);
			pthread_mutex_unlock(&mutex);
			
			sprintf(conectados, "%s", conect);
			
			char notificacion[200];
			sprintf (notificacion, "7/%s", conectados);
			
			int j;
			for (j=0; j< i; j++){
				write (sockets[j], notificacion, strlen(notificacion));
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
				int e = Pon(&lista, nombre, sock_conn);
				pthread_mutex_unlock(&mutex);
				
				if (e == -1){
					strcpy(respuesta, "2/Ya hay 100 conectados");
				}
				else{
					strcpy(respuesta, "2/SI");
					printf ("Añadido a la lista\n");
					
					char conect[500];
					conect[0] = '\0';
					
					char conectados[500];
					
					pthread_mutex_lock(&mutex);
					DameConectados(&lista, conect);
					pthread_mutex_unlock(&mutex);
					
					sprintf(conectados, "%s", conect);
					
					char notificacion[200];
					sprintf (notificacion, "7/%s", conectados);
					printf("%s", notificacion);
					
					int j;
					for (j=0; j< i; j++){
						write (sockets[j], notificacion, strlen(notificacion));
					}
				}
			}
			else
				strcpy(respuesta, "2/Error 2");
		}
		
		else if (codigo == 3) //Numero de jugadores
		{
			int idP;
			char nombres[200];
			nombres[0] = '\0';
			
			p = strtok(NULL, "/");
			idP = atoi(p);
			
			int i = Nombre(idP, nombres);
			
			if (i == 0)
			{
				strcpy(respuesta, "3/No hay jugadores");
			}
			else
				sprintf(respuesta, "3/Hay %d jugadores: %s", i, nombres);
		}
		
		if (codigo == 4) //3 ultimas partidas
		{
			
			char res[500];
			char nombre[20];
			res[0] = '\0';
			
			p = strtok(NULL, "/");
			strcpy(nombre, p);
			
			if (Ultimas(res, nombre) == 1)
			{
				sprintf(respuesta, "4/%s %s\n", nombre, res);
			}
			else
				strcpy(respuesta, "4/No ha jugado");
		}
		
		else if (codigo == 5) //fecha y duracion de ganadas
		{
			char resp[500];
			char nombre[20];
			int i;
			resp[0] = '\0';
			
			p = strtok(NULL, "/");
			strcpy(nombre, p);
			i = Ganador(nombre, resp);
			
			if (i != 0)
			{
				sprintf(respuesta, "5/Ha ganado %d partidas: %s\n", i, resp);
				
			}
			else
				strcpy(respuesta, "5/No ha ganado");
		}
		
		else if (codigo == 6) //fecha y duracion de ganadas
		{
			char resp[500];
			resp[0] = '\0';
			
			if (PruebasPartida(resp) != 0)
			{
				sprintf(respuesta, "6/%s", resp);
			}
			else
				strcpy(respuesta, "6/No hay partida");
		}
		
		if (codigo != 0)
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
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Inicializar la conexion
	conn = mysql_real_connect (conn, "shiva2.upc.es","root", "mysql", "T7tablas",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	
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
	serv_adr.sin_port = htons(50070);
	
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	//Creacion de 100 sockets para el thread.
	
	pthread_t thread;
	i = 0;

	// Bucle infinito
	for (;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		
		sockets[i] = sock_conn;
		
		pthread_create(&thread, NULL, AtenderCliente, &sockets[i]);
		i = i + 1;

		
		// Cerrar la conexion con el servidor MYSQL
	}
		mysql_close (conn);
}


	
