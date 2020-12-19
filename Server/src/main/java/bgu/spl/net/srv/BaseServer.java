package bgu.spl.net.srv;

import bgu.spl.net.impl.stomp.StompProtocol;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.function.Supplier;

public abstract class BaseServer<T> implements Server<T> {

    private final int port;
    private final Supplier<StompProtocol<T>> protocolFactory;
    private final Supplier<MessageEncoderDecoderImpl<T>> encdecFactory;
    private ServerSocket sock;
    private  ConnectionsImpl connections;


    public BaseServer(
            int port,
            Supplier<StompProtocol<T>> protocolFactory,
            Supplier<MessageEncoderDecoderImpl<T>> encdecFactory) {
        this.port = port;
        this.protocolFactory = protocolFactory;
        this.encdecFactory = encdecFactory;
		this.sock = null;
        connections = new ConnectionsImpl();

    }

    @Override
    public void serve() {

        try (ServerSocket serverSock = new ServerSocket(port)) {
			System.out.println("Server started");

            this.sock = serverSock; //just to be able to close

            while (!Thread.currentThread().isInterrupted()) {

                Socket clientSock = serverSock.accept();
                StompProtocol<T> protocol =protocolFactory.get();
                BlockingConnectionHandler<T> handler = new BlockingConnectionHandler<>(
                        clientSock,
                        encdecFactory.get(),
                        protocol
                );

                int idNumber= Data.getInstance().getIdcounter();

                protocol.start(idNumber,connections);

                connections.connect(idNumber,handler);
                execute(handler);

                            }
        } catch (IOException ex) {
        }

        System.out.println("server closed!!!");
    }

    @Override
    public void close() throws IOException {
		if (sock != null)
			sock.close();
    }

    protected abstract void execute(BlockingConnectionHandler<T>  handler);

}
