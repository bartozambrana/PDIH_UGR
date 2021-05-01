import tkinter as tk





window = tk.Tk()
window.title("Cuadrícula")



for i in range(3):  # por filas

    for j in range(3):  # por columnas
        
        frame = tk.Frame(
            master=window,         # frame dentro de la ventana "window"
            relief=tk.RAISED,      # sin espacio entre cuadros => más estético
            borderwidth=1
        )
        frame.grid(row=i, column=j)
        boton = tk.Button(master=frame, text=f"Fila {i}\nColumna {j}").pack()
        

window.mainloop()   # bucle principal

