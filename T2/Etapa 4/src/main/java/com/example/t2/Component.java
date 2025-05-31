package com.example.t2;

/**
 * Representa un componente básico del sistema de comunicación.
 * Esta es la clase padre de la que heredan otros componentes como Publisher.
 * Cada componente tiene un nombre y está asociado a un tópico específico.
 * 
 * @author GrupoT2
 * @version 1.0
 * @since 2025
 */
public class Component {
   
   /**
    * Constructor protegido sin parámetros.
    * Se usa para evitar la creación directa de componentes sin configurar.
    */
   protected Component (){}
   
   /**
    * Constructor principal que crea un componente con nombre y tópico.
    * 
    * @param componentName el nombre que identificará a este componente
    * @param topicName el nombre del tópico al que está asociado este componente
    */
   public Component(String componentName, String topicName){
      name=componentName;
      this.topicName = topicName;
   }
   
   /**
    * Obtiene el nombre del componente.
    * 
    * @return una cadena con el nombre del componente
    */
   public String getName(){
      return name;
   }
   
   /**
    * Obtiene el nombre del tópico asociado al componente.
    * 
    * @return una cadena con el nombre del tópico
    */
   public String getTopicName(){
      return topicName;
   }
   
   /**
    * El nombre identificador del componente.
    */
   protected String name;
   
   /**
    * El nombre del tópico al que está asociado este componente.
    */
   protected String topicName;
}
