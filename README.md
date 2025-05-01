# 🛠️ Preparación del Entorno MatrixMCU (para alumnos)

¡Bienvenid@! Aquí tienes todo lo necesario para dejar tu entorno de desarrollo listo para trabajar con **MatrixMCU** y **QEMU**, directamente desde Visual Studio Code usando contenedores Docker.

---

## 🚀 1. ¿Qué hace esto?

Este proceso:

- Construye una imagen Docker personalizada con todas las herramientas (compilador ARM, QEMU, MatrixMCU...).
- Configura automáticamente rutas, permisos y usuarios dentro del contenedor.
- Exporta la variable de entorno `MATRIXMCU` apuntando a la raíz del framework.
- Permite compilar, debuggear y emular sin tocar la configuración del sistema anfitrión.

---

## 🧪 2. Requisitos previos

Asegúrate de tener instalado en tu máquina:

- ✅ [Docker](https://docs.docker.com/get-docker/)
- ✅ [Visual Studio Code](https://code.visualstudio.com/)
- ✅ La extensión **Dev Containers** en VSCode

---

## 🧰 3. Cómo construir el entorno (solo una vez)

### 🪄 PASO 1 — Ejecutar la Task de Build

Según tu sistema operativo, ejecuta **una sola vez** una de estas dos tareas desde la paleta (`Ctrl+Shift+P > Tasks: Run Task`):

- 🔹 `Build MatrixMCU Environment (Linux/macOS)`
- 🔹 `Build MatrixMCU Environment (Windows-PowerShell)`

Esto hará lo siguiente:

- Detecta el sistema operativo y UID/GID del host.
- Construye la imagen personalizada `matrixmcu-env`.
- Crea la red `lab_virtual_net` si no existe.
- Descarga las imágenes necesarias para el laboratorio (para que luego no tarde).

---

## 🧠 4. ¿Qué ocurre al iniciar el contenedor?

Cuando abres `alumno/` con VSCode y eliges **Reopen in Container**, se ejecutan:

### ✅ `post-create.sh` (solo la primera vez)

- Detecta el nombre real del usuario (según UID).
- Crea `/home/$usuario/MatrixMCU`
- Crea un enlace simbólico:  
  `/home/$usuario/MatrixMCU/projects → /workspace/projects`
- Guarda el path real en `/tmp/matrixmcu_path`

### ✅ `postStartCommand` (cada vez que se abre el contenedor)

- Añade dinámicamente a `~/.bashrc` la línea:
  
```bash
export MATRIXMCU=/home/ubuntu/MatrixMCU
```

Esto garantiza que el entorno funcione en Windows, Linux y macOS.

## 🪄 5. Ejecutar MICROLAB

Tras haber construido el entorno e iniciado el DevContainer, puedes iniciar o detener el laboratorio virtual (servidor y frontend) utilizando los **Tasks** integrados de VSCode.

Estos tasks permiten:

- Levantar los contenedores necesarios (`rust-server`, `interfaz-grafica`)
- Conectar automáticamente el DevContainer a la red `lab_virtual_net`
- Abrir la interfaz web en el navegador (`http://localhost:5173`)


### ▶️ Iniciar MICROLAB

Selecciona uno de estos tasks según tu sistema operativo:

- **Linux/macOS**: `Iniciar MICROLAB (Linux/Mac)`
- **Windows**: `Iniciar MICROLAB (Windows)`

Esto ejecutará el script correspondiente (`lab.sh` o `lab.ps1`), que:

1. Lanza el entorno con `docker-compose up -d`
2. Conecta automáticamente el contenedor `matrixmcu-dev` a la red `lab_virtual_net`
3. Abre la interfaz del laboratorio en el navegador (`http://localhost:5173`)

🧠 **IMPORTANTE:**  
Después de este paso, vuelve a tu DevContainer en VSCode y pulsa **"Run and Debug → Microlab"** desde la pestaña lateral de depuración.

Esto iniciará QEMU con la conexión al entorno activo. ¡No lo olvides!

### 🛑 Parar MICROLAB

Selecciona el task correspondiente:

- **Linux/macOS**: `Parar MICROLAB (Linux/Mac)`
- **Windows**: `Parar MICROLAB (Windows)`

Esto ejecutará `docker-compose down` desde la carpeta `setup`.

---
## 🔁 6. Cambios en CMake

En tu `CMakeLists.txt` del proyecto, MatrixMCU se detecta así:

```cmake
IF(NOT DEFINED MATRIXMCU)
    SET(MATRIXMCU  $ENV{MATRIXMCU})
    MESSAGE(STATUS "MATRIXMCU path (env): ${MATRIXMCU}")
ENDIF()

INCLUDE(${MATRIXMCU}/CMakeLists.txt)
```

---

## 🐞 7. Cambios en launch.json (debug)

En todas las rutas que antes usaban `${workspaceFolder}/../../`, ahora se usa `${env:MATRIXMCU}`:

```json
"serverpath": "${env:MATRIXMCU}/../qemu_new/build/qemu-system-arm",
"configFiles": ["${env:MATRIXMCU}/openocd/stm32f4x.cfg"],
"svdFile": "${env:MATRIXMCU}/svd/STM32F405RG.svd"
```

---

## 🛡️ 8. Compatibilidad avanzada con UID y sistemas

| Sistema            | UID 1000 libre | Resultado                          |
|--------------------|----------------|------------------------------------|
| Linux (real)       | ✅ Sí           | Se crea `dev:1000` sin conflictos  |
| Docker Desktop     | ❌ No           | Usa `ubuntu` automáticamente       |

Esto evita errores de permisos y asegura que el contenedor pueda editar tus archivos.

---

## 🧠 9. Resumen visual

```plaintext
+----------------------------+           +------------------------------+
|     Linux (UID 1000 libre) |           | Docker Desktop (UID en uso)  |
+----------------------------+           +------------------------------+
| Usuario: dev               |           | Usuario: ubuntu              |
| /home/dev/MatrixMCU        |           | /home/ubuntu/MatrixMCU       |
| → Enlace: /workspace       |           | → Enlace: /workspace         |
| → $MATRIXMCU exportado     |           | → $MATRIXMCU exportado       |
+----------------------------+           +------------------------------+
```

---

## ✅ Resultado final

Con esta configuración:

- MatrixMCU funciona en **cualquier sistema operativo**.
- Puedes compilar y debuggear con **QEMU** desde VSCode sin errores.
- No necesitas configurar nada manualmente después del primer uso.

---

## ⚙️ Lista de Tasks disponibles

```jsonc
// 🚧 SOLO LA PRIMERA VEZ
"Build MatrixMCU Environment (Linux/macOS)"
"Build MatrixMCU Environment (Windows-PowerShell)"

// 🔁 Para iniciar el laboratorio
"Iniciar MICROLAB (Linux/Mac)"
"Iniciar MICROLAB (Windows)"

// 🛑 Para detener el laboratorio
"Parar MICROLAB (Linux/Mac)"
"Parar MICROLAB (Windows)"

// 🧹 DevContainer
"Parar dev-container MatrixMCU"
"Eliminar dev-container MatrixMCU"
```