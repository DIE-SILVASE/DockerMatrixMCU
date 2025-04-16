#!/bin/bash

# Nombre del contenedor VSCode (Devcontainer)
VSC_CONTAINER=$(docker ps --filter "name=vsc" --format "{{.Names}}" | head -n 1)
NETWORK=lab_virtual_net

case "$1" in
  start)
    echo "🔧 Lanzando entorno de laboratorio virtual..."
    docker-compose up -d

    echo "🔗 Conectando contenedor $VSC_CONTAINER a la red '$NETWORK'..."
    docker network connect $NETWORK $VSC_CONTAINER 2>/dev/null || echo "Ya estaba conectado."

    echo "✅ Laboratorio levantado."
    echo "🌐 Accede a la interfaz gráfica en: http://localhost:5173"
    ;;
  
  stop)
    echo "🧹 Cerrando entorno de laboratorio virtual..."
    docker-compose down
    echo "✅ Laboratorio detenido (MatrixMCU sigue activo)."
    ;;
  
  *)
    echo "Uso: ./lab.sh [start|stop]"
    ;;
esac
