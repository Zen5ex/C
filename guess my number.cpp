#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Ensure correct casting for time()
    int secretNumber = rand() % 100 + 1; // Random number between 1 and 100
    int tries = 0;
    int guess = 0;

    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "I have selected a number between 1 and 100." << endl;

    // Loop until the user correctly guesses the secret number
    do {
        cout << "Enter your guess: ";
        cin >> guess; // Get the player's guess
        ++tries; // Increment the number of tries

        if (guess > secretNumber) {
            cout << "Too high! Try again." << endl;
        } else if (guess < secretNumber) {
            cout << "Too low! Try again." << endl;
        } else {
            cout << "Congratulations! You've guessed the number " << secretNumber << " in " << tries << " tries!" << endl;
        }
    } while (guess != secretNumber); // Loop continues until the guess is correct

    return 0;
}
