CC=g++
EXE=grav
LE=gravitacion
LIB=lib$(LE).so
LPY=_$(LE).so
flags = -std=c++11 -Wall -Wextra -Wundef -Wuninitialized -Winit-self

#la libreria de Python
$(LPY): $(LE).i $(LE).o
	swig -python -c++ $(LE).i
	g++ -fPIC -c $(LE)_wrap.cxx cuerpo.cpp -I/usr/include/python3.6/
	g++ -shared $(LE).o cuerpo.o $(LE)_wrap.o -o $(LPY)

$(EXE): main.o $(LIB) libcuerpo.so
	$(CC) $(flags) -o $(EXE) -Wl,-rpath=. main.o -L. -l$(LE) -lcuerpo

main.o: main.cpp $(LE).h cuerpo.h
	$(CC) $(flags) -c -o main.o main.cpp

$(LIB): $(LE).o
	$(CC) -shared $(LE).o -o $(LIB)

libcuerpo.so: cuerpo.o
	$(CC) -shared cuerpo.o -o libcuerpo.so

$(LE).o: $(LE).cpp $(LE).h
	$(CC) $(flags) -c -fPIC -o $(LE).o $(LE).cpp

cuerpo.o: cuerpo.cpp cuerpo.h
	$(CC) $(flags) -c -fPIC -o cuerpo.o cuerpo.cpp

clean:
	rm -f *.o *.so *.cxx $(LIB) $(LE).py $(EXE) *.pyc
	rm -f -r __pycache__/

run: $(EXE)
	./$(EXE)
