FROM fedora:latest

RUN dnf update -y \
    && dnf install -y --setopt=install_weak_deps=False git cmake \
    clang gcc which nodejs python3 python3-pip make awk wget \
    && pip3 install --no-cache-dir --break-system-packages conan \
    && dnf clean all \
    && rm -rf /var/cache/dnf

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64 && \
    chmod 755 bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/bin/bazelisk
