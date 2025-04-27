# build_env.ps1

# Salir si ocurre cualquier error
$ErrorActionPreference = "Stop"

# --- Configuración ---
$IMAGE_NAME = "matrixmcu-env"
$DOCKERFILE_DIR = Get-Location

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
        Write-Host "ERROR: Docker daemon no está corriendo. Asegúrate de que Docker esté iniciado." -ForegroundColor Red
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

function Build-Image {
    Write-Host "Construyendo imagen Docker '$IMAGE_NAME'..."
    docker build `
        -f Dockerfile `
        --build-arg USERNAME=dev `
        --build-arg USER_UID=$USER_UID `
        --build-arg USER_GID=$USER_GID `
        -t $IMAGE_NAME `
        .

    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Error al construir la imagen Docker." -ForegroundColor Red
        exit 1
    }

    Write-Host "✅ Imagen '$IMAGE_NAME' creada con éxito." -ForegroundColor Green
}

# --- Ejecución principal ---
Write-Host "Iniciando construccion de entorno MatrixMCU..."

Check-DockerInstalled
Check-DockerRunning
Detect-OSAndUID
Build-Image

Write-Host "Imagen '$IMAGE_NAME' creada con éxito." -ForegroundColor Green
Write-Host "Ahora abre la carpeta 'alumno/' en VSCode y selecciona 'Reopen in Container'." 