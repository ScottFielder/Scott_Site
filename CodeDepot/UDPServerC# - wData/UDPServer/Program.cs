using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
struct Actor {
    Vector3 pos;
    Quaternion orientation;
    UInt32 ID;
}
public class UdpServer {
    public static async Task Server(int port) {
        using (UdpClient udpClient = new UdpClient(port)) {
            Console.WriteLine($"UDP Server listening on port {port}");
            while (true){
                try {
                    UdpReceiveResult result = await udpClient.ReceiveAsync();
                    IPEndPoint remoteEndPoint = result.RemoteEndPoint;
                    string message = Encoding.ASCII.GetString(result.Buffer);
                    string replyMessage = $"Server: {message}";
                    byte[] replyBytes = Encoding.ASCII.GetBytes(replyMessage);
                    await udpClient.SendAsync(replyBytes, replyBytes.Length, remoteEndPoint);
                }
                catch (SocketException se){
                              Console.WriteLine($"SocketException message: {se.Message}");
                }
                catch (Exception ex){
                    Console.WriteLine($"Error receiving UDP message: {ex.Message}");
                }
            }
        }
    }

    public static void Main(string[] args) {
        
        int port = 0x1A2B;
        Task.Run(() => Server(port));

        Console.WriteLine("Press any key to quit");
        Console.ReadKey();
    }
}
