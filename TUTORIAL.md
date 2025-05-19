# 🧪 TUTORIAL MatrixMCU 

Este tutorial te guía paso a paso para tener MatrixMCU listo en tu ordenador con Visual Studio Code.

---

## ✅ Requisitos previos

Instala lo siguiente antes de empezar:

- [Docker Desktop](https://www.docker.com/products/docker-desktop/)
- [Visual Studio Code](https://code.visualstudio.com/)
- Extensión de VSCode: [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

### ⚠️ IMPORTANTE: Mantén Docker Desktop abierto siempre que quieras trabajar con MICROLAB

MICROLAB necesita que mantengas la app Docker Desktop abierta.
De lo contrario, no podrá ejecutar los diferentes contenedores Docker necesarios para que todo funcione.
- Asegurate de que Docker Daemon está corriendo
Para ello, abre docker Desktop y abajo a la izquierda deberías ver: engine running

---

## 📥 Paso 1. Descargar el repositorio

- Ve a la página  
[https://github.com/DIE-SILVASE/DockerMatrixMCU.git](https://github.com/DIE-SILVASE/DockerMatrixMCU.git)  
- Descárgate el ZIP y descomprímelo donde quieras.

---

## 🏗️ Paso 2. Descargar las imágenes (solo la primera vez)

1. Abre la carpeta `DockerMatrixMCU/` en VSCode.  
2. Pulsa `Ctrl+Shift+P` (o `⌘+Shift+P` en Mac).  
3. Escribe y selecciona:  
   `Tasks: Run Task > Descargar imágenes`

---

## 🚪 Paso 3. Abrir el entorno

1. Pulsa `Ctrl+Shift+P` (o `⌘+Shift+P`).  
2. Escribe y selecciona:  
   `Dev Containers: Reopen in Container`
3. ¡Ya está! 🎉

Si quieres asegurarte de que está todo funcionando, abre la aplicación Docker Desktop y ve a la pestaña *Containers*.
Verás un servicio *setup* compuesto por tres contenedores (`rust-server`, `matrixmcu-env`, e `interfaz-grafica`).
Como indica la bolita verde, todos los contenedores están funcionando.

### ⚠️ IMPORTANTE: Asegúrate que los plugins se han cargado correctamente

La primera vez que te conectes al DevContainer que ejecuta el entorno de MICROLAB, es probable que los plugins necesarios no carguen correctamente.
Cuando esto ocurre, aparecerá en la esquina inferior derecha un mensaje parecido a:

> ❌ Cannot activate the 'Cortex Debug' extension because it depends on the 'debug-tracker-vscode' extension, which is not loaded. Would you like to reload the window to load the extension?

Haz click en `Reload Window` para que se recarguen todos los plugins.

---
---
---
---
---

##  🧪 DEMO 1 → Simulación básica en QEMU


**Dentro del contenedor**, en la pestaña `Run and Debug`, selecciona:

- `Clean and Debug (QEMU) → example_blink`

Puedes:

- Poner puntos de parada (¡prueba a poner uno en la línea 18!)
- Observar los periféricos en `XPERIPHERALS` (abajo a la izquierda) (¡prueba a observar el estado del LED de la nucleo (`GPIOA` PIN 5)!).

---

## 🧪 DEMO 2 → Uso de la interfaz gráfica MICROLAB

### Paso 1. Iniciar MICROLAB

1. Abre tu navegador Web favorito y escribe la siguiente URL: `localhost:5173` o pincha aquí: [MICROLAB](http://localhost:5173)

2. Deberías ser capaz de ver la interfaz gráfica de MICROLAB.

#### ⚠️ IMPORTANTE: Asegúrate de poner tu navegador en modo *light*

MICROLAB todavía no está optimizado para funcionar en modo *Dark* (ya sabes: fondo negro y letras blancas). Por favor, asegúrate que tu navegador funciona en modo *light* mientras trabajas con MICROLAB.

### Paso 2. Volver al contenedor

**Dentro del contenedor**, en la pestaña `Run and Debug`, selecciona:

- `Debug MICROLAB (QTest) → example_blink `
- Refresca la página web de la interfaz gráfica de MICROLAB.
  - Como en el ejercicio anterior, pon puntos de parada y observa como el LED de la nucleo cambia de color en la interfaz gráfica de MICROLAB.

- `Debug MICROLAB (QTest) → example_button`
   - Desde la interfaz gráfica, pulsa el botón de usuario (azul) durante más de un segundo y observa como se enciende y apaga el LED.

- `Debug MICROLAB (QTest) → example_pwm`  
   - Pulsa el botón de usuario (azul) durante más de un segundo y observa cómo cambia la intensidad de la luz del LED.
   - Inspecciona la caja informativa del pin del LED y observa la configuración mostrada. ¿Coincide el ciclo de trabajo mostrado con lo que tú esperarías?

> Puedes seleccionar distintos pines en la placa o los puedes seleccionar desde el buscador para que la interfaz gráfica de MICROLAB te muestre su configuración actual. 

### Paso 3. Parar MICROLAB

Cierra la ventana de VSCode. Con esto, el entorno se parará automáticamente.
Si quieres asegurarte, abre la aplicación Docker Desktop y ve a la pestaña *Containers*.
Verás un servicio *setup* compuesto por tres contenedores (`rust-server`, `matrixmcu-env`, e `interfaz-grafica`).
Como indica la bolita gris, todos los contenedores están apagados.



---
---
---
---
---
---
---



## 🧯 Parar los contenedores

Para cerrar el devcontainer cierra la ventana del contenedor y tienes las siguientes opciones:


#### Desde **Visual Studio Code**

puedes detener los contenedores manualmente desde una tarea:

1. Abre de nuevo la carpeta DockerMatrixMCU en Vscode (Pero asegurate de que sea en local, no el contenedor!!!)
2. Pulsa `Ctrl+Shift+P` (o `⌘+Shift+P` en Mac).
3. Escribe y selecciona:  
   `Tasks: Run Task`
4. Elige la tarea:  
   `Parar contenedores`

#### Desde **Docker Desktop**

1. Abre **Docker Desktop**.
2. Ve a la pestaña **"Containers"** (Contenedores) en el panel lateral izquierdo.
3. Localiza los contenedores en ejecución asociados al entorno (por ejemplo, `setup`, `interfaz-grafica`, `rust-server`).
4. Pulsa el botón **"Stop" (■)** a la derecha de cada contenedor para detenerlo.




## 🛑 Finalizar: Eliminar contenedores e imágenes (opcional)

Puedes borrar los contenedres e imágenes desde Docker Desktop si ya no las necesitas:

#### Contenedores

1. Abre **Docker Desktop**.
2. En la pestaña **"Containers"**, localiza los contenedores que desees eliminar.
3. Haz clic en el icono de la **papelera 🗑️** al lado del contenedor.
4. Confirma la eliminación.

#### Imágenes

1. Abre **Docker Desktop**.
2. Ve a la pestaña **"Images"** (Imágenes) en el panel lateral izquierdo.
3. Busca las imágenes que quieras eliminar:
   - `iivvjj/interfaz-grafica`
   - `iivvjj/rust-server`
   - `iivvjj/matrixmcu-env`
4. Haz clic en la **papelera 🗑️** a la derecha de cada imagen.
5. Confirma que deseas eliminarlas.


---
---
---
---
---
---


## 🧰 Lista de Tasks disponibles

```txt
🔧 Descargar imágenes
🧹 Parar contenedores
🧪 Ejecutar OpenOCD
```
