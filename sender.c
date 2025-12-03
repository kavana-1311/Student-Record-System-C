#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>  // For performance timing

#define MAX_STUDENTS 100
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

struct Student {
    int id;
    char name[50];
    int age;
    char grade[5];
};

int count = 0;
struct Student students[MAX_STUDENTS];

// List all students
void listStudents() {
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d | %s | %d | %s\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].grade);
    }
}

// Search student by ID
void searchStudent() {
    int id;
    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Found: %d | %s | %d | %s\n",
                   students[i].id,
                   students[i].name,
                   students[i].age,
                   students[i].grade);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Sort students by name and measure time
void sortStudents() {
    clock_t start_sort = clock();

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(students[j].name, students[j+1].name) > 0) {
                struct Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }

    clock_t end_sort = clock();
    double sort_time = (double)(end_sort - start_sort) / CLOCKS_PER_SEC;
    printf("Sorting Time: %.6f seconds\n", sort_time);
    printf("\nStudents sorted by name.\n");
}

// Send CSV data to server and measure time
void sendData() {
    clock_t start_send = clock();

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("Socket creation failed"); return; }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        close(sock);
        return;
    }

    FILE *file = fopen("students.csv", "r");
    if (!file) { printf("Error opening students.csv\n"); close(sock); return; }

    char buffer[1024];
    int n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(sock, buffer, n, 0);
    }

    fclose(file);
    close(sock);

    clock_t end_send = clock();
    double send_time = (double)(end_send - start_send) / CLOCKS_PER_SEC;
    printf("Data Transmission Time: %.6f seconds\n", send_time);
}

int main() {
    // Measure time to load CSV
    clock_t start_load = clock();

    FILE *file = fopen("students.csv", "r");
    if (!file) { printf("ERROR: Cannot open students.csv\n"); return 1; }

    char line[256];
    fgets(line, sizeof(line), file);  // skip header

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%49[^,],%d,%4s",
               &students[count].id,
               students[count].name,
               &students[count].age,
               students[count].grade);
        count++;
    }

    fclose(file);

    clock_t end_load = clock();
    double load_time = (double)(end_load - start_load) / CLOCKS_PER_SEC;
    printf("CSV Load & Parse Time: %.6f seconds\n", load_time);
    printf("Number of Records: %d\n", count);

    int choice;
    while (1) {
        printf("\n==== Student Menu ====\n");
        printf("1. List Students\n");
        printf("2. Search by ID\n");
        printf("3. Sort by Name\n");
        printf("4. Exit\n");
        printf("5. Send Data to Server\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: listStudents(); break;
            case 2: searchStudent(); break;
            case 3: sortStudents(); listStudents(); break;
            case 4: return 0;
            case 5: sendData(); break;
            default: printf("Invalid choice\n");
        }
    }
}
