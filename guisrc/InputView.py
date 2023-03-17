import sys

from PyQt5.QtWidgets import *

from WarningView import WarningView


class InputView(QWidget):
    def __init__(self):
        super().__init__()
        container = QVBoxLayout()

        fileBox = QGroupBox()
        fileLayout = QHBoxLayout()
        fileLayout.addWidget(QLabel("从文件导入:"))
        self.filePath = QLineEdit()
        self.filePath.setReadOnly(True)
        fileLayout.addWidget(self.filePath)
        self.fileBtn = QPushButton("选择文件")
        self.fileBtn.clicked.connect(self.getFile)
        fileLayout.addWidget(self.fileBtn)

        fileBox.setLayout(fileLayout)
        container.addWidget(fileBox)

        self.inputBox = QTextEdit()
        container.addWidget(self.inputBox)

        self.setLayout(container)

    def getFile(self):
        filename, t = QFileDialog.getOpenFileName(self, "打开文件", '', '文本文件(*.txt)')
        # 防止取消打开文件后闪退
        if filename:
            if not filename.endswith(".txt"):
                WarningView("请选择txt文件输入")
            else:
                self.filePath.setText(filename)
                with open(filename, 'r', encoding='utf-8', errors='ignore') as f:
                    data = f.read()
                self.inputBox.setText(data)

    def getInputData(self):
        return self.inputBox.toPlainText()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = InputView()

    w.show()

    # 程序进入循环等待
    app.exec_()
