FROM debian
COPY ./03sp19.cpp .

RUN apt update
RUN apt install -y build-essential gcc-multilib g++-multilib

RUN g++ -m32 -o lab03 03sp19.cpp

CMD ["/bin/sh"]

