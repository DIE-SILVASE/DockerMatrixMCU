# 🧪 TUTORIAL MatrixMCU (VERSION NO FINALIZADA)

Este tutorial te guía paso a paso para tener MatrixMCU listo en tu ordenador con Visual Studio Code.

---

## ✅ Requisitos previos

Instala lo siguiente antes de empezar:

- [Git](https://git-scm.com/)
- [Docker](https://docs.docker.com/get-docker/)
- [Visual Studio Code](https://code.visualstudio.com/)
- Extensión de VSCode: [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

>
> Solamente si vas a conectar la placa física:
>
>### Windows
>
>1. Ve a la página de descargas:  
    [https://github.com/openocd-org/openocd/releases/tag/v0.12.0](https://github.com/openocd-org/openocd/releases/tag/v0.12.0)
>2. Descarga el archivo:  
   `openocd-v0.12.0-i686-w64-mingw32.tar.gz`
>3. Crea una carpeta, por ejemplo:  
   `C:\tools\openocd`
>4. Extrae el archivo `.tar.gz` en esa carpeta.
>5. Ve a:  
   `C:\tools\openocd\bin` y asegurate de que ahí está openocd.exe
>6. Ejecuta este comando en PowerShell:
>```powershell
>    'C:\tools\openocd\bin\openocd.exe' --version
>```
>🔐 Si Windows SmartScreen bloquea la ejecución:
>- Haz clic en **Más información** → **Ejecutar de todas formas**
>- O botón derecho sobre el `.exe` → **Propiedades** → marca **Desbloquear**
>#### 🛠 3. Añadir OpenOCD al PATH del sistema
>
>1. Abre el menú de inicio y busca **Variables de entorno**.
>2. Edita la variable `Path` en **Variables del sistema**.
>3. Añade esta ruta (o la que hayas usado):  
   `C:\tools\openocd\bin`
>4. Guarda y **reinicia la terminal**.
>5. Comprueba que funciona:
>
>```powershell
>openocd --version
>```
>
>7. Instala driver: [ST-LINK](https://www.st.com/en/development-tools/stsw-link009.html)
>
>### macOS
>
>```bash
>brew install open-ocd
>openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
>```
>
>### Linux
>
>```bash
>sudo apt install openocd
>openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
>```

---

## 📥 Paso 1. Clonar el repositorio

Abre la terminal y escribe:

```bash
git clone https://github.com/DIE-SILVASE/DockerMatrixMCU.git
```

---

## 🏗️ Paso 2. Construir el entorno (una sola vez)

1. Abre la carpeta `DockerMatrixMCU/` en VSCode.
2. Pulsa `Ctrl+Shift+P` (o `⌘+Shift+P` en Mac).
3. Escribe y selecciona:  
   `Tasks: Run Task > Build MatrixMCU Environment`

---

## 🚪 Paso 3. Abrir el entorno

1. Pulsa `Ctrl+Shift+P` (o `⌘+Shift+P`).
2. Escribe y selecciona:  
   `Dev Containers: Reopen in Container`

---

## ▶️ Paso 4. Iniciar MICROLAB

1. Abre de nuevo la carpeta `DockerMatrixMCU/` desde fuera del contenedor (`Ctrl+K Ctrl+O`).
2. Pulsa `Ctrl+Shift+P` y ejecuta la task según tu sistema:

   - **Linux/macOS**: `Iniciar MICROLAB (Linux/Mac)`
   - **Windows**: `Iniciar MICROLAB (Windows)`

---

## 🛑 Paso 5. Parar MICROLAB

- **Linux/macOS**: `Parar MICROLAB (Linux/Mac)`
- **Windows**: `Parar MICROLAB (Windows)`

---

## 🐞 Paso 6. Debug con QEMU

1. Abre tu proyecto dentro del contenedor:
   ```bash
   cd projects/MI_PROYECTO
   code .
   ```
2. Ve a la pestaña "Run and Debug".
3. Selecciona `Microlab` y pulsa ▶️.

---

## 🧪 Paso 7. Uso básico de OpenOCD

### Windows

1. Instala [OpenOCD](https://github.com/openocd-org/openocd/releases/tag/v0.12.0)
2. Añade al PATH: `C:	ools\openocdin`
3. Instala driver: [ST-LINK](https://www.st.com/en/development-tools/stsw-link009.html)
4. Conecta tu placa y lanza:

```powershell
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

### macOS

```bash
brew install open-ocd
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

### Linux

```bash
sudo apt install openocd
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

---

## 🧠 Paso 8. Conexión desde DevContainer

### Linux

1. Ejecuta la task:
   `Recargar IP del Host (Linux)`
2. Elimina y vuelve a abrir el DevContainer.

### VSCode

- En la vista de depuración, selecciona:
  `Clean and Debug (stm32f446re) (External OpenOCD)`

---

## 🧹 Opcional: cerrar DevContainer

Pulsa `Ctrl+Shift+P`  
Selecciona: `Dev Containers: Close Remote Connection`

---

## 🧰 Lista de Tasks disponibles

```txt
🔧 Build MatrixMCU Environment
▶️ Iniciar MICROLAB (Linux/Mac)
▶️ Iniciar MICROLAB (Windows)
⏹ Parar MICROLAB (Linux/Mac)
⏹ Parar MICROLAB (Windows)
🧪 Run OPENOCD
🔁 Recargar IP del Host (Linux)
🧹 Parar dev-container MatrixMCU
🗑️ Eliminar dev-container MatrixMCU
```

---

¡Listo! Ya puedes trabajar con MatrixMCU desde VSCode 🎉