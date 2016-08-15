#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

external("C"){
	#include "ufrn_al5d.h"
}

//Posicao inicial para todos os servos
#define HOME_POS "#0P1500#1P1500#2P1500#3P1500#4P1500T10000"

int serial_fd, theta[5] = {90,90,90,90,0};
int terminar = 1;
char *comando;
float l, cinematica[4][4];
float x[5], y[5];

//CALCULAR A MATRIZ DE CINEMÁTICA DIRETA
void definirPosicao(int i){

	l = 2;

	//LINHA #1

	cinematica[0][0] = cos(theta[0]) * cos(theta[1] + theta[2] + theta[3] + theta[4]);
	cinematica[0][1] = - cos(theta[0]) * sin(theta[1] + theta[2] + theta[3] + theta[4]);
	cinematica[0][2] = sin(theta[0]);
	cinematica[0][3] = 	14.5 * cos(theta[0]) * cos(theta[1]) + 
						18.5 * cos(theta[0]) * cos(theta[1] + theta[2]) +
						l * cos(theta[0]) * cos(theta[1] + theta[2] + theta[3]);

	//LINHA #2

	cinematica[1][0] = sin(theta[0]) * cos(theta[1] + theta[2] + theta[3] + theta[4]);
	cinematica[1][1] = - sin(theta[0]) * sin(theta[1] + theta[2] + theta[3] + theta[4]);
	cinematica[1][2] = - cos(theta[0]);
	cinematica[1][3] = 	14.5 * sin(theta[0]) * cos(theta[1]) +
						18.5 * sin(theta[0]) * cos(theta[1] + theta[2]) +
						l * sin(theta[0]) * cos(theta[1] + theta[2] + theta[3]);

	//LINHA #3

	cinematica[2][0] = sin(theta[1] + theta[2] + theta[3] + theta[4]);
	cinematica[2][1] = cos(theta[1] + theta[2] + theta[3] + theta[4]);
	cinematica[2][2] = 0;
	cinematica[2][3] = 	7.5 + 14.5 * sin(theta[1]) +
						18.5 * sin(theta[1] + theta[2]) + l * sin(theta[1] + theta[2] + theta[3]);

	//LINHA #4

	cinematica[3][0] = 0;
	cinematica[3][1] = 0;
	cinematica[3][2] = 0;
	cinematica[3][3] = 1;

	x[i] = cinematica[0][3];
	y[i] = cinematica[1][3];

}

//ENVIAR UM COMANDO PRA UM DETERMINADO SERVO
int enviarComando(int servo, int pos){

	memset(comando, 0, BUFSIZE);
	sprintf(comando,"#%dP%d",servo,trava(servo,pos));

	if(enviar_comando(comando,serial_fd)==-1){
		printf("Problema no envio do comando\nAbortando o programa...");
		return -1;				
	}

	return 1;
}

int main(int argc, char** argv){
	char x0[50], x1[50], x2[50], x3[50], x4[50], y0[50], y1[50], y2[50], y3[50], y4[50];
	int retorno = 0, pos;
	char cmd;

	comando = (char*) malloc(sizeof(char)*BUFSIZE);
	
	serial_fd = abrir_porta();

	if(serial_fd == -1)
	{
		printf("Erro abrindo a porta serial /dev/ttyS0\nAbortando o programa...");
		return -1;
	}
	else
	{
		if(configurar_porta(serial_fd) == -1){
			printf("Erro inicializando a porta\n");
			close(serial_fd);
			return -1;
		}

	Mat image;
		
	image= imread("branco.png",CV_LOAD_IMAGE_GRAYSCALE);
	
	if(!image.data)
		printf("Não foi possível carregar a imagem\n");

	namedWindow("janela",WINDOW_AUTOSIZE);
		
		pos = theta[0]*2000/180 + 500;
		retorno = enviarComando(BAS_SERVO,pos);
		pos = theta[1]*2000/180 + 500;
		retorno = enviarComando(SHL_SERVO,pos);
		pos = theta[2]*2000/180 + 500;
		retorno = enviarComando(ELB_SERVO,pos);
		pos = theta[3]*2000/180 + 500;
		retorno = enviarComando(WRI_SERVO,pos);
		pos = 500;
		retorno = enviarComando(GRI_SERVO,pos);

		while(terminar != -1){
			
			// PRIMEIRO COMANDO - POSICAL INICIAL

			printf("\n\n\nESCOLHA ENTRE AS OPCOES DE MOVIMENTO\n");
			printf("a - INCREMENTAR BASE\n");
			printf("z - DECREMENTAR BASE\n");
			printf("s - IMCREMENTAR OMBRO\n");
			printf("x - DECREMENTAR OMBRO\n");
			printf("d - IMCREMENTAR COTOVELO\n");
			printf("c - DECREMENTAR COTOVELO\n");
			printf("f - INCREMENTAR PUNHO\n");
			printf("v - DECREMENTAR PUNHO\n");
			printf("g - ABRIR GARRA\n");
			printf("b - FECHAR GARRA\n");
			printf("1 - SALVAR VALOR 1\n");
			printf("2 - SALVAR VALOR 2\n");
			printf("3 - SALVAR VALOR 3\n");
			printf("4 - SALVAR VALOR 4\n");
			printf("5 - SALVAR VALOR 5\n");
			printf("p - CRIAR IMAGEM\n");
			printf("l - FINALIZAR APLICACAO\n \n");
			
			retorno = system("/bin/stty raw");
        		cmd = getchar();
        		retorno = system("/bin/stty cooked");
			
			if(retorno == -1)
				break;

			switch(cmd){
				case 'a':
					if(theta[0] < 180)
						theta[0] = theta[0] + 1;
					pos = theta[0]*2000/180 + 500;
					retorno = enviarComando(BAS_SERVO,pos);
					break;
				case 'z':
					if(theta[0] > 0)
						theta[0] = theta[0] - 1;
					pos = theta[0]*2000/180 + 500;
					retorno = enviarComando(BAS_SERVO,pos);
					break;
				case 's':
					if(theta[1] < 180)
						theta[1] = theta[1] + 1;
					pos = theta[1]*2000/180 + 500;
					retorno = enviarComando(SHL_SERVO,pos);
					break;
				case 'x':
					if(theta[1] > 0)
						theta[1] = theta[1] - 1;
					pos = theta[1]*2000/180 + 500;
					retorno = enviarComando(SHL_SERVO,pos);
					break;
				case 'c':
					if(theta[2] < 180)
						theta[2] = theta[2] + 1;
					pos = theta[2]*2000/180 + 500;
					retorno = enviarComando(ELB_SERVO,pos);
					break;
				case 'd':
					if(theta[2] > 0)
						theta[2] = theta[2] - 1;
					pos = theta[2]*2000/180 + 500;
					retorno = enviarComando(ELB_SERVO,pos);
					break;
				case 'f':
					if(theta[3] < 180)
						theta[3] = theta[3] + 1;
					pos = theta[3]*2000/180 + 500;
					retorno = enviarComando(WRI_SERVO,pos);
					break;
				case 'v':
					if(theta[3] > 0)
						theta[3] = theta[3] - 1;
					pos = theta[3]*2000/180 + 500;
					retorno = enviarComando(WRI_SERVO,pos);
					break;
				case 'g':
					theta[4] = 0;
					pos = 1500;
					retorno = enviarComando(GRI_SERVO,pos);
					break;
				case 'b':
					theta[4] = 1;
					pos = 2400;
					retorno = enviarComando(GRI_SERVO,pos);
					break;
				case 'l':
					terminar = -1;
					break;
				case '1':
					definirPosicao(0);
					printf("\nX[0]: %.1f Y[0]: %.1f", x[0], y[0]);
					break;
				case '2':
					definirPosicao(1);
					printf("\nX[1]: %.1f Y[1]: %.1f", x[1], y[1]);
					break;
				case '3':
					definirPosicao(2);
					printf("\nX[2]: %.1f Y[2]: %.1f", x[2], y[2]);
					break;
				case '4':
					definirPosicao(3);
					printf("\nX[3]: %.1f Y[3]: %.1f", x[3], y[3]);
					break;
				case '5':
					definirPosicao(4);
					printf("\nX[4]: %.1f Y[4]: %.1f", x[4], y[4]);
					break;
				case 'p':
					x[0] *= 50;	x[1] *= 50; x[2] *= 50; x[3] *= 50; x[4] *= 50;
					y[0] *= 50;	y[1] *= 50; y[2] *= 50; y[3] *= 50; y[4] *= 50;

					int xInt[5], yInt[5];

					xInt = x[0]; yInt = y[0];
					xInt = x[1]; yInt = y[1];
					xInt = x[2]; yInt = y[2];
					xInt = x[3]; yInt = y[3];
					xInt = x[4]; yInt = y[4];

					linha(xInt[0], yInt[0], xInt[1], yInt[1], image); 	//Ponto 1 -> Ponto 2
					linha(xInt[0], yInt[0], xInt[2], yInt[2], image);	//Ponto 1 -> Ponto 3
					linha(xInt[1], yInt[1], xInt[2], yInt[2], image);	//Ponto 2 -> Ponto 3
					linha(xInt[1], yInt[1], xInt[3], yInt[3], image);	//Ponto 2 -> Ponto 4
					linha(xInt[2], yInt[2], xInt[4], yInt[4], image);	//Ponto 3 -> Ponto 5
					linha(xInt[3], yInt[3], xInt[4], yInt[4], image);	//Ponto 4 -> Ponto 5
					imshow("janela", image);  
				  	waitKey();
					break;
				default:
					printf("\nOPÇÃO INVALIDA\n");
					break;
				
			}

			if(retorno == -1)
				break;

		}

		fechar_porta(serial_fd);
		printf("\nPROGRAMA FINALIZADO\n");

    	}

	return 0;
}