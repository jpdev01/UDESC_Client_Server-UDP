// Bibliotecas necessárias

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>


int main() {

        // definição das estruturas do cliente e do servidor
 	struct sockaddr_in target;
      
        // criação dos sockets.o sock é declarado identicamente ao cliente
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	// declaração das variáveis

        char palavra[10];
	int ad1 = sizeof(target);
        int tam, i = 0;
 
	// inicializa a estrutura do cliente
        bzero((char *)&target, ad1);
        
        // indica a família do protocolo
	target.sin_family = AF_INET;

        // especifica o endereço (IP) do servidor
	target.sin_addr.s_addr = inet_addr("127.0.0.1");

        // porta que o programa vai usar
	target.sin_port = htons(9000);
 
        // efectua a ligação ao servidor. Se falhar (por exemplo o servidor estar em baixo) o programa termina
	if(connect(sock, (struct sockaddr *)&target, ad1) == -1)
	{
		close(sock);
		puts("Conexao falhada!");
		exit(0);
	}
             printf("\n Digite 1 (uma) palavra em minisculo (sem espacos):");
	     do {

		 if (fgets(palavra, sizeof(palavra), stdin) != NULL) {
                     printf("Servidor converteu para:"); // 
                     
                 }

                // envia para o servidor os dados contidos na variável palavra
		write(sock, palavra, sizeof(palavra));
                	if(strcmp(palavra, "exit") != 0){
                        
		          read(sock, palavra, sizeof(palavra));
		          puts(palavra);
                          fflush(stdin);

                          printf("\n Digite 'exit' para sair:");
                          scanf("%s", palavra);

                        }

              
	   }while(strcmp(palavra, "exit") != 0 );
                
         // Fecha o socket
         printf("closing socket \n");
	close(sock);
	return 0;
    
}
