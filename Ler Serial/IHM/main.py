from PyQt5 import QtWidgets, uic
import sys
import serial


class Ui(QtWidgets.QMainWindow):
    global voltas
    voltas = 0

    def __init__(self):
        super(Ui, self).__init__()
        uic.loadUi('ihm.ui', self)
        self.show()
        self.conectar()
        # Botões
        self.bt_mais = self.findChild(QtWidgets.QPushButton, 'bt_mais')
        self.bt_menos = self.findChild(QtWidgets.QPushButton, 'bt_menos')
        self.bt_zerar = self.findChild(QtWidgets.QPushButton, 'bt_zerar')

        self.bt_mais.clicked.connect(self.mais)
        self.bt_menos.clicked.connect(self.menos)
        self.bt_zerar.clicked.connect(self.zerar)

        # Display
        self.display = self.findChild(QtWidgets.QLCDNumber, 'display')

        # Input números de voltas
        self.LE_voltas = self.findChild(QtWidgets.QLineEdit, 'LE_voltas')


        # Barra de progresso
        self.barra = self.findChild(QtWidgets.QProgressBar, 'barra')
        self.barra.setValue(0)
        self.barra.hide()

    def mais(self):
        global voltas
        voltas +=1
        self.display.display(voltas)
        self.progresso()
        self.ser.write("on".encode())

    def menos(self):
        global voltas
        voltas -=1
        if voltas == -1:
            voltas = 0
        self.display.display(voltas)
        self.progresso()
        self.ser.write("off".encode())

    def zerar(self):
        global voltas
        voltas = 0
        self.display.display(voltas)
        self.progresso()

    def progresso(self):
        global voltas
        try:
            self.voltas_quantidade = int(self.LE_voltas.text())
            self.barra.setValue(int((voltas/self.voltas_quantidade)*100))
            self.barra.show()
        except:
            pass

    def conectar(self):
        self.ser = serial.Serial()
        self.ser.baudrate = 115200
        self.ser.port = 'COM3'
        self.ser.open()
        print("Serial Aberta")
        

app = QtWidgets.QApplication(sys.argv)
window = Ui()
app.exec_()
