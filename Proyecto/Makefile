# Makefile para Biblioteca Vecinal de Objetos Compartidos
# Sistema de gestión para compartir objetos entre vecinos

# Variables de configuración
PROJECT_NAME = Proyecto
BUILD_DIR = build/Desktop_Qt_6_9_1_MinGW_64_bit-Debug
EXECUTABLE = $(BUILD_DIR)/$(PROJECT_NAME).exe
QT_MAKEFILE = Makefile

# Colores para mensajes (Windows PowerShell)
BLUE = [94m
GREEN = [92m
YELLOW = [93m
RED = [91m
NC = [0m

# Objetivo por defecto
.DEFAULT_GOAL := help

# Ayuda - muestra todos los comandos disponibles
help:
	@echo "$(BLUE)=== Biblioteca Vecinal de Objetos Compartidos ===$(NC)"
	@echo "$(GREEN)Comandos disponibles:$(NC)"
	@echo "  $(YELLOW)make run$(NC)      - Compilar y ejecutar la aplicación"
	@echo "  $(YELLOW)make build$(NC)    - Solo compilar el proyecto"
	@echo "  $(YELLOW)make clean$(NC)    - Limpiar archivos compilados"
	@echo "  $(YELLOW)make rebuild$(NC)  - Limpiar y recompilar todo"
	@echo "  $(YELLOW)make install$(NC)  - Verificar dependencias"
	@echo "  $(YELLOW)make help$(NC)     - Mostrar esta ayuda"

# Verificar dependencias
install:
	@echo "$(BLUE)Verificando dependencias...$(NC)"
	@qmake --version || (echo "$(RED)Error: qmake no encontrado. Instalar Qt Framework$(NC)" && exit 1)
	@g++ --version || (echo "$(RED)Error: g++ no encontrado. Instalar MinGW$(NC)" && exit 1)
	@echo "$(GREEN)✓ Todas las dependencias están instaladas$(NC)"

# Generar Makefile de Qt
$(QT_MAKEFILE): $(PROJECT_NAME).pro
	@echo "$(BLUE)Generando Makefile de Qt...$(NC)"
	@qmake $(PROJECT_NAME).pro

# Compilar el proyecto
build: $(QT_MAKEFILE)
	@echo "$(BLUE)Compilando proyecto...$(NC)"
	@mingw32-make -f $(QT_MAKEFILE)
	@if exist "$(EXECUTABLE)" ( \
		echo "$(GREEN)✓ Compilación exitosa$(NC)" \
	) else ( \
		echo "$(RED)✗ Error en la compilación$(NC)" && exit 1 \
	)

# Ejecutar la aplicación
execute:
	@echo "$(BLUE)Ejecutando aplicación...$(NC)"
	@if exist "$(EXECUTABLE)" ( \
		cd $(BUILD_DIR) && $(PROJECT_NAME).exe \
	) else ( \
		echo "$(RED)✗ Ejecutable no encontrado. Usar 'make build' primero$(NC)" && exit 1 \
	)

# Compilar y ejecutar en un solo comando
run: build execute

# Limpiar archivos compilados
clean:
	@echo "$(BLUE)Limpiando archivos compilados...$(NC)"
	@if exist "$(QT_MAKEFILE)" mingw32-make -f $(QT_MAKEFILE) clean
	@if exist "$(QT_MAKEFILE)" del /f "$(QT_MAKEFILE)"
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)" 2>nul || echo "Directorio build ya limpio"
	@echo "$(GREEN)✓ Limpieza completada$(NC)"

# Recompilar todo desde cero
rebuild: clean build

# Crear directorio de build si no existe
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

# Comandos que no crean archivos
.PHONY: help install build execute run clean rebuild

# Información adicional
info:
	@echo "$(BLUE)=== Información del Proyecto ===$(NC)"
	@echo "Nombre: $(PROJECT_NAME)"
	@echo "Directorio de build: $(BUILD_DIR)"
	@echo "Ejecutable: $(EXECUTABLE)"
	@echo "$(GREEN)Para comenzar, usar: make run$(NC)"
