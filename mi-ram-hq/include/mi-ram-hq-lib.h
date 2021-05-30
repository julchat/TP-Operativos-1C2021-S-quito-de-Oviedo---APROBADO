
#ifndef MI_RAM_HQ_LIB_H
#define MI_RAM_HQ_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <commons/config.h>
#include <shared_utils.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CLIENTS 128


//------------Estructuras------------

typedef struct 
{
	int TAMANIO_MEMORIA;
	char* ESQUEMA_MEMORIA;
	int TAMANIO_PAGINA;
	int TAMANIO_SWAP;
	char* PATH_SWAP;
	char* ALGORITMO_REEMPLAZO;
	int PUERTO;
	
}mi_ram_hq_config;


typedef struct
{
	void* base;
	uint32_t tamanio;
	uint32_t numero_segmento;
	pthread_mutex_t* mutex_segmento;

}t_segmento;

typedef struct
{
	t_segmento* segmento_pcb;
	t_segmento* segmento_tarea;
	t_list* segmentos_tripulantes;
	pthread_mutex_t* mutex_segmentos_tripulantes;

}t_tabla_de_segmento;

typedef struct
{
	bool libre;
	void* inicio_segmento;
	uint32_t tamanio_segmento;

}t_segmento_de_memoria;

//------------Variables Globales------------

mi_ram_hq_config* mi_ram_hq_configuracion;
t_log* logger_ram_hq;
int socket_escucha;
void* memoria_principal;
void* memoria_swap;

t_list* patotas;
pthread_mutex_t mutex_patotas;
pthread_mutex_t mutex_memoria;
pthread_mutex_t mutex_swap;

t_list* segmentos_memoria;

uint32_t numero_segmento_global;


//------------Firmas de funciones------------

mi_ram_hq_config* leer_config_mi_ram_hq(char*);
t_log* iniciar_logger_mi_ram_hq(char*);
void crear_estructuras_administrativas();

void* esperar_conexion(int);
int iniciar_servidor_mi_ram_hq(int);
void crear_hilo_para_manejar_suscripciones(t_list*,int);
void* manejar_suscripciones_mi_ram_hq(int*);


respuesta_ok_fail iniciar_patota_segmentacion(pid_con_tareas);
respuesta_ok_fail iniciar_tripulante_segmentacion(nuevo_tripulante);
respuesta_ok_fail actualizar_ubicacion_segmentacion(tripulante_y_posicion);
tarea obtener_proxima_tarea_segmentacion(uint32_t);
respuesta_ok_fail expulsar_tripulante_segmentacion(uint32_t);
estado obtener_estado_segmentacion(uint32_t);
posicion obtener_ubicacion_segmentacion(uint32_t);

t_tabla_de_segmento* buscar_patota(uint32_t);
t_segmento_de_memoria* buscar_segmento_tareas(t_list*);
t_segmento_de_memoria* buscar_segmento_pcb();
t_segmento_de_memoria* buscar_segmento_tcb();

void cargar_pcb_en_segmento(uint32_t,uint32_t,t_segmento*);
void cargar_tareas_en_segmento(t_list*,t_segmento*);
void cargar_tcb_en_segmento(uint32_t,estado,uint32_t,uint32_t,uint32_t,uint32_t,t_segmento*);

respuesta_ok_fail iniciar_patota_paginacion(pid_con_tareas);
respuesta_ok_fail iniciar_tripulante_paginacion(nuevo_tripulante);
respuesta_ok_fail actualizar_ubicacion_paginacion(tripulante_y_posicion);
tarea obtener_proxima_tarea_paginacion(uint32_t);
respuesta_ok_fail expulsar_tripulante_paginacion(uint32_t);
estado obtener_estado_paginacion(uint32_t);
posicion obtener_ubicacion_paginacion(uint32_t);

#endif /* MI_RAM_HQ_LIB_H */




