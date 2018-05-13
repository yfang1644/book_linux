CC     = gcc
TARGET = win

$(TARGET): $(TARGET).c
	$(CC) -o $@ $< `pkg-config libglade-2.0 --cflags --libs` -rdynamic

clean: 
	$(RM) $(TARGET)
