import java.io.*;
import java.net.*;

public class udpClient {
    public static void main(String[] args) {
        try {
            InetAddress serverAddress = InetAddress.getByName("localhost");
            int serverPort = 1234;

            // Create a socket
            DatagramSocket socket = new DatagramSocket();

            // Prepare data to send
            String message = "Hello, server!";
            byte[] sendData = message.getBytes();

            // Create a packet with the data to send, server address, and port
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, serverPort);

            // Send the packet to the server
            socket.send(sendPacket);
            System.out.println("Message sent to the server.");

            // Receive the response from the server
            byte[] receiveData = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            socket.receive(receivePacket);

            // Process the response
            String receivedMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
            System.out.println("Response from server: " + receivedMessage);

            // Close the socket
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}