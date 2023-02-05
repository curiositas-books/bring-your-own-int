FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-22.04

RUN apt-get update \
 && apt-get install -y \
                catch2 \
                gdb \
                gnuplot \
                mold \
                python3-pip \
 && apt-get autoremove -y cmake \
 && pip3 install \
                cmake==3.23.3 \
                meson==1.0.0
