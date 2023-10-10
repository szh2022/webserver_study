## 项目描述

本项目使用C++11开发，在Linux平台下实现了一个高并发服务器，旨在支持大量客户端的并发访问 和资源响应。服务器支持客户端访问各种资源，如图片和视频。此外，本项目实现了异步日志，记录服务器运行状态。

## Build

```shell
./build.sh
```

## Usage

```shell
./WebServer [-t thread_numbers] [-p port] [-l log_file_path(should begin with '/')]
```
