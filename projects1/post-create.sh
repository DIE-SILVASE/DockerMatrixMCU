#!/bin/bash
set -e

echo "🔎 Detectando usuario..."

# Detectar el usuario real
detected_user=$(cat /username_detected.txt 2>/dev/null || echo dev)
echo "👤 Usuario detectado: $detected_user"

# Definir ruta de MatrixMCU
MATRIXMCU_PATH="/home/$detected_user/MatrixMCU"

# Crear carpeta base
mkdir -p "$MATRIXMCU_PATH"

# Enlace simbólico limpio
rm -rf "$MATRIXMCU_PATH/projects"
ln -s /workspace/projects "$MATRIXMCU_PATH/projects"
chown -R "$detected_user:$detected_user" "$MATRIXMCU_PATH"
echo "✅ Enlace simbólico creado en $MATRIXMCU_PATH/projects"

# Guardar el path dinámico en /tmp
echo "$MATRIXMCU_PATH" > /tmp/matrixmcu_path
echo "✅ MATRIXMCU_PATH detectado como $MATRIXMCU_PATH y guardado en /tmp/matrixmcu_path"

