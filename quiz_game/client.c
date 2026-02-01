#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[512];
    char answer;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); // same Codespace

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    recv(sock, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    printf("Your answer (A/B/C/D): ");
    scanf(" %c", &answer);

    send(sock, &answer, 1, 0);

    recv(sock, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    close(sock);
    return 0;
}
