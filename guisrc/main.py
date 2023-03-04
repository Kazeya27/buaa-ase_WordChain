import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLabel, QLineEdit

from MainView import MainView

# todo 异常提示

if __name__ == '__main__':
    app = QApplication(sys.argv)

    w = MainView()
    w.show()

    # 程序进入循环等待
    app.exec_()