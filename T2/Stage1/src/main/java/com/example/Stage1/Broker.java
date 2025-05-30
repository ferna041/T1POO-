package com.example.tarea2;

import java.util.HashMap;

public class Broker {
    private static HashMap<String, Topic> topics = new HashMap<>();

    public static Topic getOrCreateTopic(String topicName) {
        return topics.computeIfAbsent(topicName, Topic::new);
    }
}

