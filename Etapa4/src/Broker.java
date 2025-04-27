import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Broker {
    private Map<String, List<Subscriber>> topicSubscribers = new HashMap<>();

    public void subscribe(String topic, Subscriber subscriber) {
        topicSubscribers.computeIfAbsent(topic, k -> new ArrayList<>()).add(subscriber);
    }

    public void publish(String topic, String publisherName, String message) {
        List<Subscriber> subscribers = topicSubscribers.get(topic);
        if (subscribers != null) {
            for (Subscriber subscriber : subscribers) {
                subscriber.receive(publisherName, message);
            }
        }
    }
}
