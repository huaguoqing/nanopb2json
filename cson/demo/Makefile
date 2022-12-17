INC += -I../3rd/inc
INC += -I../inc
LIB_PATH += -L../3rd/lib
LIB_PATH += -L../output
CC=gcc
CSON_C := ../script/cson-c.sh

CFLAGS :=  $(INC) -Wno-int-conversion
CFLAGS += -g 
#CFLAGS += USING_NO_CSON_REF_TBL    

LDFLAGS := $(LIB_PATH) -lcson -ljansson

SRC := test.c test2.c main.c test.h.cson_ref_tbl.c test2.h.cson_ref_tbl.c 

test: 
	$(CSON_C) test.h
	$(CSON_C) test2.h
	@$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

clean:
	@rm -rf test *.o *.cson_ref_tbl.*

