BIN = fat
OBJ = ${BIN}.o
TEST = fat_test
TESTOBJ = ${TEST}.o
FUSE = -I/usr/local/include -D_FILE_OFFSET_BITS=64
CFLAGS = -g -O0 -Wall -Wextra -std=c99 ${FUSE}
LDFLAGS = -L/usr/local/lib -lfuse

${BIN} : ${OBJ}
	${CC} ${LDFLAGS} ${OBJ} -o $@
${TEST} : ${TESTOBJ}
	${CC} ${LDFLAGS} ${TESTOBJ} -o $@
%.o : %.c
	${CC} -c $<
clean :
	rm ${OBJ} ${BIN} ${TESTOBJ} ${TEST}