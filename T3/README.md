# Entrega Proyecto Qt

Este proyecto implementa un simulador del patrón Publicador-Suscriptor utilizando Qt Creator y C++. La implementación incluye funcionalidad tanto para publicadores/suscriptores de video como de GPS, con características adicionales de control de volumen en la interfaz principal y en el visualizador de videos(Bonus).

## Archivos que componen el proyecto

### Archivos principales
- `main.cpp` - Punto de entrada de la aplicación
- `mainwindow.cpp` / `mainwindow.h` / `mainwindow.ui` - Interfaz principal de usuario
- `Entrega.pro` - Archivo de configuración del proyecto Qt

### Patrón Publicador-Suscriptor
- `broker.cpp` / `broker.h` - Implementación del broker que gestiona tópicos y suscriptores
- `component.cpp` / `component.h` - Clase base para componentes del sistema
- `publisher.cpp` / `publisher.h` - Clase base para publicadores
- `subscriber.cpp` / `subscriber.h` - Clase base para suscriptores
- `topic.cpp` / `topic.h` - Gestión de tópicos del sistema

### Funcionalidad de Video
- `videopublisher.cpp` / `videopublisher.h` - Publicador de URLs de video
- `videofollower.cpp` / `videofollower.h` - Suscriptor que reproduce videos con control de volumen

### Funcionalidad GPS
- `gpscarpublisher.cpp` / `gpscarpublisher.h` - Publicador de posiciones GPS con interpolación lineal
- `gpscarfollower.cpp` / `gpscarfollower.h` - Suscriptor que muestra seguimiento de posiciones GPS

## Instrucciones para ejecutar el proyecto

1. Abre Qt Creator
2. Selecciona **Archivo > Abrir Proyecto** y elige el archivo `Entrega.pro`
3. Configura el kit de compilación (se recomienda MinGW 64-bit)
4. Haz clic en **Construir** para compilar el proyecto
5. Haz clic en **Ejecutar** para iniciar la aplicación

## Funcionalidades implementadas

- **Publicador/Suscriptor de Video**: Permite publicar URLs de video y reproducirlas en una ventana independiente con controles de volumen
- **Publicador/Suscriptor GPS**: Carga archivos de posiciones GPS, realiza interpolación lineal entre puntos y muestra seguimiento en tiempo real
- **Control de Volumen**: Slider de volumen tanto en la interfaz principal como en el reproductor de video
- **Interfaz Gráfica**: Ventana principal organizada con secciones para publicadores y suscriptores

## Consideraciones finales

1. Para ver el avance del GPS, se debe cargar el archivo, clickear en Mostrar Ventana de Seguimiento y finalmente Iniciar Simulación
