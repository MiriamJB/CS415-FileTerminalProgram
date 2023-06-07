#include <iostream>
#include <cstring>
#include <string>
#include  <bits/stdc++.h>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;
std::string fileDirectory[50];
int fileIndex;

//displays avalable commands
void userManuel() {
    std::cout
        << "-------------------------------USER MANUEL-------------------------------\n"
        << "                  ***Commands ARE case-sensitive***\n"
        << "? OR help                                        Displays the user manuel\n"
        << "directory                                Lists all files in the directory\n"
        << "create <fileName>                    Creates a file with the desired name\n"
        << "read <fileName>                  Shows the contents of the specified file\n"
        << "write <fileName>                             Writes to the specified file\n"
        << "delete <fileName>                              Deletes the specified file\n"
        << "quit                                      Stops the File Terminal Program\n"
        << "-------------------------------------------------------------------------\n"
        << std::endl;
}

//prints all the files that are stored in fileDirectory
void showFileDirectory() {
    if (fileIndex == 0) {
        std::cout << "The file directory is empty." << std::endl;
    } else {
        std::cout << "------------------------------FILE DIRECTORY------------------------------" << std::endl;
        for (int i = 0; i < fileIndex; i++)
        std::cout << fileDirectory[i] << std::endl;
        std::cout << "--------------------------------------------------------------------------\n" << std::endl;
    }
}

//will create a file in the "files" folder
void createFile(const std::string& fileName) {
    if (fileIndex > 50) {
        std::cerr << "ERROR: could not create \"" << fileName << "\". The directory cannot hold more than 50 files.\n" << std::endl; 
    } else {
        std::ofstream file("files/" + fileName);
        if (file) {
            std::cout << fileName << " created successfully.\n" << std::endl;
            file.close();
            fileDirectory[fileIndex] = fileName;
            fileIndex++;
        } else {
            std::cerr << "ERROR: failed to create \"" << fileName << "\".\n" << std::endl;
        }
    }
}

//prints the contents of the file
void readFile(const std::string& fileName) {
    std::ifstream file("files/" + fileName);
    if (file) {
        std::cout << "\nExisting content of \"" << fileName << "\":" << std::endl;
        std::cout << "--------------------------------------------------------------------------" << std::endl;
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        std::cout << "--------------------------------------------------------------------------\n" << std::endl;
        file.close();
    } else {
        std::cerr << "ERROR: failed to open file \"" << fileName << "\".\n" << std::endl;
    }
}

//shows the current content of the file and lets the user overwrite it
void writeFile(const std::string& fileName) {
    std::ifstream file("files/" + fileName);
    if (file) {
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();

        readFile(fileName);
        std::cout << "Enter the modified content. (Type \"SAVE\" to save and exit.)" << std::endl;

        content.clear();
        while (std::getline(std::cin, line)) {
            if (line == "SAVE") {
                std::ofstream file("files/" + fileName);
                file << content;
                std::cout << "Content saved to file \"" << fileName << "\".\n" << std::endl;
                file.close();
                break;
            }
            content += line + "\n";
        }
    } else {
        std::cerr << "ERROR: failed to open file \"" << fileName << "\".\n" << std::endl;
    }
}

//asks if the user is sure about deletion and then deletes the file accordingly
void deleteFile(const std::string& fileName) {
    std::cout << "Are you sure you want to delete \"" << fileName << "\"? (Y/N) ";
    std::string response;
    std::getline(std::cin, response);

    if (response == "N" || response == "n") {
        std::cout << "File \"" << fileName << "\" has NOT been deleted.\n" << std::endl;
    } else if (response == "Y" || response == "y") {
        if (fs::remove("files/" + fileName)) {
            std::cout << "File \"" << fileName << "\" has been deleted.\n" << std::endl;
        } else {
        std::cerr << "ERROR: failed to delete file: \"" << fileName << "\".\n" << std::endl;
        }
    } else {
        std::cerr << "ERROR: invalid response.\n" << std::endl;
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
        } else if (input == "directory") {
            showFileDirectory();
        } else if (splitInput[1] != "" && splitInput[0] == "create") {
            createFile(splitInput[1]);
        } else if (splitInput[1] != "" && splitInput[0] == "read") {
            readFile(splitInput[1]);
        } else if (splitInput[1] != "" && splitInput[0] == "write") {
            writeFile(splitInput[1]);
        } else if (splitInput[1] != "" && splitInput[0] == "delete") {
            deleteFile(splitInput[1]);
        } else if (input == "quit") {
            running = false;
        } else {
            std::cerr << "ERROR: invalid command.\n" << std::endl;
        }

        //reset the input
        input = "";
        splitInput[0] = "";
        splitInput[1] = "";
    }
    
    return 0;
}