#include <cmath>
#include <iostream>

double leibnizPiStraight(int order);
double leibnizPiSeparated(int order);

int main() {
    int order;
    std::cout << "Enter the desired order of the series: ";
    std::cin >> order;
    while (order <= 0) {
        std::cout << "The order must be a positive integer: ";
        std::cin >> order;
    }
    double piStraight = leibnizPiStraight(order);
    double piSeparated = leibnizPiSeparated(order);
    double piStraightError = std::abs(M_PI - piStraight);
    double piSeparatedError = std::abs(M_PI - piSeparated);

    std::cout << "Leibniz Pi by straight sum: " << piStraight << " with error " << piStraightError << std::endl;
    std::cout << "Leibniz Pi by separated sum: " << piSeparated << " with error " << piSeparatedError << std::endl;
    return 0;
}

double leibnizPiStraight(int order) {
    double value = 0;
    for (int k = 0; k < order; ++k) {
        value += (k % 2 == 0 ? 1.0 : -1.0) / (2 * k + 1);
    }
    return 4 * value;
}

double leibnizPiSeparated(int order) {
    double oddSeries = 0;
    double evenSeries = 0;
    for (int k = 0; k < order; ++k) {
        if (k % 2 == 0) {
            evenSeries += 1.0 / (2 * k + 1);
        } else {
            oddSeries -= 1.0 / (2 * k + 1);
        }
    }
    return 4 * (evenSeries + oddSeries);
}
