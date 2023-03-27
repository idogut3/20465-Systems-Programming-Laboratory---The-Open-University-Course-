#include <stdio.h>


/***
 * @function: my_bcmp
 * @param b1 A pointer to the first index in the string the user inserted;
 * @param b2 A pointer to the second index in the string the user inserted;
 * @param len The length of the number of bytes the user asked to compare;
 * @returns 0 if both the memory pointers contain the same bytes in the given length of comparison , else returns 1;
 */

int my_bcmp(const void *b1, const void *b2, int len);

int main() {
    char str[512]; /**The maximum string length that can be given to us is 512;*/
    int i1; /**The first index the user wants to start comparing from*/
    int i2; /**The second index the user wants to start comparing from*/
    int len; /**The comparison length */
    const void *first; /***Declaring the first pointer we compare the other pointer to*/
    const void *second; /***Declaring the second pointer we compare the other pointer to*/
    printf("\nPlease enter the length of the number of bytes you want to compare: ");
    scanf("%d", &len);
    if (len < 0) {
        printf("\n\tYour length of comparison is negative, hence it is impossible to compare. ERROR");
        return -1;
    }
    printf("\nThe length of comparison you inserted is : %d ", len);

    printf("\nPlease enter the first index you want to compare from in the string: ");
    scanf("%d", &i1);
    if (i1 < 0) {
        printf("\n\tYour first index of comparison is negative, hence it is outside the bounds of the string memory you inserted. ERROR");
        return -1;
    }
    if (i1 + len > 511) {
        printf("\n\tYour comparison length is bigger than the strings maximum length, hence it is outside the bounds of the string memory. ERROR");
        return -1;
    }
    printf("\nThe first index of comparison you inserted is : %d ", i1);

    printf("\nPlease enter the second index you want to compare from in the string: ");
    scanf("%d", &i2);
    if (i2 < 0) {
        printf("\n\tYour second index of comparison is negative, hence it is outside the bounds of the string memory you inserted. ERROR");
        return -1;
    }
    if (i2 + len > 511) {
        printf("\n\tYour comparison length is bigger than the strings maximum length, hence it is outside the bounds of the string memory. ERROR");
        return -1;
    }
    printf("\nThe second index of comparison you inserted is : %d ", i2);
    printf("\nPlease enter the string you want to compare from : ");
    scanf("%s", str);
    printf("The string you inserted is : %s", str);

    /***
     * We set the 2 pointer to point to the indexes inserted;
     */
    first = &str[i1];
    second = &str[i2];
    /***
     * We call the function with the the 2 pointers and the length of compression given to us;
     */
    printf("\nThe function returned : %d \nIf the function returned 0 both the memory pointers contain the same bytes in the given length of comparison\n , otherwise it returned 1 which means the bytes in the length of comparison are not the same ", my_bcmp(first, second, len));
    return 1;
}

int my_bcmp(const void *b1, const void *b2, int len) {
    /***
     * If the length of comparison is 0 than there is nothing to compare, we return 0;
     */
    int i;
    char *pointer_b1 = (char *) b1;
    char *pointer_b2 = (char *) b2;

    if (len == 0) {
        return 0;
    }
    

    for (i = 0; i < len; ++i) {
        /***
         * If at any point the bytes are not identical we return 1;
         */
        if (*(pointer_b1 + i) != *(pointer_b2 + i)) {
            return 1;
        }
    }
    /**
     * We already compared the compression length in the 2 pointers and they were identical, hence we return 0;
     */
    return 0;
}


