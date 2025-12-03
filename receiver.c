#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>  // For performance timing

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started... waiting for connection...\n");

    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected!\n");

    // Measure CSV save time
    clock_t start_save = clock();

    FILE *fp = fopen("received.csv", "w");
    if (!fp) {
        perror("File open failed");
        close(new_socket);
        return 1;
    }

    int bytes;
    while ((bytes = read(new_socket, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes, fp);
    }

    clock_t end_save = clock();
    double save_time = (double)(end_save - start_save) / CLOCKS_PER_SEC;

    printf("CSV Save Time: %.6f seconds\n", save_time);
    printf("Data received and saved to received.csv\n");

    fclose(fp);
    close(new_socket);
    close(server_fd);

    return 0;
}
