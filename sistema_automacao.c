#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <stdlib.h>

float temperatura = 0.0f;
float umidade = 0.0f;

void salvarArquivo() {
    FILE *arquivo;
    arquivo = fopen("dados_automacao.csv", "a");
    if (arquivo == NULL) {
        printf ("Erro ao criar arquivo!");
        return;
    }

    time_t agora = time(NULL);
    struct tm *tempoInfo = localtime(&agora);

    fprintf(arquivo,
        "Sensor: Temperatura | Valor: %.2f | Sensor: Umidade | Valor: %.2f | Data/Hora: %02d-%02d-%04d %02d:%02d:%02d\n",
        temperatura,
        umidade,
        tempoInfo->tm_mday,
        tempoInfo->tm_mon + 1,
        tempoInfo->tm_year + 1900,
        tempoInfo->tm_hour,
        tempoInfo->tm_min,
        tempoInfo->tm_sec
    );

    fclose(arquivo);
    printf("Dados salvos no arquivo: %.2fC, %.2f%%\n", temperatura, umidade);
}

void painel(float x, float y, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    }
}

void desenharBarra(float x, float valor, float r, float g, float b, const char *label) {
    float altura = valor / 100.0f; 
    if (altura > 1.0f) altura = 1.0f;

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.2f, -0.8f);
        glVertex2f(x + 0.2f, -0.8f);
        glVertex2f(x + 0.2f, -0.8f + altura * 1.5f);
        glVertex2f(x - 0.2f, -0.8f + altura * 1.5f);
    glEnd();

    char texto[32];
    sprintf(texto, "%.1f", valor);
    painel(x - 0.05f, -0.8f + altura * 1.6f, texto);

    painel(x - 0.15f, -0.9f, label);
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT);

    char buffer[50];
    sprintf(buffer, "Temperatura: %.2f°C", temperatura);
    painel(-0.9f, 0.8f, buffer);

    sprintf(buffer, "Umidade: %.2f%%", umidade);
    painel(-0.9f, 0.7f, buffer);

    painel(-0.9f, 0.5f, "Pressione E para inserir dados via teclado");
    painel(-0.9f, 0.4f, "Clique com botao direito do mouse para inserir dados");
    painel(-0.9f, 0.3f, "Pressione ESC para sair");

    desenharBarra(-0.4f, temperatura, 1.0f, 0.3f, 0.3f, "Temperatura");
    desenharBarra(0.4f, umidade, 0.3f, 0.6f, 1.0f, "Umidade");

    glFlush();
}

void teclado(unsigned char key, int x, int y) {
    if (key == 27) {
        printf("Saindo da tela!\n");
        exit(0);
    } else if (key == 'E' || key == 'e') {
        printf("Digite a temperatura: ");
        scanf("%f", &temperatura);
        printf("Digite a umidade: ");
        scanf("%f", &umidade);
        salvarArquivo();
        glutPostRedisplay();
    }
}

void mouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN) {
        printf("Clique com o botao direito detectado. Digite os valores:\n");
        printf("Digite a temperatura: ");
        scanf("%f", &temperatura);
        printf("Digite a umidade: ");
        scanf("%f", &umidade);
        salvarArquivo();
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitWindowSize(1000, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sistema de Monitoramento de Automacao");

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
