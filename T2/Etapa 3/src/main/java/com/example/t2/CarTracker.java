package com.example.t2;

import javafx.geometry.Pos;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.scene.paint.Color;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import java.util.Scanner;
import javafx.application.Platform;
import java.util.Locale;

public class CarTracker extends Subscriber {
    public CarTracker(String name, String topicName) {
        super(name, topicName);
        stage = new Stage();
        //??
        car = new Circle(5, Color.RED);
        telemetry = new Label(String.format(Locale.US, "t=%.1f   x=%.2f   y=%.2f", 0.0, 0.0, 0.0));

        Pane pane = new Pane(car);
        pane.setPrefSize(400, 400);

        BorderPane root = new BorderPane();
        root.setCenter(pane);
        root.setBottom(telemetry);
        BorderPane.setAlignment(telemetry, Pos.CENTER);

        stage.setTitle("CarTracker: " + name);
        stage.setScene(new Scene(root));
    }

    @Override
    public void update(String message) {
         //??
        String[] parts = message.split("\\s+");
        try {
            double t = Double.parseDouble(parts[0]);
            double x = Double.parseDouble(parts[1]);
            double y = Double.parseDouble(parts[2]);
            Platform.runLater(() -> {
                car.setCenterX(x);
                car.setCenterY(y);
                telemetry.setText(
                        String.format(Locale.US, "t=%.1f  x=%.1f  y=%.1f", t, x, y)
                );
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void show() {
        stage.show();
    }

    private final Stage stage;
    private final Circle car;
    private final Label telemetry;
}
