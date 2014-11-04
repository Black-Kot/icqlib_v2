#include <cstddef>
#include <cstdint>
#include <cstdlib>

#define FLAP_MARKER 0x2A

namespace icq {
	typedef unsigned char u8;
	typedef char byte;
	typedef uint16_t word;
	typedef uint32_t dword;
	typedef uint64_t qword;
	typedef byte* guid;

	struct flap {
		byte id;
		byte channel;
		word seq;
		word size;
	};

	struct snac {
		word family;
		word subtype;
		word flags;
		dword request_id;
	};

	struct tlv {
		word type;
		word lenght;
		struct _data {
			byte* bdata;
			word wdata;
			dword ddata;
		} data;
	};
}
