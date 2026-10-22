#include <iostream>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#define RECV_DATA_BUF_SIZE 256

/// Only Microsoft allows this but I thought it appropriate to do it this way
/// since Winsock is exclusively theirs. I'll explain.
/// We could also put this the properties page of VS.
#pragma comment(lib, "Ws2_32.lib")
/// Personally, I find this gross - C# loves this idea - grrr

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

int main(int argc, char **argv) {

  int sockErr = 0;

  const char *hostname = "scottfielder.com";
  const char *port = "443";        /// https :D
  const char *path = "index.html"; /// root path to the website

  /// Create  Winsock subsystem
  WSADATA winSock;
  int status; /// Just an error variable

  status =
      WSAStartup(MAKEWORD(2, 2), &winSock); /// Dare you to figure that out.
  if (status != 0) {
    std::cerr << "WSAStartup failed: " << status << "\n";
    return 1;
  }
  /// Resolve the server address and port. SDL3 does a much better job than
  /// Microsoft - duh
  struct addrinfo hints{}; /// remember how I did this in Vulkan? C-code
  struct addrinfo *result = nullptr;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  status = getaddrinfo(hostname, port, &hints, &result);
  if (status != 0) {
    std::cerr << "getaddrinfo failed: " << status << "\n";
    /// We'll need to look this up. I forget.
    /// I think is just turns off the subsystem.
    WSACleanup();
    return 1;
  }

  ///  Create a socket to connect to the server
  SOCKET clientSocket = INVALID_SOCKET;
  clientSocket =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (clientSocket == INVALID_SOCKET) {
    std::cerr << "Error at socket(): " << WSAGetLastError() << "\n";
    freeaddrinfo(result);
    WSACleanup();
    return 1;
  }

  /// Try to connect to the server
  status = connect(clientSocket, result->ai_addr,
                   static_cast<int>(result->ai_addrlen));
  if (status == SOCKET_ERROR) {
    std::cerr << "connect failed: " << WSAGetLastError() << "\n";
    closesocket(clientSocket);
    clientSocket = INVALID_SOCKET;
    freeaddrinfo(result);
    WSACleanup();
    return 1;
  }
  freeaddrinfo(result);

  SSL_library_init();
  SSL_load_error_strings();
  const SSL_METHOD *method = TLS_client_method();
  SSL_CTX *ctx = SSL_CTX_new(method);
  if (!ctx) {
    std::cerr << "SSL_CTX_new failed\n";
    return 1;
  }

  SSL *ssl = SSL_new(ctx);
  SSL_set_fd(ssl, (int)clientSocket);

  // Set hostname for SNI
  SSL_set_tlsext_host_name(ssl, hostname);

  if (SSL_connect(ssl) != 1) {
    std::cerr << "SSL_connect failed: "
              << ERR_reason_error_string(ERR_get_error()) << "\n";
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    closesocket(clientSocket);
    WSACleanup();
    return 1;
  }

  /// Form the HTTP request - yes, it has to look this way.
  /// std::string and be useful sometimes
  std::string request = "GET " + std::string(path) +
                        " HTTP/1.1\r\n"
                        "Host: " +
                        std::string(hostname) +
                        "\r\n"
                        "Connection: close\r\n"
                        "\r\n";

  SSL_write(ssl, request.c_str(), (int)request.size());

  // Receive response
  char buffer[4096];
  int bytesRead;
  while ((bytesRead = SSL_read(ssl, buffer, sizeof(buffer))) > 0) {
    std::cout.write(buffer, bytesRead);
  }

  // Clean up
  SSL_shutdown(ssl);
  SSL_free(ssl);
  SSL_CTX_free(ctx);
  closesocket(clientSocket);
  WSACleanup();

  return 0;
}
