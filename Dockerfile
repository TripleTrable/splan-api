FROM docker.io/archlinux:multilib-devel-20240101.0.204074

LABEL \
    org.opencontainers.image.title="yocto" \
    org.opencontainers.image.description="Docker container to build Yocto Scarthgap" \
    org.opencontainers.image.source="https://github.com/TripleTrable/gaia-image" \
    org.opencontainers.image.licenses="MIT"

RUN pacman -Syu --noconfirm && pacman -S cjson libmicrohttpd --noconfirm

COPY build/src/ /app/

CMD ["/app/splan-server"]
#CMD ["/bin/bash"]
