from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.uic import *
import sys
import serial
from time import sleep


# Work thread
class WorkerThread(QObject):
    
    signal = pyqtSignal()
    def __init__(self):
        super().__init__()
    
    @pyqtSlot()
       
    def run(self):
        self.ser = serial.Serial()
        self.ser.baudrate = 115200
        self.ser.port = 'COM3'
        self.ser.open()
        print("Serial Aberta")
        while True:
            ser_bytes = self.ser.readline()
            decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
            #  print(decoded_bytes)
            if decoded_bytes == 1:
                self.signal.emit()
            else:
                pass


class Ui(QMainWindow):
    global voltas
    voltas = 0

    def __init__(self):
        super(Ui, self).__init__()
        loadUi('ihm.ui', self)
        self.worker = WorkerThread()
        self.workerThread = QThread()
        self.workerThread.started.connect(self.worker.run)  # Init worker run() at startup (optional)
        self.worker.signal.connect(self.mais)  # Connect your signals/slots
        self.worker.moveToThread(self.workerThread)  # Move the Worker object to the Thread object
        self.workerThread.start()
        self.show()
      
        # Botões
        self.bt_mais = self.findChild(QPushButton, 'bt_mais')
        self.bt_menos = self.findChild(QPushButton, 'bt_menos')
        self.bt_zerar = self.findChild(QPushButton, 'bt_zerar')

        self.bt_mais.clicked.connect(self.mais)
        self.bt_menos.clicked.connect(self.menos)
        self.bt_zerar.clicked.connect(self.zerar)

        # Display
        self.display = self.findChild(QLCDNumber, 'display')

        # Input números de voltas
        self.LE_voltas = self.findChild(QLineEdit, 'LE_voltas')


        # Barra de progresso
        self.barra = self.findChild(QProgressBar, 'barra')
        self.barra.setValue(0)
        self.barra.hide()
            
    def mais(self):
        global voltas
        voltas +=1
        self.display.display(voltas)
        self.progresso()
            
    def menos(self):
        global voltas
        voltas -=1
        if voltas == -1:
            voltas = 0
        self.display.display(voltas)
        self.progresso()
        
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

app = QApplication(sys.argv)
window = Ui()
app.exec_()
