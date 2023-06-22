#include <iostream>
#include <cstring>
#include <string>
#include  <bits/stdc++.h>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;
std::string currentDirectory = "";
std::string directory = "files"; 
////TODO: figure out how to subtract from strings

//creates a directory called "files" to hold the files
void startup() {
    if (!fs::exists(directory)) {
        fs::create_directory(directory);
    }
}

//displays avalable commands
void userManuel() {
    std::cout
        << "-----------------------------------USER MANUEL-----------------------------------\n"
        << "                   ***Commands ARE case-sensitive***\n"
        << "? OR help                                                Displays the user manuel\n"
        << "directory                                        Lists all files in the directory\n"
        << "create <fileName>                          Creates a file with the specified name\n"
        << "read <fileName>                          Shows the contents of the specified file\n"
        << "write <fileName>                                     Writes to the specified file\n"
        << "delete <fileName>                                      Deletes the specified file\n"
        << "encrypt <fileName>                                    Encrypts the specified file\n"
        << "decrypt <fileName>                                    Decrypts the specified file\n"
        << "quit                                              Stops the File Terminal Program\n"
        << "---------------------------------------------------------------------------------\n"
        << std::endl;
}

//prints all the files that are stored in the "files" folder
void showFileDirectory() {
    std::vector<std::string> files;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }

    if (files.empty()) {
        std::cout << "The file directory is empty.\n" << std::endl;
    } else {
        std::cout << "------------------------------FILE DIRECTORY------------------------------" << std::endl;
        for (const auto& file : files)
            std::cout << file << std::endl;
        std::cout << "--------------------------------------------------------------------------\n" << std::endl;
    }
}

//will create a file in the "files" folder
void createFile(const std::string& fileName) {
    std::ofstream file(directory + "/" + fileName);
    if (file) {
        std::cout << "\"" << fileName << "\" created successfully.\n" << std::endl;
        file.close();
    } else {
        std::cerr << "ERROR: failed to create \"" << fileName << "\".\n" << std::endl;
    }
}

//prints the contents of the file
void readFile(const std::string& fileName) {
    std::ifstream file(directory + "/" + fileName);
    if (file) {
        std::cout << "\nExisting content of \"" << fileName << "\":" << std::endl;
        std::cout << "--------------------------------------------------------------------------" << std::endl;
        std::string line;
        while (std::getline(file, line))
            std::cout << line << std::endl;
        std::cout << "--------------------------------------------------------------------------\n" << std::endl;
        file.close();
    } else {
        std::cerr << "ERROR: failed to open file \"" << fileName << "\".\n" << std::endl;
    }
}

//shows the current content of the file and lets the user overwrite it
void writeFile(const std::string& fileName) {
    std::ifstream file(directory + "/" + fileName);
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
            if (line == "SAVE" || line == "save") {
                std::ofstream file(directory + "/" + fileName);
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
    std::ifstream file(directory + "/" + fileName);
    
    if (file) {
        file.close();
        std::cout << "Are you sure you want to delete \"" << fileName << "\"? (Y/N) ";
        std::string response;
        std::getline(std::cin, response);

        if (response == "N" || response == "n") {
            std::cout << "File \"" << fileName << "\" has NOT been deleted.\n" << std::endl;
        } else if (response == "Y" || response == "y" || response == "") {
            if (fs::remove(directory + "/" + fileName)) {
                std::cout << "File \"" << fileName << "\" has been deleted.\n" << std::endl;
            } else {
            std::cerr << "ERROR: failed to delete file: \"" << fileName << "\".\n" << std::endl;
            }
        } else {
            std::cerr << "ERROR: invalid response.\n" << std::endl;
        }

    } else {
        std::cerr << "ERROR: invalid file name.\n" << std::endl;
    }  
}

void encryptFile(const std::string& fileName) {
    std::ifstream file(directory + "/" + fileName);
    if (!file) {
        std::cerr << "ERROR: failed to open file.\n" << std::endl;
        return;
    }
    
}

int main() {
    std::string input;
    std::string splitInput[2];
    bool running = true;

    //startup procedure
    startup();
    
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
        //the loop starts by printing out the prompt that tells them what directory they're in
        std::cout << currentDirectory << "> ";

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
        } else if (splitInput[1] != "" && splitInput[0] == "encrypt") {
            encryptFile(splitInput[1]);
        } else if (splitInput[1] != "" && splitInput[0] == "decrypt") {
            
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