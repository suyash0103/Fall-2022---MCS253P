#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

unordered_set<char> validCharacters;

void fillSet() {
    validCharacters.insert('-');
    validCharacters.insert('.');
    validCharacters.insert('\n');

    for (int i = 0; i <= 9; i++) {
        validCharacters.insert(i + '0');
    }
}

bool doesFileExist(string fileName, ifstream& file) {
    file.open(fileName);

    if (!file) {
        return false;
    }

    return true;
}

string getFileContents(ifstream& file) {
    string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    cout << fileContents << endl;
    return fileContents;
}

void isValidCharacter(char c) {
    if (validCharacters.find(c) == validCharacters.end()) {
        cout << "Invalid Character found:" << c << endl;
        exit(1);
    }
}

bool isNegativeValid(int numberOfDash, int numberOfDigits) {
    if (numberOfDash == 0 && numberOfDigits == 0) {
        return true;
    }

    return false;
}

bool isDecimalValid(int numberOfDots, int numberOfDigits) {
    if (numberOfDots == 0 && numberOfDigits > 0) {
        return true;
    }

    return false;
}

void resetVariables(int& numberOfDots, int& numberOfDash, int& numberOfDigits,
    int& isNegative, int& numberOfDigitsAfterDot, float& numberFormed) {
    numberOfDots = 0;
    numberOfDash = 0;
    numberOfDigits = 0;
    isNegative = 0;
    numberOfDigitsAfterDot = 0;
    numberFormed = 0;
}

bool isEmptyLine(int numberOfDigits) {
    if (numberOfDigits == 0) {
        cout << "Invalid Input" << endl;
        exit(1);
    }
}

void digitsPresentAfterDot(int numberOfDots, int numberOfDigitsAfterDot) {
    if (numberOfDots == 1 && numberOfDigitsAfterDot == 0) {
        cout << "Invalid Input" << endl;
        exit(1);
    }
}

void updateNumberIfDecimal(float& numberFormed, int numberOfDots, int numberOfDigitsAfterDot) {
    if (numberOfDots == 1) {
        numberFormed = numberFormed / pow(10, numberOfDigitsAfterDot);
    }
}

void updateNumberIfNegative(int isNegative, float& numberFormed) {
    if (isNegative) {
        numberFormed = numberFormed * (-1);
    }
}

void updateTotalSumAndNumbers(float& totalSum, int& totalNumbers, float numberFormed) {
    totalSum += numberFormed;
    totalNumbers++;
}

void isFileEmpty(string fileContents) {
    if (fileContents.length() == 0) {
        cout << "Empty File" << endl;
        exit(1);
    }
}

void addNewLineIfReqd(string& fileContents) {
    if (fileContents[fileContents.length() - 1] != '\n') {
        fileContents.push_back('\n');
    }
}

void handleNewLine(int& numberOfDots, int& numberOfDigits, int& numberOfDash, 
        int& numberOfDigitsAfterDot, int& isNegative, int& totalNumbers,
        float& totalSum, float& numberFormed) {
    isEmptyLine(numberOfDigits);

    digitsPresentAfterDot(numberOfDots, numberOfDigitsAfterDot);

    updateNumberIfDecimal(numberFormed, numberOfDots, numberOfDigitsAfterDot);
    
    updateNumberIfNegative(isNegative, numberFormed);
    
    updateTotalSumAndNumbers(totalSum, totalNumbers, numberFormed);
    
    resetVariables(numberOfDots, numberOfDash, numberOfDigits,
        isNegative, numberOfDigitsAfterDot, numberFormed);
}

void handleDash(int& numberOfDash, int& numberOfDigits, int& isNegative) {
    if (!isNegativeValid(numberOfDash, numberOfDigits)) {
        cout << "Invalid Input" << endl;
        exit(1);
    }

    numberOfDash = 1;
    isNegative = 1;
}

void handleDecimal(int& numberOfDots, int& numberOfDigits) {
    if (!isDecimalValid(numberOfDots, numberOfDigits)) {
        cout << "Invalid Input" << endl;
        exit(1);
    }

    numberOfDots = 1;
}

void updateNumber(char c, int numberOfDots, int& numberOfDigits, int& numberOfDigitsAfterDot, float& numberFormed) {
    int digit = c - '0';
    numberOfDigits++;
    if (numberOfDots == 1) {
        numberOfDigitsAfterDot++;
    }

    numberFormed = numberFormed * 10 + digit;
}

float findAverage(string fileContents) {
    isFileEmpty(fileContents);
    addNewLineIfReqd(fileContents);

    int numberOfDots, numberOfDash, numberOfDigits, 
            isNegative, numberOfDigitsAfterDot, totalNumbers = 0;
    
    float numberFormed = 0, totalSum = 0;

    resetVariables(numberOfDots, numberOfDash, numberOfDigits,
            isNegative, numberOfDigitsAfterDot, numberFormed);

    for (auto c: fileContents) {
        isValidCharacter(c);
        switch(c) {
            case '\n':
                handleNewLine(numberOfDots, numberOfDigits, numberOfDash,
                    numberOfDigitsAfterDot, isNegative, totalNumbers, totalSum,
                    numberFormed);
                break;

            case '-':
                handleDash(numberOfDash, numberOfDigits, isNegative);
                break;

            case '.':
                handleDecimal(numberOfDots, numberOfDigits);
                break;
            
            default:
                updateNumber(c, numberOfDots, numberOfDigits, 
                    numberOfDigitsAfterDot, numberFormed);
                break;
        }
    }
    return (float)(totalSum / totalNumbers);
}

int main() {
    ifstream file;
    string fileName = "numbers.txt";

    if (!doesFileExist(fileName, file)) {
        cout << "File does not exist" << endl;
        return 0;
    }

    fillSet();

    float average = findAverage(getFileContents(file));
    cout << "Average:" << average << endl;
}