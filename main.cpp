// *********************************************************************
// # Jogo Ping Pongo

// # Descri��o
// * Desenvolvemos um jogo simples de ping pong cujo objetivo � arremessar a caixa a partir da base e
// * acertar os jarros suspensos. As colis�es permitidas s�o somente na base do jarro, ou seja, a caixa
// * s� ir� quebrar o jarro se acertar exatamente na parte de baixo do jarro. Foi adicionado efeitos sonoros
// * para deixar o jogo mais din�mico. A cada 5 arremessos da caixa a partir da base, o arremesso da caixa
// * fica levemente mais r�pida que, com o passar do tempo, ser� imposs�vel acertar a caixa na base.
// 
// # Descri��o do desenvolvimento
// * O jogo foi inteiramente desenvolvido em C++ utilizando as bibliotecas GLUT para os efeitos gr�ficos, 
// * windows para utilizarmos a biblioteca de som do windows com facilidade, mmsystem que permite usar sons no jogo, 
// * stb_image que faz importa��o de texturas e glm que importa objetos 3d no projeto.
// 
// # Alunos
// * Filipe Alves Sampaio
// * Lucas Hiago de Moura Vilela
// 
// *********************************************************************
//
// Controles (sem caps lock):
// 'a': move para esquerda
// 'd': move para direita
// 'w': move para cima
// 's': move para baixo
// 
// *********************************************************************

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <windows.h>      //usada para reproduzir sons de fundo
#include <mmsystem.h>    //usada para reproduzir sons de fundo

#define STB_IMAGE_IMPLEMENTATION//usada para carregar textura das imagens
#include "stb_image.h" //usada para carregar textura das imagens

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <ctime>

#include "glm.h"

#define tam 6

double rotate_x = 0;
double rotate_y = 0;

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
GLfloat ystep = -1.0f;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

// c e d rastreia o número de vezes que 'b' e 'n' são pressionados respectivamente
// esquerda e direita indicam o índice mais à esquerda e mais à direita do retângulo móvel
// int esquerda = -5, direita = 5, cima = 5, baixo = 5;
int movimento = 0, movimento2 = -3, ponto = 10, velocidade = 170;

// blocos para contato e colisão
struct Bloco
{
	float x;
	float z;
	float y;
	bool vivo;
};

Bloco blocos[tam];

static int eixo_x = 0, eixo_y=0;
float luzX = 0.7f, luzY = 0.75f, luzZ = 8.5f;
GLfloat light0_position[] = {luzX, luzY, luzZ, 1.0f};
GLMmodel * pmodel = NULL;

void drawModel(void)
{

	if (!pmodel)
	{
		pmodel = glmReadOBJ("3d models/flowers.obj");
		if (!pmodel)
			exit(0);
		glmUnitize(pmodel);
		glmFacetNormals(pmodel);//normal do obejeto
		glmVertexNormals(pmodel, 90.0);
		// glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
	}
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);


}

/* Funcao com alguns comandos para a inicializacao do OpenGL; */
void init(void)
{
	// PlaySound(TEXT("sound/o_povo_gosta_e_do_piseiro_eric_land_ze_vaqueiro.wav"), NULL, SND_ASYNC | SND_LOOP);
	
	// PlaySound(TEXT("sound/background.wav"), NULL, SND_ASYNC | SND_LOOP);  //Inicia o áudio de fundo do jogo
	glClearColor (1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
	glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer

	// glEnable(GL_FOG);
	// glEnable(GL_COLOR_MATERIAL);// Habilita a definicao da cor do material(objeto) a partir da cor corrente
	// glEnable(GL_LIGHTING); 	//Habilita o uso de iluminacao
	// glEnable(GL_LIGHT0);	// Habilita a luz de numero 0
	// glEnable(GL_DEPTH_TEST);  // Habilita o depth-buffering
	// glEnable(GL_BLEND); //Exibe os valores de cores do fragmento computado com os valores nos buffers de cores.
	// /* Activa o modelo de sombreagem de "Gouraud". */
	// glShadeModel( GL_SMOOTH );
	glEnable(GL_TEXTURE_2D);//ativa o modo textura 2D

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
	case 'a': // esquerda
		if (movimento > -13)
			movimento -= 1;
		glutPostRedisplay();
		break;
	case 'd': // direita
		if (movimento < 7)
			movimento += 1;
		// }
		glutPostRedisplay();
		break;
	case 'w':
		if (movimento2 < 0)
			movimento2 += 1;
		glutPostRedisplay();
		break;

	case 's':
		if (movimento2 > -3)
			movimento2 -= 1;
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
	glRotatef( rotate_x, 0.0, 0.0, 1.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );

	if(inicio)
	{
		posx = 0;
		posy = -10;
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

	////////////////////

	// arena

	GLuint texture1, texture2;
	int w, h;

	unsigned char * uc = stbi_load("textures/cubo.jpg", & w, & h, NULL, 0);
	glGenTextures(1, & texture1); //gera nomes identificadores de texturas
	glBindTexture(GL_TEXTURE_2D, texture1); //Ativa a textura atual

	// Cria a textura lateral de cada bloco

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
				 0, GL_RGB, GL_UNSIGNED_BYTE, uc);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Desenha um quadrado preenchido com a cor corrente (3d)
	glTranslatef( 0, 5, -8 );	// ...move back and down a bit
	// Drawing the cube
	glBegin(GL_QUADS);		// using quadrilaterals as primitive
	// Front
	glColor3f( 0, 1, 0 );		// set colour to pure green
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f( posx,  posy,  1 );
	glTexCoord2f(1, 0);
	glVertex3f( posx,  posy + 2,  1 );
	glTexCoord2f(1, 1);
	glVertex3f( posx + 2,  posy + 2,  1 );
	glTexCoord2f(0, 1);
	glVertex3f( posx + 2,  posy,  1 );
	glTexCoord2f(0, 0);

	// Back
	glColor3f( 0, 0.8, 0 );		// a slightly darker green for the back
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f( posx,  posy, -1 );
	glVertex3f( posx + 2,  posy, -1 );
	glVertex3f( posx + 2,  posy + 2, -1 );
	glVertex3f( posx,  posy + 2, -1 );

	// Left side
	glColor3f( 0, 0.6, 0 );		// an even darker shade for the sides
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f( posx + 2,  posy,  1 );
	glVertex3f( posx + 2,  posy + 2,  1 );
	glVertex3f( posx + 2,  posy + 2, -1 );
	glVertex3f( posx + 2,  posy, -1 );

	// Right side
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(  posx,  posy,  1 );
	glVertex3f(  posx,  posy, -1 );
	glVertex3f(  posx,  posy + 2, -1 );
	glVertex3f(  posx,  posy + 2,  1 );
	glEnd();

	glDeleteTextures(1, & texture1);
	stbi_image_free(uc);

	///////////////////////////////////////////

	// Desenha o retangulo que rebate a bola (3d)
	unsigned char * uc2 = stbi_load("textures/barra.jpg", & w, & h, NULL, 0);
	glGenTextures(1, & texture2); //gera nomes identificadores de texturas
	glBindTexture(GL_TEXTURE_2D, texture2); //Ativa a textura atual

	// Cria a textura lateral de cada bloco
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
				 0, GL_RGB, GL_UNSIGNED_BYTE, uc2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTranslatef( 0, -10, 0 );	// ...move back and down a bit
	// Drawing the cube
	glBegin(GL_QUADS);		// using quadrilaterals as primitive
	// Front
	glColor3f( 0, 1, 0 );		// set colour to pure green
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f( movimento,  movimento2,  1 );
	glTexCoord2f(1, 0);
	glVertex3f( movimento,  movimento2 - 1,  1 );
	glTexCoord2f(1, 1);
	glVertex3f( movimento + 6,  movimento2 - 1,  1 );
	glTexCoord2f(0, 1);
	glVertex3f( movimento + 6,  movimento2,  1 );
	glTexCoord2f(0, 0);

	// Back
	glColor3f( 1, 0.8, 0 );		// a slightly darker green for the back
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f( movimento,  movimento2, -1 );
	glTexCoord2f(1, 0);
	glVertex3f( movimento + 6,  movimento2, -1 );
	glTexCoord2f(1, 1);
	glVertex3f( movimento + 6,  movimento2 - 1, -1 );
	glTexCoord2f(0, 1);
	glVertex3f( movimento,  movimento2 - 1, -1 );
	glTexCoord2f(0, 0);

	// Left side
	glColor3f( 0, 0.6, 0 );		// an even darker shade for the sides
	glVertex3f( movimento + 6,  movimento2,  1 );
	glVertex3f( movimento + 6,  movimento2 - 1,  1 );
	glVertex3f( movimento + 6,  movimento2 - 1, -1 );
	glVertex3f( movimento + 6,  movimento2, -1 );

	// Right side
	glVertex3f(  movimento,  movimento2,  1 );
	glVertex3f(  movimento,  movimento2, -1 );
	glVertex3f(  movimento,  movimento2 - 1, -1 );
	glVertex3f(  movimento,  movimento2 - 1,  1 );
	glEnd();

	glDeleteTextures(1, & texture1);
	stbi_image_free(uc2);

	////////////////////
	// desenha cubos que serão eliminados conforme colisão
	
	for(int i = 0; i < tam; i++)
	{
		if(blocos[i].vivo) 	//se o bloco NÃO foi tocado -> desenha
		{
			glPushMatrix();
			glColor3f(0, 0, 1);
			glTranslatef(blocos[i].x, blocos[i].y, blocos[i].z);
			glScaled(1.8, 1.8, 1.8);
			// glutSolidCube(2.0);
			// criaCubo(1.0);
			drawModel();
			glPopMatrix();
		}
	}

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

void Timer(int value)
{
	printf("\n-----\n");
	// verificando colisao com blocos superiores
	for(int n = 0; n < tam; n++)
	{
		if(blocos[n].vivo)
		{
			if(((float)blocos[n].x > posx-5 && (float)blocos[n].x < posx + 5) && (posy + 14) == (float)blocos[n].y && ystep > 0)
			{
				PlaySound(TEXT("sound/windowglass.wav"), NULL, SND_ASYNC);
				printf("colidiu! pos(%f, %f) - bloco(%f, %f)\n", posx, posy+14, (float)blocos[n].x, (float)blocos[n].y);
				ystep = -ystep; //bateu no bloco, volta
				blocos[n].vivo = false;
				break;
			}
		}
	}
	printf("-----\n");

	// Muda a direção quando chega na borda esquerda ou direita
	if(posx > 10 || posx < -12)
		xstep = -xstep;

	// Muda a direção quando chega na borda superior ou inferior
	if(posy > 2 || posy < (float)movimento2 - 9)  // limite 2 a -14
	{
		ystep = -ystep;
	}

	// identifica falha na colisao com o bloco de baixo
	if(posy <= (float)movimento2 - 9 && (movimento - 1 > posx || movimento + 6 < posx))
	{
		exit(0);
	}

	// identifica colisao com o bloco de baixo e conta +1 ponto
	if(posy <= (float)movimento2 - 9 && (movimento - 1 < posx && movimento + 6 > posx))
	{
		PlaySound(TEXT("sound/pingpong.wav"), NULL, SND_ASYNC);  //Inicia o áudio de rebate da bola
		ponto += 1;
	}

	// Move o quadrado
	posx += xstep;
	posy += ystep;

	if(ponto == 2)
	{
		velocidade -= 2;
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

	// inicia blocos para colisao
	//cria blocos
	float x = -12.0, z = 0.0, y = 12;
	for(int n = 0;  n < tam; n++)
	{
		// if(x > 5)
		// {
		// 	x = -2;
			// z += 2;
		// 	y += 3;
		// }

		blocos[n].x = x;
		blocos[n].z = z;
		blocos[n].y = y;
		blocos[n].vivo = true;
		x += 5;
	}

	/* Inicia a iluminação */
	GLfloat light_position[] = { -1.0, 1.0, 1.0, 0.0};
	GLfloat light_color[] = {1.0, 1.0, 1.0, 0.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* Inicia as características gerais dos materiais */
	GLfloat mat_ambient_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	/* Ativa o modelo de sombreagem de "Gouraud". */
	glShadeModel(GL_SMOOTH);

	/* define as funcões de callback */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, Timer, 1);
	glutMainLoop();

	glDisable(GL_TEXTURE_2D);

	return 0;
}
