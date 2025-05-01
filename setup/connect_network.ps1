# connect-network.ps1
$networkName = "lab_virtual_net"
$containerName = "matrixmcu-dev"

# Comprueba si la red existe
$networkExists = docker network ls --filter "name=^$networkName$" --format "{{.Name}}"

if (-not $networkExists) {
    Write-Host "🌐 Red $networkName no encontrada. Creándola..."
    docker network create $networkName
} else {
    Write-Host "🌐 Red $networkName ya existe."
}

# Intenta conectar el contenedor
try {
    docker network connect $networkName $containerName
    Write-Host "✅ Conectado $containerName a $networkName."
} catch {
    Write-Host "⚠️ Ya estaba conectado o ha habido un error: $($_.Exception.Message)"
}