#include <iostream>
#include <string>
#include <ctime>
#ifdef _WIN32
    #include <windows.h>
    void sleep(unsigned milliseconds) {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>
    void sleep(double milliseconds) {
        sleep(milliseconds / 1000.0);
    }
#endif

enum class Difficulty {
    EASY,
    MEDIUM,
    HARD,
    INVALID,
};
enum class KeepPlaying {
    CONTINUE,
    STOP,
};

Difficulty eval_level(std::string);
KeepPlaying eval_choice(std::string);
int limit(Difficulty);
int wait_time(Difficulty);
void print_current(int, std::string[], int);
void generate_next(int, std::string[], std::string[], int);
bool check_correctness(int, bool&, std::string[], std::string[]);

int main() {
    std::cout << "Pick a difficulty mode: (easy, medium, hard)\n";
    std::string difficulty;
    std::cin >> difficulty;

    while (eval_level(difficulty) == Difficulty::INVALID) {
        std::cout << "Invalid input. Try again\n";
        std::cin >> difficulty;

    }

    const int num_of_states = limit(eval_level(difficulty));
    const int sleep_time = wait_time(eval_level(difficulty));

    std::string states[] = {"up", "down", "left", "right", "dog", "cat", "banana", "apple"};

    std::cout << "\nStarting " << difficulty << " mode. You will have " << num_of_states << " states (";
    for (int i = 0; i < num_of_states; ++i) {
        std::cout << states[i] << ", ";
    }
    std::cout << ") \nand a period of " << (double) sleep_time / 1000 <<  " sec to look at the answers.\n\n";

    srand(time(0));
    sleep(5000);

    const int maxPlays = 30;
    bool rightAnswers = true;
    
    std::string holder[maxPlays];
    std::string player_choices[maxPlays];

    int score = 0;
    int turns = 2;

    for (int i = 0; i < turns; ++i) {
            
        int randomIndex = rand() % num_of_states; // returns a value between 0 and 3 (for 'easy' mode)
        holder[i] = states[randomIndex];
    }

    while (rightAnswers) {

        print_current(turns, holder, sleep_time);

        generate_next(num_of_states, states, holder, turns);

        sleep(sleep_time);

        for (int j = 0; j < 30; j++) {
            std::cout << std::endl;
        }

        ++turns;

        std::cout << "Now it's your turn!\n\n";

        for (int k = 0; k < turns; ++k) {
            std::string answer;
            std::cin >> answer;
            player_choices[k] = answer;
        }

        //rightAnswers = check_correctness(turns, holder, player_choices);
        check_correctness(turns, rightAnswers, holder, player_choices);

        if (!rightAnswers) {
            std::cout << "Sorry, you lost! Your final score is " << score << ".\n";
            break;
        }
        else {
            ++score;
            std::cout << "Well done! Your score is " << score << ". Do you want to keep playing? (yes/no)\n";
        }
        std::string player_wish;
        std::cin >> player_wish;

        if (eval_choice(player_wish) == KeepPlaying::CONTINUE) {
            continue;
        }
        else {
            break;
        }

    }
    std::cout << "See you soon!\n";

}
KeepPlaying eval_choice(std::string answer) {
    if (answer == "yes") {
        return KeepPlaying::CONTINUE;
    }
    else {
        return KeepPlaying::STOP;
    }
}
Difficulty eval_level(std::string level) {
    if (level == "easy") {
        return Difficulty::EASY;
    }
    else if (level == "medium") {
        return Difficulty::MEDIUM;
    }
    else if (level == "hard") {
        return Difficulty::HARD;
    }
    else {
        return Difficulty::INVALID;
    }
}
int limit (Difficulty level) {
    int max_possibilities;
    if (level == Difficulty::EASY) {
        max_possibilities = 4;
        return max_possibilities;
    }
    else if (level == Difficulty::MEDIUM) {
        max_possibilities = 6;
        return max_possibilities;
    }
    else if (level == Difficulty::HARD) {
        max_possibilities =  8;
        return max_possibilities;
    }
    else {
        std::cout << "Invalid argument.\n";
        return 0;
    }
}
int wait_time (Difficulty level) {
    int sleep_time;
    if (level == Difficulty::EASY) {
        sleep_time = 1000;
        return sleep_time;
    }
    else if (level == Difficulty::MEDIUM) {
        sleep_time = 500;
        return sleep_time;
    }
    else if (level == Difficulty::HARD) {
        sleep_time = 250;
        return sleep_time;
    }
    else {
        std::cout << "Invalid arg\n";
        return 0;
    }
}
void print_current(int count, std::string list[], int sleep_time) {

    for (int i = 0; i < count; ++i) {
        std::cout << "Simon says " << list[i] << std::endl;
        Sleep(sleep_time);

        for (int j = 0; j < 30; j++) {
            std::cout << std::endl;
        }
    }
}
void generate_next(int num_of_states, std::string states[], std::string holder[], int index) {

    int random_index = rand() % num_of_states;
    holder[index] = states[random_index];
    std::cout << "Simon says " << holder[index] << std::endl;
}
bool check_correctness(int count, bool &right_answers, std::string cpu[], std::string player[]) {
    
    for (int i = 0; i < count && right_answers; ++i) {
        if (cpu[i] != player[i]) {
            right_answers = false;
        }
    }
    return right_answers;
}