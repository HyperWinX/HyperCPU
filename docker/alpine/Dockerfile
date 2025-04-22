FROM alpine:latest


RUN apk update && \
    apk add --no-cache python3 py3-pip clang gcc git cmake make \
        ninja nodejs grep g++ \
    && pip3 install --no-cache-dir --break-system-packages conan