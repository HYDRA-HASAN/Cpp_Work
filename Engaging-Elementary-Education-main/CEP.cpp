#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <climits>

class InteractiveActivity {
public:
    virtual void start() = 0;
    virtual void displayInstructions() = 0;
    virtual void displayCompletionMessage() = 0;
    virtual int calculateScore() = 0;
    virtual ~InteractiveActivity() {}
};

class NumberGuessingGame : public InteractiveActivity {
public:
    void start() override {
        // Implement number guessing game logic
        std::cout << "Welcome to the Number Guessing Game!\n";
        int secretNumber = generateRandomNumber();
        int guess;
        attempts = 0;

        do {
            std::cout << "Enter your guess: ";
            std::cin >> guess;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            attempts++;

            if (guess == secretNumber) {
                std::cout << "Congratulations! You guessed the correct number in " << attempts << " attempts.\n";
            } else if (guess < secretNumber) {
                std::cout << "Too low. Try again.\n";
            } else {
                std::cout << "Too high. Try again.\n";
            }

        } while (guess != secretNumber);
    }

    void displayInstructions() override {
        std::cout << "Number Guessing Game Instructions: Try to guess the secret number.\n";
    }

    void displayCompletionMessage() override {
        std::cout << "Number Guessing Game Completed!\n";
    }

    int calculateScore() override {
        // You can implement scoring based on the number of attempts
        return 100 - attempts;
    }

private:
    int generateRandomNumber() {
        std::srand(static_cast<unsigned int>(std::time(0)));
        return std::rand() % 100 + 1;
    }

    int attempts = 0; // Track the number of attempts
};

class HighLowGame : public InteractiveActivity {
public:
    void start() override {
        // Implement high-low game logic
        std::cout << "Welcome to the High-Low Game!\n";
        int secretNumber = generateRandomNumber();
        int guess;
        attempts = 0;

        do {
            std::cout << "Enter your guess: ";
            std::cin >> guess;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            attempts++;

            if (guess == secretNumber) {
                std::cout << "Congratulations! You guessed the correct number in " << attempts << " attempts.\n";
            } else if (guess < secretNumber) {
                std::cout << "Too low. Try again.\n";
            } else {
                std::cout << "Too high. Try again.\n";
            }

        } while (guess != secretNumber);
    }

    void displayInstructions() override {
        std::cout << "High-Low Game Instructions: Try to guess the secret number within a range.\n";
    }

    void displayCompletionMessage() override {
        std::cout << "High-Low Game Completed!\n";
    }

    int calculateScore() override {
        // You can implement scoring based on the number of attempts
        return 100 - attempts;
    }

private:
    int generateRandomNumber() {
        std::srand(static_cast<unsigned int>(std::time(0)));
        return std::rand() % 100 + 1;
    }

    int attempts = 0; // Track the number of attempts
};

class GraphicGames : public InteractiveActivity {
public:
    void start() override {
        // Display options for Graphic Games
        std::cout << "Graphic Games Options:\n";
        std::cout << "1. Number Guessing Game\n";
        std::cout << "2. High-Low Game\n";

        int choice;
        std::cout << "Enter your choice (1 or 2): ";
        std::cin >> choice;

        if (choice == 1) {
            NumberGuessingGame numberGuessingGame;
            numberGuessingGame.displayInstructions();
            numberGuessingGame.start();
            numberGuessingGame.displayCompletionMessage();
            int score = numberGuessingGame.calculateScore();
            std::cout << "Your score: " << score << std::endl;
        } else if (choice == 2) {
            HighLowGame highLowGame;
            highLowGame.displayInstructions();
            highLowGame.start();
            highLowGame.displayCompletionMessage();
            int score = highLowGame.calculateScore();
            std::cout << "Your score: " << score << std::endl;
        } else {
            std::cout << "Invalid choice. Returning to main menu.\n";
        }
    }

    void displayInstructions() override {
        std::cout << "Graphic Games Instructions: Choose a graphic game to play.\n";
    }

    void displayCompletionMessage() override {
        std::cout << "Graphic Games Completed!\n";
    }

    int calculateScore() override {
        // You can implement scoring based on the selected game
        return 90;
    }
};

class Puzzle : public InteractiveActivity {
public:
    void start() override {
        // Implement puzzle logic
        std::vector<int> puzzle = {1, 2, 3, 4, 5, 6, 7, 8, 0}; // 0 represents the empty space
        shufflePuzzle(puzzle);

        while (!isPuzzleSolved(puzzle)) {
            displayPuzzle(puzzle);
            int move;
            std::cout << "Enter the number to move (1-8): ";
            std::cin >> move;
            if (isValidMove(move, puzzle)) {
                performMove(move, puzzle);
            } else {
                std::cout << "Invalid move. Try again.\n";
            }
        }

        std::cout << "Congratulations! Puzzle solved!\n";
    }

    void displayInstructions() override {
        std::cout << "Jigsaw Puzzle Instructions: Arrange the pieces to solve the puzzle.\n";
    }

    void displayCompletionMessage() override {
        std::cout << "Jigsaw Puzzle Completed!\n";
    }

    int calculateScore() override {
        return 100;
    }

private:
    void shufflePuzzle(std::vector<int>& puzzle) {
        std::random_shuffle(puzzle.begin(), puzzle.end());
    }

    void displayPuzzle(const std::vector<int>& puzzle) {
        // Display the current state of the puzzle
        std::cout << "Current Puzzle State:\n";
        for (size_t i = 0; i < puzzle.size(); ++i) {
            std::cout << puzzle[i] << " ";
            if ((i + 1) % 3 == 0) {
                std::cout << '\n';
            }
        }
    }

    bool isValidMove(int move, const std::vector<int>& puzzle) {
        // Check if the selected move is valid
        auto emptyIter = std::find(puzzle.begin(), puzzle.end(), 0);
        auto moveIter = std::find(puzzle.begin(), puzzle.end(), move);

        if (emptyIter != puzzle.end() && moveIter != puzzle.end()) {
            size_t emptyIndex = std::distance(puzzle.begin(), emptyIter);
            size_t moveIndex = std::distance(puzzle.begin(), moveIter);

            return (std::abs(int(emptyIndex / 3 - moveIndex / 3)) + std::abs(int(emptyIndex % 3 - moveIndex % 3))) == 1;
        }

        return false;
    }

    void performMove(int move, std::vector<int>& puzzle) {
        auto emptyIter = std::find(puzzle.begin(), puzzle.end(), 0);
        auto moveIter = std::find(puzzle.begin(), puzzle.end(), move);

        if (emptyIter != puzzle.end() && moveIter != puzzle.end()) {
            std::iter_swap(emptyIter, moveIter);
        }
    }

    bool isPuzzleSolved(const std::vector<int>& puzzle) {
        return std::is_sorted(puzzle.begin(), puzzle.end());
    }
};

class Mathematics : public InteractiveActivity {
public:
    void start() override {
        // Implement math exercises and quizzes
        int num1 = rand() % 10;
        int num2 = rand() % 10;

        int answer;
        std::cout << "What is " << num1 << " + " << num2 << "? ";
        std::cin >> answer;

        if (answer == num1 + num2) {
            std::cout << "Correct! Good job.\n";
        } else {
            std::cout << "Incorrect. The correct answer is " << num1 + num2 << ".\n";
        }
    }

    void displayInstructions() override {
        std::cout << "Mathematics Instructions: Solve the math exercises and quizzes.\n";
    }

    void displayCompletionMessage() override {
        std::cout << "Mathematics Completed!\n";
    }

    int calculateScore() override {
        return 90;
    }
};

class GeographyInformation : public InteractiveActivity {
public:
    void start() override {
        // Implement geography information logic
        std::cout << "Welcome to Geography Information!\n";
        std::cout << "Let's learn about countries and capitals.\n";
        std::cout << "What is the capital of France? ";
        std::string userAnswer;
        std::cin.ignore(); // Clear the newline character from the buffer
        std::getline(std::cin, userAnswer);

        std::string correctAnswer = "Paris";

        if (userAnswer == correctAnswer) {
            std::cout << "Correct! Paris is the capital of France.\n";
        } else {
            std::cout << "Incorrect. The correct answer is Paris.\n";
        }
    }

    void displayInstructions() override {
        std::cout << "Geography Information Instructions: Learn about countries, capitals, and landmarks.\n";
    }

    void displayCompletionMessage() override {
        std::cout << "Geography Information Completed!\n";
    }

    int calculateScore() override {
        return 80;
    }
};

class UserInterface {
public:
    void showMenu() {
        std::cout << "1. Puzzle\n2. Mathematics\n3. Graphic Games\n4. Geography Information\n";
    }

    int getUserChoice() {
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        return choice;
    }

    void displayErrorMessage() {
        std::cout << "Invalid choice. Please try again.\n";
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    Puzzle puzzle;
    Mathematics math;
    GraphicGames graphicGames;
    GeographyInformation geography;

    std::vector<InteractiveActivity*> activities = {&puzzle, &math, &graphicGames, &geography};

    UserInterface userInterface;

    while (true) {
        userInterface.showMenu();
        int choice = userInterface.getUserChoice();

        if (choice == 3) {
            graphicGames.displayInstructions();
            graphicGames.start();
            graphicGames.displayCompletionMessage();
            int score = graphicGames.calculateScore();
            std::cout << "Your score: " << score << std::endl;
        } else if (choice >= 1 && choice <= activities.size()) {
            activities[choice - 1]->displayInstructions();
            activities[choice - 1]->start();
            activities[choice - 1]->displayCompletionMessage();
            int score = activities[choice - 1]->calculateScore();

            std::cout << "Your score: " << score << std::endl;
        } else {
            userInterface.displayErrorMessage();
        }
    }

    return 0;
}
