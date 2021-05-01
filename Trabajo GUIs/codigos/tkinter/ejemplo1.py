#!/usr/bin/env python
# -*- coding: utf-8 -*-

from tkinter import *
#from tkinter import ttk
from tkinter.filedialog import askopenfilename 



# Crea una clase Python para definir el interfaz de usuario de
# la aplicación. Cuando se cree un objeto del tipo 'Aplicacion'
# se ejecutará automáticamente el método __init__() qué 
# construye y muestra la ventana con todos sus widgets: 

class Aplicacion():
    def __init__(self):
        raiz = Tk()                      # crear la ventana
        raiz.geometry('300x200')         # definir tamaño en pixeles
        raiz.configure(bg = 'beige')     # definir fondo de la ventana
        raiz.title('Aplicación')         # título de la ventana
        Label(raiz, text="Programa básico con Tkinter").pack(side=LEFT)
        Button(raiz, text='Abrir archivo', command=Aplicacion.abrir_archivo).pack(side=LEFT)
        Button(raiz, text='Salir',command=raiz.destroy).pack(side=BOTTOM)  # habilitar el botón y colocarlo al final de la ventana (pegado al borde inferior)

        raiz.mainloop()              # bucle infinito de ejecución de la GUI

    def abrir_archivo():
        filename = askopenfilename()
        print(filename)
        v1 = Tk()
        v1.geometry('300x200')
        v1.title("Lector de archivos")
        Label(v1, text=filename).pack()


# Definir la función main(): que indica 
# el comienzo del programa. Dentro de ella se crea el objeto 
# aplicación 'mi_app' basado en la clase 'Aplicación':

def main():
    mi_app = Aplicacion()  # instanciamos la clase Aplicacion
    return 0


# __name__ es una variable especial de python que constituye el main del programa,
# la semilla de ejecución, por decirlo así
if __name__ == '__main__':
    main()
