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

## 🧰 3. Clonar el repositorio

Abre una terminal y ejecuta:

```bash
git clone https://github.com/tu_usuario/DockerMatrixMCU.git
```

Opcionalmente:
```bash
git config --global core.autocrlf input
```
Esto evitará problemas con saltos de línea si trabajas en Windows.

---

## 🧰 4. Construir el entorno (solo una vez)

### 🪄 PASO 1 — Ejecutar la Task de Build

Desde la paleta de comandos de VSCode (`Ctrl+Shift+P > Tasks: Run Task`):

- 🔹 `Build MatrixMCU Environment (Linux/macOS)`
- 🔹 `Build MatrixMCU Environment (Windows-PowerShell)`

Esto:

- Detecta el sistema operativo y UID del host.
- Construye la imagen `matrixmcu-env`.
- Crea la red `lab_virtual_net` si no existe.
- Descarga las imágenes necesarias del laboratorio.

---


## 🧠 5. Abrir el DevContainer

Abre la carpeta `DockerMatrixMCU/` en VSCode y selecciona `Reopen in Container`.

Esto ejecutará automáticamente algunos scripts de configuración del entorno.

> _ℹ️ **Scripts de inicialización dentro del contenedor:**_  
> _• `post-create.sh` (solo la primera vez): detecta el usuario real dentro del contenedor, crea `/home/$usuario/MatrixMCU`, establece un enlace simbólico hacia `/workspace/projects` y guarda la ruta efectiva en `/tmp/matrixmcu_path`._  
> _• `postStartCommand` (cada vez que se abre el contenedor): añade dinámicamente a `~/.bashrc` la ruta efectiva guardada en `/tmp/matrixmcu_path`:_  
>
> ```bash
> export MATRIXMCU=/home/ubuntu/MatrixMCU
> 
> o
> 
> export MATRIXMCU=/home/dev/MatrixMCU
> ```
> _Esto garantiza compatibilidad con Windows, Linux y macOS y permite que el sistema detecte automáticamente la ruta al framework MatrixMCU._

### 🧭 Una vez dentro del DevContainer

Para trabajar en un proyecto específico, abre una terminal e introduce:

```bash
cd projects/mi_proyecto
code .
```

Esto abrirá el proyecto dentro del contenedor en una nueva ventana de VSCode, permitiéndote compilar, depurar y usar todas las tareas integradas.


---

## 🧪 6. Ejecutar MICROLAB

Tras haber construido el entorno e iniciado el DevContainer, puedes iniciar o detener el laboratorio virtual (servidor y frontend) utilizando los **Tasks** integrados de VSCode.

Estos tasks permiten:

- Levantar los contenedores necesarios (`rust-server`, `interfaz-grafica`)
- Conectar automáticamente el DevContainer a la red `lab_virtual_net`
- Abrir la interfaz web en el navegador (`http://localhost:5173`)


### ▶️ Iniciar MICROLAB

> ℹ️ **Nota importante:**  
> Después del paso anterior (`Reopen in Container`), solo tendrás abierta la carpeta `DockerMatrixMCU/` *dentro del DevContainer*.  
> Para ejecutar los tasks generales como **"Iniciar MICROLAB"** o **"Parar MICROLAB"**, necesitas volver a abrir la carpeta raíz del proyecto (`DockerMatrixMCU/`) desde fuera del contenedor.
>
> Puedes hacerlo con `Ctrl+K Ctrl+O` y seleccionando la carpeta original.  
> Así tendrás **dos ventanas de VSCode abiertas**: una con el entorno del DevContainer (`DockerMatrixMCU/`) y otra con el proyecto local donde están los tasks.

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

## 🔁 Cambios en CMake

En tu `CMakeLists.txt`, MatrixMCU se detecta así:

```cmake
IF(NOT DEFINED MATRIXMCU)
    SET(MATRIXMCU  $ENV{MATRIXMCU})
    MESSAGE(STATUS "MATRIXMCU path (env): ${MATRIXMCU}")
ENDIF()

INCLUDE(${MATRIXMCU}/CMakeLists.txt)
```

---

## 🐞 Cambios en `launch.json` (debug)

En lugar de rutas relativas, se usa `${env:MATRIXMCU}`:

```json
"serverpath": "${env:MATRIXMCU}/../qemu_new/build/qemu-system-arm",
"configFiles": ["${env:MATRIXMCU}/openocd/stm32f4x.cfg"],
"svdFile": "${env:MATRIXMCU}/svd/STM32F405RG.svd"
```

---

## 🛡️ Compatibilidad con UID y sistemas

### 🔍 ¿Por qué importa el UID?

Cuando usamos contenedores Docker, los archivos del proyecto se montan desde el sistema anfitrión (tu máquina) al contenedor.  
Para que el contenedor pueda **leer y escribir correctamente en esos archivos**, el usuario dentro del contenedor debe tener **el mismo UID (User ID)** que el del sistema anfitrión.

Esto es importante porque, si el UID no coincide, el contenedor podría no tener permisos para editar, compilar o guardar archivos en las carpetas compartidas.

#### 🧪 Ejemplo:

- En un sistema Linux real, el primer usuario suele tener UID `1000`, pero si ese UID ya está ocupado, el siguiente será `1001`, `1002`, etc.
- El entorno detecta automáticamente tu UID con `id -u` y crea un usuario con ese mismo UID dentro del contenedor (`dev:UID`).
- Así, los archivos montados siguen siendo accesibles y editables desde el contenedor sin problemas de permisos.

---

### ⚠️ ¿Y por qué no podemos hacer esto en Docker Desktop?

En **Docker Desktop** (Windows o macOS), los contenedores no se ejecutan directamente sobre tu sistema, sino dentro de una **máquina virtual Linux oculta**.

Esto implica que:

- El contenedor **no puede saber quién eres tú realmente** como usuario de Windows o macOS.
- No existe un UID/GID equivalente a tu cuenta local que se pueda detectar desde el contenedor.
- Aunque el contenedor cree un usuario con UID `1000`, **eso no significa nada real para el sistema host**.
- Todos los archivos montados desde Windows/macOS aparecerán como propiedad de `root` o de un UID simulado, y no se puede cambiar.

---

### ✅ Solución implementada por MatrixMCU

- En **Linux real**: se detecta el UID real (`id -u`) y se crea un usuario con ese UID en la imagen (`dev`), asegurando permisos correctos.
- En **Docker Desktop**: como no se puede detectar el UID real, el entorno usa un **usuario genérico (`ubuntu`)** con permisos amplios y preconfigurados.
- Se confía en que Docker Desktop monte los volúmenes con permisos que permitan escribir (lo cual suele funcionar correctamente si no se fuerzan UIDs).

Además:

- La ruta real `/home/dev/MatrixMCU` o `/home/ubuntu/MatrixMCU` se detecta automáticamente.
- La variable de entorno `$MATRIXMCU` se exporta de forma correcta en cada caso, sin intervención manual.

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

---

## 🧼 Opcional: detener el DevContainer manualmente

Si necesitas cerrar el entorno:

1. Abre la paleta (`Ctrl+Shift+P`)
2. Ejecuta `Dev Containers: Close Remote Connection`

Esto cierra el contenedor sin destruirlo. Puedes reabrirlo más tarde con `Reopen in Container`.

También puedes usar los tasks desde fuera del contenedor:   
```jsonc
"Parar dev-container MatrixMCU"
"Eliminar dev-container MatrixMCU"
```

-----
## 🛠️ Run OpenOCD Task

# 🔧 Instalación y uso de OpenOCD con DevContainer

---

## 🪟 Windows

### ✅ 1. Descargar el binario de OpenOCD

1. Ve a: [https://github.com/openocd-org/openocd/releases/tag/v0.12.0](https://github.com/openocd-org/openocd/releases/tag/v0.12.0)
2. Descarga:
   ```
   openocd-v0.12.0-i686-w64-mingw32.tar.gz
   ```

---

### 📦 2. Extraer el contenido

1. Crea una carpeta, por ejemplo:
   ```
   C:\tools\openocd
   ```
2. Extrae el `.tar.gz` en esa carpeta.
3. Entra en:
   ```
   C:\tools\openocd\bin
   ```
4. Ejecuta una prueba:

```powershell
& 'C:\tools\openocd\bin\openocd.exe' --version
```

🔐 Si aparece SmartScreen:
- Pulsa **Más información** → **Ejecutar de todas formas**
- O ve a Propiedades del `.exe` → marca **Desbloquear**

---

### 🛠 3. Añadir al PATH del sistema

1. Busca `Variables de entorno` en el menú de inicio.
2. Edita `Path` en **Variables del sistema**.
3. Añade esta ruta (o donde lo hayas guardado):
   ```
   C:\tools\openocd\bin
   ```
4. Guarda y **reinicia la terminal**.
5. Verifica:

```powershell
openocd --version
```

---

### 🧲 4. Instalar driver ST-Link

1. Descarga desde ST:
   👉 [https://www.st.com/en/development-tools/stsw-link009.html](https://www.st.com/en/development-tools/stsw-link009.html)
2. Instala el paquete (driver oficial ST-LINK).

---

### 🧪 5. Prueba desde el host (Windows)

Conecta la placa y ejecuta:

```powershell
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

🔧 Si da error, mantén pulsado RESET al lanzarlo.

También puedes usar la task:
```
Run OpenOCD (Windows)
```

---

>**Depuración desde DevContainer**
>En `launch.json`:
>
>```json
>"gdbTarget": "host.docker.internal:3333",
>"servertype": "external"
>```

---
## 🍏 macOS

### ✅ 1. Instalar OpenOCD con Homebrew

```bash
brew update
brew install open-ocd
```

> ⚠️ Nota: El paquete se llama `open-ocd` con guión.

---

### ✅ 2. Verificar instalación

```bash
openocd --version
```

---

### ✅ 3. Ejecutar con la placa conectada

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

> 🔐 En macOS no necesitas drivers, pero asegúrate de permitir acceso USB en Configuración del sistema > Seguridad y privacidad.

>**Depuración desde DevContainer**
>En `launch.json`:
>
>```json
>"gdbTarget": "host.docker.internal:3333",
>"servertype": "external"
>```

---
## 🐧 Linux

### ✅ 1. Instalar OpenOCD

```bash
sudo apt update
sudo apt install openocd
```

---

### ✅ 2. Verificar instalación

```bash
openocd --version
```

---

### ✅ 3. Prueba con placa conectada

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

🔧 Si falla, mantén pulsado RESET al lanzar.

---

# 🐧 Soporte Linux con IP externa (sin Docker Desktop)

## 🎯 Objetivo
Conectar desde el DevContainer al OpenOCD en el host Linux **sin usar `host.docker.internal`**, ya que no existe en Linux.

---

## 🧠 Solución automatizada

### Task en el host (Linux) para detectar IP y lanzar OpenOCD

```json
 {
			"label": "Recargar IP del Host (Linux)",
			"type": "shell",
			"command": "bash",
			"args": [
			  "-c",
			  "ip r get 1.1.1.1 | grep -oP 'src \\K[0-9.]+' > ./projects/.ip_host_openocd"
			],
			"problemMatcher": []
		  }
```

---

### En `devcontainer.json`:

```json
"postStartCommand": "if [ -f /workspaces/MatrixMCU/projects/.ip_host_openocd ]; then echo export OPENOCD_HOST_IP=$(cat /workspaces/MatrixMCU/projects/.ip_host_openocd) >> ~/.bashrc; fi"
```

---

### En `launch.json`:

```json
"gdbTarget": "${env:OPENOCD_HOST_IP}:3333"
```

---

## ✅ Resultado

- IP detectada automáticamente
- No necesitas tocar nada manualmente
- OpenOCD se lanza en el host y se comunica correctamente con GDB desde el DevContainer



## 🧪🧪🧪**Uso básico (FLUJO)**🧪🧪🧪
   - Conecta tu placa STM32 al USB. 

  > ***HOST***
  >
  > **SI estás en linux, es importante que en caso de no haberlo hecho antes de abrir el devcontainer, hagas la Task "Recargar IP del Host (Linux)". (y eliminar el devcontainer con la task)... (para que se recargue la variable d entorno OPENOCD_HOST_IP) Y luego habras el devcontainer** 

   - Ejecuta en PowerShell:
     ```powershell
     openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
     ```
     o el task: Run OPENOCD
     
   - Verás la salida de OpenOCD indicando que está “listening on port 3333”.
   
   <!-- Para que OpenOCD acceda al adaptador ST-Link, abre PowerShell o CMD **como Administrador**:
   ```powershell
   openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
   ``` -->
  ***DEVCONTAINER***
  -Launch.json: "Clean and Debug (stm32f446re) (External OpenOCD)





### Preguntas frecuentes

- **¿Puedo pararlo?**  
  Sí: pulsa el botón ■ “Terminate Task” en el panel de Terminal o presiona Ctrl+C en esa terminal.

- **¿Lo hago una vez y ya?**  
  Mientras la task siga activa no necesitas relanzarla.

- **¿Cómo funciona?**  
  Inicia OpenOCD en segundo plano escuchando en el puerto GDB (3333).  
  Tu DevContainer (VSCode) se conecta a ese puerto para depurar con Cortex-Debug.


---

¡Listo! Tu entorno está preparado para trabajar con MatrixMCU 🎉
