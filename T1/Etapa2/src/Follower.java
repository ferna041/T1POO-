import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Follower extends Subscriber {

    public Follower(String name, String topic, String outputFile) {
        super(name, topic, outputFile);
    }

    @Override
    public void receive(String publisherName, String message) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(outputFile, true))) {
            writer.println(name + " " + topic + " " + message);
        } catch (IOException e) {
            System.out.println("Error writing to file: " + outputFile);
        }
    }
}
