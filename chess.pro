QT += widgets
#requires(qtConfig(filedialog))

HEADERS     = mainwindow.h \
              boardwidget.h \
              homepage.h \
              timer.h
RESOURCES   = \
    resources.qrc
SOURCES     = main.cpp \
              boardwidget.cpp \
              homepage.cpp \
              mainwindow.cpp \
              timer.cpp

#QMAKE_PROJECT_NAME = dndpuzzle


#INSTALLS += target
