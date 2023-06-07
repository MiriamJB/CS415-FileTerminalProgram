#include <iostream>
#include <cstring>
#include <string>
#include  <bits/stdc++.h>
#include <filesystem>
#include <sstream>


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

int main() {
    std::string input;
    std::string command[2];
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

        //split the input and put it into the command variable
        int i = 0;
        std::stringstream ssin(input);
        while (ssin.good() && i < 2){
            ssin >> command[i];
            ++i;
        }
    
        if (input == "") {
            //if the user simply presses enter, it will re-start the loop
        } else if (input == "?" || input == "help") {
            userManuel();
        } else if (command[0] == "create") {
            std::cout << "File \"" << command[1] << "\" created.\n";
        } else if (command[0] == "read") {
        } else if (command[0] == "write") {
        } else if (command[0] == "delete") {
        } else if (input == "quit") {
            running = false;
        } else {
            std::cout << "Error: invalid command.\n";
        }
    }
    
    return 0;
}