#include <string>
#include <algorithm>

extern "C" {

void sort_and_replace(std::string& input) {
    std::sort(input.begin(), input.end(), std::greater<char>());

    for (size_t i = 0; i < input.size(); ) {
        if (isdigit(input[i]) && (input[i] - '0') % 2 == 0) {
            input.replace(i, 1, "КВ");
            i += 2;
        } else {
            ++i;
        }
    }
}


int sum_numeric(const std::string& input) {
    int sum = 0;
    for (char c : input) {
        if (isdigit(c)) {
            sum += c - '0';
        }
    }
    return sum;
}

bool analyze_length(const std::string& input) {
    return (input.size() > 2) && (input.size() % 32 == 0);
}

}