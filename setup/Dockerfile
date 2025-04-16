# Base: Ubuntu 24.04
FROM ubuntu:24.04

# Argumentos para usuario
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=1000

ENV DEBIAN_FRONTEND=noninteractive

# Instala herramientas básicas del sistema
RUN apt-get update && apt-get install -y --no-install-recommends \
    sudo git curl wget xz-utils ca-certificates lsb-release \
    build-essential cmake make gcc g++ \
    gdb-multiarch \
    python3 python3-pip python3-venv \
    libglib2.0-dev libpixman-1-dev zlib1g-dev \
    ninja-build flex bison libncurses-dev zsh \
    openocd \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Crear usuario dev con UID y GID personalizados
RUN groupadd --gid ${USER_GID} ${USERNAME} || true && \
    useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} && \
    echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Añadir el PATH global del toolchain ARM
ENV MATRIXMCU_TOOLCHAIN=/opt/MatrixMCU/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi
ENV PATH=/opt/MatrixMCU/bin:$PATH

# Descargar e instalar el toolchain ARM (como root)
RUN mkdir -p /opt/MatrixMCU/bin && \
    wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz -O /tmp/arm-toolchain.tar.xz && \
    tar -xf /tmp/arm-toolchain.tar.xz -C /opt/MatrixMCU && \
    ln -s ${MATRIXMCU_TOOLCHAIN}/bin/arm-none-eabi-* /opt/MatrixMCU/bin/ && \
    ln -sf $(which gdb-multiarch) /opt/MatrixMCU/bin/arm-none-eabi-gdb && \
    rm /tmp/arm-toolchain.tar.xz

# Cambiar a usuario no root
USER ${USERNAME}
WORKDIR /home/${USERNAME}

# Clona QEMU y lo compila
RUN git clone -b dev-stm32-gpio https://github.com/DIE-SILVASE/qemu_new.git && \
    cd qemu_new && \
    mkdir build && cd build && \
    ../configure --target-list=arm-softmmu && \
    make -j$(nproc)

# Clona el repositorio de MatrixMCU
RUN git clone --recursive https://github.com/sdg2DieUpm/MatrixMCU.git

# Carpeta de trabajo por defecto
WORKDIR /home/${USERNAME}/MatrixMCU


#Expone el puerto para conexión qemu-qtest
EXPOSE 3000


# Shell interactiva
CMD ["bash"]
 