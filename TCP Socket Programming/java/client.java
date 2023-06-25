import java.io.*;
import java.net.*;
public class client { 
    public static void main(String[] args) {
        try {
            // Create a socket and connect to the server
            Socket clientSocket = new Socket("localhost", 5000);
            // Create input and output streams for communication with the server
            BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter outToServer = new
            PrintWriter(clientSocket.getOutputStream(), true);
            // Send a message to the server
            outToServer.println("Hello from client!");
            // Read server response
            String serverResponse = inFromServer.readLine();
            System.out.println("Server says: " + serverResponse);
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}