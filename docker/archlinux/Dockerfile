FROM archlinux:latest

ARG USER=bazel
ARG BAZELISK_TAG=v1.15.0

RUN pacman -Syu --noconfirm --needed \
    python python-pip git cmake clang gcc \
    base-devel wget \
    && pip install --no-cache-dir --break-system-packages conan \
    && pacman -Scc --noconfirm

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64 && \
    chmod 755 bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/bin/bazelisk

RUN useradd -m ${USER} && \
    mkdir /home/${USER}/workspace && \
    chown ${USER}:${USER} /home/${USER}/workspace

USER ${USER}
WORKDIR /home/${USER}/workspace
