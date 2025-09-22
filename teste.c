#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0); // vermelho
        glVertex2f(-0.5f, -0.5f);

        glColor3f(0.0, 1.0, 0.0); // verde
        glVertex2f( 0.5f, -0.5f);

        glColor3f(0.0, 0.0, 1.0); // azul
        glVertex2f( 0.0f,  0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// modo de display
    glutInitWindowSize(400, 400);               // tamanho da janela
    glutCreateWindow("Teste FreeGLUT");         // título da janela
    glutDisplayFunc(display);                   // função de desenho
    glutMainLoop();                             // loop principal
    return 0;
}
