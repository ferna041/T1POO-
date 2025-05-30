public class Publisher extends Component {
    private Broker broker;
    private String topic;

    public Publisher(String name, Broker broker, String topic) {
        super(name);
        this.broker = broker;
        this.topic = topic;
    }

    public void publish(String message) {
        broker.publish(topic, name, message);
    }
}
