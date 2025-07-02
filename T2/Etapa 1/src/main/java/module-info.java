module com.example.t2 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.t2 to javafx.fxml;
    exports com.example.t2;
}