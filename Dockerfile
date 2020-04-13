# Dockerfile for the interactive demo of RTEMS for the Real-Time Systems RTOS Survey
FROM bvobart/rtems:sparc-erc32
WORKDIR /workspace/demo

ARG password=""

# Copy the demo source code into the Docker container
COPY . .

# Pre-compile all examples
RUN cd classic-api \
  && waf configure --rtems=$PREFIX --rtems-tools=$PREFIX --rtems-bsps=sparc/erc32 \
  && waf

# Install and allow SSH connections
# RUN dnf install -y sshd ?????

CMD ./demo.sh
