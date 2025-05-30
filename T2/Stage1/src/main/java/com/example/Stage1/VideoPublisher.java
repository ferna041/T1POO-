package com.example.tarea2;

import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;

public class VideoPublisher extends Publisher {
    private VBox view;

    public VideoPublisher(String name, String topic) {
        super(name, topic);

        Label infoLabel = new Label("Publicador: " + name + " | Tópico: " + topic);

        TextField urlField = new TextField();
        urlField.setPromptText("Ingrese URL del video");
        urlField.setOnAction(e -> {
            String url = urlField.getText();
            publish(url);
            urlField.clear();
        });

        view = new VBox(infoLabel, urlField);
        view.setSpacing(5);
    }

    public VBox getView() {
        return view;
    }
}

