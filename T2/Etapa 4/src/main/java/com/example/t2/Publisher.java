package com.example.t2;

/**
 * Representa un publicador que extiende la funcionalidad de Component.
 * Esta clase se encarga de publicar mensajes a un tópico específico a través de un broker.
 * Los publicadores pueden enviar eventos/mensajes a todos los suscriptores del tópico.
 * 
 * @author GrupoT2
 * @version 1.0
 * @since 2025
 */
public class Publisher extends Component {
    
    /**
     * Constructor protegido sin parámetros.
     * Se prohíbe su uso para evitar crear publicadores sin configurar apropiadamente.
     */
    protected Publisher() {} // to ban calls to this constructor
    
    /**
     * Constructor principal que crea un publicador conectado a un broker y tópico.
     * 
     * @param name el nombre del publicador
     * @param broker el broker que maneja la comunicación entre componentes
     * @param topicName el nombre del tópico donde este publicador enviará mensajes
     */
    public Publisher(String name, Broker broker, String topicName) {
        super(name, topicName);
        topic = broker.createTopic(topicName);
    }
    
    /**
     * Publica un nuevo evento/mensaje al tópico asociado.
     * Este método notifica a todos los suscriptores del tópico sobre el nuevo mensaje.
     * 
     * @param message el mensaje o evento que se quiere publicar
     */
    protected void publishNewEvent(String message) {
        topic.notify(message);
    }
    
    /**
     * El tópico al cual este publicador envía sus mensajes.
     * Es creado por el broker durante la construcción del publicador.
     */
    private Topic topic;
}