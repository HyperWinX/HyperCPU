FROM hyperwin/hcpu-ci:gentoo-musl-build

ARG BAZELISK_TAG=v1.15.0

RUN emerge llvm-core/clang --getbinpkg && \
    rm -rf /var/lib/repos/gentoo

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64 && \
    chmod 755 bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/bin/bazelisk
