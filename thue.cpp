#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <algorithm>
// store lhs and rhs of each rule
struct Rule {
    std::string lhs, rhs;
};

std::vector<Rule> rules;
std::string state;

void loadThueFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file " << filename << std::endl;
        exit(1);
    }
    std::string line;
    bool parsingRules = true;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (parsingRules) {
            if (line == "::=") {
                parsingRules = false;
                continue;
            }
            size_t pos = line.find("::=");
            if (pos != std::string::npos) {
                rules.push_back({line.substr(0, pos), line.substr(pos + 3)});
            }
        } else {
            state += line + "\n";
        }
    }
    file.close();
}

void applyRules(bool step) {
    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::vector<size_t> applicableRules;
        for (size_t i = 0; i < rules.size(); ++i) {
            if (state.find(rules[i].lhs) != std::string::npos) {
                applicableRules.push_back(i);
            }
        }

        if (applicableRules.empty()) break;

        std::uniform_int_distribution<size_t> dist(0, applicableRules.size() -1);
        size_t chosenIndex = applicableRules[dist(gen)];

        Rule& rule = rules[chosenIndex];
        
        // find all instances of lhs in the string
        std::vector<size_t> positions = {};
        for (size_t i = 0; i < state.length() - rule.lhs.length(); ++i) {
            if (state.substr(i, rule.lhs.length()) == rule.lhs) {
                positions.push_back(i);
            }
        }
        std::uniform_int_distribution<size_t> chosenInstance(0, positions.size() - 1);
        size_t pos = positions[chosenInstance(gen)];

        if (rule.rhs.empty()) {
            std::cout << rule.rhs << "\n"; // Print rather than replace
        } else if (rule.rhs[0] == '~') {
            std::cout << rule.rhs << "\n";
        } else{
            state.replace(pos, rule.lhs.length(), rule.rhs);
        }
        if (step) {
            std::cout << state << std::endl;
        }
    }
    std::cout << "Final State: " << state << "\n";
}

int main(int argc, char* argv[]) {
    bool step = false;
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1; 
    }
    if (argc == 3 && std::string(argv[2]) == "-step") {
        step = true;
    }
    loadThueFile(argv[1]);
    applyRules(step);

    return 0;
}