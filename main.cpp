#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <unistd.h>

//A combo of ofstream and ifstream: creates, reads, and writes to files
#include <fstream>


//https://www.youtube.com/watch?v=I_aWPGCaaFA
//https://stackoverflow.com/questions/3512434/using-struct-stat
//https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
//inline bool exists_test0 (const std::string& name) {
//    ifstream f(name.c_str());
//    return f.good();
//}
//
//inline bool exists_test1 (const std::string& name) {
//    if (FILE *file = fopen(name.c_str(), "r")) {
//        fclose(file);
//        return true;
//    } else {
//        return false;
//    }
//}
//
//inline bool exists_test2 (const std::string& name) {
//    return ( access( name.c_str(), F_OK ) != -1 );
//}
//
//inline bool exists_test3 (const std::string& name) {
//    struct stat buffer;
//    return (stat (name.c_str(), &buffer) == 0);
//}

enum REGISTERORLOGIN {REGISTER, LOGIN};
enum STRINGTYPE {USERNAME, PASSWORD};

void clear_cin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

REGISTERORLOGIN isLoginOrRegister() {
    int input_choice;
    std::cin >> input_choice;

    if (std::cin.fail() || (input_choice != 0 && input_choice != 1)) {
        //is there a better way to completely clear the input stream?
        clear_cin();
        std::cout << "Please enter either 0 or 1" << std::endl;
        return isLoginOrRegister();
    }
    else if (input_choice == 0) {
        clear_cin();
        return REGISTERORLOGIN::REGISTER;
    }
    else {
        clear_cin();
        return REGISTERORLOGIN::LOGIN;
    }
}

const int str_len_min = 4;
const int str_len_max = 8;

bool valid_input_str(const std::string& str) {
    int str_len = str.length();
    if (str_len < str_len_min || str_len > str_len_max) {
        std::cout << "Length should be between " << str_len_min << " and " << str_len_max << std::endl;
        return false;
    }

    bool hasspace = std::find_if(str.begin(), str.end(), isspace) != str.end();

    if (hasspace) {
        std::cout << "Must not contain spaces" << std::endl;
        return false;
    }
    return true;
}

bool usrname_exists(const std::string& path) {
    struct stat buffer{};
//    http://codewiki.wikidot.com/c:system-calls:stat
    return (stat (path.c_str(), &buffer) == 0);
}

std::string get_str(const STRINGTYPE& type) {
    std::string label;
    if (type == STRINGTYPE::USERNAME) {
        label = "Username";
    } else {
        label = "Password";
    }

    std::cout << "Enter " + label + " (must be between " << str_len_min << " to " << str_len_max << " characters, no "
                                                                                                    "spaces)" << std::endl;
    std::string input_str;

    std::getline(std::cin, input_str);

    if (!valid_input_str(input_str)) {
        return get_str(type);
    }

    std::cout << "You entered " + label + " " + input_str << std::endl;
    return input_str;
}

int register_user() {
    std::string username = get_str(STRINGTYPE::USERNAME);
    if (usrname_exists(username)) {
        std::cout << "Username " + username + " already registered" << std::endl;
        return register_user();
    }
    std::string password = get_str(STRINGTYPE::PASSWORD);
    std::ofstream PwdFile(username);
    PwdFile << password;
    PwdFile.close();
    return 0;
}

int log_in_user() {
    std::string user_entered_username = get_str(STRINGTYPE::USERNAME);
    std::string user_entered_pwd = get_str(STRINGTYPE::PASSWORD);
    std::string pwd;
    std::ifstream PwdFile(user_entered_username);
    std::getline(PwdFile, pwd);
    if (user_entered_pwd == pwd) {
        std::cout << "Log in successful" << std::endl;
        return 1;
    } else {
        std::cout << "Username or password incorrect" << std::endl;
        return log_in_user();
    }
}

int main() {
    std::cout << "#0 Register" << std::endl;
    std::cout << "#1 Log In" << std::endl;
    REGISTERORLOGIN loginOrRegister = isLoginOrRegister();

    if (loginOrRegister == REGISTERORLOGIN::REGISTER) {
        return register_user();
    } else if (loginOrRegister == REGISTERORLOGIN::LOGIN) {
        return log_in_user();
    }

//    std::string input_choice_str;
//    getline(std::cin, input_choice);



//    std::stringstream(input_choice_str) >> input_choice;

//    std::cout << input_choice;

//    std::cin >> input_choice_str;
//    std::cout << input_choice_str;

//    int input_choice_int;
//    stringstream
//    std::cin
}
