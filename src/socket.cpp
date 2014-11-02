#include <socket.hpp>

namespace icq {

	Socket::Socket(std::string host, int port) {

		if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			return;
		}
		int TRUE = 1;
		struct timeval tv;
		tv.tv_sec = 60;
		tv.tv_usec = 0;
		if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv)) {
			perror("setsockopt: rcvtimeo");
		}
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*) &TRUE, sizeof (int));
#ifdef SO_NOSIGPIPE
		setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void*) &TRUE, sizeof (int));
#endif
		struct hostent* h;
		if ((h = gethostbyname(host.c_str())) == 0) {
			sockfd = -1;
			return;
		}

		if (h->h_length != sizeof ( struct in_addr)) {
			sockfd = -1;
		} else {
			memcpy(&server.sin_addr, h->h_addr, sizeof ( struct in_addr));
		}
		free(h);
		server.sin_family = AF_INET;
		server.sin_port = htons(port);
	}

	Socket::~Socket(){

	};

	bool Socket::connect(){
		if (sockfd != -1) {
			return true;
		}

		if (::connect(sockfd, (struct sockaddr *) &server, sizeof (struct sockaddr)) < 0) {
			return false;
		}

		return true;
	};

	void Socket::disconnect(){
		if (sockfd == -1)
			return;
		close(sockfd);
		sockfd = -1;
	};

	ConnErrorNo Socket::recv(){
		if(sockfd == -1)
			return ConnErrorNo::NotConnected;

		char* buf = new char[MAX_BUF];
		memset(buf, 0, MAX_BUF);
		ssize_t r = ::recv(sockfd, buf, MAX_BUF, MSG_NOSIGNAL);
		if (r == -1 || r == 0) {
			disconnect();
			return ConnErrorNo::SocketClosed;
		}
		buf[r] = 0;
		if (buf[0] == FLAP_MARKER) {
			//icq_packet_in* packet = new icq_packet_in(buf, r);
			//client->getOscarParser()->parser(packet);
			//delete packet;
		} else {
			delete [] buf;
		}
		return ConnErrorNo::OK;
	};

	ConnErrorNo Socket::send(char* buf, ssize_t len){
		if (sockfd == -1)
			return ConnErrorNo::NotConnected;
		if(sendall(buf, len, MSG_NOSIGNAL) == -1) {
			disconnect();
			return ConnErrorNo::SocketClosed;
		}
		return ConnErrorNo::OK;

	};

	bool Socket::changeHost(std::string host, int port){
		disconnect();

		if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
			return false;
		}
		int TRUE = 1;
		struct timeval tv;
		tv.tv_sec = 60;
		tv.tv_usec = 0;
		if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv)) {
			perror("setsockopt: rcvtimeo");
		}
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*) &TRUE, sizeof (int));
#ifdef SO_NOSIGPIPE
		setsockopt(sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void*) &TRUE, sizeof (int));
#endif
		struct hostent* h;
		if ((h = gethostbyname(host.c_str())) == 0) {
			sockfd = -1;
			return false;
		}

		if (h->h_length != sizeof ( struct in_addr)) {
			sockfd = -1;
		} else {
			memcpy(&server.sin_addr, h->h_addr, sizeof ( struct in_addr));
		}
		free(h);
		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		return connect();
	};

	ssize_t Socket::sendall(char *buf, ssize_t len, int flags) {
		ssize_t total = 0;
		ssize_t n = 0;
		while (total < len) {
			n = ::send(sockfd, buf + total, len - total, flags);
			if (n == -1) {
				break;
			}
			if (n == 0) {
				n = -1;
				break;
			}
			total += n;
		}
		return (n == -1 ? -1 : total);
	};
}
