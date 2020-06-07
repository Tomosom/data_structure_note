CC := g++

SRC += ./main.cpp

OBJ = $(SRC:%.cpp=%.o)

TARGET = a.out

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	$(RM) $(OBJ) $(TARGET)

