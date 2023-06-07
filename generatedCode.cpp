#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void createFile(const std::string& filePath) {
    std::ofstream file(filePath);
    if (file) {
        std::cout << "File created successfully: " << filePath << std::endl;
        file.close();
    } else {
        std::cerr << "Failed to create file: " << filePath << std::endl;
    }
}

void readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
}

void writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (file) {
        file << content;
        std::cout << "Content written to file: " << filePath << std::endl;
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
}

void modifyFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file) {
        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();

        std::cout << "Existing content of the file:\n" << content << std::endl;
        std::cout << "Enter the modified content (type 'SAVE' to save and exit):" << std::endl;

        content.clear();
        while (std::getline(std::cin, line)) {
            if (line == "SAVE") {
                writeFile(filePath, content);
                break;
            }
            content += line + "\n";
        }
    } else {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
}

void deleteFile(const std::string& filePath) {
    if (fs::remove(filePath)) {
        std::cout << "File deleted successfully: " << filePath << std::endl;
    } else {
        std::cerr << "Failed to delete file: " << filePath << std::endl;
    }
}

int main() {
    std::string filePath, content;
    int choice;

    do {
        std::cout << "File Terminal Program" << std::endl;
        std::cout << "1. Create a file" << std::endl;
        std::cout << "2. Read a file" << std::endl;
        std::cout << "3. Write to a file" << std::endl;
        std::cout << "4. Modify a file" << std::endl;
        std::cout << "5. Delete a file" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the file path: ";
                std::cin >> filePath;
                createFile(filePath);
                break;
            case 2:
                std::cout << "Enter the file path: ";
                std::cin >> filePath;
                readFile(filePath);
                break;
            case 3:
                std::cout << "Enter the file path: ";
                std::cin >> filePath;
                std::cout << "Enter the content: ";
                std::cin.ignore();
                std::getline(std::cin, content);
                writeFile(filePath, content);
                break;
            case 4:
                std::cout << "Enter the file path: ";
                std::cin >> filePath;
                modifyFile(filePath);
                break;
            case 5:
                std::cout << "Enter the file path: ";
                std::cin >> filePath;
                deleteFile(filePath);
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
