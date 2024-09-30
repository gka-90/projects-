#include <iostream>
#include <climits>
#include <string>

using namespace std;

const int ROWS = 9;
const int COLS = 5;

const string HIRAGANA[ROWS][COLS] =
                        {{ "a",   "i",   "u",  "e",  "o"},
                         {"ka",  "ki",  "ku", "ke", "ko"},
                         {"sa", "shi",  "su", "se", "so"},
                         {"ta", "chi", "tsu", "te", "to"},
                         {"na",  "ni",  "nu", "ne", "no"},
                         {"ha",  "hi",  "hu", "he", "ho"},
                         {"ma",  "mi",  "mu", "me", "mo"},
                         {"ra",  "ri",  "ru", "re", "ro"},
                         {"ya",  "wa",  "yu",  "n", "yo"}
                        };

const int A = 125;
const int C = 11;
const int MOD = 1024;

const int SYL_IN_WORD_MAX = 5;
const int NUM_LINES_MAX = 15;
const int NUM_SYLS_MAX = 40;

/**
 * @brief A pseudo-random number generator
 * Note: seed is an *optional parameter*. If an argument is passed to this
 * function, the state will be reset to this seed. Otherwise, if you call the
 * function with no arguments, seed will be set to the default of INT_MIN.
 * When this happens, the state will be updated to the next pseudo-random
 * number. Either way, the state is returned.
 *
 * @param seed (optional) - When passed, resets the seed
 * @return int - The pseudo-random integer.
 */
int rand_int(int seed = INT_MIN) {
    static int state = 0;

    if (seed != INT_MIN) {
        // If a seed is passed, then set/reset the state
        state = seed;
    }
    else {
        // Otherwise, update the state to the next pseudo-random number
        state = (A * state + C) % MOD;
    }

    return state;
}

/* ------- Do not change anything in the section above ------- */

void generate_poem(int seed, int lines, int syllables[], bool capitalize, bool vertical) {
        string poem[15];
        for (int i = 0; i < lines; i++) {
            int remaining_syllables = syllables[i];
            string line = "";

            while (remaining_syllables > 0) {
                int syllables_in_word = rand_int() % 5 + 1;
                if (syllables_in_word > remaining_syllables) {
                    syllables_in_word = remaining_syllables;
                }
                remaining_syllables -= syllables_in_word;

                string word = "";
                for (int j = 0; j < syllables_in_word; j++) {
                    int row = rand_int() % 9;
                    int col = rand_int() % 5;
                    word += HIRAGANA[row][col];
                }
                line += word + " ";
            }

            if (capitalize) {
                line[0] = toupper(line[0]);
            }

            poem[i] = line;
        }


        if (vertical) {

            int max_length = 0;
            for (int i = 0; i < lines; i++) {
                if (poem[i].length() > max_length) {
                    max_length = poem[i].length();
                }
            }

            for (int col = 0; col < max_length; col++) {
                bool printed =false;
                for (int row = lines - 1; row >= 0; row--) {
                    if (col < poem[row].length()) {
                        cout << poem[row][col];
                        printed =true;
                    } else {
                        cout << " ";
                    }
                }
                if (printed){
                cout << endl;
            }
        }
        } else {

            for (int i = 0; i < lines; i++) {
                cout << poem[i].substr(0, poem[i].length() - 1) << endl;
            }
        }
}

// Controls operation of program
int main() {
    int seed;
    int lines;
    int syllables[15];
    int capitalize_setting, vertical_setting;

    cin >> seed;
    cin >> lines;
    for (int i = 0; i < lines; i++) {
        cin >> syllables[i];
    }
    cin >> capitalize_setting >> vertical_setting;

    rand_int(seed);
    generate_poem(seed, lines, syllables, capitalize_setting == 1, vertical_setting == 1);

    return 0;
}