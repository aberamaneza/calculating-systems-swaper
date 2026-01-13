#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <algorithm> 
#include <cmath>
std::map<char,int> HexDec = {
    {'A', 10},
    {'B', 11},
    {'C', 12},
    {'D', 13},
    {'E', 14},
    {'F', 15}
};
std::map<std::string,int> Systems = {
    {"binary", 2},
    {"ternary", 3},
    {"quaternary", 4},
    {"quinary", 5},
    {"senary", 6},
    {"septenary", 7},
    {"octal", 8},
    {"nonary", 9},
    {"decimal", 10},
    {"undecimal", 11},
    {"duodecimal", 12},
    {"hexadecimal", 16}
};



std::string itos(int n) {
    if (n < 10) return std::string(1, '0' + n);
    else return std::string(1, 'A' + (n - 10));
}

void help(){
	std::cout<<"type 'systems' for see the supported calculating systems"<<std::endl;
	std::cout<<"type 'swap' for swap type to other one"<<std::endl;
	std::cout<<"type 'exit' for exit"<<std::endl;
	//std::cout<<"type 'systems' for see the supported calculating systems"<<std::endl;
}
void  systems(){
	    for (auto &[key, value] : Systems) {
        std::cout << key << "\n";
    }
}
double to_decimal(const std::string &number, int base){
    double result = 0;
    int power = 0;

    for (int i = number.size() - 1; i >= 0; --i){
        char c = number[i];
        int tmp;
        if (c >= '0' && c <= '9') tmp = c - '0';
        else if (HexDec.find(c) != HexDec.end()) tmp = HexDec[c];
        else { std::cerr << "Invalid digit " << c << std::endl; return 0; }

        result += tmp * pow(base, power);
        power++;
    }
    return result;
}
std::string to_system(int number, int base) {
    if (number == 0) return "0";
    std::string result;
    while (number > 0) {
        int rem = number % base;
        result += itos(rem);
        number /= base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}
void swap(){
	std::string base, tobase, num;

	std::cout << "type ur base: ";
	std::cin >> base;

	std::cout << "type ur swap base: ";
	std::cin >> tobase;

	std::cout << "type ur number: ";
	std::cin >> num;

	auto it = Systems.find(base);
	auto it2 = Systems.find(tobase);

	if (it == Systems.end() || it2 == Systems.end()){
		std::cerr << "system not exist" << std::endl;
		return;
	}

	int from_base = it->second;
	int to_base = it2->second;

	double tmpnum = to_decimal(num, from_base);
	std::string tosystem = to_system((int)tmpnum, to_base);

	std::cout << "the num (" << num << " in " << base << ") in base " << tobase << " is " << tosystem << std::endl;
}

std::map<std::string,std::function<void()>> functions = {
	{"help", help},
	{"systems", systems},
	{"swap", swap},
	//{"help", help},
};
int main(){
	while(true) {
		std::string input;
		std::cout << "type help for see commands\n$-> : ";
		std::cin >> input;

		auto it = functions.find(input);
		if (it != functions.end()){
			it->second();
		} else if (input == "exit") {
			break;
		} else {
			std::cout << "Unknown command\n";
		}
	}
	return 0;
}