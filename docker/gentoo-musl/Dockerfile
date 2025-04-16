FROM gentoo/stage3:musl

RUN emerge --sync > /dev/null
RUN getuto
RUN sed -i 's/^MAKEOPTS=".*"/MAKEOPTS="& -j8"/' /etc/portage/make.conf
RUN emerge llvm-core/clang cmake gtest re2 libfmt dev-vcs/git nodejs --getbinpkg -j2
