import java.io.*;
import java.net.*;

public class udpServer {
    public static void main(String[] args) {
        try {
            int serverPort = 1234;

            // Create a socket
            DatagramSocket socket = new DatagramSocket(serverPort);
            System.out.println("Server started. Waiting for messages...");

            // Create a packet to store the received data
            byte[] receiveData = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

            // Receive packets in an infinite loop
            while (true) {
                // Receive a packet from the client
                socket.receive(receivePacket);

                // Process the received data
                String receivedMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println("Received message from client: " + receivedMessage);

                // Prepare data to send back to the client
                String responseMessage = "Hello, client!";
                byte[] sendData = responseMessage.getBytes();

                // Get the client's address and port from the received packet
                InetAddress clientAddress = receivePacket.getAddress();
                int clientPort = receivePacket.getPort();

                // Create a packet with the response data, client address, and port
                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, clientAddress, clientPort);

                // Send the response packet to the client
                socket.send(sendPacket);
                System.out.println("Response sent to client.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}