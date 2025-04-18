FROM gentoo/stage3:musl

RUN emerge --sync > /dev/null && \
    getuto  && \
    sed -i 's/^MAKEOPTS=".*"/MAKEOPTS="& -j8"/' /etc/portage/make.conf  && \
    emerge llvm-core/llvm cmake gtest re2 libfmt dev-vcs/git --getbinpkg
