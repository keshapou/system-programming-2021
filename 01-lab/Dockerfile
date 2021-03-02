FROM alpine
COPY ./01sp19.sh .

RUN apk update

RUN adduser -S kesha -s /bin/sh
RUN echo "kesha:kesha" | chpasswd

RUN chmod +s 01sp19.sh

CMD ./01sp19.sh
