#!/bin/bash

# Ruta al archivo tasks.json
TASKS_JSON_PATH="${workspaceFolder}/.vscode/tasks.json"

# Directorio donde se encuentran las subcarpetas
PROJECTS_DIR="${workspaceFolder}/projects"

# Crear un array vacío para las opciones
OPTIONS=()

# Listar las subcarpetas y guardarlas en un array
for dir in ${PROJECTS_DIR}/*/; do
  # Solo agregar directorios, no archivos
  if [ -d "$dir" ]; then
    OPTIONS+=("$(basename "$dir")")
  fi
done

# Convertir el array de opciones a una cadena JSON
OPTIONS_JSON=$(printf '"%s", ' "${OPTIONS[@]}")
OPTIONS_JSON="[${OPTIONS_JSON%, }]"  # Eliminar la última coma extra

# Usar jq para actualizar el archivo tasks.json
# Asegúrate de que jq esté instalado en tu sistema
jq --arg options "$OPTIONS_JSON" '.tasks[0].inputs[0].args.options = ($options | fromjson)' "$TASKS_JSON_PATH" > tmp.json && mv tmp.json "$TASKS_JSON_PATH"

echo "Las opciones en tasks.json se han actualizado."
