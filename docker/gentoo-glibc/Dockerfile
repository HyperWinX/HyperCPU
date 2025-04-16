FROM gentoo/stage3:systemd

RUN emerge --sync > /dev/null
RUN getuto
RUN emerge llvm-core/clang cmake dev-vcs/git re2 libfmt gtest which nodejs --getbinpkg
RUN source /etc/profile
