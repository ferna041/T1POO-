# Biblioteca Vecinal de Objetos Compartidos

Sistema de gestión para compartir objetos entre vecinos de una comunidad desarrollado en C++ con Qt Framework.

## Requisitos

- Qt Framework 6.9.1 o superior
- Compilador MinGW 64-bit
- SQLite 3 (incluido con Qt)
- Windows

## Instalación

1. Descargar e instalar Qt desde qt.io
2. Instalar Qt Creator con MinGW compiler
3. Agregar las rutas de Qt al PATH del sistema

Para verificar que todo está instalado correctamente:
```
qmake --version
g++ --version
```

## Compilación y Ejecución

### Opción 1: Usando el Makefile

```
make help
make run
make build
make clean
```

### Opción 2: Comandos manuales

```
cd "c:\Users\Seba4\Desktop\U\POO\Tareas\Proyecto"
qmake Proyecto.pro
mingw32-make
cd build\Desktop_Qt_6_9_1_MinGW_64_bit-Debug
.\Proyecto.exe
```

### Opción 3: Qt Creator

1. Abrir Qt Creator
2. File -> Open File or Project
3. Seleccionar Proyecto.pro
4. Configurar MinGW 64-bit
5. Ctrl + R para compilar y ejecutar

## Estructura del Proyecto

```
Proyecto/
├── src/
│   ├── models/
│   ├── database/
│   ├── ui/
│   └── main.cpp
├── build/
├── Proyecto.pro
└── README.md
```

## Uso

1. Registrar usuario con datos personales
2. Publicar objetos disponibles para préstamo
3. Buscar objetos en el catálogo
4. Reservar objetos
5. Gestionar reservas activas
6. Recibir notificaciones

## Problemas Comunes

### "qmake no se reconoce como comando"
- Verificar instalación de Qt
- Agregar C:\Qt\6.9.1\mingw_64\bin al PATH

### Error de compilación
- Verificar dependencias instaladas
- Ejecutar: make clean && make

### "Cannot find -lQt6Core"
- Verificar kit de compilación
- Reinstalar Qt con dependencias

## Base de Datos

La aplicación crea automáticamente biblioteca_vecinal.db con estas tablas:
- usuarios
- objetos
- reservas
- notificaciones
