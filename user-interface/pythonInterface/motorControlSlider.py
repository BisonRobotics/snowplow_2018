# everything in this file runs on the base
# station computer, not the robot

import sys
from PyQt4 import QtGui, QtCore

class MotorControl(QtGui.QWidget):

    def __init__(self):
        super(MotorControl, self).__init__()
        self.uiSetup()

    def uiSetup(self):
        # LCD displays for each motor
        rMotorDisp = QtGui.QLCDNumber(self)
        lMotorDisp = QtGui.QLCDNumber(self)

        # slider for each motor
        global rMotorControl
        rMotorControl = QtGui.QSlider(QtCore.Qt.Vertical, self)
        rMotorControl.setMinimum(-1000)
        rMotorControl.setMaximum(1000)
        global lMotorControl
        lMotorControl = QtGui.QSlider(QtCore.Qt.Vertical, self)
        lMotorControl.setMinimum(-1000)
        lMotorControl.setMaximum(1000)

        # create a frame for the left motor display and a label
        lVFrame = QtGui.QVBoxLayout()
        lVFrame.addWidget(QtGui.QLabel('Left', self))
        lVFrame.addWidget(lMotorDisp)

        # create a frame for the right motor display and a label
        rVFrame = QtGui.QVBoxLayout()
        rVFrame.addWidget(QtGui.QLabel('Right', self))
        rVFrame.addWidget(rMotorDisp)

        # combine the left a right frames into one and add the slider widgets between
        mainHFrame = QtGui.QHBoxLayout()
        mainHFrame.addLayout(lVFrame)
        mainHFrame.addWidget(lMotorControl)
        mainHFrame.addWidget(rMotorControl)
        mainHFrame.addLayout(rVFrame)

        self.setLayout(mainHFrame)

        rMotorControl.valueChanged.connect(rMotorDisp.display)
        lMotorControl.valueChanged.connect(lMotorDisp.display)

        self.setGeometry(400, 400, 500, 300)
        self.show()

    # default keypress event handler
    def keyPressEvent(self, e):
        if e.key() == QtCore.Qt.Key_0:
            rMotorControl.setValue(0) # reset the sliders to zero
            lMotorControl.setValue(0)

def main():
    app = QtGui.QApplication(sys.argv)
    mainUI = MotorControl()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()

