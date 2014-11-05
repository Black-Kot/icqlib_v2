#include <base.hpp>
#include <icq_types.hpp>

namespace icq {

	class packet_out{
		public:
		packet_out(byte channel);

		~packet_out();

		void writeByte(byte b);

		void writeString(byte* b, ssize_t len);

		void writeWord(word w);

		void writeLEWord(word w);

		void writeDWord(dword dw);

		void writeLEDWord(dword dw);

		void writeQWord(qword qw);

		void writeLEQWord(qword qw);

		void writeGuid(guid g);

		void writeTlvByte(word type, byte data);

		void writeTlvString(word type, word len, byte* data);

		void writeTlvWord(word type, word data);

		void writeTlvDWord(word type, dword data);

		void writeTlvQWord(word type, qword data);

		void setSeq(word seq);

		void setSize(word size);

		byte* getBuf();

		ssize_t getSize();

		private:

		vector<byte> buf;

	};

}
