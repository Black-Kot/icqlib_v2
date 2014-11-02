#include <base.h>
#include <iostream>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));
	std::cout << "START" << std::endl;
	int a = icq::utils::random(1,10);
	std::cout << a << std::endl;
	std::cout << "END" << std::endl;
	return 0;
}
