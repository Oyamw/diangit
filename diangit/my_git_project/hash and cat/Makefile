CC = gcc
CFLAGS = -Wall

TARGETS = diangit_hash_object diangit_cat_file

all: $(TARGETS)

diangit_hash_object: hash_object.c
	$(CC) $(CFLAGS) hash_object.c -o diangit_hash_object

diangit_cat_file: cat_file.c
	$(CC) $(CFLAGS) cat_file.c -o diangit_cat_file

clean:
	del diangit_hash_object.exe diangit_cat_file.exe

.PHONY: all clean

