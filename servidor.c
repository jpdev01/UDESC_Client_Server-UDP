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

    struct sockaddr_in me, from;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);  // UDP

    int tam, tam2 = 0, i = 0;
    socklen_t ad1 = sizeof(from);
    char palavra[10];

    bzero((char *)&me, sizeof(me));
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    me.sin_port = htons(9000);

    if (bind(sock, (struct sockaddr *)&me, sizeof(me)) == -1) {
        close(sock);
        puts("Porta Ocupada!");
        exit(0);
    }

    struct sockaddr_in local_addr;
        socklen_t addr_len = sizeof(local_addr);
        getsockname(sock, (struct sockaddr *)&local_addr, &addr_len);
        char server_ip[INET_ADDRSTRLEN];
        printf("Server IP: %s\n", inet_ntop(AF_INET, &(local_addr.sin_addr), server_ip, INET_ADDRSTRLEN));
        printf("Server Port: %d\n", ntohs(local_addr.sin_port));

        printf("Servidor UDP iniciado\n");


    for (;;) {
        bzero(palavra, sizeof(palavra));

        // Recebe dados do cliente
        recvfrom(sock, palavra, sizeof(palavra), 0, (struct sockaddr *)&from, &ad1);

        if (strcmp(palavra, "exit") != 0) {
            tam = strlen(palavra);
            for (i = 0; i < tam; i++) {
                if ((palavra[i] >= 'a') && (palavra[i] <= 'z')) {
                    palavra[i] = toupper(palavra[i]);
                }
            }
            tam2 = strlen(palavra);

            // Envia de volta para o cliente
            sendto(sock, palavra, tam2, 0, (struct sockaddr *)&from, ad1);
        } else {
            printf("closing socket \n");
            close(sock);
            break;
        }
    }

    return 0;
}
