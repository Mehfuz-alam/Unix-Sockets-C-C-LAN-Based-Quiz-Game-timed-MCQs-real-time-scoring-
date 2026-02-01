#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define QUESTION_TIME 10   // seconds

typedef struct {
    int sock;
    int score;
    char name[20];
    int answered;
} Client;

void send_leaderboard(Client clients[]) {
    char board[512] = "\n--- Leaderboard ---\n";
    char line[64];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].sock > 0) {
            sprintf(line, "%s : %d\n", clients[i].name, clients[i].score);
            strcat(board, line);
        }
    }

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].sock > 0) {
            send(clients[i].sock, board, strlen(board), 0);
        }
    }
}

int main() {
    int server_fd, max_sd, activity;
    struct sockaddr_in address;
    Client clients[MAX_CLIENTS];
    fd_set readfds;
    struct timeval timeout;

    char question[] =
        "Q1: What is the capital of Nepal?\n"
        "A) Pokhara\nB) Kathmandu\nC) Lalitpur\nD) Biratnagar\n";
    char correct = 'B';

    time_t start_time = 0;
    int quiz_started = 0;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].sock = 0;
        clients[i].score = 0;
        clients[i].answered = 0;
        sprintf(clients[i].name, "Player%d", i + 1);
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Quiz Server running on port %d\n", PORT);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].sock > 0) {
                FD_SET(clients[i].sock, &readfds);
                if (clients[i].sock > max_sd)
                    max_sd = clients[i].sock;
            }
        }

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        activity = select(max_sd + 1, &readfds, NULL, NULL, &timeout);

        /* New client connection */
        if (FD_ISSET(server_fd, &readfds)) {
            int new_socket;
            socklen_t addrlen = sizeof(address);
            new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].sock == 0) {
                    clients[i].sock = new_socket;
                    clients[i].answered = 0;

                    send(new_socket, question, strlen(question), 0);

                    if (!quiz_started) {
                        start_time = time(NULL);
                        quiz_started = 1;
                        printf("Quiz started\n");
                    }
                    break;
                }
            }
        }

        /* Receive answers */
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = clients[i].sock;
            char ans;

            if (sd > 0 && FD_ISSET(sd, &readfds) && !clients[i].answered) {
                recv(sd, &ans, 1, 0);
                clients[i].answered = 1;

                if (ans == correct)
                    clients[i].score += 10;
            }
        }

        /* Timer check */
        if (quiz_started && difftime(time(NULL), start_time) >= QUESTION_TIME) {
            printf("Time up! Sending leaderboard...\n");
            send_leaderboard(clients);
            break;
        }
    }

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].sock > 0)
            close(clients[i].sock);
    }

    close(server_fd);
    return 0;
}
