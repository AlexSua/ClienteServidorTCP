
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

int main(){
    int socketClient,n;
    struct sockaddr_in direccionSocket;
    socklen_t tDireccion;
    char mensaje[1000];
    int puerto=8000;
    while(1){	
    socketClient=socket(PF_INET,SOCK_STREAM,0);
    if (socketClient<0){
        perror("No se pudo crear socket");
        exit(-1);
    }
    direccionSocket.sin_addr.s_addr=inet_addr("127.0.0.1");
    direccionSocket.sin_family=AF_INET;
    direccionSocket.sin_port=htons(puerto);
    tDireccion=sizeof(direccionSocket);
    if (connect (socketClient,(struct sockaddr *)&direccionSocket, tDireccion)==-1){
        perror("No conecta");
        exit(-1);
    }
   // if(recv (socketClient,mensaje,1000,0) <0){
   //     perror("No se pudo recuperar");
  //      exit(-1);
  //  }
   // printf("\n%s\n",mensaje);
    	
    printf("Introduzca el mensaje a pasar a mayusculas: ");
    scanf(" %[^\n]s",mensaje);
    if ((n=send (socketClient, mensaje, sizeof(mensaje), 0))<0){
        perror("No se pudo enviar el mensaje");
    }
	printf("\nMensaje enviado....nBytes=%d\n",n);
    if((n=recv(socketClient,mensaje,sizeof(mensaje),0))<0){
         perror("puto error");
    }
    printf("\nEl mensaje en mayusculas es : %s\n",mensaje);	
    close(socketClient);
    }
}
