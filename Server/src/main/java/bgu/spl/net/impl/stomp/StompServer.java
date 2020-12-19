package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.srv.Data;
import bgu.spl.net.srv.MessageEncoderDecoderImpl;
import bgu.spl.net.srv.Server;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class StompServer {
    //private ConcurrentHashMap<String, ConcurrentLinkedQueue<String>> channels = new ConcurrentHashMap<>();

    public static void main(String[] args) {
        if (args[1] == "tpc"){
            Data.getInstance();
        Server.threadPerClient(
                Integer.parseInt(args[0]), //port
                () -> new StompProtocol(), //protocol factory
                MessageEncoderDecoderImpl::new //message encoder decoder factory

        ).serve();
    }
        else
            Data.getInstance();
        Server.reactor(
                Runtime.getRuntime().availableProcessors(),
                Integer.parseInt(args[0]), //port
                () ->  new StompProtocol(), //protocol factory
                 MessageEncoderDecoderImpl::new //message encoder decoder factory
        ).serve();



    }


}
