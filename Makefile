CC			= g++

TARGET		= space

$(TARGET):	main.o init.o draw.o font.o
	$(CC) -o $(TARGET) main.o init.o draw.o font.o `sdl-config --libs` -lGL -lGLU -lm -lSDL_mixer -lpthread

main.o:		main.cc main.h 
	$(CC) -c main.cc `sdl-config --cflags`
	
init.o:		init.cc main.h 
	$(CC) -c init.cc `sdl-config --cflags`

draw.o:		draw.cc main.h 
	$(CC) -c draw.cc `sdl-config --cflags`

font.o:		font.cc main.h 
	$(CC) -c font.cc `sdl-config --cflags`
	
clean:
	rm -f $(TARGET) main.o init.o draw.o font.o
