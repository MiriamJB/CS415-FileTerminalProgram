#include <iostream>
#include <cstring>
#include <string>
#include  <bits/stdc++.h>

int main() {
    std::string input;
    char* prompt = ">";
    
    std::cout << "\nWelcome to Miriam's File Terminal Program. You may enter a command." << std::endl;
    std::cout << prompt;
    std::getline(std::cin, input);
    
    if (input == "?") {
        userManuel();
    }
    
    return 0;
}

void userManuel() {
    std::cout << "------------------------USER MANUEL------------------------\n"
        << "\t";
}