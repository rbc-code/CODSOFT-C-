#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    srand(time(0));
    int randomNumber = rand() % 100 + 1;
    int userGuess = 0;
    cout << "Welcome to the Number Guessing Game!\n";
    cout << "I have generated a random number between 1 and 100. Can you guess it?\n";
    while (true) {
        cout << "Enter your guess: ";
        cin >> userGuess;
        if (userGuess > randomNumber) {
            cout << "Too high! Try again.\n";
        } else if (userGuess < randomNumber) {
            cout << "Too low! Try again.\n";
        } else {
            cout << "Congratulations! You guessed the number correctly.\n";
            break;
        }
    }
    return 0;
}
