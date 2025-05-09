# build_env.ps1

# Salir si ocurre cualquier error
$ErrorActionPreference = "Stop"

# --- Configuración ---
$IMAGE_NAME = "matrixmcu-env"
$DOCKER_IMAGENAME = "iivvjj/matrixmcu-env:v1"
$DOCKERFILE_DIR = Get-Location
$HOST_SERVER = "host.docker.internal"

# --- Funciones ---
function Check-DockerInstalled {
    if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
        Write-Host "ERROR: Docker no está instalado. Por favor instala Docker primero." -ForegroundColor Red
        exit 1
    }
}

function Check-DockerRunning {
    try {
        docker info | Out-Null
    } catch {
        Write-Host "ERROR: Docker daemon no esta corriendo. Asegurate de que Docker esté iniciado." -ForegroundColor Red
        exit 1
    }
}

function Detect-OSAndUID {
    $OS_TYPE = (Get-CimInstance Win32_OperatingSystem).Caption
    Write-Host "Detectando sistema operativo..."
    Write-Host "Sistema detectado: $OS_TYPE"
    
    # En Windows no se usa UID/GID reales
    $Global:USER_UID = 1000
    $Global:USER_GID = 1000

    Write-Host "UID=$USER_UID, GID=$USER_GID"
}

function Create-Network {
    try {
        docker network inspect lab_virtual_net | Out-Null
        Write-Host "Red 'lab_virtual_net' ya existe."
    } catch {
        Write-Host "Red 'lab_virtual_net' no encontrada. Creandola..."
        docker network create lab_virtual_net
    }
}

function Build-Image {
    Write-Host "Construyendo imagen Docker '$IMAGE_NAME'..."
    
    # & docker build `
    #     -f Dockerfile `
    #     --build-arg USERNAME=dev `
    #     --build-arg USER_UID=$USER_UID `
    #     --build-arg USER_GID=$USER_GID `
    #     --build-arg HOST_SERVER=$HOST_SERVER ` 
    #     -t $IMAGE_NAME `
    #     .
    & docker buildx build `
        --platform linux/amd64,linux/arm64 `
        -f Dockerfile `
        --build-arg USERNAME=dev `
        --build-arg USER_UID=$USER_UID `
        --build-arg USER_GID=$USER_GID `
        --build-arg HOST_SERVER=$HOST_SERVER `
        -t $IMAGE_NAME `
        --load `
        .

    if ($LASTEXITCODE -ne 0) {
        Write-Host " Error al construir la imagen Docker." -ForegroundColor Red
        exit 1
    }

    Write-Host " Imagen '$IMAGE_NAME' creada con exito." -ForegroundColor Green
}


function Get-DockerComposeImages {
    Write-Host " Descargando imagenes definidas en docker-compose.yml..."
    docker-compose pull

    if ($LASTEXITCODE -ne 0) {
        Write-Host " Error al descargar las imagenes de docker-compose." -ForegroundColor Red
        exit 1
    }

    Write-Host "Imagenes descargadas con exito." -ForegroundColor Green
}

function Pull-Image {
    Write-Host "Descargando imagen preconstruida '$DOCKER_IMAGENAME' desde Docker Hub..."
    docker pull $DOCKER_IMAGENAME

    if ($LASTEXITCODE -ne 0) {
        Write-Host " Error al descargar la imagen." -ForegroundColor Red
        exit 1
    }

    Write-Host "Renombrando '$DOCKER_IMAGENAME' como '$IMAGE_NAME'..."
    docker tag $DOCKER_IMAGENAME $IMAGE_NAME

    Write-Host " Imagen '$DOCKER_IMAGENAME' descargada y renombrada como '$IMAGE_NAME' con éxito." -ForegroundColor Green
}

# --- Ejecución principal ---
Write-Host "Iniciando construccion de entorno MatrixMCU..."

Check-DockerInstalled
Check-DockerRunning
Detect-OSAndUID
Create-Network
Build-Image
#Pull-Image
Get-DockerComposeImages

Write-Host "Imagen '$IMAGE_NAME' creada con exito." -ForegroundColor Green
Write-Host "Ahora abre la carpeta `alumno/` en VSCode y selecciona `Reopen in Container`." -ForegroundColor Yellow