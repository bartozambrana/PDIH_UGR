package principal; 


import javax.swing.*;        

public class Principal {
 
    private static void createAndShowGUI() {

        JFrame frame = new JFrame("Mi primera ventana");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel texto = new JLabel("Hola a todos.");
        frame.getContentPane().add(texto);  // añadir texto a la ventana 
        frame.pack();                       // necesario
        frame.setVisible(true);             // que la ventana esté visible 
    }

    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();  // configurador de la GUI
            }
        });
    }
}
