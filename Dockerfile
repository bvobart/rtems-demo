# Dockerfile for the interactive demo of RTEMS for the Real-Time Systems RTOS Survey
FROM bvobart/rtems:sparc-erc32
WORKDIR /workspace/demo

ARG password=rtems-demo

# Install and allow SSH connections
RUN dnf install -y openssh-server \
  && ssh-keygen -t ed25519 -f /etc/ssh/ssh_host_ed25519_key -N '' \
  && ssh-keygen -t ecdsa -f /etc/ssh/ssh_host_ecdsa_key -N '' \
  && ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N '' \
  && echo "root:$password" | chpasswd

# Set up bashrc so that people SSH'ing in will correctly see the demo environment
RUN echo "export PREFIX=/workspace/rtems/5" >> /root/.bashrc \
  && echo "export PATH='$PREFIX/bin:$PATH'" >> /root/.bashrc \
  && echo "cd /workspace/demo" >> /root/.bashrc \
  && echo "./demo.sh" >> /root/.bashrc \
  && rm -rf /run/nologin

# Copy the demo source code into the Docker container
COPY . .

# Pre-compile all examples
RUN cd classic-api \
  && waf configure --rtems=$PREFIX --rtems-tools=$PREFIX --rtems-bsps=sparc/erc32 \
  && waf \
  && cd ../rm-manager \
  && waf configure --rtems=$PREFIX --rtems-tools=$PREFIX --rtems-bsps=sparc/erc32 \
  && waf \
  && cd ../cbs \
  && waf configure --rtems=$PREFIX --rtems-tools=$PREFIX --rtems-bsps=sparc/erc32 \
  && waf

EXPOSE 22
CMD /usr/sbin/sshd -D & ./demo.sh
