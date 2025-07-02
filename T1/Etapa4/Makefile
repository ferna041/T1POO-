# Makefile para la Etapa 2 de T1POO

# Compilador de Java
JAVAC = javac

# Directorios
SRC_DIR = src
BIN_DIR = bin

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.java)
CLASSES = $(SOURCES:$(SRC_DIR)/%.java=$(BIN_DIR)/%.class)

# Objetivo por defecto: compilar todo
all: $(BIN_DIR) $(CLASSES)

# Crear directorio bin si no existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compilar todos los archivos .java juntos
$(CLASSES): $(SOURCES)
	$(JAVAC) -d $(BIN_DIR) $(SOURCES)

# Ejecutar el programa
run: all
	java -cp $(BIN_DIR) Simulador config.txt

# Limpiar archivos generados (.class) y archivos de salida
clean:
	rm -rf $(BIN_DIR)/*.class
	rm -f seguidor_1.txt
	rm -f seguidor_2.txt
	rm -f trayectoria.csv
	rm -f ubicacion.txt

# Phony targets
.PHONY: all run clean