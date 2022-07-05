PLATFORM := $(shell uname)
ifeq ($(OS),Windows_NT) #WINDOWS
6502CPU: 6502cpu.o bus.o main.o
	g++ 6502cpu.o bus.o main.o -o 6502CPU -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17
	make clean

6502cpu.o: 6502cpu.cpp
	g++ -c 6502cpu.cpp

bus.o: bus.cpp
	g++ -c bus.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	del *.o
else ifeq ($(PLATFORM),Linux) #LINUX
6502CPU: 6502cpu.o bus.o main.o
	g++ 6502cpu.o bus.o main.o -o 6502CPU -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
	make clean

6502cpu.o: 6502cpu.cpp
	g++ -c 6502cpu.cpp

bus.o: bus.cpp
	g++ -c bus.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o
else #MACOS
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),x86_64)
6502CPU: 6502cpu.cpp bus.cpp main.cpp
	clang++ -arch x86_64 -std=c++17 -mmacosx-version-min=10.15 -framework OpenGL -framework GLUT -framework Carbon -lpng 6502cpu.cpp bus.cpp main.cpp -o 6502CPU  
else
6502CPU: 6502cpu.cpp bus.cpp main.cpp
	clang++  -I/opt/homebrew/Cellar/libpng/1.6.37/include -L/opt/homebrew/Cellar/libpng/1.6.37/lib/  -std=c++17 -mmacosx-version-min=10.15 -framework OpenGL -framework GLUT -framework Carbon -lpng 6502cpu.cpp bus.cpp main.cpp -o 6502CPU
endif
endif