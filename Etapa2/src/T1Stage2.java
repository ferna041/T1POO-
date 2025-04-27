import java.io.*;
import java.util.*;

public class T1Stage2 {

    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.out.println("Uso: java T1Stage2 config.txt");
            return;
        }

        String configFile = args[0];
        Broker broker = new Broker();
        Publisher publisher = null;

        // Leer configuración
        try (BufferedReader reader = new BufferedReader(new FileReader(configFile))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] tokens = line.trim().split("\\s+");

                if (tokens.length == 0) continue;

                if (tokens[0].equalsIgnoreCase("publicador")) {
                    String name = tokens[1];
                    String topic = tokens[2];
                    publisher = new Publisher(name, broker, topic);
                }

                if (tokens[0].equalsIgnoreCase("suscriptor") && tokens[1].equalsIgnoreCase("Registrador")) {
                    String name = tokens[2];
                    String topic = tokens[3];
                    String outputFile = tokens[4];
                    Recorder recorder = new Recorder(name, topic, outputFile);
                    broker.subscribe(topic, recorder);
                }
            }
        }

        if (publisher == null) {
            System.out.println("No se encontró publicador en la configuración.");
            return;
        }

        // Leer coordenadas desde teclado
        Scanner scanner = new Scanner(System.in);
        System.out.println("Ingrese coordenadas x y (Ctrl+D para terminar):");
        while (scanner.hasNextLine()) {
            String message = scanner.nextLine();
            if (message.trim().isEmpty()) continue;
            publisher.publish(message);
        }
        scanner.close();
    }
}