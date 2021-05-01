#Importamos system para permitir manejar el estado de salido.
import sys

#Importamos las calses necesasiros.
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QLabel
from PyQt5.QtWidgets import QWidget

# Creamos un objeto QApplication para crear la aplicación, toda
# aplicación QtPy5 ha de crearlo. Proporcionándonos información globla.
# Se le pasa sys.argv ya que utiliza el constructor para crear la aplicación
# utilizando argc y argv en c++.
app = QApplication(sys.argv)



# Creamos la ventana de la palicación. es decir la GUI de la aplicación.
# Para ello nos bastamos con un QWidget.
window = QWidget()
# Establecemos el título de la ventana
window.setWindowTitle('Hola Mundo Aplicación')
# Establecemos el tamaño de la ventana.
# Primer y segundo argumento xy, tercer y cuarto anchura y altura
window.setGeometry(100,300,300,100)
# Establecemos la posición de la ventana.
window.move(60,15)

# Para mostrar texto en la GUI hay que establecer un objeto QLabel.
# Los objetos pueden aceptar HTML lo cual puede llegar a ser muy funcinal.
# A la hora de crearlo hay que asociarle la ventana en la que queremos que se 
# muestre. Cabe destacar que se puede utilizar cualquier widget
# como ventana de nivel superior (botón, etiqueta)
#
mensaje = QLabel('<h1>Hola mundo Cruel</h1>',parent=window)



#Mostramos la venta.
window.show()

# Hacemos que se ejecute en bucle la interfaz
# se establece dentro de sys.exit para limpiar recursos.
sys.exit(app.exec_())



