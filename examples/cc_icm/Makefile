HEADERS = icm.h \
	icmIo.h \
	icm_env.h \
	encode.h
SOURCES = icm_env.cc \
	encode.cc \
	main.cc
OBJECTS = icm_env.o \
	encode.o \
	main.o

TARGET = ccicm

INCPATH  = -I. -I/opt/icm/include
LIBS     = -pthread -L/opt/icm/lib -licm


.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<


all: $(TARGET)

$(TARGET) : $(OBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

