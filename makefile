INT=Iflog.h Stats.h main.h
REAL=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
EXE=bin/analog
LIBS=
CPPFLAGS= -Wall -ansi -pedantic -std=c++11
DMAP=#-DMAP
ECHO=@echo

%.o:%.cpp
	g++ $(CPPFLAGS) $(DMAP) -c $< -o $@

$(EXE):$(OBJ)
	g++ -o $(EXE) $(OBJ) $(LIBS)

clean:
	rm -f *.o $(EXE)
