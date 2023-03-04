import sys

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


class OptionView(QWidget):
    # _model: 0 -n
    #         1 -w
    #         2 -c
    _model = 0

    def __init__(self):
        super().__init__()
        layout = QVBoxLayout()

        model = QGroupBox()
        modelLayout = QVBoxLayout()
        self.allBtn = QRadioButton("所有单词链 -n")
        self.allBtn.setChecked(True)
        self.wordBtn = QRadioButton("最多单词数量的单词链 -w")
        self.letterBtn = QRadioButton("最多字母数量的单词链 -c")

        self.allBtn.clicked.connect(self.clickAllBtn)
        self.wordBtn.clicked.connect(self.clickWordBtn)
        self.letterBtn.clicked.connect(self.clickLetterBtn)

        modelLayout.addWidget(self.allBtn)
        modelLayout.addWidget(self.wordBtn)
        modelLayout.addWidget(self.letterBtn)
        model.setLayout(modelLayout)
        layout.addWidget(model)

        addition = QGroupBox()
        additionLayout = QVBoxLayout()

        beginWidget = QWidget()
        beginLayout = QHBoxLayout()
        # self.beginCheck = QCheckBox("指定单词链开头字母：")
        self.beginCharBox = QComboBox()
        self.beginCharBox.addItem("任意")
        for c in range(ord('a'), ord('z')):
            self.beginCharBox.addItem(chr(c))
        beginLayout.addWidget(QLabel("指定单词链开头字母："))
        beginLayout.addWidget(self.beginCharBox)
        beginWidget.setLayout(beginLayout)

        endWidget = QWidget()
        endLayout = QHBoxLayout()
        self.endCharBox = QComboBox()
        self.endCharBox.addItem("任意")
        for c in range(ord('a'), ord('z')):
            self.endCharBox.addItem(chr(c))
        endLayout.addWidget(QLabel("指定单词链结尾字母："))
        endLayout.addWidget(self.endCharBox)
        endWidget.setLayout(endLayout)

        banWidget = QWidget()
        banLayout = QHBoxLayout()
        self.banCharBox = QComboBox()
        self.banCharBox.addItem("---")
        for c in range(ord('a'), ord('z')):
            self.banCharBox.addItem(chr(c))
        banLayout.addWidget(QLabel("禁止单词链所有单词首字母："))
        banLayout.addWidget(self.banCharBox)
        banWidget.setLayout(banLayout)

        self.circleBtn = QCheckBox("允许单词环")

        self.beginCharBox.setEnabled(False)
        self.endCharBox.setEnabled(False)
        self.banCharBox.setEnabled(False)
        self.circleBtn.setEnabled(False)
        additionLayout.addWidget(self.circleBtn)
        additionLayout.addWidget(beginWidget)
        additionLayout.addWidget(endWidget)
        additionLayout.addWidget(banWidget)
        addition.setLayout(additionLayout)
        layout.addWidget(addition)
        self.setLayout(layout)

    def clickAllBtn(self):
        self._model = 0
        self.beginCharBox.setEnabled(False)
        self.beginCharBox.setCurrentIndex(0)
        self.endCharBox.setEnabled(False)
        self.endCharBox.setCurrentIndex(0)
        self.banCharBox.setEnabled(False)
        self.banCharBox.setCurrentIndex(0)
        self.circleBtn.setEnabled(False)
        self.circleBtn.setChecked(False)

    def clickWordBtn(self):
        self._model = 1
        self.beginCharBox.setEnabled(True)
        self.endCharBox.setEnabled(True)
        self.banCharBox.setEnabled(True)
        self.circleBtn.setEnabled(True)

    def clickLetterBtn(self):
        self._model = 2
        self.beginCharBox.setEnabled(True)
        self.endCharBox.setEnabled(True)
        self.banCharBox.setEnabled(True)
        self.circleBtn.setEnabled(True)

    def getOption(self):
        model = self._model
        beginLetter = self.beginCharBox.currentText()
        if len(beginLetter) > 1:
            beginLetter = '0'
        endLetter = self.endCharBox.currentText()
        if len(endLetter) > 1:
            endLetter = '0'
        banLetter = self.banCharBox.currentText()
        if len(banLetter) > 1:
            banLetter = '0'
        enableLoop = self.circleBtn.isChecked()
        return model, beginLetter, endLetter, banLetter, enableLoop


if __name__ == "__main__":
    app = QApplication(sys.argv)

    w = OptionView()

    w.show()

    # 程序进入循环等待
    app.exec_()
