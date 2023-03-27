#include <stdio.h>
#include <math.h>

void print_in_binary(unsigned int a);

unsigned int my_rottate(unsigned int a, int b);

int main() { /**The main method*/
    unsigned int a;
    int b;
    printf("\nPlease enter a number to rotate\n");
    scanf("%u", &a);
    printf("Please enter the number of times you want to rotate the number:\n");
    scanf("%d", &b);

    printf("The number is: %u, and the number of rotations is: %d \n", a, b);

    printf("The number in an octal representation: %o \n", a);
    printf("The number in a hexadecimal representation: \n%x\n", a);
    printf("The number in a binary representation : \t");
    print_in_binary(a);

    a = my_rottate(a, b);
    printf("\nThe number after the rotation: %u \n", a);
    printf("The number after the rotation in an octal number number representation: %o \n", a);
    printf("\"The number after the rotation in a hexadecimal number representation: %x \n", a);
    printf("The number after the rotation in a binary representation: \n");
    print_in_binary(a);
	 printf("\n");
    return 0;
}

/**
 * @function_name: print_in_binary;
 * @param: a - The number we need to print in binary (in a decimal value);
 * @description:
 * <p>
 *    prints the number it get in binary;
 * <p>
*/
void print_in_binary(unsigned int a) {
    int i;
    for (i = (sizeof(a) * 8); i > 0; i--) {
        if (a & (1 << ((sizeof(a) * 8) - 1))) {
            printf("1");
        } else {
            printf("0");
        }
        a <<= 1;
    }
}

/**
 * @function_name: my_rottate;
 * @param: a - The number we need to rotate;
 * @param: b - Number of rotations;
 * @return: The number after all the rotations.
 * @description:
 * <p>
 * the function checks if the number of rotations is positive,
 * if it is positive (b>0) the rotation will be to the right.
 * If the number is negative (b<0) the rotation will be to the left.
 * The function saves all the bits that are going to be rotated to the other side of the word, then extracts them out, moves the other bits forward/backward (depends on the value of b negative/positive),
 * and then puts the saved bits in the other side of the number.
 * <p>
*/
unsigned int my_rottate(unsigned int a, int b) {
    unsigned int saved_bits; /**The bits that we are going to re-enter from the other side of the number;*/
    unsigned int a_after_removal; /**'a' after the moving all the bits b times;*/
    unsigned int insert_to_a; /**The number which is going to be re-inserted to 'a' from the other side of 'a';*/

    /**Size of a returns the size in bytes, 1 byte = 8 bits hence sizeof(a)*8 = the num of bits;*/
    unsigned int a_size_in_bits = (sizeof(a) * 8);
    unsigned int mask = (pow(2, -b) - 1);

    if (b > 0) { /*Rotation to the right;*/
        saved_bits = a & ((1 << b) - 1);
        /**The new number with all the bits that are going to be re-inserted from the word to the other side;*/
        insert_to_a = saved_bits << (a_size_in_bits - b);
        a_after_removal = a >> b;
    } else { /**Rotation to the left;*/
        saved_bits = a & (mask << (a_size_in_bits + b));
        insert_to_a = saved_bits >> (a_size_in_bits + b);
        a_after_removal = a << -b;
    }
    /**Re-inserting all the bits that were removed out of a for the rotation and returning the result;*/
    return (a_after_removal | insert_to_a);
}
