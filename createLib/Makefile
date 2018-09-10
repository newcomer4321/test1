redisThreadPath= .
SUBDIRS= .
OBJS += \
        $(patsubst $(redisThreadPath)/%.c,%.o,$(foreach dir,$(SUBDIRS), $(sort $(wildcard $(redisThreadPath)/$(dir)/*.c))))

#target=../lib/testlib.a

SOURCE= $(foreach dir,$(SUBDIRS), $(sort $(wildcard $(redisThreadPath)/$(dir)/*.c)))
#$(target):$(OBJS)
#	ar -cr  $@ $^

target=../lib/testlib.so

$(target):$(OBJS)
	gcc -fPIC -shared -o $(target) $(SOURCE)


clean:
	rm -rf $(OBJS) $(target)
