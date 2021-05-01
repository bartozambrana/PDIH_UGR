import sys

from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QLabel
from PyQt5.QtWidgets import QPushButton
from PyQt5.QtWidgets import QVBoxLayout
from PyQt5.QtWidgets import QWidget

def greeting():
    if msg.text():
        msg.setText("")
    else:
        msg.setText("Hola mundo cruel")

app = QApplication(sys.argv)
window = QWidget()
window.setWindowTitle('Señales y reglas')
layout = QVBoxLayout()

btn = QPushButton('Click me')
btn.clicked.connect(greeting)  # Connect clicked to greeting()

layout.addWidget(btn)
msg = QLabel('')
layout.addWidget(msg)
window.setLayout(layout)
window.show()
sys.exit(app.exec_())