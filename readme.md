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
2. Removida a chamada connect(), pois UDP é sem conexão. -> UDP não exige nem permite a criação de uma "conexão" com o cliente —
cada mensagem pode vir de um cliente diferente, e o servidor não mantém uma ligação persistente com nenhum deles.
3. Substituídas as chamadas write() e read() por sendto() e recvfrom().
4. Lógica original mantida sempre que possível para facilitar leitura e manutenção.

Iimprimir IP e porta do cliente atribuídos dinamicamente:
1. Removido o uso de bind() manual com INADDR_ANY e porta 0. 
2. Adicionado o uso de connect() com o endereço do servidor UDP,
3. permitindo que o sistema operacional defina o IP e porta de origem.
- Utilizado getsockname() após o connect() para capturar o IP e porta efetivamente utilizados na comunicação.
- Impressão do IP e porta do cliente logo após a criação do socket.
