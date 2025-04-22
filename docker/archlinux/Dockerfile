FROM archlinux:latest

RUN pacman -Syu --noconfirm --needed \
        python python-pip cmake git clang gcc \
        base-devel nodejs make \
    && pip install --no-cache-dir --break-system-packages conan \
    && pacman -Scc --noconfirm
