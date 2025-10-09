FROM debian:trixie


RUN dpkg --add-architecture armhf && \
    dpkg --add-architecture arm64 && \
    apt-get update && apt-get install -y \
    build-essential pkg-config \
    gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf \
    gcc-aarch64-linux-gnu g++-aarch64-linux-gnu \
    libbluetooth-dev:armhf libbluetooth-dev:arm64 \
    qemu-user && \
    apt-get clean

WORKDIR /ble_comm
COPY Makefile .
COPY src/ ./src

VOLUME ["/ble_comm/build"]

CMD ["bash", "-c", "make ARCH=arm32 && make ARCH=arm64 && make ARCH=x86_64"]
