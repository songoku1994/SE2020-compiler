FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc copmpiler.cpp -o program
RUN chmod +x program
