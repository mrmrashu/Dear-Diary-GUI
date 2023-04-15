
CC  = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
APP = index
LIBS = `pkg-config --libs gtk+-3.0`

${APP}: ${APP}.c
	${CC} ${CFLAGS} -o ${APP} ${APP}.c ${LIBS} 

clean: 
	rm ${APP}