#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
 
int main() {
        
        // definição das estruturas do cliente e do servidor
  	struct sockaddr_in me, from;
        
        // criação dos sockets.o sock é declarado identicamente ao cliente
  	int newSock, sock = socket(AF_INET, SOCK_STREAM, 0);
        
        // declaração das variáveis
	int tam, tam2 = 0, i = 0;
	int ad1 = sizeof(me);
  	char palavra[10];
 
        // inicializa a estrutura do servidor
  	bzero((char *)&me, ad1);
        
        // indica a família do protocolo
  	me.sin_family = AF_INET;
        
        // fica associado a todos os endereços IP do host local
  	me.sin_addr.s_addr = htonl(INADDR_ANY);

       // porta em que o servidor vai estar à escuta
  	me.sin_port = htons(9000);
 
        // se a porta estiver ocupada o servidor não pode correr e é terminado
  	if(bind(sock, (struct sockaddr *)&me, ad1) == -1)
	{
		close(sock);
		puts("Porta Ocupada!"); 
		exit(0);
	}
        
        // coloca o socket à escuta. Podem ser mantidos em espera 5 pedidos de ligação
	listen(sock, 1);

        // gera um novo socket específico para essa ligação
   	newSock = accept(sock, (struct sockaddr *)&from, (void *)&ad1);
        
        // fechar o socket antigo
	close(sock);
        
       //Ciclo infinito que trata dos pedidos do cliente
       printf("Conversão Realizada \n");
       for(;;){
		read(newSock, palavra, 10);
               // recebe os dados do cliente e guarda-os na variável palavra

		if(strcmp(palavra, "exit") != 0){
			tam = strlen(palavra);
                        for(i=0;i<tam;i++){
				if((palavra[i]>='a') && (palavra[i]<='z')){
					palavra[i] = toupper(palavra[i]);
                                        
				}
                               tam2 = strlen(palavra);
			}
			//palavra2[i] = '0';
                       	// envia os dados que estão na variável palavra para o cliente
                         fflush(stdin);
			 write(newSock, palavra, tam2);
                                                  
                      
		}
		else{
                        printf("closing socket \n");
			close(newSock);
                        break;
			exit(0);
		}
	} 
	return 0;

}
