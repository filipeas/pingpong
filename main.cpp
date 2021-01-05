/**
 * Trabalho final
 * Mesa de ping pong
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <ctime>

#define pi 3.142857

// Posição inicial e tamanho do quadrado respectivamente
// GLfloat glx1 = 100.0f;
// GLfloat gly1 = 150.0f;
GLfloat posx = 0.0f;
GLfloat posy = 0.0f;
BOOLEAN inicio = true;
// GLsizei rsize = 20;

// Tamanho do incremento nas direções x e y
// (número de pixels para se mover a cada
// intervalo de tempo)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

// c e d rastreia o número de vezes que 'b' e 'n' são pressionados respectivamente
// esquerda e direita indicam o índice mais à esquerda e mais à direita do retângulo móvel
int esquerda = -5, direita = 5, movimento = 0, ponto = 0, velocidade = 100;

/* Funcao com alguns comandos para a inicializacao do OpenGL; */
void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
	glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer
}

void reshape (int w, int h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h)
	{
		windowHeight = 250.0f * h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f * w / h;
		windowHeight = 250.0f;
	}

	// gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
	gluPerspective(60, (float)w / (float)h, 1.0, 20.0);
	gluLookAt(0.0, 0.0, 10.0, 	// posição da câmera (olho)
			  0.0, 0.0, 0.0, 	// centro da cena
			  0.0, 1.0, 0.0); // direção de cima
	glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'b': // esquerda
		// if(esquerda < windowWidth - rsize){
		movimento -= 1;
		esquerda += 1;
		direita -= 1;
		// }
		glutPostRedisplay();
		break;
	case 'n': // direita
		// if(direita > windowWidth - rsize){
		movimento += 1;
		esquerda -= 1;
		direita += 1;
		// }
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void display(void)
{
	if(inicio)
	{
		posx = 0;
		posy = 0;
		inicio = false;
	}
	else
	{
		posx = posx;
		posy = posy;
	}
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
	glLoadIdentity();

	// Especifica que a cor corrente é vermelha
	//         R     G     B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Desenha um quadrado preenchido com a cor corrente (3d)
	glTranslatef( 0, 5, -8 );	// ...move back and down a bit
	// Drawing the cube
	glBegin(GL_QUADS);		// using quadrilaterals as primitive
	// Front
	glColor3f( 0, 1, 0 );		// set colour to pure green
	glVertex3f( posx,  posy,  1 );
	glVertex3f( posx,  posy + 2,  1 );
	glVertex3f( posx + 2,  posy + 2,  1 );
	glVertex3f( posx + 2,  posy,  1 );

	// Back
	glColor3f( 0, 0.8, 0 );		// a slightly darker green for the back
	glVertex3f( posx,  posy, -1 );
	glVertex3f( posx + 2,  posy, -1 );
	glVertex3f( posx + 2,  posy + 2, -1 );
	glVertex3f( posx,  posy + 2, -1 );

	// Left side
	glColor3f( 0, 0.6, 0 );		// an even darker shade for the sides
	glVertex3f( posx + 2,  posy,  1 );
	glVertex3f( posx + 2,  posy + 2,  1 );
	glVertex3f( posx + 2,  posy + 2, -1 );
	glVertex3f( posx + 2,  posy, -1 );

	// Right side
	glVertex3f(  posx,  posy,  1 );
	glVertex3f(  posx,  posy, -1 );
	glVertex3f(  posx,  posy + 2, -1 );
	glVertex3f(  posx,  posy + 2,  1 );
	glEnd();

	// Desenha o retangulo que rebate a bola (3d)
	glTranslatef( 0, -10, 0 );	// ...move back and down a bit
	// Drawing the cube
	glBegin(GL_QUADS);		// using quadrilaterals as primitive
	// Front
	glColor3f( 0, 1, 0 );		// set colour to pure green
	glVertex3f( movimento,  -3,  1 );
	glVertex3f( movimento,  -4,  1 );
	glVertex3f( movimento + 6,  -4,  1 );
	glVertex3f( movimento + 6,  -3,  1 );

	// Back
	glColor3f( 0, 0.8, 0 );		// a slightly darker green for the back
	glVertex3f( movimento,  -3, -1 );
	glVertex3f( movimento + 6,  -3, -1 );
	glVertex3f( movimento + 6,  -4, -1 );
	glVertex3f( movimento,  -4, -1 );

	// Left side
	glColor3f( 0, 0.6, 0 );		// an even darker shade for the sides
	glVertex3f( movimento + 6,  -3,  1 );
	glVertex3f( movimento + 6,  -4,  1 );
	glVertex3f( movimento + 6,  -4, -1 );
	glVertex3f( movimento + 6,  -3, -1 );

	// Right side
	glVertex3f(  movimento,  -3,  1 );
	glVertex3f(  movimento,  -3, -1 );
	glVertex3f(  movimento,  -4, -1 );
	glVertex3f(  movimento,  -4,  1 );
	glEnd();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

void Timer(int value)
{
	// Muda a direção quando chega na borda esquerda ou direita
	if(posx > 10 || posx < -12)
		xstep = -xstep;

	// Muda a direção quando chega na borda superior ou inferior
	if(posy > 2 || posy < -12) // limite 2 a -14
		ystep = -ystep;

// 	tentativa de deixar os movimentos aleatorios
	

	// identifica falha na colisao com o bloco de baixo
	if(posy <= -12 && (movimento - 1 > posx || movimento + 6 < posx))
	{
		exit(0);
	}

	// identifica colisao com o bloco de baixo e conta +1 ponto
	if(posy <= -12 && (movimento - 1 < posx && movimento + 6 > posx))
	{
		ponto += 1;
	}

	// Move o quadrado
	posx += xstep;
	posy += ystep;

	if(ponto == 2)
	{
		velocidade -= 5;
		ponto = 0;
	}

	// Redesenha o quadrado com as novas coordenadas
	glutPostRedisplay();
	glutTimerFunc(velocidade, Timer, 1);
}

int main(int argc, char** argv)
{
	/* inicia o GLUT */
	glutInit(&argc, argv);

	/* inicia o display usando RGB e double-buffering */
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(250, 100);
	glutCreateWindow("Ping Pong");

	/* Funcao com alguns comandos para a inicializacao do OpenGL; */
	init ();

	/* define as funcões de callback */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, Timer, 1);
	glutMainLoop();

	return 0;
}
