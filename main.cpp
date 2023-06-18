#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <random>

#include "hiragana_ascii.h"

std::unordered_map<std::string, std::string> readCSV(const std::string& filename){
    std::ifstream file("alphabets/hiragana.csv");

    if (file.fail()) {
        std::cout << "File open failed.\n";
        return std::unordered_map<std::string, std::string>();
    }

    std::string line;
    std::unordered_map<std::string, std::string> dictionary;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string CHAR, NAME;

        while (std::getline(ss, CHAR, ',') && std::getline(ss, NAME, ',')) {
            dictionary[NAME] = CHAR;
        }
    }

    file.close();

    return dictionary;
}

std::pair<std::string, std::string> getRandomElement(const std::unordered_map<std::string, std::string>& dictionary) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, dictionary.size() - 1);

    int randomIndex = distr(gen);

    auto iter = dictionary.begin();
    std::advance(iter, randomIndex);

    return *iter;
}

int main(){

    std::cout << "こんにちわ!" << std::endl;

    std::string input;

    std::unordered_map<std::string, std::string> hiragana_dict = readCSV("alphabets/hiragana.csv");
    // std::unordered_map<std::string, std::string>::const_iterator character = hiragana_dict.find (input_letter);

    while (true) {

        auto random_element = getRandomElement(hiragana_dict);
        std::cout << random_element.second << std::endl;
        std::cout << ascii_images[random_element.first] << std::endl;
        
        std::getline(std::cin, input);

        if (input == "done") {
            break;
        }

        if (input == random_element.first) {
            std::cout << "Well done!" << std::endl;
        } else {
            std::cout << "Wrong answer. It should've been " << random_element.first << "." << std::endl; 
        }
        
    }

    return 0;

}