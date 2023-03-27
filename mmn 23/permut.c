#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 100

void permut(char file_name[MAX_LEN], char str[MAX_LEN]);


int main(){
    char file_name[MAX_LEN];
    char str[MAX_LEN];
    
    printf("\n Enter file name please:\n");
    scanf("%s", file_name);
    
    printf("Enter the string please:");
    scanf("%s", str);
    
    permut(file_name, str);
    return 0;
}







void permut(char file_name[MAX_LEN], char str[MAX_LEN])
{
	
	FILE *file = fopen(file_name, "r"); /*opening the file*/
	char line[MAX_LEN]; /*The string that will contain each line in the file one by one*/
	char pemutation[MAX_LEN] = ""; /*The string that contains our word permutation*/
	char temp[MAX_LEN] = ""; /*The string that will contain the str we are checking for the permutations*/
	int i;
	int j;
	int k;
	bool legal_flag = false; /*A flag that tells if the character in the permutation is legal or not*/
	bool print_flag = false; /*A flag for telling us if there were any permutations in the file*/

	while(fgets(line, MAX_LEN, file) != NULL) /*Inserting a line from the file in our buffer (line char) until there are no more lines in our file*/
	{

		for(k = 0; k < strlen(str); k++) /*Inserting to our temp the str we are checking for the permutations*/
		{
			temp[k] = str[k];
		}

		for(i = 0; i < strlen(line); i++)
		{
			if(strlen(temp) == 0) /*If our temp is empty then the word contained in the permutation str is a permutation*/
			{
				printf("%s\n", pemutation); /*Printing the permutation*/
				print_flag = true; /*Marking that there was a permutation in the file*/

				for(k = 0; k < strlen(str); k++) /*Reseting temp*/
				{
					temp[k] = str[k];
				}
			}

			for(j = 0; j < strlen(temp); j++) /*Running on temp*/
			{
				if(line[i] == temp[j])
				{
					pemutation[strlen(str) - strlen(temp)] = line[i]; /*If there are two characters that are equal in temp and line, then we insert the identical charecter in the permutation char*/

					for(k = 0; k < strlen(temp); k++) /*Removing the identical character from temp*/
					{
						if(k > j)
						{
							temp[k - 1] = temp[k];
						}
					}
					temp[strlen(temp) - 1] = (int)NULL;

					legal_flag = true; /*Marking that the character is legal*/
					break;
				}
			}

			if(legal_flag == false)
			{

				for(k = 0; k < strlen(str); k++) /*If the legal character flag is false, then the current char is not legal hence we reset temp*/
				{
					temp[k] = str[k];
				}
			}

			legal_flag = false; /*Reseting the legal character flag*/
		}
	}

	if(print_flag == false) /*If the print flag is false, there are no permutations in the file so an error messege is being printed*/
	{
		printf("No permutations are found for the str: %s  in the file: %s\n", str, file_name);
	}
}
