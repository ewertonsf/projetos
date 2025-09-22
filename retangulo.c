#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.6, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glEnd();

    glFlush();
}

void teclado(unsigned char key, int x, int y){
    if (key == 'q' || key == 'Q') {
        exit(0);
    }
}

void mouse(int button, int estado, int x, int y){
    if (estado == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            printf("botao esquerdo do mouse\n");
        }

        else if (button == GLUT_RIGHT_BUTTON) {
            printf("botao direito do mouse.\n");
        }
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("retangulo vermelho");
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}