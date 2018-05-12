SRC    = main.c prime.c
TARGET = prime
OBJ    = $(SRC:.c=.o)
DEP    = $(OBJ:.o=.d)

CC     = gcc
CFLAGS = -O2 -g

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o:%.c | %.d
	$(CC) -c $< $(CFLAGS)

%.d: %.c
	$(CC) -MM -o $@ $<

-include $(DEP)

.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP) $(TARGET)
