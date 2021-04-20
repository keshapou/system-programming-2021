FROM debian
COPY ./second.cpp .
COPY ./first.cpp .

RUN apt update
RUN apt install -y build-essential gcc-multilib g++-multilib

RUN g++ -lm -o first first.cpp
RUN g++ -lm -o second second.cpp

CMD ["/bin/sh"]

