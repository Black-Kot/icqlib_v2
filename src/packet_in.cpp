#include <packet_in.hpp>

namespace icq {

		packet_in::packet_in(char* bytes, ssize_t len){
			buf = bytes;
			lenght = len;
		};

		packet_in::~packet_in(){
			delete [] buf;
		};

		flap packet_in::readFlap(){
			flap tmp;
			tmp.id = readByte();
			tmp.channel = readByte();
			tmp.seq = readWord();
			tmp.size = readWord();
			return tmp;
		};

		snac packet_in::readSnac(){
			snac tmp;
			tmp.family = readWord();
			tmp.subtype = readWord();
			tmp.flags = readWord();
			tmp.request_id = readQWord();
			return tmp;
		};

		tlv packet_in::readTlv(){
			tlv tmp;
			tmp.type = readWord();
			tmp.lenght =  = readWord();
			tmp.data.bdata = readString(tmp.lenght);
			return tmp;

		};

		std::map<word, tlv> packet_in::readAllTlv(word count){
			if (count == 0)
				count = readWord();
			std::map<word, tlv> tlvs;
			for (word i =0; i < count; i++) {
				tlv tmp = readTlv();
				tlvs[tmp.type] = tmp;
			}
			return tlvs;
		};

		byte packet_in::readByte(){
			if(getSize() < 1)
				return NULL;
			return buf[offset++];
		};

		byte* packet_in::readString(word len){
			if(getSize() < len)
				return NULL;
			byte* tmp = new byte[len];
			for(word i =0; i < len; i++)
				tmp = buf[offset++];
			return tmp;
		};

		word packet_in::readWord(){
			if(getSize() < 2)
				return NULL;
			word tmp = 0;
			tmp = buf[offset++] << 8;
			tmp |= buf[offset++];
			return tmp;
		};

		word packet_in::readLEWord(){
			if(getSize() < 2)
				return NULL;
			word tmp = 0;
			tmp = buf[offset++];
			tmp |= buf[offset++] << 8;
			return tmp;
		};

		word packet_in::readDWord(){
			if(getSize() < 4)
				return NULL;
			word tmp = 0;
			tmp = buf[offset++] << 24;
			tmp |= buf[offset++] << 16;
			tmp |= buf[offset++] << 8;
			tmp |= buf[offset++];
			return tmp;
		};

		word packet_in::readLEDWord(){
			if(getSize() < 4)
				return NULL;
			word tmp = 0;
			tmp = buf[offset++];
			tmp |= buf[offset++] << 8;
			tmp |= buf[offset++] << 16;
			tmp |= buf[offset++] << 24;
			return tmp;
		};

		qword packet_in::readQWord(){
			if(getSize() < 8)
				return NULL;
			qword tmp;
			dword a = readDWord();
			tmp = ((qword)a) << 32;
			dword b = readDWord();
			tmp |= b;
			return tmp;
		};

		qword packet_in::readLEQWord(){
			if(getSize() < 8)
				return NULL;
			qword tmp;
			dword a = readDWord();
			tmp = b;
			dword b = readDWord();
			tmp |= ((qword)a) << 32;
			return tmp;
		};

		guid packet_in::readGuid(){
			if(getSize() < 16)
				return NULL;
			return readString(16);
		};

		ssize_t packet_in::getSize(){
			lenght - offset;
		};

		private:

		char* buf;
		ssize_t offset;
		ssize_t lenght;
	};

}
