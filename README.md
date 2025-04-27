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
- ✅ La extensión **Remote Development** en VSCode

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

## 🛠️ 5. Notas avanzadas de compatibilidad (UID, permisos y DevContainers)

---

## 🧠 ¿Por qué importa el UID?

Cuando montamos carpetas externas (como `projects1`) en el contenedor:

- Si el usuario dentro del contenedor no tiene el **mismo UID** que el propietario real de los archivos,
- Podríamos tener **problemas de permisos**: no poder leer, escribir o compilar archivos.

---

## 🚀 ¿Cómo lo solucionamos?

Durante la construcción de la imagen Docker:

- Intentamos crear un usuario llamado `dev` con **UID 1000** y **GID 1000**.
- Si el UID 1000 **ya está ocupado** (por ejemplo, por un usuario `ubuntu` en imágenes de Docker Desktop),
  - Detectamos automáticamente el nombre del usuario que ocupa el UID 1000,
  - Guardamos su nombre en un archivo `/username_detected.txt` dentro del contenedor,
  - Y usamos ese usuario para configurar todo el entorno de MatrixMCU (clonar repositorios, permisos, paths, etc).

✅ Todo funciona de forma transparente para ti como desarrollador.

Además, durante el build verás mensajes claros como:

```
✅ Usuario 'dev' creado correctamente.
```
o
```
⚠ UID 1000 ocupado. Usando usuario existente: 'ubuntu'.
```

---

## 🌍 Diferencias entre sistemas

| Sistema | ¿UID 1000 libre? | Resultado |
|:--------|:----------------:|:---------:|
| Linux real (Ubuntu, Debian, etc.) | ✅ Normalmente libre | Se crea `dev:1000` sin problemas |
| Docker Desktop (Windows/macOS) | ❌ Puede estar ocupado (usuario `ubuntu`) | Se usa el usuario existente automáticamente |

---

## 🛡️ ¿Qué implica para ti?

- No necesitas preocuparte por permisos o configuraciones manuales.
- Siempre trabajarás como un usuario no root adecuado.
- Las carpetas externas (`projects1`, etc.) estarán correctamente accesibles.
- MatrixMCU funciona de manera consistente en Linux, Windows y macOS.

---

## 📢 Esquema visual rápido

```plaintext
┌─────────────────────────────┐           ┌──────────────────────────────────────┐
│         Linux real          │           │          Docker Desktop (Windows/Mac) │
├─────────────────────────────┤           ├──────────────────────────────────────┤
│ UID 1000 libre               │           │ UID 1000 ocupado (usuario 'ubuntu')   │
│ ➡ Se crea dev:1000           │           │ ➡ Se detecta usuario existente       │
│ ➡ Montaje correcto           │           │ ➡ Montaje correcto                   │
│ ➡ Sin conflictos             │           │ ➡ Sin conflictos                     │
└─────────────────────────────┘           └──────────────────────────────────────┘
```

---

## 📦 Resultado

Gracias a esta configuración:

- Tu entorno MatrixMCU es 100% funcional en **Linux, Windows, WSL y macOS**.
- No hay conflictos de usuarios o permisos.
- Puedes clonar, compilar, y trabajar sin errores desde el primer minuto.
