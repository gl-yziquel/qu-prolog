
TEMPLATE = app
INCLUDEPATH += .

# Input
HEADERS += interact.h qpconfig.h qthelp.h term.h xqp.h xqpqueries.h
SOURCES += interact.cc \
           main.cc \
           qpconfig.cc \
           qthelp.cc \
           term.cc \
           xqp.cc \
           xqpqueries.cc
#The following line was inserted by qt3to4
QT +=  qt3support 
