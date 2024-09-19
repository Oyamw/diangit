CC = gcc
CFLAGS = -Wall

TARGETS = diangit_commit diangit_log

all: $(TARGETS)

diangit_commit: diangit_commit.c
	$(CC) $(CFLAGS) diangit_commit.c -o diangit_commit

diangit_log: diangit_log.c
	$(CC) $(CFLAGS) diangit_log.c -o diangit_log

clean:
	del $(TARGETS)

.PHONY: all clean
