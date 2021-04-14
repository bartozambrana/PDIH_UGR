#include <ncurses.h>
#include <unistd.h>


#define DELAY 30000
typedef struct
{
    int x, y; 
} raqueta;

/**
 * Función para comprar si da la bola en la paleta, únicamente teniendo en 
 * cuenta la coordenada y, ya que partimos que la paleta tiene una altura x.
 * 
 * posicion_superior, se trata de la coordenada y superior de la paleta.
 * posicion_inferior, se trata de la coordenada y inferior de la paleta.
 * posicion_pelota, se trata de la coordenada y de la pelota.
 * 
 * Return True solo si se puede mover, false en otro caso
*/
bool chocar_paletas_y(int posicion_superior, int posicion_inferior, int posicion_pelota){
	bool resultado;
	
	if(posicion_pelota >= posicion_superior && posicion_pelota <= posicion_inferior)
		resultado = true;
	else 
		resultado = false; 
	
	return resultado;
}


int main(int argc, char *argv[]){
	
	// DECLARACIÓN DE LAS VARIALBLES. 
	int filas, columnas; 		// Filas y columnas utilizada para crear la ventana de las opciones del juego.
	int max_y, max_x;	 		// Número máximo de filas y columnas que posee la pantalla del juego.
	int i;				 		// Contador de un bucle utilizado anteriormente.
	int x,y;	 		 		// Coordenadas de posicionamiento de la pelota.
	int next_x = 0;		 		// Coordenada X a la que se va a desplazar la pelota.
	int directionx = -1; 		// Dirección coordenada X de la pelota, -1 izquierda, +1 derecha.
	int next_y = 0;		 		// Coordenada Y a la que se va a desplazar la pelota.
	int directiony = -1; 		// Dirección coordenada Y de la pelota, -1 arriba, +1 abajo.
	bool parar = false;	 		//	Varible de control para finalizar el juego.
	int aux;			 		// Variable auxiliar para controlar el movimiento de las paletas.
	int puntos_derecha = 0;		//Puntos de jugador 2.
	int puntos_izquierda = 0;   // Puntos del jugador 1. 
	
	/*************************************************************************/
	// Tareas inciales ncurses: 
	initscr();				
	keypad(stdscr, true);
	noecho();
	curs_set(FALSE);
	
	clear(); //Limpiamos la pantalla.
	refresh();

	/*************************************************************************/
	// MENÚ DE CONTROLES DEL JUEGO.
	
	getmaxyx(stdscr,filas,columnas);
	WINDOW *window = newwin(filas,columnas,0,0);
	box(window,'|','=');
	mvwprintw(window,4,4,"jugador 1 movimientos con w arriba y con s abajo");
	mvwprintw(window,5,4,"jugador 2 movimientos con flecha arriba y con flecha abajo");
	mvwprintw(window,6,4,"PULSAR p para pausar el juego.");
	mvwprintw(window,7,4,"PULSAR escape para salir del juego.");
	mvwprintw(window,8,4,"PULSAR CUALQUIER TECLA PARA COMENZAR");
	wrefresh(window);
	getch();

	/*************************************************************************/
	// Inicio del juego
	
	// Establecemos modo nodelay, para evitar el bloqueo de pantalla al pulsar
	// una tecla. 
	nodelay(stdscr,1); 

	// Capturar tamaño de pantalla y 
	// establecer punto de inicio para la pelota, mitad de la pantalla.
	getmaxyx(stdscr,max_y,max_x);
	x=max_x/2;
	y=max_y/2;

	// Creación de los objetos raqueta, para tartar los datos de una forma más sencilla.
	raqueta raqueta_derecha = {max_x-1,max_y/2}, raqueta_izquierda = {1,max_y/2};
	clear();

	//Bucle del juego.
	while(!parar){

		//movimiento de la bola
		clear();

		//Dibujamos la pelotita y barra divisoria de campos 
		mvprintw(y, x, "o");
		mvvline(0, max_x / 2, ACS_VLINE, max_y);
		
		// dibujado de los contadores de cada jugador. 
		mvprintw(2, max_x / 2 - 2, "%i | %i", puntos_izquierda, puntos_derecha);

		// dibujar PALETAS izda y dcha
		for(i= -2; i < 5; i++){
			mvprintw(raqueta_derecha.y + i, raqueta_derecha.x, "|");
			mvprintw(raqueta_izquierda.y + i, raqueta_izquierda.x, "|");
		}
		
		// refrescar pantalla para 
		refresh();
		// retardo para evitar extrema complejidad del juego
		usleep(DELAY);		 
		
		/*********************************************************************/
		
		// CONTROL DE LA PELOLA Y PALETAS
		next_x = x + directionx;
		next_y = y + directiony;

		// Caso 1: la pelota choca con la paleta (en el lado en que esté)
		if ((next_x >= raqueta_derecha.x && chocar_paletas_y(raqueta_derecha.y-2,raqueta_derecha.y+5,next_y)) || 
			(next_x <= raqueta_izquierda.x && chocar_paletas_y(raqueta_izquierda.y-2,raqueta_izquierda.y+5,next_y))){ //Va a dar en una paleta
		
			directionx *= -1;  // cambiar dirección 
		}

		// caso 2: la pelota NO CHOCA con la paleta DERECHA
		else if((next_x >= raqueta_derecha.x && !chocar_paletas_y(raqueta_derecha.y-2,raqueta_derecha.y+5,next_y))){	// jugador derecha no alcanza pelota => puntos para el de la izda
			puntos_izquierda++;
			//Volvemos la pelota al medio.
			x = max_x/2;
			y = max_y/2;

		// caso 3: la pelota NO CHOCA con la paleta IZQUIEDA 
		}else if((next_x <= raqueta_izquierda.x && !chocar_paletas_y(raqueta_izquierda.y-2,raqueta_izquierda.y+5,next_y) )){	//al reves
			puntos_derecha++;
			//Volvemos la pelota al medio.
			x = max_x/2;
			y = max_y/2;
			
		// caso 4: la pelota NO CHOCA con NINGUNA paleta 
		}else{
			// movimiento "habitual de la bola" en X
			x += directionx;

			// controlar topes superior e inferior de pantalla
			if (next_y >= max_y || next_y < 0)
			{
				directiony *= -1;
			}
			else  // no está en topes superior/inferior => puede seguir movimient
			{
				y += directiony;
			}
		}
			
		//Pulsaciones de los jugadores.
		switch (getch()){
			case KEY_UP:          
				aux = raqueta_derecha.y;
				aux--;
				if(aux - 2 >= 0)
					raqueta_derecha.y--;			//Subir
				break;
				
			case KEY_DOWN:		
				aux = raqueta_derecha.y;
				aux++;
				if(aux + 5 <= max_y)
					raqueta_derecha.y++;			//Bajar
				break;
			
			case 'w':
				aux = raqueta_izquierda.y;
				aux--;
				if(aux - 2 >= 0)
					raqueta_izquierda.y--; 	//Subir
				break;
				
			case 's':
				aux = raqueta_izquierda.y;
				aux++;
				if(aux + 5 <= max_y)
					raqueta_izquierda.y++; 	//Bajar
				break;
			case 'p':
				getchar();				//Parar
				break;
			case 0x1B:					//Salir
				parar = true;
				break;
		}

	}
	
	endwin();  // cerrar ventana de ncurses  (acabar programa)
	return 0;

}
