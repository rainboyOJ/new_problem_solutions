#include <iostream>


int main(){
	char c;
	std::cin >> std::noskipws >> c;	
	std::cout << "  " << (char)(c) << "\n";
	std::cout << " " << (char)(c) << (char)(c) << (char)(c) << "\n";
	std::cout << (char)(c) << (char)(c) << (char)(c) << (char)(c) << (char)(c) << "\n";
	std::cout << " " << (char)(c) << (char)(c) << (char)(c) << "\n";
	std::cout << "  " << (char)(c) << "\n";
	return 0;
}
