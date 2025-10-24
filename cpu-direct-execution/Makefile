CC = gcc
CFLAGS = -O2 -Wall -Wextra
TARGETS = test-syscall test-syscall-2 test-context-switch

all: $(TARGETS)

test-syscall: test-syscall.c
	$(CC) $(CFLAGS) $< -o $@

test-syscall-2: test-syscall-2.c
	$(CC) $(CFLAGS) $< -o $@

test-context-switch: test-context-switch.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
