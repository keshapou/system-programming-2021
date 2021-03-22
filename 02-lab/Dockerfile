FROM alpine
COPY ./asm-lab02.s .

RUN apk update
RUN apk add build-base musl-dev libc-dev gdb

RUN gcc -m64 -fno-pie -no-pie asm-lab02.s -o asm-lab02 -g 

CMD ["/bin/sh"]