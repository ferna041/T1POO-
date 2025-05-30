package com.example.tarea2;

public abstract class Publisher extends Component {
    protected Topic topicRef;

    public Publisher(String name, String topic) {
        super(name, topic);
        topicRef = Broker.getOrCreateTopic(topic);
    }

    public void publish(String message) {
        topicRef.publish(message);
    }
}

