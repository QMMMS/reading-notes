# Socket

## 客户端

下面的代码模拟了手动连接水木社区欢迎页，即`telnet bbs.newsmth.net`

```java
try (Socket socket = new Socket("bbs.newsmth.net", 23);) {
    InputStream is = socket.getInputStream();
    Scanner scanner = new Scanner(is, "gbk");

    while (scanner.hasNextLine()) {
        String line = scanner.nextLine();
        System.out.println(line);
    }

} catch (UnknownHostException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}
```

建立套接字`Socket socket = new Socket(host, port)`，其中host 为主机名，port 为端口号（23 为默认的 telnet 端口号）。如果无法确定主机的 IP 地址，则抛出 `UnknownHostException` 异常；如果在创建套接字时发生 IO 错误，则抛出 `IOException` 异常。

需要注意的是，套接字在建立的时候，如果远程主机不可访问，这段代码就会阻塞很长时间，直到底层操作系统的限制而抛出异常。所以一般会在套接字建立后设置一个超时时间。`socket.setSoTimeout(10000);`

套接字连接成功后，可以通过 `java.net.Socket` 类的 `getInputStream()` 方法获取输入流。有了 `InputStream` 对象后，可以借助文本扫描器类（Scanner）将其中的内容打印出来。

- Socket：表示客户端套接字，负责与服务器端建立连接并进行数据的读写。
- ServerSocket：表示服务器端套接字，负责监听客户端连接请求。当有新的连接请求时，ServerSocket 会创建一个新的 Socket 实例，用于与客户端进行通信。

## TCP服务器

```java
try (
    ServerSocket server = new ServerSocket(8888);
    Socket socket = server.accept();
    InputStream is = socket.getInputStream();
    OutputStream os = socket.getOutputStream();
    Scanner scanner = new Scanner(is)
) 
{
    PrintWriter pw = new PrintWriter(new OutputStreamWriter(os, "gbk"), true);
    pw.println("你好啊QMMMS");

    boolean done = false;
    while (!done && scanner.hasNextLine()) {
        String line = scanner.nextLine();
        System.out.println(line);

        if ("2048".equals(line)) {
            done = true;
        }
    }
} catch (UnknownHostException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}
```

建立服务器端的套接字也比较简单，只需要指定一个能够独占的端口号就可以了（注意0~1023 这些端口都已经被系统预留了）

```java
ServerSocket server = new ServerSocket(8888);
```

调用 ServerSocket 对象的 `accept()` 等待客户端套接字的连接请求。一旦监听到客户端的套接字请求，就会返回一个表示连接已建立的 Socket 对象，可以从中获取到输入流和输出流。

- 客户端套接字发送的所有信息都会包裹在服务器端套接字的输入流中
- 而服务器端套接字发送的所有信息都会包裹在客户端套接字的输出流中

```java
Socket socket = server.accept();
InputStream is = socket.getInputStream();
OutputStream os = socket.getOutputStream();
```

服务器端向客户端发送消息：

```java
PrintWriter pw = new PrintWriter(new OutputStreamWriter(os, "gbk"), true);
pw.println("你好啊QMMMS");
```

服务器端读取客户端发送过来的消息：

```java
Scanner scanner = new Scanner(is);
boolean done = false;
while (!done && scanner.hasNextLine()) {
    String line = scanner.nextLine();
    System.out.println(line);

    if ("2048".equals(line)) {
        done = true;  // 输入2048结束
    }
}
```

运行该服务后，可以通过 `telnet localhost 8888` 命令连接该远程服务

## 为多个客户端服务

上面的例子中，服务器端只能为一个客户端服务——这不符合服务器端一对多的要求。按此修改：服务器端接收到客户端的套接字请求时，可以启动一个线程来处理，而主程序继续等待下一个连接。

```java
try (ServerSocket server = new ServerSocket(8888)) {
    while (true) {
        Socket socket = server.accept();
        Thread thread = new Thread(new Runnable() {

            @Override
            public void run() {
              // 套接字处理程序
            }
        });
        thread.start();
    }
} catch (IOException e) {
    e.printStackTrace();
}
```

线程内部（`run(){}` 方法里）用来处理套接字，代码示例如下：

```java
try {
    InputStream is = socket.getInputStream();
    OutputStream os = socket.getOutputStream();
    Scanner scanner = new Scanner(is);

   // 其他代码省略
   // 向客户端发送消息
   // 读取客户端发送过来的消息
} catch (IOException e) {
    e.printStackTrace();
} finally {
    try {
        socket.close();
    } catch (IOException e) {
        e.printStackTrace();
    }
}
```

## 多线程

```java
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class MultiThreadedServer {
    public static void main(String[] args) throws IOException {
        int port = 12345;
        ServerSocket serverSocket = new ServerSocket(port);
        System.out.println("Server is listening on port " + port);

        while (true) {
            Socket socket = serverSocket.accept();
            System.out.println("Client connected");
            new ClientHandler(socket).start();
        }
    }
}
class ClientHandler extends Thread {
    private Socket socket;

    public ClientHandler(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try {
            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));

            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println("Received: " + line);
                writer.println("Server: " + line);
            }

            socket.close();
        } catch (IOException e) {
            System.out.println("Client disconnected");
        }
    }
}
```

在这个示例中，我们使用了一个 ClientHandler 类，该类继承自 Thread 类。这使得每个客户端连接都可以在单独的线程中处理，从而允许服务器同时处理多个客户端连接。当一个新客户端连接到服务器时，服务器会创建一个新的 ClientHandler 对象，并使用 `start()` 方法启动线程。ClientHandler 类的 `run()` 方法包含处理客户端请求的逻辑。

客户端代码：

```java
import java.io.*;
import java.net.Socket;

public class Client {
    public static void main(String[] args) throws IOException {
        String hostname = "localhost";
        int port = 12345;

        Socket socket = new Socket(hostname, port);
        System.out.println("Connected to the server");

        InputStream input = socket.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(input));

        OutputStream output = socket.getOutputStream();
        PrintWriter writer = new PrintWriter(output, true);

        writer.println("Hello, server!");
        String response = reader.readLine();
        System.out.println("Server response: " + response);

        socket.close();
    }
}
```

## UDP服务器

DatagramSocket 类是 Java 中实现 UDP 协议的核心类。与基于 TCP 的 Socket 和 ServerSocket 类不同，DatagramSocket 类提供了无连接的通信服务，发送和接收数据包。由于无需建立连接，UDP 通常比 TCP 更快，但可能不如 TCP 可靠。

服务器端代码：

```java
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class UDPServer {
    public static void main(String[] args) throws IOException {
        int port = 12345;
        DatagramSocket serverSocket = new DatagramSocket(port);
        System.out.println("Server is listening on port " + port);

        byte[] buffer = new byte[1024];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

        serverSocket.receive(packet);
        String message = new String(packet.getData(), 0, packet.getLength());
        System.out.println("Received: " + message);

        serverSocket.close();
    }
}
```

客户端代码：

```java
import java.io.IOException;
import java.net.*;

public class UDPClient {
    public static void main(String[] args) throws IOException {
        String hostname = "localhost";
        int port = 12345;

        InetAddress address = InetAddress.getByName(hostname);
        DatagramSocket clientSocket = new DatagramSocket();

        String message = "Hello, server!";
        byte[] buffer = message.getBytes();

        DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, port);
        clientSocket.send(packet);
        System.out.println("Message sent");

        clientSocket.close();
    }
}
```

在这个示例中，服务器端创建一个 DatagramSocket 对象并监听端口 12345。然后，它创建一个 DatagramPacket 对象，用于存储接收到的数据包。`serverSocket.receive(packet)` 方法阻塞，直到收到一个数据包。收到数据包后，服务器从数据包中提取并打印消息。

客户端首先解析服务器的 IP 地址，然后创建一个 DatagramSocket 对象。接着，客户端创建一个包含要发送消息的 DatagramPacket 对象，并指定目标地址和端口。最后，客户端通过调用 `clientSocket.send(packet)` 方法发送数据包。