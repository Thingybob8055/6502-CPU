ifeq ($(OS),Windows_NT)
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
else
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
endif