#!/bin/bash

# 更新包管理器
sudo apt update -y

# 安装gcc、g++、cmake、gdb
sudo apt install -y gcc g++ cmake gdb

# 安装FFmpeg
sudo apt install -y ffmpeg

# 安装python3的开发库
sudo apt install -y python3-dev

# 安装FFmpeg的开发库
sudo apt install -y libavcodec-dev libavformat-dev libavutil-dev libswscale-dev

# 安装redis的开发库
sudo apt install -y libhiredis-dev

# 安装MySQL Connector/C++
sudo apt install -y libmysqlcppconn-dev
sudo apt install -y libmysqlclient-dev

# 安装Exiv2的开发库
sudo apt install -y libexiv2-dev

# 安装PkgConfig工具
sudo apt install -y pkg-config
