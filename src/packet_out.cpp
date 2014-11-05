#include <packet_out.hpp>

namespace icq {

		packet_out::packet_out(byte channel){
			writeByte(FLAP_MARKER);
			writeByte(channel);
			writeWord(0x0000);
			writeWord(0x0000);
		};

		packet_out::~packet_out(){

		};

		void packet_out::writeByte(byte b){
			buf.insert(b);
		};

		void packet_out::writeString(byte* b, ssize_t len){
			for (ssize_t i = 0; i < len; i++)
				writeByte(b[i]);

		};

		void packet_out::writeLEString(byte* b, ssize_t len){
			for (ssize_t i = len; i != 0; i--)
				writeByte(b[i]);

		};

		void packet_out::writeWord(word w){
			writeByte((w & 0xff00) >> 8);
			writeByte(w & 0x00ff);
		};

		void packet_out::writeLEWord(word w){
			writeByte(w & 0x00ff);
			writeByte((w & 0xff00) >> 8);

		};

		void packet_out::writeDWord(dword dw){
			writeByte((dw & 0xff000000) >> 24);
			writeByte((dw & 0x00ff0000) >> 16);
			writeByte((dw & 0x0000ff00) >> 8);
			writeByte(dw & 0x000000ff);
		};

		void packet_out::writeLEDWord(dword dw){
			writeByte(dw & 0x000000ff);
			writeByte((dw & 0x0000ff00) >> 8);
			writeByte((dw & 0x00ff0000) >> 16);
			writeByte((dw & 0xff000000) >> 24);
		};

		void packet_out::writeQWord(qword qw){
			writeDWord((dword)(qw >> 32));
			writeDWord((dword)(qw & 0xffffffff));
		};

		void packet_out::writeLEQWord(qword qw){
			writeLEDWord((dword)(qw & 0xffffffff));
			writeLEDWord((dword)(qw >> 32));
		};

		void packet_out::writeGuid(guid g){
			writeString(g, 16);
		};

		void packet_out::writeTlvByte(word type, byte data){
			writeWord(type);
			writeWord(0x0001);
			writeByte(data);
		};

		void packet_out::writeTlvString(word type, word len, byte* data){
			writeWord(type);
			writeWord(len);
			writeString(data);
		};

		void packet_out::writeTlvWord(word type, word data){
			writeWord(type);
			writeWord(0x0002);
			writeWord(data);
		};

		void packet_out::writeTlvDWord(word type, dword data){
			writeWord(type);
			writeWord(0x0004);
			writeDWord(data);
		};

		void packet_out::writeTlvQWord(word type, qword data){
			writeWord(type);
			writeWord(0x0008);
			writeQWord(data);
		};

		void packet_out::setSeq(word seq){
			buf[3] = (seq & 0x00ff);
			buf[4] = (seq >> 8 & 0xff00);
		};

		void packet_out::setSize(word size){
			buf[5] = (size & 0x00ff);
			buf[6] = (size >> 8 & 0xff00);
		};

		byte* packet_out::getBuf(){
			buf.data();
		};

		ssize_t packet_out::getSize(){
			buf.size();
		};

}
