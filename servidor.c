
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

//ssh(172.25.45.68)
//scp cliente.c 172.25.45.68:simboloMasoMenos/Redes
//
int main(){
    int socketServ,socketClient;
    struct sockaddr_in direccionSocket;
    socklen_t tDireccion;
    int puerto=8000,n,i;
    char mensaje[]="Conectado correctamente al servidor\0";
    char mensajeCliente[1000];
    socketServ=socket(PF_INET,SOCK_STREAM,0);
    if (socketServ<0){
        perror("No se pudo crear socket");
        exit(-1);
    }
    direccionSocket.sin_addr.s_addr=htonl(INADDR_ANY);
    direccionSocket.sin_family=AF_INET;
    direccionSocket.sin_port=htons(puerto);
    tDireccion=sizeof(direccionSocket);
    if (bind (socketServ,(struct sockaddr *)&direccionSocket,tDireccion)<0){
        perror("No se pudo asignar direccion");
        exit(-1);
    }
    if (listen(socketServ,2)==-1){
        perror("No escucha");
        exit(-1);
    }
    while(1){
        if((socketClient=accept(socketServ,(struct sockaddr *)&direccionSocket,&tDireccion))<0){
            perror("No se pudo atender peticion");
            exit(-1);
        }
        printf("\nConectado a cliente con direccion %s y puerto %d\n",inet_ntoa(direccionSocket.sin_addr),ntohs(direccionSocket.sin_port));
        //if (send (socketClient, mensaje, sizeof(mensaje), 0)==-1){
        //    perror("No se pudo enviar el mensaje");
        //   }
        if((n=recv(socketClient,mensajeCliente,sizeof(mensajeCliente),0))<0){
            perror("puto error");

	}
	for(i=0;i<strlen(mensajeCliente);i++){
		mensajeCliente[i]=toupper(mensajeCliente[i]);
	
	}
	mensajeCliente[strlen(mensajeCliente)]='\0';
        if (send (socketClient, mensajeCliente, sizeof(mensajeCliente), 0)==-1){
           perror("No se pudo enviar el mensaje");
         }
	printf("\nbytes recibidos%d, %s\n",n,mensajeCliente);
        close(socketClient);
    }
    close(socketServ);
}
