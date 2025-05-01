# lab.ps1
$ErrorActionPreference = "Stop"

$networkName = "lab_virtual_net"
$vscContainer = "matrixmcu-dev"

Write-Host "🔧 Iniciando entorno MICROLAB..."
try {
    docker-compose up -d
} catch {
    Write-Error " Error: Fallo al iniciar docker-compose. $_"
    exit 1
}

Write-Host "Verificando red '$networkName'..."
try {
    $exists = docker network ls --filter "name=^$networkName$" --format "{{.Name}}"
    if (-not $exists) {
        Write-Host "Red no encontrada. Creando '$networkName'..."
        docker network create $networkName
    }
} catch {
    Write-Error " Error: No se pudo verificar o crear la red '$networkName'. $_"
    exit 1
}

Write-Host "🔗Conectando contenedor $vscContainer a la red '$networkName'..."
try {
    docker network connect $networkName $vscContainer
} catch {
    Write-Warning "ℹ Ya estaba conectado o hubo un problema (¿existe el contenedor?)."
}

Write-Host "Abriendo interfaz gráfica en http://localhost:5173"
try {
    Start-Process "http://localhost:5173"
} catch {
    Write-Warning "ℹ  Abre manualmente: http://localhost:5173"
}
