package com.example.tarea2;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;

public class VideoFollower extends Subscriber {
    private VBox view;
    private Button videoButton;

    public VideoFollower(String name, String topic) {
        super(name, topic);

        Label infoLabel = new Label("Suscriptor: " + name + " | Tópico: " + topic);

        videoButton = new Button("Esperando video...");
        videoButton.setPrefWidth(300);

        view = new VBox(infoLabel, videoButton);
        view.setSpacing(5);
    }

    @Override
    public void receive(String message) {
        videoButton.setText(message);  // En esta etapa solo se actualiza el texto
    }

    public VBox getView() {
        return view;
    }
}
