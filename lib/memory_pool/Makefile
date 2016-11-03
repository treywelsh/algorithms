TARGET = pool

#libs
TARGET_SO = lib$(TARGET).so
TARGET_ST = lib$(TARGET).a

#test
TARGET_TEST = test_$(TARGET)

CC ?= gcc
INCLUDE = -I. -I../../include
SRC = pool.c 
OBJ = $(SRC:.c=.o)
FPIC_OBJ = $(SRC:.c=.fpic.o)
CFLAGS ?= -Wall -Wextra
LDFLAGS ?=

#Mandatory flags
CFLAGS += ${INCLUDE}
LDFLAGS += 

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -O0 -g -fno-inline -fno-strict-aliasing
else
	CFLAGS += -DNDEBUG -O2 -fstrict-aliasing
endif

all: $(TARGET_SO) $(TARGET_ST)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

#static
$(TARGET_ST) : $(OBJ)
	$(AR) cru $@ $^
	
#shared
$(TARGET_SO) : $(FPIC_OBJ)
	$(CC) -shared $(LDFLAGS) -o $@ $<

%.fpic.o: %.c
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

#test
#test: $(TARGET_SO) $(TARGET_ST)
test: $(TARGET_ST)
	$(CC) -static $(CFLAGS) $(LDFLAGS) main.c $(TARGET_ST) -o $(TARGET_TEST)_static
	#$(CC) -static $(CFLAGS) $(LDFLAGS) main.c -L. -l$(TARGET) -o $@_static
	#$(CC) $(CFLAGS) $(LDFLAGS) main.c $(TARGET_SO) -o $@_shared

.PHONY: clean
clean :
	@rm -f $(OBJ) $(FPIC_OBJ) $(TARGET_SO) $(TARGET_ST) $(TARGET_TEST)_static main.o
