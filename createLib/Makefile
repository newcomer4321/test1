redisThreadPath= .
SUBDIRS= .
REDIS_SRC = ../..
OBJS += \
        $(patsubst $(redisThreadPath)/%.c,%.o,$(foreach dir,$(SUBDIRS), $(sort $(wildcard $(redisThreadPath)/$(dir)/*.c))))

#target=../lib/testlib.a

SOURCE=  $(wildcard $(redisThreadPath)/*.c)

SOURCE += $(REDIS_SRC)/zmalloc.c $(REDIS_SRC)/adlist.c

target=../lib/testlib.so

test=test

$(target):$(OBJS)
	gcc -fPIC -shared -o $(target) $(SOURCE)


$(test):$(SOURCE)
	gcc -g  -o $(test)  $(SOURCE)
clean:
	rm -rf $(OBJS) $(target) $(test) 
