SRCS = rodcut.c inputreader.c keypair.c rodcutsolver.c vec.c
HDRS = inputreader.h keypair.h rodcutsolver.h vec.h

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: rodcut

rodcut: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

rodcut.o: rodcut.c inputreader.h keypair.h rodcutsolver.h vec.h

inputreader.o: inputreader.c inputreader.h

keypair.o: keypair.c keypair.h

rodcutsolver.o: rodcutsolver.c rodcutsolver.h

vec.o: vec.c vec.h

clean:
	rm -f rodcut $(OBJS) 