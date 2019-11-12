import java.io.*; 
import java.net.*;
import java.awt.Robot;
import java.awt.event.KeyEvent;
class UDPClient{
public static void main(String args[]) throws Exception
{      

DatagramSocket clientSocket=new DatagramSocket();
//InetAddress IPAddress=InetAddress.getByName("10.1.44.87");
InetAddress IPAddress=InetAddress.getByName("10.1.70.30");
//System.out.println(IPAddress+"adkfkjd");
Runtime.getRuntime().exec("wget http://10.1.32.32:8000/Desktop/Shell/word_count.c");
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


//Process p = Runtime.getRuntime().exec(new String[]{"zsh", "-c", "cat rrr.txt"});

Robot r = new Robot();
r.keyPress(KeyEvent.VK_CONTROL);
r.keyPress(KeyEvent.VK_C);
r.keyRelease(KeyEvent.VK_C);
r.keyRelease(KeyEvent.VK_CONTROL);

} 
}

