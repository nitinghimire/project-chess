QT += widgets
#requires(qtConfig(filedialog))

HEADERS     = mainwindow.h \
              boardwidget.h \
              homepage.h
RESOURCES   = \
    resources.qrc
SOURCES     = main.cpp \
              boardwidget.cpp \
              homepage.cpp \
              mainwindow.cpp

#QMAKE_PROJECT_NAME = dndpuzzle


#INSTALLS += target
