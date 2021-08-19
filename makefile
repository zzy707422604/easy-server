src = $(wildcard *.c)
target = $(patsubst %.c, % ,$(src))

ALL:$(target)

%:%.c
	gcc -g -Wall -D_GNU_SOURCE -lpthread $< -o $@

clean:
	-rm -rf $(target)

.PHONY: clean ALL
