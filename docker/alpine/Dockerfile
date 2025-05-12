FROM alpine:latest

ARG BAZELISK_TAG=v1.15.0

RUN apk update \
    && apk add --no-cache python3 py3-pip clang gcc git cmake make ninja grep g++ linux-headers wget \
    && pip3 install --no-cache-dir --break-system-packages conan

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64 && \
    chmod 755 bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/bin/bazelisk
