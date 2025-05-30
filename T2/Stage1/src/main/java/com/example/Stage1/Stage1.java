package com.example.tarea2;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class Stage1 extends Application {

    private VBox publishersBox = new VBox();
    private VBox subscribersBox = new VBox();

    @Override
    public void start(Stage primaryStage) {
        BorderPane root = new BorderPane();

        MenuBar menuBar = new MenuBar();

        Menu pubMenu = new Menu("Publisher");
        MenuItem pubVideo = new MenuItem("Video");
        pubVideo.setOnAction(e -> {
            TextInputDialog nameDialog = new TextInputDialog();
            nameDialog.setHeaderText("Nombre del publicador");
            nameDialog.showAndWait().ifPresent(name -> {
                TextInputDialog topicDialog = new TextInputDialog();
                topicDialog.setHeaderText("Nombre del tópico");
                topicDialog.showAndWait().ifPresent(topic -> {
                    VideoPublisher vp = new VideoPublisher(name, topic);
                    publishersBox.getChildren().add(vp.getView());
                });
            });
        });
        pubMenu.getItems().add(pubVideo);

        Menu subMenu = new Menu("Subscriber");
        MenuItem subVideo = new MenuItem("Video");
        subVideo.setOnAction(e -> {
            TextInputDialog nameDialog = new TextInputDialog();
            nameDialog.setHeaderText("Nombre del suscriptor");
            nameDialog.showAndWait().ifPresent(name -> {
                TextInputDialog topicDialog = new TextInputDialog();
                topicDialog.setHeaderText("Nombre del tópico");
                topicDialog.showAndWait().ifPresent(topic -> {
                    VideoFollower vf = new VideoFollower(name, topic);
                    subscribersBox.getChildren().add(vf.getView());
                });
            });
        });
        subMenu.getItems().add(subVideo);

        menuBar.getMenus().addAll(pubMenu, subMenu);

        root.setTop(menuBar);


        VBox pubContainer = new VBox(new Label("Publicadores"), publishersBox);
        VBox subContainer = new VBox(new Label("Suscriptores"), subscribersBox);
        pubContainer.setSpacing(10);
        subContainer.setSpacing(10);

        HBox centerBox = new HBox(pubContainer, subContainer);
        centerBox.setSpacing(20);

        publishersBox.setSpacing(10);
        subscribersBox.setSpacing(10);

        root.setCenter(centerBox);

        Scene scene = new Scene(root, 800, 600);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Simulador Publicador-Suscriptor: Etapa 1");
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
