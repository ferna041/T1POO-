package com.example.t2;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.util.Duration;
import java.util.Scanner;
import java.util.Locale;

/**
 * Simula un publicador GPS de un vehículo que reporta su posición en tiempo real.
 * Esta clase extiende Publisher y publica continuamente la posición del vehículo
 * basándose en datos de un archivo que contiene coordenadas GPS con timestamps.
 * 
 * La clase interpola entre puntos GPS para simular movimiento suave del vehículo
 * y actualiza tanto la interfaz visual como publica eventos de posición.
 * 
 * @author GrupoT2
 * @version 1.0
 * @since 2025
 */
public class GPSCarPublisher extends Publisher {

    /**
     * Constructor que crea un publicador GPS para un vehículo.
     * Inicializa la animación temporal que reporta posiciones y configura la interfaz visual.
     * 
     * @param name el nombre identificador del vehículo
     * @param broker el broker que maneja la comunicación
     * @param topicName el nombre del tópico donde se publicarán las posiciones GPS
     * @param scanner fuente de datos GPS que contiene: tiempo, coordenada X, coordenada Y
     */
    public GPSCarPublisher(String name, Broker broker, String topicName, Scanner scanner) {
        super(name, broker, topicName);
        view = new HBox();
        GPS = new Label();
        view.getChildren().addAll(new Label(name + "->" + topicName+":"), GPS);
        GPSfile = scanner;
        timeline = new Timeline(new KeyFrame(Duration.millis(1000), e -> reportPosition()));
        if (GPSfile.hasNextDouble()) {
            time_i = GPSfile.nextDouble();
            xi = GPSfile.nextDouble();
            yi = GPSfile.nextDouble();
        }
        if (GPSfile.hasNextDouble()) {
            time_f = GPSfile.nextDouble();
            xf = GPSfile.nextDouble();
            yf = GPSfile.nextDouble();
        }
        time = time_i;
        String initMsg = String.format(Locale.US, "%.1f %.1f %.1f", time, xi, yi);
        publishNewEvent(initMsg);
        GPS.setText(initMsg);

        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();
    }

    /**
     * Método privado que calcula y reporta la posición actual del vehículo.
     * Interpola entre dos puntos GPS para simular movimiento suave.
     * Cuando se alcanza el punto final, avanza al siguiente segmento del recorrido.
     * Si no hay más datos GPS, detiene la simulación.
     */
    private void reportPosition() {
        if (time < time_f) {
            time += 1;
            double frac = (time - time_i) / (time_f - time_i);
            double x = xi + frac * (xf - xi);
            double y = yi + frac * (yf - yi);
            String msg = String.format(Locale.US, "%.1f %.1f %.1f", time, x, y);
            publishNewEvent(msg);
            GPS.setText(msg);
        } else {
            xi = xf;
            yi = yf;
            time_i = time_f;
            time = time_i;
            if (GPSfile.hasNextDouble()) {
                time_f = GPSfile.nextDouble();
                xf = GPSfile.nextDouble();
                yf = GPSfile.nextDouble();
            } else {
                timeline.stop();
            }
        }
    }

    /**
     * Obtiene la vista visual del componente GPS.
     * 
     * @return un HBox que contiene la representación visual del estado actual del GPS
     */
    public HBox getView(){return view;}

    /**
     * Contenedor visual que muestra el estado del GPS en la interfaz.
     */
    private HBox view;
    
    /**
     * Etiqueta que muestra la información de posición actual del GPS.
     */
    private Label GPS;
    
    /**
     * Scanner que lee los datos GPS desde el archivo fuente.
     */
    private Scanner GPSfile;
    
    /**
     * Coordenadas inicial (xi, yi) y final (xf, yf) del segmento actual,
     * junto con los tiempos inicial (time_i), actual (time) y final (time_f).
     */
    private double xi,yi,xf,yf, time_i,time,time_f;
    
    /**
     * Timeline que controla la animación temporal y las actualizaciones periódicas de posición.
     */
    Timeline timeline;
}
