# lab.ps1
$ErrorActionPreference = "Stop"

$networkName = "lab_virtual_net"
$vscContainer = "matrixmcu-dev"
$frontendURL = "http://localhost:5173"



Write-Host "Iniciando entorno MICROLAB..."

# Verificar y crear red antes de docker-compose
# Write-Host "Verificando red '$networkName'..."
# try {
#     $exists = docker network ls --filter "name=^$networkName$" --format "{{.Name}}"
#     if (-not $exists) {
#         Write-Host "Red no encontrada. Creando '$networkName'..."
#         docker network create --driver bridge $networkName
#     }
# } catch {
#     Write-Error "Error: no se pudo verificar o crear la red '$networkName'. $_"
#     exit 1
# }

# Levantar contenedores
try {
    docker-compose up -d
} catch {
    Write-Error "Error: fallo al iniciar docker-compose. $_"
    exit 1
}



# Write-Host "Conectando contenedor '$vscContainer' a la red '$networkName'..."
# try {
#     docker network connect $networkName $vscContainer
# } catch {
#     Write-Warning "Aviso: ya estaba conectado o hubo un problema (¿existe el contenedor?)."
# }


# Abrir la interfaz gráfica automáticamente
Write-Host "Abriendo interfaz gráfica en $frontendURL"
Start-Process "powershell" "-NoProfile -Command Start-Process '$frontendURL'"
