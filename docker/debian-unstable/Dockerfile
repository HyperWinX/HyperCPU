FROM debian:unstable

RUN apt-get update && apt-get install -y --no-install-recommends \
        git cmake clang libre2-11 libre2-dev gnu-which nodejs python3 python3-pip make gcc g++ \
    && pip3 install --no-cache-dir --break-system-packages conan \
    && rm -rf /var/lib/apt/lists/*
