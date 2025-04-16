# 🛠️ Preparación del Entorno MatrixMCU (para alumnos)

¡Bienvenid@! Aquí tienes todo lo necesario para dejar tu entorno de desarrollo listo para trabajar con **MatrixMCU** y **QEMU**, directamente desde Visual Studio Code usando contenedores Docker.

---

## 🚀 1. ¿Qué hace esto?

Este proceso:

- Construye una imagen Docker personalizada con las herramientas necesarias (compilador, QEMU, MatrixMCU...).
- Ajusta los permisos para que puedas editar archivos sin problemas.
- Permite trabajar desde VSCode con **DevContainers**, de forma automática.

---

## 🧪 2. Requisitos previos

Asegúrate de tener instalado en tu máquina:

- ✅ [Docker](https://docs.docker.com/get-docker/)
- ✅ [Visual Studio Code](https://code.visualstudio.com/)
- ✅ La extensión **Dev Containers** en VSCode

---

## 🧰 3. Cómo construir el entorno (solo una vez)

Abre una terminal y ejecuta lo siguiente desde esta carpeta:

```bash
chmod +x build_env.sh
./build_env.sh
```

Este script detectará tu sistema operativo, UID/GID, y construirá la imagen Docker matrixmcu-env.

## 🧠 4. ¿Y después?
Abre la carpeta alumno/ con VSCode.

Cuando VSCode te lo pregunte, selecciona:

Reopen in Container

Espera unos minutos mientras se crea el entorno... y 🎉 ¡ya estás dentro!