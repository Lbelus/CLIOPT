FROM ubuntu:latest

ENV DEBIAN_FRONTEND=non-interactive

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    llvm\
    libssl-dev \
    clang \
    cmake \
    git \
    wget \
    unzip \
    pkg-config \
    nasm

# Clean up to reduce image size
RUN   apt-get autoremove -y && \
      apt-get clean

ENV DEBIAN_FRONTEND=

WORKDIR /workspace
CMD ["bash"]
