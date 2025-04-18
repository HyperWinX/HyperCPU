FROM gentoo/stage3:systemd

RUN emerge --sync > /dev/null && \
    getuto && \
    emerge llvm-core/clang cmake dev-vcs/git re2 libfmt gtest which nodejs --getbinpkg -j2
