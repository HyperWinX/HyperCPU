FROM ubuntu:latest

RUN apt update && apt install -y --no-install-recommends \
    git cmake clang libre2-10 libre2-dev python3 python3-pip make gcc g++ \
    && pip3 install --no-cache-dir --break-system-packages conan \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64 && \
    chmod 755 bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/bin/bazelisk

RUN useradd -m ${USER}

WORKDIR /home/${USER}/workspace
USER ${USER}
