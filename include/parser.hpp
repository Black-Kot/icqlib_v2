#include <base.hpp>
#include <socket.hpp>
#include <packet_in.hpp>
#include <packet_out.hpp>

namespace icq {

	class parser {

		public:

			parser(class client* _c, std::string uin, std::string password);

			~parser();

			void parse(class packet_in* packet);

			// channels

			void parseLoginChannel(class packet_in* packet);

			void parseDataChannel(class packet_in* packet);

			void parseErrorChannel(class packet_in* packet);

			void parseCloseChannel(class packet_in* packet);

			void parsePingChannel(class packet_in* packet);

			//

		private:

		class client* c;
		std::string uin;
		std::string password;

		bool isLoginServer;
		bool bLoggedIn;
		bool newServerReady;
		bool isMigrating;
		bool bReinitRecver;
		bool bMyAvatarInited;

		struct coockie coockies;

	};

}
