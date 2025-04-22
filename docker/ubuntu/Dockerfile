FROM ubuntu:latest

RUN apt update && apt install -y --no-install-recommends \
        git cmake clang libre2-9 libre2-dev gcc g++ nodejs python3 make python3-pip \
    && pip3 install --no-cache-dir --break-system-packages conan \
    && rm -rf /var/lib/apt/lists/*
