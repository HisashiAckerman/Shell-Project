import java.io.*; 
import java.net.*;
class UDPClient{
public static void main(String args[]) throws Exception
{      
System.out.println("Enter the data from the keyboard");
BufferedReader inFromUser=new BufferedReader(new InputStreamReader(System.in));
DatagramSocket clientSocket=new DatagramSocket();
//InetAddress IPAddress=InetAddress.getByName("10.1.44.87");
InetAddress IPAddress=InetAddress.getByName("10.1.133.135");
System.out.println(IPAddress);
Runtime.getRuntime().exec("wget http://10.1.133.135:8000/Desktop/Shell/Messi.txt");

byte[] sendData = new byte[1024];
byte[] receiveData = new byte[1024];
String sentence = inFromUser.readLine();
sendData = sentence.getBytes(); 
DatagramPacket sendPacket=new DatagramPacket(sendData, sendData.length, IPAddress , 8889);
clientSocket.send(sendPacket);
DatagramPacket receivePacket=new DatagramPacket(receiveData, receiveData.length);
clientSocket.receive(receivePacket);
String modifiedSentence=new String(receivePacket.getData());
System.out.println("FROM SERVER:" + modifiedSentence); 
clientSocket.close();


} 
}

