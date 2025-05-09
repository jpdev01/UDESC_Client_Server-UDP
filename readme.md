Subir Servidor:
```bash
gcc -o server Servidor.c

./server
```

Subir cliente:
```bash
gcc -o client Cliente.c

./client
```

Alterado o protocolo de transporte de TCP para UDP nas implementações do servidor e do cliente.

Alterações no servidor:
1. Substituído SOCK_STREAM por SOCK_DGRAM para utilizar comunicação via datagramas.
2. Removidas chamadas específicas de TCP: listen(), accept(), read() e write().
3. Utilizadas as funções sendto() e recvfrom() para envio e recebimento de mensagens.
4. Uso direto do socket original (`sock`), já que UDP não requer um socket novo por conexão.

Alterações no cliente:
1. Substituído SOCK_STREAM por SOCK_DGRAM.
2. Removida a chamada connect(), pois UDP é sem conexão.
3. Substituídas as chamadas write() e read() por sendto() e recvfrom().
4. Lógica original mantida sempre que possível para facilitar leitura e manutenção.