redisThreadPath= .
SUBDIRS= .
REDIS_SRC = ../..
OBJS += \
        $(patsubst $(redisThreadPath)/%.c,%.o,$(foreach dir,$(SUBDIRS), $(sort $(wildcard $(redisThreadPath)/$(dir)/*.c))))

#target=../lib/testlib.a

STD=-std=c99 -pedantic -DREDIS_STATIC=''
#WARN=-Wall -W -Wno-missing-field-initializers

FINAL_CFLAGS=$(STD)
FINAL_LDFLAGS+= -rdynamic
FINAL_LIBS+=-ldl -pthread -lrt
FINAL_CFLAGS+= -DUSE_JEMALLOC -I../../../deps/jemalloc/include
FINAL_CFLAGS+= -I../../../deps/hiredis -I../../../deps/linenoise -I../../../deps/lua/src

SOURCE=  $(wildcard $(redisThreadPath)/*.c)

SOURCE += $(REDIS_SRC)/zmalloc.c $(REDIS_SRC)/adlist.c $(REDIS_SRC)/server.c

target=../lib/testlib.so

test=test

$(target):$(OBJS)
	gcc -fPIC -shared -o $(target) $(SOURCE)


$(test):$(SOURCE)
	gcc -g  -o $(test)  $(SOURCE) -lpthread -I../../ $(FINAL_CFLAGS)
clean:
	rm -rf $(OBJS) $(target) $(test) 
