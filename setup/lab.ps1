# lab.ps1
$ErrorActionPreference = "Stop"

# $networkName = "lab_virtual_net"
$vscContainer = "matrixmcu-dev"
$frontendURL = "http://localhost:5173"



Write-Host "Iniciando entorno MICROLAB..."
# Levantar contenedores
try {
    docker-compose up -d
} catch {
    Write-Error "Error: fallo al iniciar docker-compose. $_"
    exit 1
}


# Abrir la interfaz gráfica automáticamente
Write-Host "Abriendo interfaz gráfica en $frontendURL"
Start-Process "powershell" "-NoProfile -Command Start-Process '$frontendURL'"
