#include <iostream>
#include <cstring>
#include <string>
#include  <bits/stdc++.h>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;
char fileDirectory[50];
int fileIndex;

//displays avalable commands
void userManuel() {
    std::cout
        << "-------------------------------USER MANUEL-------------------------------\n"
        << "                  ***Commands ARE case-sensitive***\n"
        << "? OR help                                        Displays the user manuel\n"
        << "showfiles                                Lists all files in the directory\n"
        << "create <fileName>                    Creates a file with the desired name\n"
        << "read <fileName>                  Shows the contents of the specified file\n"
        << "write <fileName>                             Writes to the specified file\n"
        << "delete <fileName>                              Deletes the specified file\n"
        << "quit                                      Stops the File Terminal Program\n"
        << "\n";
}

//will create a file in the "files" folder
void createFile(const std::string& fileName) {
    std::ofstream file("files/" + fileName);
    if (file) {
        std::cout << fileName << " created successfully." << std::endl;
        file.close();
        //////////////////////////////// TODO: add created files to directory
    } else {
        std::cerr << "ERROR: could not create \"" << fileName << "\"." << std::endl;
    }
}

////////////////////////////////////////////////////// TODO: refine readfile
void readFile(const std::string& fileName) {
    std::ifstream file("files/" + fileName);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }
}

int main() {
    std::string input;
    std::string splitInput[2];
    bool running = true;
    char* prompt = "> ";
    fileIndex = 0;
    
    //welcome message
    std::cout << R"(
    ___________                  .__              .__       _____                
    \__    ___/__________  _____ |__| ____ _____  |  |     /  _  \   ____  ____  
      |    |_/ __ \_  __ \/     \|  |/    \\__  \ |  |    /  /_\  \_/ ___\/ __ \ 
      |    |\  ___/|  | \/  Y Y  \  |   |  \/ __ \|  |__ /    |    \  \__\  ___/ 
      |____| \___  >__|  |__|_|  /__|___|  (____  /____/ \____|__  /\___  >___  >
                 \/            \/        \/     \/               \/     \/    \/ 
    
    Welcome to the TERMINAL ACE File Terminal Program.
    You may enter a command or type "?" for a list of avalable commands.
    )" << std::endl;
    
    //this is the loop that runs the program
    while (running) {
        //the loop starts by printing out the prompt
        std::cout << prompt;

        //read input from the user
        std::getline(std::cin, input);

        //split the input and put it into the splitInput variable
        int i = 0;
        std::stringstream ssin(input);
        while (ssin.good() && i < 2){
            ssin >> splitInput[i];
            ++i;
        }
    
        if (input == "") {
            //if the user simply presses enter, it will re-start the loop
        } else if (input == "?" || input == "help") {
            userManuel();
        } else if (splitInput[0] == "create") {
            createFile(splitInput[1]);
        } else if (splitInput[0] == "read") {
            readFile(splitInput[1]);
        } else if (splitInput[0] == "write") {
        } else if (splitInput[0] == "delete") {
        } else if (input == "quit") {
            running = false;
        } else {
            std::cerr << "ERROR: invalid command.\n";
        }
    }
    
    return 0;
}