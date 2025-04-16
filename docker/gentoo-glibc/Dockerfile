FROM gentoo/stage3:systemd

RUN emerge --sync
RUN getuto
RUN emerge llvm-core/clang cmake dev-vcs/git re2 libfmt gtest which --getbinpkg
RUN source /etc/profile
