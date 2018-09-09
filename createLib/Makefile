redisThreadPath= .
SUBDIRS= .
OBJS += \
        $(patsubst $(redisThreadPath)/%.c,%.o,$(foreach dir,$(SUBDIRS), $(sort $(wildcard $(redisThreadPath)/$(dir)/*.c))))

target=../lib/testlib.so


$(target):$(OBJS)
	ar -cr  $@ $^

clean:
	rm -rf $(OBJS) $(target)
