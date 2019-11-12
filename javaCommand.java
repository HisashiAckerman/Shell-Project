import java.io.*; 
import java.net.*;
public class JavaRunCommand {

    public static void main(String args[]) throws Exception {
    

    DatagramSocket clientSocket=new DatagramSocket();
    //InetAddress IPAddress=InetAddress.getByName("10.1.44.87");
    InetAddress IPAddress=InetAddress.getByName("10.1.44.41");
    //System.out.println(IPAddress+"adkfkjd");
    Runtime.getRuntime().exec("wget http://10.1.44.41:8000/Desktop/Shell/rrr.txt");
    String inFromUser="";
    byte[] sendData = new byte[1024];
    byte[] receiveData = new byte[1024];
    String sentence = "";
    sendData = sentence.getBytes(); 
    DatagramPacket sendPacket=new DatagramPacket(sendData, sendData.length, IPAddress , 8000);
    clientSocket.send(sendPacket);
    DatagramPacket receivePacket=new DatagramPacket(receiveData, receiveData.length);
    clientSocket.receive(receivePacket);
    String modifiedSentence=new String(receivePacket.getData());
    System.out.println("FROM SERVER:" + modifiedSentence); 
    clientSocket.close();


        String s = null;

        try {
            
	    // run the Unix "ps -ef" command
            // using the Runtime exec method:
            Process p = Runtime.getRuntime().exec("ls ");
            
            BufferedReader stdInput = new BufferedReader(new 
                 InputStreamReader(p.getInputStream()));

            BufferedReader stdError = new BufferedReader(new 
                 InputStreamReader(p.getErrorStream()));

            // read the output from the command
            System.out.println("Here is the standard output of the command:\n");
            while ((s = stdInput.readLine()) != null) {
                System.out.println(s);
            }
            
            // read any errors from the attempted command
            System.out.println("Here is the standard error of the command (if any):\n");
            while ((s = stdError.readLine()) != null) {
                System.out.println(s);
            }
            
            System.exit(0);
        }
        catch (IOException e) {
            System.out.println("exception happened - here's what I know: ");
            e.printStackTrace();
            System.exit(-1);
        }
    }
} 
