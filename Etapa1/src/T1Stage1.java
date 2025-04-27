import java.util.Scanner;

public class T1Stage1 {

    public static void main(String[] args) {
        // Configuración directa
        Broker broker = new Broker();
        String topic = "Notificaciones_1";

        // Crear publicador (Streamer)
        Publisher publisher = new Publisher("Streamer_1", broker, topic);

        // Crear suscriptor (Follower)
        Follower follower = new Follower("Seguidor_1", topic, "seguidor.txt");
        broker.subscribe(topic, follower);

        // Leer notificaciones desde teclado
        Scanner scanner = new Scanner(System.in);
        System.out.println("Ingrese notificaciones (Ctrl+D para terminar):");
        while (scanner.hasNextLine()) {
            String message = scanner.nextLine();
            if (message.trim().isEmpty()) continue; // Ignorar líneas vacías
            publisher.publish(message);
        }
        scanner.close();
    }
}