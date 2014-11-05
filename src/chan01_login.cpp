#include <parser.hpp>

namespace icq {

	void parser::parseLoginChannel(class packet_in* packet){
		icq_packet_out* out = new icq_packet_out(ICQ_CHANNEL_LOGIN);
		if(isLoginServer) {
			isLoginServer = false;

			out->writeDWord(0x00000001);
			out->writeTlvString(0x0001, uin.size(), uin.c_str());

			// Pack old style password hash
			BYTE hash[20];
			BYTE table[] =
			{
				0xf3, 0x26, 0x81, 0xc4,
				0x39, 0x86, 0xdb, 0x92,
				0x71, 0xa3, 0xb9, 0xe6,
				0x53, 0x7a, 0x95, 0x7c
			};

			for (int i = 0; i < password.size(); i++)
				hash[i] = (password[i] ^ table[i % 16]);

			out->writeTlvString(0x0002, password.size(), hash);

			// Pack client identification details
			out->writeTlvString(0x0003, (WORD)sizeof(CLIENT_ID_STRING)-1, (byte*)CLIENT_ID_STRING);
			out->writeTlvWord(0x0017, CLIENT_VERSION_MAJOR);
			out->writeTlvWord(0x0018, CLIENT_VERSION_MINOR);
			out->writeTlvWord(0x0019, CLIENT_VERSION_LESSER);
			out->writeTlvWord(0x001a, CLIENT_VERSION_BUILD);
			out->writeTlvWord(0x0016, CLIENT_ID_CODE);
			out->writeTlvDWord(0x0014, CLIENT_DISTRIBUTION);
			out->writeTlvString(0x000f, 0x0002, (byte*)CLIENT_LANGUAGE);
			out->writeTlvString(0x000e, 0x0002, (byte*)CLIENT_COUNTRY);
			out->writeTlvString(0x0094, 0x0001, &c->m_bConnectionLost); // CLIENT_RECONNECT flag

			c->send(out);

			if(coockies.len) {
				delete [] coockies.data;
				coockies.data = NULL;
				coockies.len = 0;
			}

		} else {
			if(coockies.len) {
				out->writeDWord(0x00000001);
				out->writeTlvString(0x0006, coockies.len, coockies.data);

				// Pack client identification details
				out->writeTlvString(0x0003, (WORD)sizeof(CLIENT_ID_STRING)-1, (LPBYTE)CLIENT_ID_STRING);
				out->writeTlvWord(0x0017, CLIENT_VERSION_MAJOR);
				out->writeTlvWord(0x0018, CLIENT_VERSION_MINOR);
				out->writeTlvWord(0x0019, CLIENT_VERSION_LESSER);
				out->writeTlvWord(0x001a, CLIENT_VERSION_BUILD);
				out->writeTlvWord(0x0016, CLIENT_ID_CODE);
				out->writeTlvDWord(0x0014, CLIENT_DISTRIBUTION);
				out->writeTlvString(0x000f, 0x0002, (LPBYTE)CLIENT_LANGUAGE);
				out->writeTlvString(0x000e, 0x0002, (LPBYTE)CLIENT_COUNTRY);
				out->writeDWord(0x00940001); // reconnect flag
				out->writeByte(0);
				out->writeTlvDWord(0x8003, 0x00100000); // Unknown
				c->send(out);

				delete [] coockies.data;
				coockies.data = NULL;
				coockies.len = 0;
			}
		}
	};

}
