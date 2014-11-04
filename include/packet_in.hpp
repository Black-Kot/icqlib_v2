#include <base.hpp>

namespace icq {

	class packet_in {

		public:

		packet_in(char* bytes, ssize_t len);

		~packet_in();

		flap readFlap();

		snac readSnac();

		tlv readTlv();

		std::map<word, tlv> readAllTlv(word count = 0);

		byte readByte();

		byte* readString(word len);

		word readWord();

		word readDWord();

		word readLEDWord();

		qword readQWord();

		word readLEWord();

		qword readLEQWord();

		guid readGuid();

		ssize_t getSize();

		private:

		char* buf;
		ssize_t offset;
		ssize_t lenght;
	};

}
