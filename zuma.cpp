#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to handle eliminations after each insertion
string eliminateBeads(string sequence) {
    bool changed;
    do {
        changed = false;
        int n = sequence.size();
        for (int i = 0; i < n - 2; ++i) {
            if (sequence[i] == sequence[i+1] && sequence[i] == sequence[i+2]) {
                // Find a group of 3 or more consecutive same beads
                int j = i;
                while (j < n && sequence[j] == sequence[i]) {
                    ++j;
                }
                sequence = sequence.substr(0, i) + sequence.substr(j); // Remove the group
                changed = true;
                break;
            }
        }
    } while (changed);

    return sequence;
}

int main() {
    string sequence;
    cin >> sequence; // Initial bead sequence
    int n;
    cin >> n; // Number of insertions

    // Process each insertion
    for (int i = 0; i < n; ++i) {
        int k;
        char bead;
        cin >> k >> bead; // Read insertion position and color

        // Insert bead at the given position
        sequence.insert(k, 1, bead);

        // After insertion, eliminate beads if possible
        sequence = eliminateBeads(sequence);

        // Output the sequence after the elimination process
        if (sequence.empty()) {
            cout << "-" << endl;
        } else {
            cout << sequence << endl;
        }
    }

    return 0;
}
