FROM debian

COPY ./main.cpp .

RUN apt update
RUN apt install -y build-essential gcc-multilib g++-multilib

RUN g++ -lm -o main main.cpp -pthread -ggdb3 

CMD ["/bin/sh"]