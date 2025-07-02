import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Recorder extends Subscriber {

    public Recorder(String name, String topic, String outputFile) {
        super(name, topic, outputFile.endsWith(".csv") ? outputFile : outputFile + ".csv");
    }

    @Override
    public void receive(String publisherName, String message) {
        String[] coords = message.trim().split("\\s+");
        if (coords.length != 2) return;

        try (PrintWriter writer = new PrintWriter(new FileWriter(outputFile, true))) {
            writer.println(name + "," + topic + "," + coords[0] + "," + coords[1]);
        } catch (IOException e) {
            System.out.println("Error writing to file: " + outputFile);
        }
    }
}