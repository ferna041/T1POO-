package com.example.t2;

public class Component {
   protected Component (){}
   public Component(String componentName, String topicName){
      name=componentName;
      this.topicName = topicName;
   }
   public String getName(){
      return name;
   }
   public String getTopicName(){
      return topicName;
   }
   protected String name;
   protected String topicName;
}
