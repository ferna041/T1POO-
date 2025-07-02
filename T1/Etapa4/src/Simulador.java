import java.io.*;
import java.util.*;

public class Simulador {

    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.out.println("Uso: java Simulador config.txt");
            return;
        }

        String configFile = args[0];
        Broker broker = new Broker();
        Map<String, Publisher> publishers = new HashMap<>();

        // Leer configuración
        try (BufferedReader reader = new BufferedReader(new FileReader(configFile))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] tokens = line.trim().split("\\s+");
                if (tokens.length == 0) continue;

                if (tokens[0].equalsIgnoreCase("publicador")) {
                    String name = tokens[1];
                    String topic = tokens[2];
                    Publisher publisher = new Publisher(name, broker, topic);
                    publishers.put(name, publisher);
                }

                if (tokens[0].equalsIgnoreCase("suscriptor")) {
                    String type = tokens[1];
                    String name = tokens[2];
                    String topic = tokens[3];
                    String outputFile = tokens[4];

                    if (type.equalsIgnoreCase("Seguidor")) {
                        Follower follower = new Follower(name, topic, outputFile);
                        broker.subscribe(topic, follower);
                    } else if (type.equalsIgnoreCase("Registrador")) {
                        Recorder recorder = new Recorder(name, topic, outputFile);
                        broker.subscribe(topic, recorder);
                    } else if (type.equalsIgnoreCase("Monitor")) {
                        Monitor monitor = new Monitor(name, topic, outputFile);
                        broker.subscribe(topic, monitor);
                    }
                }
            }
        }

        if (publishers.isEmpty()) {
            System.out.println("No se encontró ningún publicador en la configuración.");
            return;
        }

        // Leer eventos desde teclado
        Scanner scanner = new Scanner(System.in);
        System.out.println("Ingrese eventos en el formato <nombre_publicador> <mensaje> (Ctrl+D para terminar):");

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) continue;

            String[] parts = line.split("\\s+", 2); // dividir en 2 partes: nombre y mensaje
            if (parts.length < 2) {
                System.out.println("Formato inválido. Use: <nombre_publicador> <mensaje>");
                continue;
            }

            String publisherName = parts[0];
            String message = parts[1];

            Publisher publisher = publishers.get(publisherName);
            if (publisher != null) {
                publisher.publish(message);
            } else {
                System.out.println("Unknown Publisher");
            }
        }

        scanner.close();
    }
}
