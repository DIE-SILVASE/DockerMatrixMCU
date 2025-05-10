# Base: Ubuntu 24.04
FROM ubuntu:24.04

# Argumentos para usuario
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=1000
ARG QTEST_PORT=3000
ARG HOST_SERVER=localhost

ENV HOST_SERVER=${HOST_SERVER}
ENV DEBIAN_FRONTEND=noninteractive

# Instalar herramientas básicas del sistema
RUN apt update && apt install -y \
    sudo wget git ca-certificates

# Crear grupo según GID. Si ya existe, se renombre
RUN echo "Configuring GID ${USER_GID}..." && \
    # Check if group already exists
    if getent group ${USER_GID}; then \
      existing_group=$(getent group ${USER_GID} | cut -d: -f1) && \
      if [ "$existing_group" != "${USERNAME}" ]; then \
        echo "🔄 Renaming group ${existing_group} to ${USERNAME}" && \
        groupmod -n ${USERNAME} $existing_group; \
      else \
        echo "✅ Group ${USERNAME} already exists with GID ${USER_GID}"; \
      fi && \
      existing_group=${USERNAME}; \
    else \
      echo "➕ Creating new group with GID ${USER_GID}" && \
      groupadd --gid ${USER_GID} ${USERNAME}; \
    fi

# Crear el usuario según UID y GID. Si ya existen, se reutilizan
RUN echo "Configuring UID ${USER_UID}..." && \
    if getent passwd ${USER_UID}; then \
        existing_user=$(getent passwd ${USER_UID} | cut -d: -f1) && \
        if [ "$existing_user" != "${USERNAME}" ]; then \
            echo "🔄 Renaming user $existing_user to ${USERNAME}" && \
            usermod -l ${USERNAME} -d /home/${USERNAME} -m $existing_user; \
        else \
            echo "✅ User ${USERNAME} already exists with UID ${USER_UID}"; \
        fi \
    else \
        echo "➕ Creating new user with UID ${USER_UID}" && \
        useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME}; \
    fi && \
    echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Clonar MatrixMCU e instalar dependencias
RUN git clone --recursive --depth=1 -b dev https://github.com/sdg2DieUpm/MatrixMCU.git /MatrixMCU && \
    /MatrixMCU/install/ubuntu24.sh && \
    rm /tmp/arm-toolchain.tar.xz


# Instalar herramientas necesarias para compilar QEMU
RUN apt install -y \
    curl xz-utils lsb-release \
    python3 python3-pip python3-venv \
    libglib2.0-dev libpixman-1-dev zlib1g-dev \
    ninja-build flex bison libncurses-dev zsh

# Clonar QEMU y compilarlo
RUN git clone --depth=1 -b dev-stm32-gpio https://github.com/DIE-SILVASE/qemu_new.git /qemu_new && \
    cd /qemu_new && mkdir build && cd build && \
    ../configure --target-list=arm-softmmu && make -j$(nproc)

# Limpiar cache de apt
RUN apt clean && rm -rf /var/lib/apt/lists/*

# Crear variable de entorno para apuntar a MatrixMCU
ENV MATRIXMCU=/MatrixMCU
# Añadir al PATH global la toolchain de ARM y QEMU
ENV PATH=/opt/MatrixMCU/bin:/qemu_new/build:$PATH

# # Cambiar permisos de los directorios
# RUN chown -R ${USERNAME}:${USERNAME} /home/${USERNAME}

# # Trabajar en MatrixMCU
# WORKDIR /home/${USERNAME}/MatrixMCU

# Exponer puerto QTest
EXPOSE ${QTEST_PORT}

# Shell
CMD ["bash"]
