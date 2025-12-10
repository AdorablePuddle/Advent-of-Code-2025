#include <chrono>
#include <iomanip>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int solution(int target_config, vector<int> button_config, vector<int> joltage_requirements) {
    /*
        target_config = binary representation of the target_state.
        button_config = what each buttons do.

        (1, 2, 3) == 0b111
        To use a button, xor it with the current config.

        For now joltage requirement is not necessary.

        Part 1 Solution: Brute Force
    */
    
    int solution = 1e9 + 7;
    for (int i = 0; i < (1 << (int)button_config.size()); i++) {
        int button_sequence = 0;
        int button_pressed = __builtin_popcount(i);
        for (int j = 0; j < button_config.size(); j++) {
            if (i & (1 << j)) {
                button_sequence ^= button_config[j];
            }
        }
        if (button_sequence == target_config) {
            solution = min(solution, button_pressed);
        }
    }
    return solution;
}

vector<string> splitter(string input) {
    stringstream stream;
    stream << input;
    vector<string> output;
    string tmp;
    while (stream >> tmp) {
        output.push_back(tmp);
    }
    return output;
}

void test_formatter(vector<string> input, int &target_config, vector<int> &button_config, vector<int> &joltage_requirements) {
    int size = (int)input.size();

    // target_config
    target_config = 0;
    for (int i = (int)input[0].size() - 2; i > 0; i--) {
        target_config <<= 1;
        switch (input[0][i]) {
            case '.':
            break;
            case '#':
                target_config |= 1;
            break;
        }
    }

    // joltage_requirements
    joltage_requirements.clear();
    string current_value = "";
    for (int i = 1; i < (int)input[size - 1].length(); i++) {
        if (input[size - 1][i] == ',' || input[size - 1][i] == '}') {
            joltage_requirements.push_back(stoi(current_value));
            current_value = "";
        } else {
            current_value = current_value + input[size - 1][i];
        }
    }

    // button_config
    button_config.clear();
    for (int config = 1; config < size - 1; config++) {
        string current_config = input[config];
        current_value = "";
        int button = 0;
        for (int i = 1; i < (int)current_config.length(); i++) {
            if (current_config[i] == ',' || current_config[i] == ')') {
                int position = 1 << stoi(current_value);
                button |= position;
                current_value = "";
            } else {
                current_value = current_value + current_config[i];
            }
        }
        button_config.push_back(button);
    }
}

int main(){
    auto start = chrono::high_resolution_clock::now();
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // Solution Here:

    vector<string> current_test_case;
    string test_case;
    int final_solution = 0;
    while (getline(cin, test_case)) {
        current_test_case = splitter(test_case);
        int target_config = 0;
        vector<int> button_config, joltage_requirements;
        test_formatter(current_test_case, target_config, button_config, joltage_requirements);
        int current_solution = solution(target_config, button_config, joltage_requirements);
        // cout << current_solution << "\n";
        final_solution += current_solution;
    }
    cout << "Final solution: " << final_solution << "\n";
    // End of solution.
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cerr << "Solution time: " << fixed << setprecision(3) << (float)duration.count() / 1000 << "s\n";
}