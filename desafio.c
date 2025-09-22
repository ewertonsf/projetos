#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    int num_segmentos = 100;
    float radio = 0.5;
     for (int i = 0; i < num_segmentos; i++) {
        float t = 2.0f * 3.14 * i / num_segmentos;
        float x = radio * cosf(t);
        float y = radio * sinf(t);
        glVertex2f(x, y);
     }
     glEnd();

     glFlush();
}

void mouse (int botao, int estado, int x, int y) {
    if (estado == GLUT_DOWN) {
        if (botao == GLUT_LEFT_BUTTON) {
            time_t agora;
            time(&agora);
            struct tm *infotempo = localtime(&agora);

            printf("Clique (%d, %d) - Data/Hora: %s\n", x, y, asctime(infotempo));
            fflush(stdout);
        }
    }
}

int main (int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(420, 420);
    glutCreateWindow("desafio passado por lucas feito com exelencia");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    
    return 0;
}