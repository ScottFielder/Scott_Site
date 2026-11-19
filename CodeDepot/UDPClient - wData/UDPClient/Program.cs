using System;
using System.Net;
using System.Net.Sockets;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

public struct Actor {
    public Vector3 pos;
    public Quaternion orientation;
    public UInt32 ID;
}
public class UdpClientSender {
     public static async Task Main(string[] args) {
        string serverName = "127.0.0.1"; 
        int port = 0x1A2B;
       
        Actor actor = new Actor();
        actor.pos.X = 11;
        actor.pos.Y = 12;
        actor.pos.Z = 13;
        actor.orientation.W = 14;
        actor.orientation.X = 15;
        actor.orientation.Y = 16;
        actor.orientation.Z = 17;
        actor.ID = 18;


        /// The term "await" means to wait here until the async thread finishes
        await SendDataAsync(serverName, port, actor);

        Console.WriteLine("Press any key to exit");
        Console.ReadKey();
    }

    public static async Task SendDataAsync(string hostname, int port, Actor actor) {
        /// C# uses managed memory, what a pain. In this context the term "using" means to deallocate
        /// the udpClient memory once it goes out of scope. Managed memory - good grief
        using (UdpClient udpClient = new UdpClient()) {
            try {
                byte[] sendBytes = StructToBytes(actor); /// See code below
                /// The term "await" means to wait here until the async thread finishes
                await udpClient.SendAsync(sendBytes, sendBytes.Length, hostname, port);
            }
            catch (SocketException se) {
                Console.WriteLine($"SocketException message: {se.Message}");
            }
            catch (Exception ex) {
                Console.WriteLine($"Exception message: {ex.Message}");
            }
        }
    }
   /// C# is not a literal as C++, I need to convert to binary by tricking C#
   /// This is a C# version of a template
   /// The keyword "unmanaged" means this code only works for unmanaged stuff like a struct of floats and ints ...
   public static byte[] StructToBytes<T>(T myStruct) where T : unmanaged {
        int structSize = Marshal.SizeOf<T>(); /// Marshaling is dealing with managed and unmanaged memory
        byte[] buffer = new byte[structSize];
        MemoryMarshal.Write(buffer, in myStruct);
        return buffer;
    }
}

