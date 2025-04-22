FROM debian:latest

RUN apt-get update && apt-get install -y --no-install-recommends \
        git cmake clang gcc g++ nodejs python3 python3-pip make \
    && pip3 install --no-cache-dir --break-system-packages conan \
    && rm -rf /var/lib/apt/lists/*
