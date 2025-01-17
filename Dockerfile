# 베이스 이미지로 Ubuntu 22.04 사용
FROM ubuntu:22.04

# 시스템 패키지 업데이트 및 기본 도구 설치
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    autoconf \
    automake \
    libtool \
    curl \
    make \
    gcc-12 \
    g++-12 \
    unzip \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# 작업 디렉토리 생성
WORKDIR /tmp

# Protobuf 3.20.3 설치
RUN wget https://github.com/protocolbuffers/protobuf/releases/download/v3.20.3/protobuf-cpp-3.20.3.tar.gz \
    && tar -xzf protobuf-cpp-3.20.3.tar.gz \
    && cd protobuf-3.20.3 \
    && ./configure \
    && make -j$(nproc) \
    && make install \
    && ldconfig \
    && cd .. \
    && rm -rf protobuf-3.20.3 protobuf-cpp-3.20.3.tar.gz

# Protobuf 설치 확인
RUN protoc --version && \
    ldconfig -p | grep libproto

# Boost 1.83.0 설치
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.tar.gz \
    && tar -xzf boost_1_83_0.tar.gz \
    && cd boost_1_83_0 \
    && ./bootstrap.sh \
    && ./b2 install --with=all -j$(nproc) \
    && cd .. \
    && rm -rf boost_1_83_0 boost_1_83_0.tar.gz

# Boost 설치 확인
RUN ls /usr/local/include/boost/version.hpp && \
    cat /usr/local/include/boost/version.hpp | grep "BOOST_LIB_VERSION" && \
    ls /usr/local/lib/libboost*

# spdlog 설치 (최신 버전)
RUN git clone https://github.com/gabime/spdlog.git \
    && cd spdlog \
    && mkdir build && cd build \
    && cmake .. \
    && make -j$(nproc) \
    && make install \
    && ldconfig \
    && cd ../.. \
    && rm -rf spdlog

# 프로젝트 디렉토리 생성
WORKDIR /app

# 볼륨 마운트 포인트 생성
VOLUME ["/app"]

# 기본 명령어 설정
CMD ["/bin/bash"]


