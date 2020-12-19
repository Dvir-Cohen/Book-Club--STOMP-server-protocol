package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.Data;
import bgu.spl.net.srv.User;

import javax.swing.*;
import java.util.Queue;

public class StompProtocol <T> implements StompMessagingProtocol, MessagingProtocol {
    private int connectionId;
    private Connections<String> connections;
    private boolean terminate;
    private Data data;
    private User user =null;

    public StompProtocol (){
        data = Data.getInstance();
        terminate = false;
    }

    public void start(int connectionId, Connections<String> connections){
         this.connectionId = connectionId;
         this.connections = connections;
    }

    public void process(String   msg){
        Frame frame = new Frame(msg);
        if (frame.getType() == "login"){
            login(frame);}
        else if (user!= null && user.isLog()){
        switch (frame.getType()) {
            case "join":
                join(frame);
                break;
            case "exit":
                exit(frame);
                break;
            case "add":
                add(frame);
                break;
            case "borrow":
                borrow(frame);
                break;
            case "borrow1":
                borrow1(frame);
                break;
            case "borrow2":
                borrow2(frame);
                break;
            case "return":
                Return(frame);
                break;
            case "status":
                status(frame);
                break;
            case "status1":
                status1(frame);
                break;
            case "logout":
                logout(frame);
                break;
        }

        }

    }

    private  void login(Frame frame){
        String name = frame.getUsername();
        String code = frame.getPasscode();
        if (!data.isRegisterd(name)) { // new user
            User user = new User(name, code);
            user.login();
            user.setConnectionId(connectionId);
            data.addUser(user);
            this.user = user;
            connections.send(connectionId, "CONNECTED\n" +"version:1.2\n" );
        }
        else if (data.getUser(name).getPasscode().compareTo(code)!=0){ // wrong passcode
                connections.send(connectionId, "ERROR\n" + "Wrong password\n" );
        }
        else if (data.getUser(name).isLog()){ // user is already logged
            connections.send(connectionId, "ERROR\n" + "User already logged in\n");
        }
        else{  // connect user
            this.user = data.getUser(name);
            data.getUser(name).setConnectionId(connectionId);
            data.getUser(name).login();
            connections.send(connectionId, "CONNECTED\n" +"version:1.2\n" );

        }

    }

    private  void join(Frame frame){
       String genre = frame.getGenre();
       if (user.Subscribe(genre, frame.getId()))
        connections.send(connectionId, "RECEIPT\n" + "receipt-id:"+ frame.getReceiptId() +"\n" );
    }

    private  void exit(Frame frame){
        if (user.unSubscribe(frame.getId()))
            connections.send(connectionId, "RECEIPT\n" + "receipt-id:"+ frame.getReceiptId() +"\n");
    }

    private  void add (Frame frame){
        connections.send(frame.getGenre(),"MESSAGE\n" +
                "subscription:" + user.getTopicId(frame.getGenre())+ "\n"+
                "Message-id:" + data.getMsgCounter() +"\n"+
                "destination:" + frame.getGenre()+ "\n"+
                frame.getUsername()+ " has added the book " + frame.getBookName()+"\n");
    }

    private  void borrow (Frame frame){
        connections.send(frame.getGenre(),"MESSAGE\n" +
                "subscription:" + user.getTopicId(frame.getGenre())+ "\n"+
                "Message-id:" + data.getMsgCounter() +"\n"+
                "destination:" + frame.getGenre()+ "\n"+
                frame.getUsername() + " wish to borrow " + frame.getBookName()+ "\n");
    }
    private void borrow1 (Frame frame){
        connections.send(frame.getGenre(),"MESSAGE\n" +
                "subscription:"+ user.getTopicId(frame.getGenre())+"\n" +
                "Message-id:"+ data.getMsgCounter() +"\n" +
                "destination:"+ frame.getGenre() +"\n" +
                 frame.getUsername()  +" has " + frame.getBookName() + "\n" );}

    private void borrow2 (Frame frame){
        connections.send(frame.getGenre(),"MESSAGE\n" +
                "subscription:" + user.getTopicId(frame.getGenre()) + "\n" +
                "Message-id:" + data.getMsgCounter() + "\n" +
                "destination:"+ frame.getGenre()+"\n" +
                "Taking "+ frame.getBookName() + " from " + frame.getUsername() +"\n" );}

    private  void Return (Frame frame){
        String msg ="MESSAGE\n" +
                "subscription:" + user.getTopicId(frame.getGenre())+"\n"+
                "Message-id:" + data.getMsgCounter() +"\n"+
                "destination:" + frame.getGenre() + "\n"+
                "Returning " + frame.getBookName()+ " to " + frame.getUsername()+  "\n";

        connections.send(frame.getGenre(),msg);
    }

    private  void status (Frame frame){
        connections.send(frame.getGenre(),"MESSAGE\n" +
                "subscription:"+ user.getTopicId(frame.getGenre())+"\n" +
                "Message-id:"+ data.getMsgCounter() +"\n"+
                "destination:"+ frame.getGenre() +"\n" +
                "Book status\n" );
    }

    private  void status1 (Frame frame){
        connections.send(frame.getGenre(),"MESSAGE\n" +
                "subscription:"+ user.getTopicId(frame.getGenre()) +"\n" +
                "Message-id:" + data.getMsgCounter() + "\n" +
                "destination:"+ frame.getGenre() +"\n" +
                frame.getBookStatus()+ "\n");
    }

    private  void logout (Frame frame){
        user.logout();
        connections.send(connectionId, "RECEIPT\n" + "receipt-id:"+ frame.getReceiptId() +"\n" );
    }

    @Override
    public Object process(Object msg) {
        return null; // can impl MessageProtocol;
    }

    public boolean shouldTerminate() {
       return terminate;
    }

    public void Terminate() {
        terminate = false;
    }
}

