#Primera cosa que hemos de realizar. Importar el paquete.
import wx;

#Creamos el objeto de aplicación que se encontrará constantemente ejecutándose.
app = wx.App()

#Creamos el frame, lo que será la ventana.
frame = wx.Frame(None,title="Hola mundo")

#Mostramos la ventana.
frame.Show()

#Hacemos el el objeto app se ejecute en forma de bucle.
app.MainLoop();