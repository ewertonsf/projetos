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
    }

    time_t agora = time(NULL);
    struct tm *tempoInfo = localtime(&agora);

    fprintf(arquivo, "Data/Hora: %02d/%02d/%04d,%02d:%02d:%02d,\nTemperatura: %.2f\nUmidade: %.2f\n",
    tempoInfo->tm_mday,
    tempoInfo->tm_mon + 1,
    tempoInfo->tm_year + 1900,
    tempoInfo->tm_hour,
    tempoInfo->tm_min,  
    tempoInfo->tm_sec,
    temperatura,
    umidade);

    fclose(arquivo);
    printf ("Dados salvos no arquivo: %.2fC, %.2f%%\n", temperatura, umidade);
}

void painel(float x, float y, const char *string) {
    glRasterPos2f(x, y);
    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    }
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT);

    char buffer[50];
    sprintf (buffer, "Temperatura: %.2fC", temperatura);
    painel(-0.9f, 0.2f, buffer);

    sprintf(buffer, "Umidade %.2f%%", umidade);
    painel(-0.9f, 0.0f, buffer);

    painel(-0.9f, -0.4f, "Pressione E para inserir dados via teclado");
    painel(-0.9f, -0.6f, "Clique com botao direito do mouse para inserir dados");
    painel(-0.9f, -0.8f, "Pressione ESC para sair");

    glFlush();
}

void teclado(unsigned char key, int x, int y) {
    if (key == 27){
        printf("saindo da tela!");
        exit(0);
    } else if (key == 'E' || key == 'e') {
        printf("Digite a temperatura: ");
        scanf("%f", &temperatura);
        printf("Digite a Umidade: ");
        scanf("%f", &umidade);
    }

    salvarArquivo(temperatura, umidade);
    glutPostRedisplay();
}

void mouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_RIGHT_BUTTON) {
        printf("clique com o botao direito detectado. Digite os valores: \n");
        printf("Digite a Temperatura: ");
        scanf("%f", &temperatura);
        printf("Digite a umidade: ");
        scanf("%f", &umidade);
    }

    salvarArquivo(temperatura, umidade);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitWindowSize(500, 650);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sistema de monitoramento de Automação");

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