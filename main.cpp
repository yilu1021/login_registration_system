#include <iostream>
#include <sstream>
#include <string>
#include <limits>
//https://www.youtube.com/watch?v=I_aWPGCaaFA

enum REGISTERORLOGIN {REGISTER, LOGIN};

REGISTERORLOGIN isLoginOrRegister() {
    int input_choice;
    std::cin >> input_choice;

    if (std::cin.fail() || (input_choice != 0 && input_choice != 1)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter either 0 or 1" << std::endl;
        return isLoginOrRegister();
    }
    else if (input_choice == 0) {
        return REGISTERORLOGIN::REGISTER;
    }
    else {
        return REGISTERORLOGIN::LOGIN;
    }
}

int main() {
    std::cout << "#0 Register" << std::endl;
    std::cout << "#1 Log In" << std::endl;
    REGISTERORLOGIN loginOrRegister = isLoginOrRegister();
    std::cout << loginOrRegister;

//    std::string input_choice_str;
//    getline(std::cin, input_choice);



//    std::stringstream(input_choice_str) >> input_choice;

//    std::cout << input_choice;

//    std::cin >> input_choice_str;
//    std::cout << input_choice_str;

//    int input_choice_int;
//    stringstream
//    std::cin
    return 0;
}
