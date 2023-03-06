import sys
import re

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

from InputView import InputView
from OptionView import OptionView
from OutputView import OutputView
from WarningView import WarningView


class MainView(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("WordChain")
        layout = QHBoxLayout()

        IOView = QGroupBox()
        IOLayout = QVBoxLayout()

        self.inputView = InputView()
        self.outputView = OutputView()
        IOLayout.addWidget(self.inputView)
        IOLayout.addWidget(self.outputView)

        IOView.setLayout(IOLayout)

        optionView = QGroupBox()
        optionLayout = QVBoxLayout()

        self.option = OptionView()
        self.confirmBtn = QPushButton("开始计算")
        self.confirmBtn.clicked.connect(self.confirm)

        self.runTime = QLabel("运行时间：")

        optionLayout.addWidget(self.option)
        optionLayout.addWidget(self.confirmBtn)
        optionLayout.addWidget(self.runTime)
        optionView.setLayout(optionLayout)
        layout.addWidget(IOView)
        layout.addWidget(optionView)

        self.setLayout(layout)

    def getWords(self):
        temp = self.inputView.getInputData()
        pattern = re.compile("[a-zA-Z]{2,}")
        words = pattern.findall(temp)
        return words

    def confirm(self):
        model, head, tail, banLetter, enableLoop = self.option.getOption()
        # print(model, beginLetter, endLetter, banLetter, enableLoop)
        words = self.getWords()
        print(words)
        # todo 调用计算函数
        result = "xxx"
        self.outputView.setOutputView(result)
        warn = WarningView("出现了blabla错误")
        warn.show()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = MainView()

    w.show()

    # 程序进入循环等待
    app.exec_()
