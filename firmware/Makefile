FOLDER = /home/john/u8
CFLAGS = -g -Wall -I$(FOLDER)/csrc/.  -DU8G_16BIT `sdl-config --cflags`
CXXFLAGS = -g -Wall -I$(FOLDER)/csrc/. -I$(FOLDER)/cppsrc/. -DU8G_16BIT `sdl-config --cflags`

SRC = $(shell ls $(FOLDER)/csrc/*.c) $(shell ls $(FOLDER)/sfntsrc/*.c) $(FOLDER)/sys/sdl/dev/u8g_dev_sdl.c
CPPSRC = $(shell ls $(FOLDER)/cppsrc/*.cpp) main.cpp gui.cpp


OBJ = $(SRC:.c=.o)
CPPOBJ = $(CPPSRC:.cpp=.o)

sdl_firmware: $(OBJ) $(CPPOBJ) 
	$(LINK.cc) $(LDFLAGS) $(OBJ) $(CPPOBJ) `sdl-config --libs` -o sdl_firmware

clean:	
	-rm $(OBJ) $(CPPOBJ) sdl_firmware

