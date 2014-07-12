CFLAGS := -ggdb
INC := -I.
#CC := i686-pc-linux-gnu-gcc
CC := gcc

ifneq ($(V),)
	CFLAGS += -Wall
endif

all: bview

bview: bview.c
#	echo $(CC) $(CFLAGS) $(INC)
	$(CC) $(CFLAGS) $(INC) -o bview bview.c 
    
clean:
	rm -f bview

