#include <stdio.h>
#include <stdlib.h>

int main() {
    char frase[50];
    FILE *f = fopen("/dev/mychardev", "wt");
    if (f == NULL) exit(-1);
    fprintf(f, "hello");
    fclose(f); 
    f = fopen("/dev/mychardev", "rt");
    if (f == NULL) exit(-1);
    fscanf(" %s", frase);
    fclose(f); 
    printf("%s", frase);
    f = fopen("/dev/mychardev", "wt");
    if (f == NULL) exit(-1);
    fprintf(f, "world");
    fclose(f); 
    f = fopen("/dev/mychardev", "rt");
    if (f == NULL) exit(-1);
    fscanf(" %s", frase);
    fclose(f); 
    printf("%s", frase);
    f = fopen("/dev/mychardev", "rt");
    if (f == NULL) exit(-1);
    fscanf(" %s", frase);
    fclose(f); 
    printf("%s", frase);
    f = fopen("/dev/mychardev", "wt");
    if (f == NULL) exit(-1);
    fprintf(f, "testing");
    fclose(f); 
    f = fopen("/dev/mychardev", "rt");
    if (f == NULL) exit(-1);
    fscanf(" %s", frase);
    fclose(f); 
    printf("%s", frase);
    return 0;
}