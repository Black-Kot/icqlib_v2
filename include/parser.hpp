#include <base.hpp>
#include <socket.hpp>
#include <packet_in.hpp>
#include <packet_out.hpp>

namespace icq {

	class parser {

		public:

			parser(class client* _c);

			~parser();

			void parse(class scoket* sock,class packet_in* packet);

		private:

		class client* c;

	};

}
