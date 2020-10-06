FROM g++:10
WORKDIR /app/
COPY ./* ./
RUN gcc compiler.cpp -o program
RUN chmod +x program
