FROM alpine:3
RUN apk add cmake gcc g++ libgcc build-base make --no-cache
WORKDIR /app/
COPY ./* ./
RUN g++ compiler.cpp -o main
RUN chmod +x main
