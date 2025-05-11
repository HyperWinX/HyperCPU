FROM gentoo/stage3:systemd

ARG BAZELISK_TAG=v1.15.0

RUN emerge --sync > /dev/null && \
    getuto && \
    emerge llvm-core/clang cmake dev-vcs/git re2 libfmt gtest which wget conan --getbinpkg -j2 && \
    rm -rf /var/lib/repos/gentoo

RUN wget https://github.com/bazelbuild/bazelisk/releases/download/${BAZELISK_TAG}/bazelisk-linux-amd64 && \
    chmod 755 bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/bin/bazelisk
