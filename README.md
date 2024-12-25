# 20465-Systems-Programming-Laboratory---The-Open-University-Course-
This is a systems programming laboratory course I took at the "Open university of Israel", the repository contains course assignments (mmns) and the final project of the course. Credit to Omrie Kalil for working with me on the final project.

The final project was to build an assembler to an assembly-like language. A program which reades out assembly code and outputs the machine code for the computer to read, understand and run.
 
#### here is a picture of what it is supposed to do:
![](https://github.com/idogut3/20465-Systems-Programming-Laboratory-The-Open-University-Course/blob/main/images/asembler_picture1.png)

#### MMN 11 task:
##### Question 1 (Main Program in abc.c)

###### We will define a shortened string in the following way:

Given a string of characters, we will search for ascending sequences of characters from the English alphabet, whose length is at least 3. For example, in the following string there are three such sequences, emphasized with lines: dabcefLMNOPQrstuv567zyx
Each sequence will be shortened to three characters: the first letter in the sequence, a hyphen, and the last letter in the sequence. For the example above, we will get the shortened string: da-cefL-OpQr-v567zyx

Note: These are sequences of alphabet letters only (and not other characters). Lowercase and uppercase letters are considered different. The sequence is determined according to the corresponding ASCII codes.

You must write a function that receives a string as a parameter and converts it to a shortened string.

Note: The function does not create a new string, but changes the string passed to it.

In addition, you must write a main program (the main function) that will perform input of a string from the user, run the function on the input string, and neatly print the shortened string.

It is permissible to assume that the maximum length of the input string is 80 characters.

The input for the program is from stdin, and can come from the keyboard or from a file (using redirection when running the program). For your convenience, prepare several input files and use them repeatedly for debugging the program

##### Question 2 (Main Program in my_rotate.c)

You need to write a program containing the following function:
```c
unsigned int my_rotate(unsigned int a, int b)
```
This function performs a rotation (shift) of 6 bits on parameter a.

Explanation: When referring to performing a rotation of 6 places on parameter a, it means shifting the bits of parameter a, 6 bits to the right when b is positive, and 6 bits to the left when b is negative. As a result of shifting b bits to the right, the b leftmost bits of parameter a are "emptied". The bits that were discarded from a on its right side will be inserted into a on its left side. (Exactly the opposite when b is negative. The bits "falling off" the left end of a are inserted into the empty spaces created at the right end of a. Example below).

The function must return the value after performing the rotation. The program must print the value before and after the change. The values will be entered in base 10, as explained below. The printouts, before and after the change, must be done in bases 16, 8, and 2, in addition to base 10.   

Note: The implementation must not be computer-dependent, i.e., it is not guaranteed here that the representation of a variable of type unsigned int will occupy two bytes of memory.

Example: Given the following variable x:

x = 1010111011111011
Then my_rotate(x, 3) will give:

x = 0111010111011111
And my_rotate(x, -3) will give:

x = 0111011111011101
The input for the program is from stdin, and can come from the keyboard or from a file (using redirection when running the program). It is recommended to prepare several input files and use them repeatedly for debugging the program.
The input for the program is from stdin, and can come from the keyboard or from a file (using redirection when running the program).


#### MMN 12 task:
##### Question 1 (Main Program in my_bcmp.c)

###### You must implement the following function:

```c
int my_bcmp(const void *b1, const void *b2, int len);
```
b1 - Pointer to the first memory segment.
b2 - Pointer to the second memory segment.
len - The number of bytes to compare.

Purpose of the function: To compare len bytes, starting from the location pointed to by b1, with len bytes, starting from the location pointed to by b2.

Return value: 0 if it is found that the two memory segments contain identical content, otherwise a value other than 0.

Notes:

Memory segments can overlap partially or completely.
Memory segments of length 0 are always identical to each other.
It cannot be assumed that the memory segments end with a null character, and the function must not modify the segments.
To test the function, we will use memory segments that are entered into the program by the user, as follows:

The program will receive a string as input, two indices into the string, and the value len. The indices represent pointers to the memory segments (of course, pointers must be built from the indices for the purpose of calling the function).

The order of the data in the input is: len, followed by the two indices, and finally the string. It is permissible to assume that the maximum length of the string is 512. Each of the four data items must be entered separately.

Note: len is not the length of the input string, but the number of bytes to compare.

You must write a main program (the main function) that will perform input from the user, call the my_bcmp function, and print the result returned by the function in a neat manner.

It is mandatory to perform input validation before calling the function. In case of any error in the input data, the program should print an appropriate error message and exit.

In case of any error in the input data, the program should print an appropriate error message and exit.

The following are examples of possible errors (more errors can be added):
One of the indices and/or the value len is not a non-negative whole decimal number.
One of the memory segments overflows the string boundaries (according to the values of the indices and len).
The input for the program is from stdin, and can come from the keyboard or from a file (using redirection when running the program).

#### MMN 23 task:
##### Question 2 (Main program in file permut.c)

###### Definition: A permutation of a string of characters is a string that is obtained by some shuffling of the order of the characters in the original string.

You must write a program that receives two arguments on the command line: the name of an input file and a string of characters.
The program should scan the contents of the file and print to standard output all permutations of the string that are found in the file.

The permutations will be printed in the order of their appearance in the file. Each permutation will be printed on a new line. There may be multiple instances of each permutation, and all of them must be printed. Assume that there are no permutations in the file that overlap with each other.

For example, if the command line looks like this:

prog data.in chair

and the contents of the file data.in are:

I am a chair

You are an arich and not a CHAIR

We are haircs and not gariches

Goodbye

the program's output will be:

chair

arich

hairc

arich

The program should print an appropriate error message to the standard error file and stop its work in the following cases: the number of arguments on the command line is not as required; a problem opening the file; the file is empty.

If the program scanned all the contents of the file but did not find any permutations, it should print an appropriate message to the standard output file and end its run.   

Explanation of the terms:

Permutation: A permutation is a rearrangement of a set of objects. In the context of strings, it means rearranging the order of the characters in the string.
Standard input: The input that the program receives from the user or another program.
Standard output: The output that the program produces.
Standard error file: A file where the program sends error message




