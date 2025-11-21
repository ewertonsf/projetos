#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <stdlib.h>

int main() {
FILE *fp = fopen("dados.txt", "r");
char linha[100];
while (fgets(linha, sizeof(linha), fp) != NULL) {
    printf("%s", linha);
}
fclose(fp);

return 0;
}