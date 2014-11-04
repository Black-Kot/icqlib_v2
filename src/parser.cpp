#include <parser.hpp>

namespace icq {

	parser::parser(class client* _c) {
		c = _c;
	}

	void parser::parse(class socket* sock, class packet_in* packet){
		while (true) {
			flap first = packet->readFlap();
			if (first.id != FLAP_MARKER)
				return;
			if(first.size > packet->getOffset())
				return;
		}
	};

}
