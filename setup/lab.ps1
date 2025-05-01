# lab.ps1
$ErrorActionPreference = "Stop"

$networkName = "lab_virtual_net"
$vscContainer = "matrixmcu-dev"
$frontendURL = "http://localhost:5173"



Write-Host "Iniciando entorno MICROLAB..."

# Verificar y crear red antes de docker-compose
Write-Host "Verificando red '$networkName'..."
try {
    $exists = docker network ls --filter "name=^$networkName$" --format "{{.Name}}"
    if (-not $exists) {
        Write-Host "Red no encontrada. Creando '$networkName'..."
        docker network create --driver bridge $networkName
    }
} catch {
    Write-Error "Error: no se pudo verificar o crear la red '$networkName'. $_"
    exit 1
}

# Levantar contenedores
try {
    docker-compose up -d
} catch {
    Write-Error "Error: fallo al iniciar docker-compose. $_"
    exit 1
}



Write-Host "Conectando contenedor '$vscContainer' a la red '$networkName'..."
try {
    docker network connect $networkName $vscContainer
} catch {
    Write-Warning "Aviso: ya estaba conectado o hubo un problema (¿existe el contenedor?)."
}

Write-Host "Abriendo interfaz grafica en http://localhost:5173"
# Esperar a que el contenedor 'interfaz-grafica' esté healthy
$frontendContainer = "interfaz-grafica"
$maxRetries = 20
$retryDelay = 2

Write-Host "Esperando a '$frontendContainer'"
for ($i = 0; $i -lt $maxRetries; $i++) {
    try {
        $status = docker inspect --format='{{.State.Health.Status}}' $frontendContainer
        if ($status -eq "healthy") {
            Write-Host "'$frontendContainer' está listo. Abriendo interfaz gráfica."
            Start-Process $frontendURL
            break
        } else {
            Write-Host "  → Intento $($i+1)/$maxRetries`: Estado actual = `$status"
        }
    } catch {
        Write-Warning "No se pudo obtener el estado de salud. ¿Está corriendo el contenedor?"
    }
    Start-Sleep -Seconds $retryDelay
}

if ($status -ne "healthy") {
    Write-Warning "La interfaz gráfica no está lista después de $($maxRetries * $retryDelay) segundos. Ábrela manualmente: $frontendURL"
}
