#!/bin/bash

# Script para construir la imagen Docker personalizada de MatrixMCU

# --- Configuración --- 
IMAGE_NAME="matrixmcu-env"
SETUP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)" #Carpeta 'setup'

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

function create_network() {
    if ! docker network inspect lab_virtual_net >/dev/null 2>&1; then
        echo "🌐 Red 'lab_virtual_net' no encontrada. Creándola..."
        docker network create lab_virtual_net
    else
        echo "🌐 Red 'lab_virtual_net' ya existe."
    fi
}

function detect_os_and_uid() {
    OS_TYPE=$(uname -s)
    echo "🔎 Detectando sistema operativo..."
    echo "Sistema detectado: $OS_TYPE"

    if [[ "$OS_TYPE" == "Linux" ]]; then
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
        -t $IMAGE_NAME "$SETUP_DIR"
    if [ $? -ne 0 ]; then
        echo "❌ Error: No se pudo construir la imagen Docker '${IMAGE_NAME}'."
        exit 1
    else
        echo "✅ Imagen Docker '${IMAGE_NAME}' creada con éxito"
    fi
}

function pull_docker_compose_images() {
    if [ -f "$SETUP_DIR/docker-compose.yml" ]; then
        echo "📥 Descargando imágenes definidas en 'docker-compose.yml'..."
        sudo docker-compose -f "$SETUP_DIR/docker-compose.yml" pull
    else
        echo "⚠️ Archivo 'docker-compose.yml' no encontrado en '$SETUP_DIR'."
    fi
}

# --- Ejecución principal ---
echo "🚀 Iniciando construcción de entorno MatrixMCU..."

check_docker_installed
check_docker_running
detect_os_and_uid
create_network
build_image
pull_docker_compose_images

echo "Ahora abre la carpeta 'alumno/' en VSCode y selecciona 'Reopen in Container'."
