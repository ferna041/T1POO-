package com.example.tarea2;

import java.util.ArrayList;
import java.util.List;

public class Topic {
    private String name;
    private List<Subscriber> subscribers = new ArrayList<>();

    public Topic(String name) {
        this.name = name;
    }

    public void subscribe(Subscriber s) {
        subscribers.add(s);
    }

    public void publish(String message) {
        for (Subscriber s : subscribers) {
            s.receive(message);
        }
    }

    public String getName() {
        return name;
    }
}
