FROM gentoo/stage3:systemd

RUN emerge --sync > /dev/null && \
    getuto && \
    emerge llvm-core/clang cmake dev-vcs/git re2 libfmt gtest which nodejs conan --getbinpkg -j2 &&
    rm -rf /var/lib/repos/gentoo
