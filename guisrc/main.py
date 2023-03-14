import sys
from PyQt5.QtWidgets import QApplication

from MainView import MainView

if __name__ == '__main__':
    app = QApplication(sys.argv)

    w = MainView()
    w.show()

    # 程序进入循环等待
    app.exec_()
