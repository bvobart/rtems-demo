# RTEMS Demo

Interactive demo for the RTOS survey assignment in the Real-Time Systems course of 2020 at TU Delft.

## Quickstart

The demo consists of a Docker container preconfigured with everything required to build a few example
applications. Additionally, it is possible to SSH into this container by providing a password as a
build argument. The default password is `rtems-docker`

#### Building
```sh
# either
docker build -t rtems-demo .
# or
docker build -t rtems-demo --build-arg password=your-password .
```

#### Running
```sh
# either
docker run -it --rm rtems-demo
# or to expose SSH port to port 2222 on the host
docker run -it --rm -p 2222:22 rtems-demo
```
