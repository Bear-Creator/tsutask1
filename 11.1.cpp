#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

#define MAX_SIZE 100

int main() {
    // Использование cin и cout
    int a;
    cout << "Insert a: ";
    cin >> a;
    cout << "You iserted a = " << a << endl;

    // Использование scanf и printf
    float b;
    printf("Insert b: ");
    scanf("%f", &b);
    printf("You iserted b = %.2f\n", b);

    // Использование gets: функция gets была объявлена устаревшей и удалена из стандарта C++11!

    // Использование fopen и fclose
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Err while opening file");
        exit(1);
    }
    fputs("Insert in file exampe", file);
    fclose(file);

    // Использование fscanf и fprintf
    int x, y, z;
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Err while opening file");
        exit(1);
    }
    fscanf(file, "%d%d%d", &x, &y, &z);
    printf("Reading file example: x = %d, y = %d, z = %d\n", x, y, z);
    fclose(file);

    // Использование read и write
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("Err while opening file");
        exit(1);
    }
    char buffer[MAX_SIZE];
    ssize_t numBytes = read(fd, buffer, MAX_SIZE);
    if (numBytes == -1) {
        perror("Err while reading file");
        exit(1);
    }
    write(STDOUT_FILENO, buffer, numBytes);
    close(fd);

    // Использование feof
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Err while opening file");
        exit(1);
    }
    while (!feof(file)) {
        char c = fgetc(file);
        if (c != EOF) {
            putchar(c);
        }
    }
    fclose(file);

    // Использование макроопределения EOF
    int ch;
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Err while opening file");
        exit(1);
    }
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);

    return 0;
}
