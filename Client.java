import java.io.*;
import java.net.*;
class Client
{
  public static void main(String[] args) throws Exception
  {
     Socket sock = new Socket("172.16.110.129", 6666); // reading from keyboard (keyRead object)
    
     BufferedReader keyRead = new BufferedReader(new InputStreamReader(System.in)); // sending to client (pwrite object)
    
     OutputStream ostream = sock.getOutputStream();
    
     PrintWriter pwrite = new PrintWriter(ostream, true); // receiving from server ( receiveRead  object)
     
     InputStream istream = sock.getInputStream();
     
     BufferedReader receiveRead = new BufferedReader(new InputStreamReader(istream));

     System.out.println("Begin Conversation:");

     String receiveMessage, sendMessage;
     
     while(true)
      {
        sendMessage = keyRead.readLine();  // keyboard reading
        pwrite.println(sendMessage);       // sending to server
        pwrite.flush();                    // flush the data
        if((receiveMessage = receiveRead.readLine()) != null) //receive from server
        {
          System.out.println("Server say: " + receiveMessage); // displaying at DOS prompt
          System.out.println("Say Something Nice:");
        }
      }
    }
 }
