FROM alpine
COPY ./asm-lab02_x64.s .
COPY ./cpp-lab02.cpp .
COPY ./c-lab02.c . 

RUN apk update
RUN apk add build-base musl-dev libc-dev gdb

RUN g++ cpp-lab02.cpp -static -o cpp-lab02
RUN gcc c-lab02.c -static -o c-lab02
RUN gcc -m64 -fno-pie -no-pie asm-lab02_x64.s -o asm-lab02 -g 

CMD ["/bin/sh"]

