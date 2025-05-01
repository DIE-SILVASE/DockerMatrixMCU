#!/bin/bash
set -e

echo "🔎 Detectando usuario..."

detected_user=$(cat /username_detected.txt 2>/dev/null || echo dev)

echo "👤 Usuario detectado: $detected_user"

if id "$detected_user" &>/dev/null; then
    echo "✅ Configurando entorno para $detected_user..."
    mkdir -p /home/$detected_user/MatrixMCU/projects
    chown -R $detected_user:$detected_user /home/$detected_user
    ln -sfn /workspace/projects /home/$detected_user/MatrixMCU/projects
else
    echo "⚠ Usuario $detected_user no encontrado. Usando root."
fi