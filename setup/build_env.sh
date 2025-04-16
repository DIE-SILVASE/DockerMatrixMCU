#!/bin/bash

# Script profesional para construir la imagen Docker personalizada de MatrixMCU


# --- Configuración ---
IMAGE_NAME="matrixmcu-env"
DOCKERFILE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"  # Carpeta 'alumno'
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"         # Carpeta 'preparacion_entorno'

# --- Funciones ---
function check_docker_installed() {
    if ! command -v docker &> /dev/null; then
        echo "❌ Docker no está instalado. Por favor instala Docker primero."
        exit 1
    fi
}

function check_docker_running() {
    if ! sudo docker info &> /dev/null; then
        echo "❌ Docker daemon no está corriendo. Asegúrate de que Docker esté iniciado."
        exit 1
    fi
}

function detect_os_and_uid() {
    OS_TYPE=$(uname -s)
    echo "🔎 Detectando sistema operativo..."
    echo "Sistema detectado: $OS_TYPE"

    if [[ "$OS_TYPE" == "Linux" || "$OS_TYPE" == "Darwin" ]]; then
        USER_UID=$(id -u)
        USER_GID=$(id -g)
    else
        USER_UID=1000
        USER_GID=1000
    fi

    echo "👤 UID=${USER_UID}, GID=${USER_GID}"
}

function build_image() {
    echo "🚧 Construyendo imagen Docker '${IMAGE_NAME}'..."
    sudo docker build \
        --build-arg USERNAME=dev \
        --build-arg USER_UID=$USER_UID \
        --build-arg USER_GID=$USER_GID \
        -t $IMAGE_NAME "$DOCKERFILE_DIR"
}

# --- Ejecución principal ---
echo "🚀 Iniciando construcción de entorno MatrixMCU..."

check_docker_installed
check_docker_running
detect_os_and_uid
build_image

echo "✅ Imagen '${IMAGE_NAME}' creada con éxito."
echo "👉 Ahora abre la carpeta 'alumno/' en VSCode y selecciona 'Reopen in Container'."