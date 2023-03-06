import sys

from PyQt5.QtWidgets import *


class OutputView(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()
        layout.addWidget(QLabel("运行结果："))

        self.outputView = QTextEdit()
        self.outputView.setReadOnly(True)

        layout.addWidget(self.outputView)

        self.exportBtn = QPushButton("导出结果")
        self.exportBtn.clicked.connect(self.export)
        layout.addWidget(self.exportBtn)

        self.setLayout(layout)

    def setOutputView(self, output):
        self.outputView.setText(output)

    def export(self):
        filename, t = QFileDialog.getSaveFileName(self, '导出结果', 'ans', "文本文件(*.txt)")
        if filename:
            with open(filename, 'w') as f:
                f.write(self.outputView.toPlainText())


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = OutputView()

    w.show()

    # 程序进入循环等待
    app.exec_()
