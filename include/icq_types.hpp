#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <icq_constants.h> // from Miranda IM

#define FLAP_MARKER 0x2A

#define ICQ_CHANNEL_LOGIN	0x01
#define ICQ_CHANNEL_DATA	0x02
#define ICQ_CHANNEL_ERROR	0x03
#define ICQ_CHANNEL_CLOSE	0x04
#define ICQ_CHANNEL_PING	0x05

#define UINMAXLEN                   11 // DWORD string max len + 1

namespace icq {
	typedef char byte;
	typedef int16_t word;
	typedef int32_t dword;
	typedef int64_t qword;
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
			byte bdata;
			byte* sdata;
			word wdata;
			dword ddata;
			qword qdata;
		} data;
	};

	struct coockie {
		byte* data;
		word len;
	};
}
