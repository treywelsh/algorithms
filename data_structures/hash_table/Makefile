CC ?= gcc
CFLAGS ?= -Wall -Wextra
LDFLAGS ?=
DEBUG ?= 0
STATIC ?= 0
INCLUDE= -I ../../include/

TARGET = hash_test
#SRC = $(wildcard *.c)
SRC = hash.c main.c
OBJ = $(SRC:.c=.o)

ifeq ($(CC), clang)
	CFLAGS = -Weverything
	DEBUG = 1
endif

#Mandatory flags
CFLAGS += ${INCLUDE}

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -O0 -g -fno-inline
else
	CFLAGS += -DNDEBUG -O2 -fstrict-aliasing
endif

ifeq ($(STATIC), 1)
	LDFLAGS += -static
endif

all: $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS) $(CFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean :
	@rm -f $(OBJ) $(TARGET)
