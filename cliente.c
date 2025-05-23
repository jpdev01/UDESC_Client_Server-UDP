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
    struct sockaddr_in target;

    // cria o socket UDP
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    char palavra[10];
    socklen_t ad1 = sizeof(target);
    int tam, i = 0;

    bzero((char *)&target, ad1);
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr("127.0.0.1");
    target.sin_port = htons(9000);

    // Faz um connect apenas para descobrir IP e porta usados
    connect(sock, (struct sockaddr *)&target, sizeof(target));

    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);
    getsockname(sock, (struct sockaddr *)&local_addr, &addr_len);

    printf("Client IP: %s\n", inet_ntoa(local_addr.sin_addr));
    printf("Client Port: %d\n", ntohs(local_addr.sin_port));


    printf("\nDigite 1 (uma) palavra em minúsculo (sem espaços):");

    do {
        if (fgets(palavra, sizeof(palavra), stdin) != NULL) {
            // Remove newline do fgets
            palavra[strcspn(palavra, "\n")] = '\0';
        }

        // Envia para o servidor
        sendto(sock, palavra, sizeof(palavra), 0, (struct sockaddr *)&target, ad1);

        if (strcmp(palavra, "exit") != 0) {
            // Recebe resposta do servidor
            recvfrom(sock, palavra, sizeof(palavra), 0, (struct sockaddr *)&target, &ad1);
            printf("Servidor converteu para: %s\n", palavra);

            printf("\nDigite 'exit' para sair: ");
            scanf("%s", palavra);
            getchar(); // limpar o \n do buffer
        }

    } while (strcmp(palavra, "exit") != 0);

    printf("closing socket \n");
    close(sock);
    return 0;
}
