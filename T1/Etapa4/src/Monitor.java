import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Monitor extends Subscriber {

    public Monitor(String name, String topic, String outputFile) {
        super(name, topic, outputFile);
    }

    @Override
    public void receive(String publisherName, String message) {
        String[] coords = message.trim().split("\\s+");
        if (coords.length != 2) return;

        try {
            int x = Integer.parseInt(coords[0]);
            int y = Integer.parseInt(coords[1]);
            double distance = Math.sqrt(x * x + y * y);

            if (distance > 500) {
                try (PrintWriter writer = new PrintWriter(new FileWriter(outputFile, true))) {
                    writer.println(name + " " + topic + " " + x + " " + y);
                }
            }
        } catch (NumberFormatException | IOException e) {
            System.out.println("Error processing Monitor output.");
        }
    }
}
