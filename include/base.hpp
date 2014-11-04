#include <cstdlib>
#include <limits>
#include <random>
#include <memory>
#include <clocale>
#include <locale>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cerrno>
#include <unistd.h>
#include <icq_types.hpp>

namespace icq {

	namespace utils {

			static int random(int start, int end) {
				std::random_device generator;
				std::uniform_int_distribution<int> distribution(start,end);
				int result = distribution(generator);
				return result;
			}

			static int random(int end = 1000){
				return random(1, end);
			};
			
			static std::string random(std::string str, int count){
				std::string out;
				for(int i = 0; i < count; i++)
					out += str[random(0, str.size())];
				return out;
			};
	}
}
