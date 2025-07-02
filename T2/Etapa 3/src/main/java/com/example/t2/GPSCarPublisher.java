package com.example.t2;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.util.Duration;
import java.util.Scanner;
import java.util.Locale;

public class GPSCarPublisher extends Publisher {

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

    public HBox getView(){return view;}

    private HBox view;
    private Label GPS;
    private Scanner GPSfile;
    private double xi,yi,xf,yf, time_i,time,time_f;
    Timeline timeline;
}
