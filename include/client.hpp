#include <base.hpp>
#include <parser.hpp>
#include <socket.hpp>

namespace icq {

	class client {

		public:

		client(std::string host, int port, std::string uin, std::string password);

		~client();

		bool connect();

		void disconnect();

		ConnErrorNo recv();

		private:

		class socket* sock;

	};
}
