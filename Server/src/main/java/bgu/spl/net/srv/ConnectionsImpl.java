package bgu.spl.net.srv;

import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;

public class ConnectionsImpl <T> implements Connections<T> {
    private  Data data;

    public ConnectionsImpl () {
    data= Data.getInstance();
    }

   public boolean send(int connectionId, T msg){

        if (data.getConnection(connectionId) == null)
            return false;
        else
            data.getConnection(connectionId).send(msg);
        return true;

    }

    public void send(String channel, T msg) {
        if (data.getSubscribers(channel) != null) {
            Queue<User> q= data.getSubscribers(channel);
            for (User user : q) {

                if (user.isLog())
                    send(user.getConnectionId(), msg);
            }
        }
    }

    @Override
    public void disconnect(int connectionId) throws IOException {

        data.deleteConnection(connectionId);
    }
    public void connect(int connectionId,ConnectionHandler<T> handler){
        data.addConnection(connectionId,handler);
    }
}






