#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <locale>
#include <sstream>

using namespace std;

// Function to populate a set from a file
void populateSetFromFile(const string& filename, unordered_set<string>& wordSet) {
    ifstream file(filename);
    if (file.is_open()) {
        string word;
        while (getline(file, word)) {
            // Convert word to lowercase for consistency
            transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
                return tolower(c);
            });
            wordSet.insert(word);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Function to perform sentiment analysis based on sets of words from files
string predictSentiment(string text) {
    // Convert input text to lowercase for case-insensitive matching
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return tolower(c);
    });

    unordered_set<string> positiveWords;
    unordered_set<string> negativeWords;
    unordered_set<string> neutralWords;
    unordered_set<string> negationWords;

    // Populate sets from respective files
    populateSetFromFile("positive_words.txt", positiveWords);
    populateSetFromFile("negative_words.txt", negativeWords);
    populateSetFromFile("neutralwords.txt", neutralWords);
    populateSetFromFile("negation_words.txt", negationWords);

    // Count occurrences of positive, negative, and neutral words in the input text
    size_t numPositive = 0, numNegative = 0, numNeutral = 0, numNegation=0;
    string word;
    istringstream iss(text);
    while (iss >> word) {
        if (positiveWords.find(word) != positiveWords.end()) {
            numPositive++;
        } else if (negativeWords.find(word) != negativeWords.end()) {
            numNegative++;
        } else if (neutralWords.find(word) != neutralWords.end()) {
            numNeutral++;
        }
        else if (negationWords.find(word) != negationWords.end()) {
            numNegation++;

        }
    }

    // Determine sentiment based on word occurrences
    if (numPositive > numNegative && numPositive > numNeutral) {
        return "Positive";
    } else if (numNegative > numNeutral) {
        return "Negative";
    } else if (numNegation > numPositive && numNegative > numNeutral) {
        return "Negative";
    } else {
        return "Neutral";
    }
}

int main() {
    string userInput;

    cout << "Enter your text: ";
    getline(cin, userInput);

    // Perform sentiment analysis and display the predicted sentiment
    string predictedSentiment = predictSentiment(userInput);
    cout << "Predicted sentiment: " << predictedSentiment << endl;

    return 0;
}