package com.example.t2;

import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;

public class VideoPublisher extends Publisher {
    public VideoPublisher(String name, Broker broker, String topicName) {
        super(name, broker, topicName);
        //??
        Label info = new Label("Pub[" + getName() + "] → " + topicName + ":");

        message = new TextField();
        message.setPromptText("Enter video URL and press ENTER");
        message.setOnAction(e -> {
            String url = message.getText().trim();
            if (!url.isEmpty()) {
                publishNewEvent(url);
                message.clear();
            }
        });

        view = new HBox(10, info, message);
    }
    public HBox getView(){return view;}
    private HBox view;
    private TextField message;
}