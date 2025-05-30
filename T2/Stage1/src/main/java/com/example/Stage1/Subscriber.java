package com.example.tarea2;

public abstract class Subscriber extends Component {
    protected Topic topicRef;

    public Subscriber(String name, String topic) {
        super(name, topic);
        topicRef = Broker.getOrCreateTopic(topic);
        topicRef.subscribe(this);
    }

    public abstract void receive(String message);
}
