# RTEMS Demo

Interactive demo for the RTOS survey assignment in the Real-Time Systems course of 2020 at TU Delft.

## Quickstart

The demo consists of a Docker container preconfigured with everything required to build a few example
applications. Additionally, it is possible to SSH into this container by providing a password as a
build argument.

#### Without SSH access
```sh
docker build -t rtems-demo .
docker run -it --rm rtems-demo
```

#### With SSH access
```sh
docker build -t rtems-demo --build-arg password=your-password .
docker run -it --rm rtems-demo
```
