package bgu.spl.net.srv;

import java.io.IOException;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.LinkedBlockingQueue;

public class Data {
    private ConcurrentHashMap <String , Queue<User>> Subscribers;  // each topic has a q of all subscribers
    private ConcurrentHashMap <String ,User> users;  // each topic has a q of all subscribers

    private int msgCounter,idCounter;
    private ConcurrentHashMap<Integer, ConnectionHandler> handlerMap;

    private static Data instance = null;
    private Data(){
         Subscribers=new ConcurrentHashMap<>();
        users = new ConcurrentHashMap<>();
        msgCounter = 0;
        idCounter=0;
        this.handlerMap = new ConcurrentHashMap<>();
    };
    /**
     * Retrieves the single instance of this class.
     */
    public static Data getInstance() {

        if (instance == null)
            instance = new Data();
        return instance;
    }

    public void addUser (User user){
        users.putIfAbsent(user.getName(), user);
    }

    public User getUser (String name){
        return users.get(name);
    }

    public void Subscribe (User user, String genre){

        if (Subscribers.containsKey(genre))
            Subscribers.get(genre).add(user);
        else {

            Subscribers.put(genre, new LinkedBlockingQueue<>());
            Subscribers.get(genre).add(user);
        }
    }
    public void UnSubscribe (User user, String genre){
       if (Subscribers.containsKey(genre)&& Subscribers.get(genre).contains(user))
           Subscribers.get(genre).remove(user);
        }

        public Queue<User> getSubscribers(String genre){
        if (Subscribers.containsKey(genre))
            return Subscribers.get(genre);
        return null;
        }


    public boolean isRegisterd (String name){
        return users.containsKey(name);
    }

    public synchronized int getMsgCounter() {
        this.msgCounter ++;
        return msgCounter;

    }

    public synchronized int getIdcounter() {
        this.idCounter ++;
        return idCounter;

    }
    public void addConnection (int id,ConnectionHandler CH){
        handlerMap.putIfAbsent(id,CH);
    }
    public  ConnectionHandler getConnection(int id){
        if (handlerMap.containsKey(id))
            return handlerMap.get(id);
        return null;
    }
    public void deleteConnection (int id) throws IOException {
        if (handlerMap.containsKey(id)) {
            handlerMap.get(id).close();
            handlerMap.remove(id);
        }
    }

}
