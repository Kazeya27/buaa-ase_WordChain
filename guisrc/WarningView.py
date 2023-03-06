from PyQt5.QtWidgets import *


class WarningView(QWidget):
    def __init__(self, msg):
        super().__init__()
        warn = QMessageBox()
        warn.setText(msg)
        warn.setIcon(QMessageBox.Critical)
        warn.setWindowTitle("异常提示")
        warn.exec_()

