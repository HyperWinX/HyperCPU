FROM fedora:latest

RUN dnf update -y \
    && dnf install -y --setopt=install_weak_deps=False git cmake \
        clang gcc which nodejs python3 python3-pip make \
    && pip3 install --no-cache-dir --break-system-packages conan \
    && dnf clean all \
    && rm -rf /var/cache/dnf
