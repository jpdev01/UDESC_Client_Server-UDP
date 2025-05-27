#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    struct sockaddr_in target;

    // cria o socket UDP
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in local;
    bzero((char *)&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(0); // Porta 0 deixa o SO escolher uma

    bind(sock, (struct sockaddr *)&local, sizeof(local)); // necessário para aparecer no netstat

    char palavra[256]; // Buffer maior para evitar truncamento
    socklen_t ad1 = sizeof(target);

    bzero((char *)&target, ad1);
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr("127.0.0.1");
    target.sin_port = htons(9000);

    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);
    getsockname(sock, (struct sockaddr *)&local_addr, &addr_len);

    do {
        printf("\nDigite 1 (uma) palavra em minúsculo (sem espaços): ");

        if (fgets(palavra, sizeof(palavra), stdin) != NULL) {
            // Remove newline do fgets
            palavra[strcspn(palavra, "\n")] = '\0';
        }

        if (strcmp(palavra, "exit") != 0) {
            // Envia apenas o tamanho necessário da palavra
            sendto(sock, palavra, strlen(palavra) + 1, 0, (struct sockaddr *)&target, ad1);

            printf("Client Port: %d\n", ntohs(local_addr.sin_port));

            // Recebe resposta do servidor
            int recv_len = recvfrom(sock, palavra, sizeof(palavra) - 1, 0, (struct sockaddr *)&target, &ad1);
            if (recv_len > 0) {
                palavra[recv_len] = '\0'; // Garante que a string recebida seja terminada corretamente
                printf("Servidor converteu para: %s\n", palavra);
            }

            printf("\nDigite 'exit' para sair: ");
        }
    } while (strcmp(palavra, "exit") != 0);

    printf("closing socket\n");
    close(sock);
    return 0;
}