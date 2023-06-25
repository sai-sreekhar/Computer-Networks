import java.io.*;
import java.net.*;
public class server {
public static void main(String[] args) {
    try {
            // Create a server socket on port 5000
            ServerSocket serverSocket = new ServerSocket(5000);
            System.out.println("Server started. Waiting for client...");
            // Listen for incoming connections
            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected.");
            // Create input and output streams for communication with the client
            BufferedReader inFromClient = new BufferedReader(new
            InputStreamReader(clientSocket.getInputStream()));
            PrintWriter outToClient = new PrintWriter(clientSocket.getOutputStream(), true);
            // Read client message
            String clientMessage = inFromClient.readLine();
            System.out.println("Client says: " + clientMessage);
            // Send a response to the client
            outToClient.println("Hello from server!");
            // Close the connection
            clientSocket.close();
            serverSocket.close();
        } catch (IOException e) {
        e.printStackTrace();
        }
    }
}