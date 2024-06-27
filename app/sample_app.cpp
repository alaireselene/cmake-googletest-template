#include "sample_library.hpp"
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define MAX_LENGTH 1000

// Print the menu
void printMenu() {
  std::cout << "1. Input from keyboard" << std::endl;
  std::cout << "2. Input from file" << std::endl;
  std::cout << "3. Chaotic mode: Randomly generate 50 testcase to file"
            << std::endl;
  std::cout << "4. Exit" << std::endl;
}

// Input validation: Check if the input is valid or not. If not, throw exception
void inputValidate(const BigInt &a, const BigInt &b) {
  int aLen = a.length();
  int bLen = b.length();
  try {
    if (aLen > MAX_LENGTH || bLen > MAX_LENGTH) {
      std::cout << "WARNING: The length of a or b exceeds the maximum limit of "
                << MAX_LENGTH
                << " digits, which may cause the program to run slowly. Please "
                   "proceed with caution."
                << std::endl;
    }
  } catch (std::exception &e) {
    throw e;
  }
}

// Take input from keyboard
void inputFromKeyboard(BigInt &a, BigInt &b) {
  try {
    std::cout << "Enter two integers a and b (each with at most " << MAX_LENGTH
              << " digits): ";
    std::cin >> a >> b;
    inputValidate(a, b);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return;
  }
}

// Take input from file.
void inputFromFile(BigInt &a, BigInt &b, std::string fileName = "test.inp") {
  std::ifstream inputFile(fileName);
  if (!inputFile.is_open()) {
    throw std::invalid_argument(
        "Input file is not exist or not found. Please "
        "put input file in same directory of exec file and try again.");
  }
  try {
    inputFile >> a >> b;
    inputFile.close();
    inputValidate(a, b);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return;
  }
}

// Do arithmetic operations, write output to console (if available) and file. If
// division by 0 then write "NULL" to file and show error message in console (if
// available).
void calcAndExport(const BigInt &a, const BigInt &b,
                   std::string fileName = "test.out",
                   bool printConsole = true) {
  std::ofstream outputFile(fileName);
  BigInt sum(a + b);
  BigInt diff(a - b);
  BigInt prod(a * b);
  if (printConsole) {
    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a - b = " << diff << std::endl;
    std::cout << "a * b = " << prod << std::endl;
  }
  outputFile << sum << std::endl;
  outputFile << diff << std::endl;
  outputFile << prod << std::endl;
  try {
    BigInt idiv(a / b);
    BigInt mod(a % b);
    if (printConsole) {
      std::cout << "a / b = " << idiv << std::endl;
      std::cout << "a % b = " << mod << std::endl;
    }
    outputFile << a / b << std::endl;
    outputFile << a % b << std::endl;
  } catch (std::logic_error &e) {
    if (printConsole) {
      std::cout << "a / b = " << e.what() << std::endl;
      std::cout << "a % b = " << e.what() << std::endl;
    }
    outputFile << "NULL" << std::endl;
    outputFile << "NULL" << std::endl;
  }
  outputFile.close();
  if (printConsole) {
    std::cout << "Output has been written!" << std::endl;
  }
}

// Chaotic mode: Randomly generate input and output to seperated folders. For
// testcase generation only. It will generate 50 testcases, each with two random
// integers a and b, then write the input to test.inp and the output to
// test.out.
void chaoticMode() {
  std::filesystem::create_directories("testcases");
  for (int i = 0; i < 50; ++i) {
    std::cout << "Generating test case #" << i + 1 << "..." << std::endl;
    int raa = rand() % 1001;
    int rab = rand() % 1001;
    // Special case: a = 1000, b = 500 for extreme division test.
    if (i == 49) {
      raa = 1000;
      rab = 500;
    }
    BigInt ra(randomize(raa));
    BigInt rb(randomize(rab));
    std::stringstream ss;
    ss << "testcase_" << i + 1;
    std::string path = "testcases/" + ss.str();
    std::filesystem::create_directories(path);
    std::ofstream inputFile(path + "/test.inp");
    inputFile << ra << " " << rb;
    inputFile.close();
    calcAndExport(ra, rb, path + "/test.out", false);
  }
  std::cout << "All files generated" << std::endl;
  return;
}
// Main function
int main() {
  BigInt a, b, sum, diff, prod, idiv, mod;
  std::string choice = "";
  do {
    printMenu();
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice == "1") {
      try {
        inputFromKeyboard(a, b);
        calcAndExport(a, b);
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        break;
      }
      break;
    } else if (choice == "2") {
      try {
        inputFromFile(a, b);
        calcAndExport(a, b);
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        break;
      }
      break;
    } else if (choice == "3") {
      chaoticMode();
      break;
    } else if (choice == "4") {
      std::cout << "Goodbye!" << std::endl;
      break;
    } else {
      std::cout << "Invalid choice. Please re-run the program and choose 1-4."
                << std::endl;
    }
  } while (choice != "3");
  return 0;
}