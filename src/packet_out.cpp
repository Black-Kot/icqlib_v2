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
			writeByte((wValue & 0xff00) >> 8);
			writeByte(wValue & 0x00ff);
		};

		void packet_out::writeLEWord(word w){
			writeByte(wValue & 0x00ff);
			writeByte((wValue & 0xff00) >> 8);

		};

		void packet_out::writeDWord(dword qw){
			writeByte((dwValue & 0xff000000) >> 24);
			writeByte((dwValue & 0x00ff0000) >> 16);
			writeByte((dwValue & 0x0000ff00) >> 8);
			writeByte(dwValue & 0x000000ff);
		};

		void packet_out::writeLEDWord(dword qw){
			writeByte(dwValue & 0x000000ff);
			writeByte((dwValue & 0x0000ff00) >> 8);
			writeByte((dwValue & 0x00ff0000) >> 16);
			writeByte((dwValue & 0xff000000) >> 24);
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

		byte* packet_out::getBuf(){
			buf.data();
		};

		ssize_t packet_out::getSize(){
			buf.size();
		};

}
