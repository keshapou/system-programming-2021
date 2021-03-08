FROM alpine
COPY ./01sp19.sh .

RUN adduser -S kesha -s /bin/sh
RUN echo "kesha:kesha" | chpasswd

RUN chmod u+s 01sp19.sh

CMD ./01sp19.sh
