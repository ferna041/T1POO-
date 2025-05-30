package com.example.t2;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;

public class VideoFollower extends Subscriber {
   public VideoFollower(String name, String topicName) {
      super(name, topicName);
      //??
      Label info = new Label("Sub[" + getName() + "] → " + topicName + ":");

      video = new Button("Waiting for video...");
      video.setPrefWidth(300);

      view = new HBox(10, info, video);
   }
   public void update(String message) {
      //??
      video.setText(message);
   }
   public HBox getView() {return view;}
   private HBox view;
   private Button video;
}