# 🧪 TUTORIAL MatrixMCU 

Este tutorial te guía paso a paso para tener MatrixMCU listo en tu ordenador con Visual Studio Code.

---

## ✅ Requisitos previos

Instala lo siguiente antes de empezar:

- [Docker Desktop](https://www.docker.com/products/docker-desktop/)
- [Visual Studio Code](https://code.visualstudio.com/)
- Extensión de VSCode: [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

---

## 📥 Paso 1. Descargar el repositorio

Ve a la página  
[https://github.com/DIE-SILVASE/DockerMatrixMCU.git](https://github.com/DIE-SILVASE/DockerMatrixMCU.git)  
Descárgate el ZIP y descomprímelo donde quieras.

---

## 🏗️ Paso 2. Descargar las imágenes (una sola vez)

1. Abre la carpeta `DockerMatrixMCU/` en VSCode.  
2. Pulsa `Ctrl+Shift+P` (o `⌘+Shift+P` en Mac).  
3. Escribe y selecciona:  
   `Tasks: Run Task > Download Images`

---

## 🚪 Paso 3. Abrir el entorno

1. Pulsa `Ctrl+Shift+P` (o `⌘+Shift+P`).  
2. Escribe y selecciona:  
   `Dev Containers: Reopen in Container`


## 🎉 ¡Entorno funcionando!

---
---
---
---
---

##  🧪 DEMO 1 → Simulación básica en QEMU


Dentro del contenedor, selecciona:

- `Clean and Debug (QEMU) → example_blink`

Puedes:

- Poner puntos de parada  
- Observar los periféricos en XPERIPHERALS (abajo a la izquierda), por ejemplo el led (GPIOA PIN 5).
---

## 🧪 DEMO 2 → Uso de la interfaz gráfica MICROLAB

### Paso 1. Iniciar MICROLAB

1. Abre de nuevo la carpeta `DockerMatrixMCU/` desde **fuera del contenedor**.  
2. Pulsa `Ctrl+Shift+P` y ejecuta la tarea:

   ```
   Iniciar MICROLAB
   ```

> Es probable que, al abrirse la página, el entorno aún no esté listo.  
> **Refresca la ventana** hasta que aparezca la interfaz de MICROLAB.

### Paso 2. Volver al contenedor

Ejecuta:

- `Clean and Debug MICROLAB (QTest) → example_blink `  
  - puntos de parada  
  - observar periféricos (LED GPIO A5)

- `Clean and Debug MICROLAB (QTest) → example_button`
   -Pulsa el botón de usuario (azul) durante más de un segundo y observa como se enciende y apaga el led

- `Clean and Debug MICROLAB (QTest) → example_pwm`  
   -Pulsa el botón de usuario (azul) durante más de un segundo y observa como cambia la intensidad de la luz del led.

> Puedes seleccionar distintos pines en la placa o los puedes seleccionar desde el buscador.  

### Paso 3. Parar MICROLAB

Desde la ventana de VSCode **fuera del contenedor**, ejecuta:

```
Parar MICROLAB
```

---

📦 Puedes comprobar en Docker Desktop cómo los contenedores `interfaz-grafica` y `rust-server` han sido detenidos.

---

## 🧪 DEMO 3 → Depuración con placa física (OpenOCD)

### 🔧 Instalación (solo si vas a conectar la placa)

#### Windows

1. Descarga desde:  
   [https://github.com/openocd-org/openocd/releases/tag/v0.12.0](https://github.com/openocd-org/openocd/releases/tag/v0.12.0)
2. Archivo:  
   `openocd-v0.12.0-i686-w64-mingw32.tar.gz`
3. Extrae el contenido en:  
   `C:\tools\openocd`
4. Verifica que `openocd.exe` está en:  
   `C:\tools\openocd\bin`
5. Comprueba la instalación:
```powershell
'C:\tools\openocd\bin\openocd.exe' --version
```

🛡️ Si Windows SmartScreen bloquea la ejecución:

- Haz clic en **Más información → Ejecutar de todas formas**
- O haz clic derecho en el `.exe` → **Propiedades → Desbloquear**

6. Instala el driver [ST-LINK](https://www.st.com/en/development-tools/stsw-link009.html)

#### macOS

```bash
brew install open-ocd
```

#### Linux

```bash
sudo apt install openocd
```

---

### Paso 1. Conectar la placa
Conecta la placa a tu ordenador.

### Paso 2. Ejecutar OpenOCD

Desde **VSCode fuera del contenedor**, ejecuta la task:

```
RUN OpenOCD
```

### Paso 3. Volver al contenedor

Ejecuta:

- `Clean and Debug (stm32f446re) (Docker) → example_blink `
  - puntos de parada  
  - mirar periféricos (SVD)  

>Nota: los logs del código aparecen en la terminal del host


- `Clean and Debug (stm32f446re) (Docker) → example_pwm`

### Paso 4. Parar OpenOCD

En la terminal de VSCode fuera del contenedor, pulsa `Ctrl+C` para detener la tarea.

---
---
---
---
---
---
---

## 🛑 Finalizar

Para cerrar el devcontainer:

1. Cierra la ventana del contenedor  
2. Opcionalmente, desde las tareas:

   - 🧹 `Parar dev-container MatrixMCU`  
   - 🗑️ `Eliminar dev-container MatrixMCU`

Puedes borrar las imágenes desde Docker Desktop si ya no las necesitas.

---
---
---
---
---
---


## 🧰 Lista de Tasks disponibles

```txt
🔧 Download images
▶️ Iniciar MICROLAB
⏹ Parar MICROLAB
🧪 Run OPENOCD
🧹 Parar dev-container MatrixMCU
🗑️ Eliminar dev-container MatrixMCU
```
