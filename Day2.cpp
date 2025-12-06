#ifndef DAY2_CPP
#define DAY2_CPP

#include "Day2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

auto trim = [](std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
};

void Day2::run() {
	cout << "Day 2: Hello, World!" << endl;

    std::fstream file("daytwo.txt");
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    int idsFound = 0;
    long long sumOfIds = 0;

	std::string line;
    if (!std::getline(file, line)) {
        cout << "input.txt is empty." << endl;
        return;
    }
    if (!line.empty()) {
        std::vector<std::string> ranges;
		std::stringstream ss(line);
		std::string range;
        while (std::getline(ss, range, ',')) {
            ranges.push_back(range);
        }

        for (const auto& r : ranges) {
            std::string token = r;
			trim(token);
            size_t dashPos = token.find('-');
            if (dashPos != std::string::npos) {
                long long start = std::stoll(token.substr(0, dashPos));
                long long end = std::stoll(token.substr(dashPos + 1));
                
                for (long long i = start; i <= end; ++i) {
					std::string numberStr = std::to_string(i);
					trim(numberStr);
                    int n = static_cast<int>(numberStr.size());
                    for (int j = 1; j <= n / 2; ++j) {
                        bool isMatch = true;
                        std::string substr = numberStr.substr(0, j);
                        for (int k = j; k < n; k += j) {
                            if (numberStr.substr(k, j) != substr) {
                                isMatch = false;
                            }
                        }
                        if (isMatch) {
                            idsFound++;
                            cout << "Found ID: " << i << endl;
                            sumOfIds += i;
                            break;
                        }
                    }
				}
            } else {
                cout << "Invalid range format: " << token << endl;
			}
        }
    } else {
        cout << "input.txt is empty." << endl;
        return;
	}

    file.close();
	cout << "IDs found: " << idsFound << endl;
	cout << "Sum of IDs: " << sumOfIds << endl;
}

#endif // !DAY2_CPP
