CC := gcc

SRC := ./main.c
OBJ = $(SRC:%.c=%.o)

TARGET = a.out

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	$(RM) $(OBJ) $(TARGET)

