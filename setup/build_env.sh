#!/bin/bash

# Script para construir la imagen Docker personalizada de MatrixMCU

# --- Configuración --- 
IMAGE_NAME="matrixmcu-env"
IMAGE_REMOTE="iivvjj/matrixmcu-env:v2"
SETUP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)" #Carpeta 'setup'
HOST_SERVER="localhost"

IS_MACOS=false


# --- Funciones ---
function check_docker_installed() {
    if ! command -v docker &> /dev/null; then
        echo "❌ Docker no está instalado. Por favor instala Docker primero."
        exit 1
    fi
}

function check_docker_running() {
    if ! docker info &> /dev/null; then
        echo "❌ Docker daemon no está corriendo. Asegúrate de que Docker esté iniciado."
        exit 1
    fi
}


# function detect_os_and_uid() {
#     OS_TYPE=$(uname -s)
#     echo "🔎 Detectando sistema operativo..."
#     echo "Sistema detectado: $OS_TYPE"

#     if [[ "$OS_TYPE" == "Darwin" ]]; then
#         IS_MACOS=true
#         USER_UID=1000
#         USER_GID=1000
#         HOST_SERVER="host.docker.internal"
#     elif [[ "$OS_TYPE" == "Linux" ]]; then
#         USER_UID=$(id -u)
#         USER_GID=$(id -g)
#         HOST_SERVER="localhost"
#     else
#         echo "⚠️ Sistema no reconocido. Usando UID/GID por defecto (1000)"
#         USER_UID=1000
#         USER_GID=1000
#     fi

#     echo "👤 UID=${USER_UID}, GID=${USER_GID}"
# }

# function pull_remote_image() {
#     echo "📥 Descargando imagen preconstruida '${IMAGE_REMOTE}' desde Docker Hub..."
#     docker pull "$IMAGE_REMOTE"
#     if [ $? -ne 0 ]; then
#         echo "❌ Error: No se pudo descargar la imagen remota."
#         exit 1
#     fi

#     echo "🏷️ Etiquetando como '${IMAGE_NAME}'..."
#     docker tag "$IMAGE_REMOTE" "$IMAGE_NAME"
# }

# function build_image() {
#     echo "🚧 Construyendo imagen Docker '${IMAGE_NAME}'..."
#     docker build \
#         --build-arg USERNAME=dev \
#         --build-arg USER_UID=$USER_UID \
#         --build-arg USER_GID=$USER_GID \
#         --build-arg HOST_SERVER=$HOST_SERVER \
#         -t $IMAGE_NAME "$SETUP_DIR"
#     if [ $? -ne 0 ]; then
#         echo "❌ Error: No se pudo construir la imagen Docker '${IMAGE_NAME}'."
#         exit 1
#     else
#         echo "✅ Imagen Docker '${IMAGE_NAME}' creada con éxito"
#     fi
# }

function pull_docker_compose_images() {
    if [ -f "$SETUP_DIR/docker-compose.yml" ]; then
        echo "📥 Descargando imágenes definidas en 'docker-compose.yml'..."
        docker compose -f "$SETUP_DIR/docker-compose.yml" pull
    else
        echo "⚠️ Archivo 'docker-compose.yml' no encontrado en '$SETUP_DIR'."
    fi
}

# --- Ejecución principal ---
echo "🚀 Iniciando construcción de entorno MatrixMCU..."

check_docker_installed
check_docker_running
# detect_os_and_uid


# if $IS_MACOS; then
#     echo "🍏 macOS detectado: se usará imagen preconstruida para evitar build local."
#     pull_remote_image
# else
#     build_image
# fi

#pull_remote_image

pull_docker_compose_images

echo " Imagenes descargadas con exito."
echo "Ahora abre el contenedor pulsando F1 (o Ctrl+Shift+P) y seleccionando: 'Dev Containers: Reopen in Container'."
