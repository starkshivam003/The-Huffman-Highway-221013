#include <iostream>

int main() {
    const int numScores = 10;
    int examScores[numScores];

    std::cout << "Enter 10 exam scores:" << std::endl;
    for (int i = 0; i < numScores; ++i) {
        std::cout << "Score " << (i + 1) << ": ";
        std::cin >> examScores[i];
    }

    int sum = 0;
    for (int i = 0; i < numScores; ++i) {
        sum += examScores[i];
    }
    double average = static_cast<double>(sum) / numScores;

    int highest = examScores[0];
    int lowest = examScores[0];
    for (int i = 1; i < numScores; ++i) {
        if (examScores[i] > highest) {
            highest = examScores[i];
        }
        if (examScores[i] < lowest) {
            lowest = examScores[i];
        }
    }

    int aboveAverageCount = 0;
    int belowAverageCount = 0;
    for (int i = 0; i < numScores; ++i) {
        if (examScores[i] > average) {
            ++aboveAverageCount;
        } else if (examScores[i] < average) {
            ++belowAverageCount;
        }
    }

    std::cout << "Average exam score: " << average << std::endl;
    std::cout << "Highest exam score: " << highest << std::endl;
    std::cout << "Lowest exam score: " << lowest << std::endl;
    std::cout << "Number of exam scores above the average: " << aboveAverageCount << std::endl;
    std::cout << "Number of exam scores below the average: " << belowAverageCount << std::endl;

    return 0;
}
