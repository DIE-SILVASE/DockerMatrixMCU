#!/bin/bash
set -euo pipefail

NETWORK_NAME="lab_virtual_net"
VSC_CONTAINER="matrixmcu-dev"


echo "🔌 Verificando red '$NETWORK_NAME'..."
if ! docker network inspect "$NETWORK_NAME" >/dev/null 2>&1; then
    echo "📡 Red no encontrada. Creando '$NETWORK_NAME'..."
    if ! docker network create "$NETWORK_NAME"; then
        echo "❌ Error: No se pudo crear la red '$NETWORK_NAME'."
        exit 1
    fi
fi

echo "🔧 Iniciando entorno MICROLAB..."
if ! docker compose up -d; then
    echo "❌ Error: Fallo al iniciar docker-compose."
    exit 1
fi


# echo "🔗 Conectando contenedor $VSC_CONTAINER a la red '$NETWORK_NAME'..."
# if ! docker network connect "$NETWORK_NAME" "$VSC_CONTAINER" 2>/dev/null; then
#     echo "ℹ️  Ya estaba conectado o hubo un problema (puede que no exista el contenedor)."
# fi

echo "🌐 Abriendo interfaz gráfica en http://localhost:5173"
if command -v xdg-open >/dev/null; then
    xdg-open http://localhost:5173 >/dev/null 2>&1 
elif command -v open >/dev/null; then
    open http://localhost:5173 >/dev/null 2>&1 || echo "ℹ️  No se pudo abrir el navegador automáticamente."
else
    echo "ℹ️  Abre manualmente: http://localhost:5173"
fi
