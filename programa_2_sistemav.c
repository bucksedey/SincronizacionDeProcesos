//Flores Anzurez Marco Antonio
//Actividad 4 4CV1 Programa 2 Sistema V
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define SHMKEY 75
#define TRUE 1

int region_critica();
int region_no_critica(int pid);
int esperando_turno(int pid);

// ESTE PROGRAMA SE CORRE SEGUNDO para sistema V. programa_2_sistemav.c

int main()
{
    // Declaracion de variables
    int shmid, pid;
    char *addr, *turno;
    pid = getpid(); // Obtenemos el Pid del proceso
    shmid = shmget(SHMKEY, 10, 0777 | IPC_CREAT);/* Crear la region de memoria y obtener la direcciòn*/
    addr = shmat (shmid,0,0);/*ENLAZAR REGIÒN AL ESPACIO DE DIRECCIONAMIENTO DEL PROCESO*/
    turno = (char *)addr; /*Reservar addr*/
    
    /*CODIG0 DE SINCRONIZACION*/
    printf("\n [I] Variables Declaradas");
    sleep (5); /*Para dar tiempo a que se ejecute el primer proceso*/
    while(TRUE){
        while((*turno) != '1')esperando_turno(pid); // Espera a su turno
        region_critica(pid); // manda a llamar a region ciritca
        sleep(1); 
        (*turno) = '0'; // Cambia el turno
        region_no_critica(pid); // manda a llamar a region no critica
    }
    
    /*Separar la regiòn del espacio de direccionamiento del proceso */
    shmdt(addr);
    return 0;
} /*fin de la funciòn main*/

int esperando_turno(int pid){
    printf("\n [I] Proceso %d y esperando turno :p",pid);
    sleep(2);
    return 0;
}

int region_critica(){
    printf("\n\n [O] Cambiando Variables");
    for(int i = 0; i < 5; i++){
        printf("\n [O] Turno %d",i+1);
        sleep(1);
    }
    return 0;
}

int region_no_critica(int pid){
    printf("\n [O] Proceso %d y turno tomado :))))))))))))))))))))))))\n",pid);
    return 0;
}
