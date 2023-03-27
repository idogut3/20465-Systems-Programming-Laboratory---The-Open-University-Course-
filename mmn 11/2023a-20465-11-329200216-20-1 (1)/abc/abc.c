#include <stdio.h>
#include <string.h>

/***
 * Boundaries for the "abc..." letters and "ABC..." letters as presented in the ASCII table;
 */
#define ascii_table_a 97
#define ascii_table_z 122
#define ascii_table_A 65
#define ascii_table__Z 90

/***
 * Method: "shortened_word";
 * @description:
 * <p>
 * The function gets a string/word and shortens every alphabetic streak (of 3 letters or more) in the string/word;
 * <p>
 * @param str - Pointer of the string/word;
 */
void shortened_word(char *str);

/***
 * Method: "shorten_curr_streak";
 * @description:
 * <p>
 * The function gets a string/word and shortens a specific alphabetic streak in the string/word;
 * <p>
 * @param str - Pointer of the string/word;
 * @param first - The first point in which we start replacing our values until the end of the current streak (not including the last index of the streak);
 * @param last - The last place that we remove values from;
 */
void shorten_curr_streak(char str[], int first, int last);

void shorten_curr_streak(char str[], int first, int last) {
    str[first] = '-';
    str[first + 1] = str[last];
    int i;
    for (i = 2; i < strlen(str); i++) {
        if (i + last - 1 < strlen(str)) {
            str[first + i] = str[i + last - 1];
        } else {
            break;
        }
    }
    str[i + first] = '\0';
}


void shortened_word(char *str) {
    int i;

    int alphabetic_streak = 0;
    char last_char; /**The value in the previous index ~ word[i-1];*/
    int start_of_streak;

    for (i = 0; i < strlen(str); i++) { /**Looping through our word;
        The char at this index is an english alphabetic letter:*/
        if ((ascii_table_a <= str[i] && str[i] <= ascii_table_z) ||
            (ascii_table_A <= str[i] && str[i] <= ascii_table__Z)) {
            if (alphabetic_streak == 0) { /**A new streak begins;*/
                last_char = str[i];  /**Saving the last char of our streak;*/
                start_of_streak = i;  /**Setting i as the new start of streak;*/
                alphabetic_streak++; /**Updating our streak counter;*/
            } else if (alphabetic_streak > 0) {  /**There was already a streak in play;*/

                if (last_char + 1 == str[i]) {  /**The streak continues;*/
                    last_char = str[i];  /**Saving the last char of our streak;*/
                    alphabetic_streak++;  /**Updating our streak counter;*/
                } else {  /**The streak ended;*/
                    if (3 <= alphabetic_streak) {  /**We need to shorten our word because of the streak;*/
                        shorten_curr_streak(str, start_of_streak + 1, i - 1);  /**We shorten the streak;*/
                    }
                    alphabetic_streak = 1;  /**Reinitializing the alphabetic streak for further use;*/
                    start_of_streak = i;
                    last_char = str[i];
                }
            }
        }
            /**The char at this index is not an english alphabetic:*/
        else {  /**The streak ended / was no streak at all;*/
            if (3 <= alphabetic_streak) {  /**We need to shorten our word because of the streak;*/
                shorten_curr_streak(str, start_of_streak + 1, i - 1);/**We shorten the streak;*/
            }
            alphabetic_streak = 0;
        }
    }
    if (3 <= alphabetic_streak) {
        shorten_curr_streak(str, start_of_streak + 1, i - 1);
    }
    alphabetic_streak = 0;
}

int main() {
    printf("\nPlease enter a word/string you want to shorten: :) \n");
    char str[80];
    scanf("%s", str);
    printf("The word/string you entered --> \t%s", str);
    shortened_word(&str);
    printf("\nThe shortened string/word -- > \t%s\n", str);
    return 0;
}
