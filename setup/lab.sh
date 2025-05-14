#!/bin/bash
set -euo pipefail

# NETWORK_NAME="lab_virtual_net"
VSC_CONTAINER="matrixmcu-dev"


echo "🔧 Iniciando entorno MICROLAB..."
if ! docker compose up -d; then
    echo " Error: Fallo al iniciar docker-compose."
    exit 1
fi

echo " Abriendo interfaz grafica en http://localhost:5173"
if command -v xdg-open >/dev/null; then
    xdg-open http://localhost:5173 >/dev/null 2>&1 
elif command -v open >/dev/null; then
    open http://localhost:5173 >/dev/null 2>&1 || echo " No se pudo abrir el navegador automáticamente."
else
    echo " Abre manualmente: http://localhost:5173"
fi
