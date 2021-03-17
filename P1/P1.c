/*
	Autores: Alonso Bueno Herrero y BartolomÃ© Zambrana PÃ©rez.
	Asignatura: PDIH.
	Prï¿½ctica: 1.
*/

#include <stdio.h>
#include <dos.h>


/*** VARIABLES PARA ESTABLECER COLORES ***/
int text_color = 15; 		//Blanco por defecto.
int background_color = 0;  	//Negro por defecto.

void reseter_colores(){
	text_color = 15;
	background_color = 0;
}
//Obtiene un caracter de la pantalla
int mi_getchar(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}
//Establece el caracter que se le pasa por pantalla
void mi_putchar(char caracter){
	 union REGS inregs, outregs;

	 inregs.h.ah = 2;
	 inregs.h.dl = caracter;
	 int86(0x21, &inregs, &outregs);
}

//Se hace uso de las implementacions anteriorioes para realizarlo
void getche(){
	int temporary;
	printf("\n Introduce un caracter: ");
	temporary = mi_getchar();
  printf("\n El caracer introducido es el siguiente: ");
	mi_putchar((char)temporary );
	printf("\n");

}


//Modifica el color de primer plano con que se mostrarï¿½ los caracteres.
void textcolor(int  color){
	text_color = color;
}

//Modifica el color de fondo con que se mostrarï¿½n los caracteres.
void textbackground(int color){
	background_color = color;
}

void gotoxy(int x, int y){
	union REGS inregs, outregs;

	inregs.h.ah = 2;
	inregs.h.dh = x;
	inregs.h.dl = y;
	inregs.h.bh = 0;
	int86(0x10, &inregs, &outregs);
}


void mi_pausa(){
	union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21,&inregs, &outregs);
}

int getvideomode(){
	union REGS inregs, outregs;
	inregs.h.ah = 0xF;
	int86(0x10, &inregs, &outregs);
	//Devolvemos modo en el que se encuentra.
	return outregs.h.al;
}

void setvideomode( unsigned char modo){
	union REGS inregs, outregs;
	inregs.h.ah=0x00;
	inregs.h.al=modo;

	int86(0x10, &inregs, &outregs);
}



// Borra toda la pantalla.
void clrscr(){
	int modo; //Variable para mostar el modo
	int i;
	modo = getvideomode();
	//Realizamos el clear si se encuentra en
	//modo texto sino no tiene sentido.
	if(modo == 0 || modo == 1 || modo == 2 ||
		 modo == 3 || modo == 7){

		//Todos los modo texto tienen 25 lï¿½neas.

		for( i = 0; i < 25 ; i++)
		printf("\n");

		gotoxy(0,0);
	}


}


void cputchar(unsigned char c){
	union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;
	inregs.h.bl = background_color << 4 | text_color;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
}

//Fija el aspecto del cursor admitiendo tres valores.
void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

// Dibuja un rectÃ¡ngulo por pantalla mediante *
void recuadro(int x1, int y1, int x2, int y2, int color_fondo, int color_fuente){
		int i,j;
		//Establecemos los colores.
		textcolor(color_fuente);
		textbackground(color_fondo);


		for(i = 0; i <= (x2 - x1); i++){
				//Lateral derecha.
				gotoxy(x1 + i, y1);
				cputchar('*');

				//Lateral izquierda.
				gotoxy(x2 - i , y2);
				cputchar('*');
		}

		for(j = 0; j <= (y2 - y1); j++){
				//Horizontal superior.
				gotoxy(x1, y1 + j);
				cputchar('*');

				//Horizontal inferior
				gotoxy(x2, y2 - j);
				cputchar('*');
		}
}



int main(){


		int funcion = 12;
		int i;

		while(funcion != 0){

			clrscr();
			printf("\n Funciones a seleccionar");
			printf("\n 0.- Finalizar ejecuci¢n");
			printf("\n 1.- gotoxy");
			printf("\n 2.- setcursortype");
			printf("\n 3.- setvideomode");
			printf("\n 4.- getvideomode");
			printf("\n 5.- textcolor");
			printf("\n 6.- textbackground");
			printf("\n 7.- clrscr");
			printf("\n 8.- cputchar");
			printf("\n 9.- getche");
			printf("\n 10.- pintarRectangulo");
			printf("\nIntroduce el d¡gito de la funci¢n a ejecutar:");
			scanf("%d",&funcion);

				//Comprobamos el caso de finalizaciÃ³n
				if(funcion != 0){
						//Limpiamos la pantalla:
						clrscr();
						switch (funcion)
						{
						case 1:
								printf("\n Movemos el cursor a la posici¢n 4,4");
								gotoxy(4,4);
								mi_pausa();
								break;
						case 2:
								printf("\nCursor invisible: ");
								setcursortype(0);
								mi_pausa();
								printf("\nCursor grueso: ");
								setcursortype(2);
								mi_pausa();
								printf("\nCursor normal: ");
								setcursortype(1);
								mi_pausa();
								break;
						case 3:
								printf("Establecemos modo de video gr fico");
								setvideomode(4);
								printf("El modo de video actual es: %d \n", getvideomode());
								mi_pausa();
								printf("Establecemos modo de video texto");
								setvideomode(3);
								printf("El modo de video actual es: %d \n", getvideomode());
								mi_pausa();

								break;
						case 4:
								printf("El modo de video actual es: %d \n", getvideomode());
								mi_pausa();
								break;
						case 5:
								//Reseteamos lo colores a los originales.
								reseter_colores();
								printf("\nCambiamos el color del caracter * a ");
								textcolor(6);
								cputchar('*');
								mi_pausa();
								break;
						case 6:
								//Reseteamos los colores a los originales.
								reseter_colores();
								printf("\nCambiamos el color del fondo del caracter * a ");
								textbackground(2);
								cputchar('*');
								mi_pausa();
								break;
						case 7:
								printf("Limpiamos la pantalla");
								clrscr();
								mi_pausa();
								break;
						case 8:
								printf("\nCambiamos el color del fondo y texto del caracter * a ");
								textbackground(2);
								textcolor(6);
								cputchar('*');
												mi_pausa();
								break;
						case 9:
								getche();
								mi_pausa();//Para apreciar los datos tomados
								break;
						case 10:
								recuadro(3,3,10,10,2,1);
								printf("\n\n\n");
								mi_pausa();
								break;
						}
				}
		}
	return 0;

}





