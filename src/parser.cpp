#include <parser.hpp>

namespace icq {

	parser::parser(class client* _c, std::string _uin, std::string _password) {
		c = _c;
		isLoginServer = true;
		bLoggedIn = false;
		newServerReady = false;
		isMigrating = false;
		bReinitRecver = false;
		bMyAvatarInited = false;
		uin = _uin;
		password = _password;
	}

	void parser::parse(class packet_in* packet){
		while (true) {
			flap first = packet->readFlap();
			if (first.id != FLAP_MARKER)
				return;
			if(first.size > packet->getOffset())
				return;
			switch(first.channel) {
				case ICQ_CHANNEL_LOGIN:
					parseLoginChannel(packet);
				break;
				case ICQ_CHANNEL_DATA:
				break;
				case ICQ_CHANNEL_ERROR:
				break;
				case ICQ_CHANNEL_CLOSE:
				break;
				case ICQ_CHANNEL_PING:
				break;
				default:
				break;
			}
		}
	};

}
