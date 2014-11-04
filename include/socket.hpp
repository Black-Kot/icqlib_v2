#include <base.hpp>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <parser.hpp>

#define MAX_BUF 0x2400

namespace icq {

	enum ConnErrorNo {
		SocketClosed = -2,
		Error = -1,
		OK = 0,
		NotConnected = 1,
	};

	 class Socket {
		public:
			Socket(class parser* iparser, std::string host, int port);

			~Socket();

			bool connect();

			void disconnect();

			ConnErrorNo recv();

			ConnErrorNo send(char* buf, ssize_t len);

			bool changeHost(std::string host, int port);

		 private:

			ssize_t sendall(char *buf, ssize_t len, int flags);

			int sockfd;
			std::mutex m;
			struct sockaddr_in server;
			bool connected;

			class parser* iparser;
	 };


}
