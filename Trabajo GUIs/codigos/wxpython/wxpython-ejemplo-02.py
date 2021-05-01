#Primera cosa que hemos de realizar. Importar el paquete.
import wx;

#Como se dijo anteriormente los marcos y los diáglogos no son acogidos 
#dentro del widget principal frame. POr lo tanto tenemos que realizar nuestro 
#propio frame si queremos realizar un menú. Ejemplo:

class HolaMundoFrame(wx.Frame):
    #Contructor de la clase.
    def __init__(self, *args, **kw):
        #llamamos al constructor de la clase padre.
        super(HolaMundoFrame,self).__init__(*args,**kw)
        #cetnramos la pantalla.
        self.Centre()
        #Creamos el panel donde se encontrará el texto, se trata de un cuadro de texto.
        panel = wx.Panel(self)

        #establecemos el hola mundo en el panel con letra negrita.
        st = wx.StaticText(panel,label="Hola Mundo Cruel")
            #Obtenemos la fuente
        font = st.GetFont()
            #Aumentamos el tamaño.
        font.PointSize += 10
            #La establecemos en negrita.
        font = font.Bold()
            #Establecemos la fuente.
        st.SetFont(font)

        # Creamos un boxSizer vertical, una caja donde se añaden verticalmente a la izquierde y ariba
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(st, wx.SizerFlags().Border(wx.TOP|wx.LEFT, 25))
        panel.SetSizer(sizer)

        # Cramos el menú
        self.makeMenuBar()

        # Creamos la barra de estado
        self.CreateStatusBar()
        self.SetStatusText("Bienvenidos a  wxPython!")


    def makeMenuBar(self):
        # La barra de menú está compuesta de items, por lo tanto creamoslos todos.
        

        # Creamos el objeto submenu.
        submenu1 = wx.Menu()

        # Creamos el primer item. Una nota de texto.
        notaItem = submenu1.Append(-1, "&Nota")
        #Establecemos un separador.
        submenu1.AppendSeparator()
        #Establecemos la salida.
        exitItem = submenu1.Append(wx.ID_EXIT)

        # Creamos otros submenor que nos aporte la ayuda.
        submenu2 = wx.Menu()
        helpItem = submenu2.Append(wx.ID_ABOUT)

        #Creamos el menú principal donde agregamos los submenús.
        menuBar = wx.MenuBar()
        menuBar.Append(submenu1, "&File")
        menuBar.Append(submenu2, "&Help")

        # Añadimos el submenú al frame.
        self.SetMenuBar(menuBar)

        # Asociamos los eventos al pulsar sobre el menú.
        self.Bind(wx.EVT_MENU, self.OnNota, notaItem)
        self.Bind(wx.EVT_MENU, self.OnExit, exitItem)
        self.Bind(wx.EVT_MENU, self.OnHelp, helpItem)


    def OnExit(self, event):
        #Cerramos la aplicación.
        self.Close(True)


    def OnNota(self, event):
        #Establece un mensaje de hola.
        wx.MessageBox("Hola de nuevo wxPython")


    def OnHelp(self, event):
        wx.MessageBox("Este es un mensaje de ayuda, estamos en un tutorial.", "Sobre la aplicación",
                      wx.OK|wx.ICON_INFORMATION)


if __name__ == '__main__':
    # Cuando este módulo no se importe se ejecutará como el main.
    app = wx.App()
    frm = HolaMundoFrame(None, title='Hola mundo Cruel 2',size=(300, 200))
    frm.Show()
    app.MainLoop()

