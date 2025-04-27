public abstract class Subscriber extends Component {
    protected String topic;
    protected String outputFile;

    public Subscriber(String name, String topic, String outputFile) {
        super(name);
        this.topic = topic;
        this.outputFile = outputFile;
    }

    public abstract void receive(String publisherName, String message);
}
