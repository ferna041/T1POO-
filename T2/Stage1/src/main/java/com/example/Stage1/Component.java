package com.example.tarea2;

public abstract class Component {
    protected String name;
    protected String topic;

    public Component(String name, String topic) {
        this.name = name;
        this.topic = topic;
    }

    public String getName() {
        return name;
    }

    public String getTopic() {
        return topic;
    }
}
