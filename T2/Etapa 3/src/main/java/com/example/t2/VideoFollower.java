package com.example.t2;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.HBox;
import javafx.scene.layout.BorderPane;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import javafx.util.Duration;

public class VideoFollower extends Subscriber {
   public VideoFollower(String name, String topicName) {
      super(name, topicName);
      //??
      Label info = new Label("Sub[" + getName() + "] → " + topicName + ":");

      video = new Button("Nothing yet.");
      video.setPrefWidth(300);
      video.setOnAction(e -> {
         if (!lastUrl.isEmpty()) {
            playVideo(lastUrl);
         }
      });

      view = new HBox(10, info, video);
      view.setPadding(new Insets(5));
      view.setAlignment(Pos.CENTER_LEFT);
   }

   @Override
   public void update(String message) {
      //??
      lastUrl = message;
      Platform.runLater(() -> video.setText(message));
   }

   public HBox getView() {return view;}

   private void playVideo(String url) {
      Media media = new Media(url);
      MediaPlayer player = new MediaPlayer(media);
      MediaView mediaView = new MediaView(player);

      // Botón retroceder 5 segundos
      Button backButton = new Button("<<");
      backButton.setOnAction(e -> {
         Duration current = player.getCurrentTime();
         Duration newTime = current.subtract(Duration.seconds(5));
         if (newTime.lessThan(Duration.ZERO)) {
            newTime = Duration.ZERO;
         }
         player.seek(newTime);
      });

      // Botón play/pause
      Button playPause = new Button("▶");
      playPause.setOnAction(e -> {
         if (player.getStatus() == MediaPlayer.Status.PLAYING) {
            player.pause();
            playPause.setText("▶");
         } else {
            player.play();
            playPause.setText("⏸");
         }
      });

      // Slider de volumen
      Slider volume = new Slider(0, 1, 0.5);
      volume.setPrefWidth(100);
      player.setVolume(0.5);
      volume.valueProperty().addListener((obs) -> player.setVolume(volume.getValue()));

      HBox controls = new HBox(10, backButton, playPause, new Label("Vol:"), volume);
      controls.setPadding(new Insets(5));
      controls.setAlignment(Pos.CENTER);

      BorderPane pane = new BorderPane(mediaView);
      pane.setCenter(mediaView);
      pane.setBottom(controls);
      pane.setPrefSize(640, 480);

      Stage videoStage = new Stage();
      videoStage.setTitle("Playing: " + url);
      videoStage.setScene(new Scene(pane));

      videoStage.setOnCloseRequest((WindowEvent we) -> {
         player.stop();
         player.dispose();
      });

      videoStage.show();

      player.play();
      playPause.setText("⏸");
   }

   private HBox view;
   private Button video;
   private String lastUrl = "";
}