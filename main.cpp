#include <iostream>
#include <cstring>
#include <string>
#include  <bits/stdc++.h>
#include <filesystem>

namespace fs = std::filesystem;

//displays avalable commands
void userManuel() {
    std::cout
        << "-------------------USER MANUEL-------------------\n"
        << "      ***Commands ARE case-sensitive***\n"
        << "? OR help                Displays the user manuel\n"
        << "create                 Opens the Create File menu\n"
        << "read                     Opens the Read File menu\n"
        << "write                   Opens the Write File menu\n"
        << "delete                 Opens the Delete File menu\n"
        << "quit              Stops the File Terminal Program\n"
        << "\n";
}

void createMenu() {

}

int main() {
    std::string command;
    std::string input;
    bool running = true;
    char* prompt = ">";
    
    //welcome message
    std::cout << "\nWelcome to Miriam's File Terminal Program. You may enter a command." << std::endl;
    
    //this is the loop that runs the program
    while (running) {
        //the loop starts by printing out the prompt
        std::cout << prompt;

        //read input from the user
        std::getline(std::cin, input);
        command = input; /////////////////////TODO: get first word from input
    
        if (input == "") {
            //if the user simply presses enter, it will re-start the loop
        } else if (input == "?" || input == "help") {
            userManuel();
        } else if (input == "create") {
            createMenu();
        } else if (input == "quit") {
            running = false;
        } else {
            std::cout << "Error: invalid command.\n";
        }
    }
    
    return 0;
}