#include <client.hpp>

namespace icq {

		client::client(std::string host, int port, std::string uin, std::string password){
			iparser = new parser(this, uin, password);
			sock = new socket(iparser,host, port);
			m_bConnectionLost = 0x00;
		};

		client::~client(){
			delete iparser;
			delete sock;
		};

		bool client::connect(){
			return sock->connect();

		};

		void client::disconnect(){

		};

		ConnErrorNo client::recv(){

		};
}
