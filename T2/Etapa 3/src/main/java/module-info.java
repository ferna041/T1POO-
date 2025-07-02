module com.example.t2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.media;


    opens com.example.t2 to javafx.fxml;
    exports com.example.t2;
}