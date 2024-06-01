CC=gcc
LDC=gcc
LD_FLAGS = -lstdc++ -lopencv_core -lopencv_highgui -lopencv_imgproc
FLAGS= -I/usr/include/opencv4  # Update this line to include the directory
PROGC = test.cx
OBJSC = stegoC.o imgC.o

RM = /bin/rm

#all rule
all: $(PROGC)

$(PROGC): $(OBJSC)
	$(LDC) $^ $(LD_FLAGS) -o $@

%C.o: %.c*
	$(CC) $(FLAGS) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o $(PROGC) *.mod
