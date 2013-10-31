TARGET           = pdf-show-highlights
OBJS             = pdf-show-highlights.o
CC               = gcc

PKG_CONFIG       = pkg-config
PACKAGES         = poppler-glib

PC_CFLAGS       := $(shell $(PKG_CONFIG) $(PACKAGES) --cflags)
PC_LIBS         := $(shell $(PKG_CONFIG) $(PACKAGES) --libs)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(PC_CFLAGS) $(LDFLAGS) $(PC_LIBS)

%.o : %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(PC_CFLAGS)

clean :
	rm $(TARGET) $(OBJS)
