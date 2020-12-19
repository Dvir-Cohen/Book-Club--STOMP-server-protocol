package bgu.spl.net.srv;



import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;

public class User {
    private String name;
    private String passcode;
    private boolean log;
    private int connectionId;
    private ConcurrentHashMap<Integer, String> topics;


    public User(String name, String pass) {
        this.name = name;
        this.passcode = pass;
        this.topics = new ConcurrentHashMap<>();
        login();
    }

    public String getName() {
        return name;
    }

    public String getPasscode() {
        return passcode;
    }

    public void login() {
        this.log = true;
    }

    public void logout() {
        this.log = false;
        for (int id : topics.keySet())
            unSubscribe(id);

    }

    public boolean isLog() {
        return log;
    }

    public void setConnectionId(int connectionId) {
        this.connectionId = connectionId;
    }

    public int getConnectionId() {
        return connectionId;
    }

    public boolean Subscribe(String genre, int id) {
        if (!topics.contains(genre)) {
            topics.put(id, genre);
            Data.getInstance().Subscribe(this, genre);
            return true;
        }
        return false;
    }

    public boolean unSubscribe(int id) {
        if (topics.containsKey(id)) {
            Data.getInstance().UnSubscribe(this, topics.get(id));
            topics.remove(id);
            return true;
        }
        return false;
    }

    public int getTopicId(String genre) {
        for (int id : topics.keySet()) {
            if (topics.get(id).equals(genre)) {
                return id;
            }
        }
        return -1;
    }
}