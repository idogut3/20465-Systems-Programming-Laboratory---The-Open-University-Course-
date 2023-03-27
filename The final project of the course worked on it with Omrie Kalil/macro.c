#include "project.h"


/***
 * @function: identify_mcr
 
 * @param A FILE called file;
 * @param A File called new file in which we will open up all the macros
 
 * @returns void;
 
 * @description: 
 * The function identifies all the macro declarations, saves the contents of the macros, then opens them up in the new file;  
 */


void identify_mcr(FILE *file, FILE *new_file)
{

	char *mcr_names[max];
	char *mcr_content[max];
	char buffer[max];
	int mcr_count = 0;
	int j;
	int count = 0;
	
	while(fgets(buffer, max, file) != NULL)
	{
		
		if(strstr(buffer, "mcr ") != NULL) /*Searching for the word mcr, if found we then allocate memory to save the name of the mcr and the contents of it*/
		{
			mcr_names[mcr_count] = (char *)malloc(max * sizeof(char)); /*Allocating memory for the name of the mcr*/
			mcr_content[mcr_count] = (char *)malloc(max * sizeof(char)); /*Allocating memory for the contents of the mcr*/
			
			for(j = 0; j < max; j++) 
			{
				mcr_names[mcr_count][j] = strstr(buffer, "mcr")[j + 4];
			}
			
			find_mcr_content(file, mcr_content[mcr_count]);
			mcr_count++;
		}
		
		count++;
	}
	
	fseek(file, 0, SEEK_SET); /*Resetting the file pointer to the start of the file*/
	open_mcr(file, new_file, mcr_names, mcr_content, mcr_count); /*Calling a function to open up all the macro functions in the code*/
	
	if(mcr_count > 0)
	{
		free(mcr_names[0]);
		free(mcr_content[0]);
	}

}

/***
 * @function: find_mcr_content
 
 * @param A FILE called file;
 * @param A char pointer containing all the mcr content we saved up until now;
 
 * @returns void;
 
 * @description: 
 * The function is called when we identify a macro declaration, it copies the contents of the macro up until the point where we see the string "endmcr"
 * which informs us that thats the end of the macro declaration;
 */

void find_mcr_content(FILE *file, char *mcr_content)
{

	char buffer[max];
	bool flag = false;

	while(fgets(buffer, max, file) != NULL)
	{

		if(strstr(buffer, "endmcr") != NULL)
		{
			flag = true;
		}
		
		if(flag == true)
		{
			return;
		}
		
		else
		{
			strcat(mcr_content, buffer);
		}
	}
}

/***
 * @function: open_mcr
 
 * @param A FILE called file;
 * @param A FILE called new file in which we will open up all the macros;
 * @param An array of pointers called mcr_names containing all the macro functions names for each function;
 * @param An array of pointers called mcr_content containing all the macro functions content for each macro function;
 * @param An int mcr_count containing the number of macros we have in the file;
 
 * @returns void;
 
 * @description: 
 * The function gets the parameters *file and *new_file, it copies down every line of file to the new_file while opening up all the macros in the places where
 * the macros where used in, while also moving all the ".data" , ".string" declarations to the end of the file; 
 */


void open_mcr(FILE *file, FILE *new_file, char *mcr_names[max], char *mcr_content[max], int mcr_count)
{
	char buffer[max];
	int i;
	int j;
	int count = 0;
	int k;
	bool flag = false;
	bool flag2 = false;
	char *values[max];
	int value_count = 0;

	while(fgets(buffer, max, file) != NULL) /*Looping through the main file with buffer*/
	{

		for(i = 0; i < strlen(buffer); i++) /*Looping through our current line (buffer)*/
		{
		
/*If we locate a ".data" declaration or a ".string" declaration we then copy the statement then later paste it in the end of our machine code and only then is when we open it up */
			
			if(strstr(buffer, ".data") != NULL || strstr(buffer, ".string") != NULL) 
			{
				values[value_count] = (char *)malloc(max * sizeof(char));
				strcpy(values[value_count], buffer);
				flag2 = true;
				value_count++;
				break;
			}
			if(strstr(buffer, "mcr ") != NULL)
			{
				flag = true;
				break;
			}
			
			if(strstr(buffer, "endmcr") != NULL || buffer == NULL || strcmp(buffer, "\n") == 0)
			{
				flag = false;
				flag2 = true;
				break;
			}
			
			for(j = 0; j < mcr_count; j++)
			{

				for(k = 0; k < strlen(buffer) - i; k++)
				{

					if(buffer[i + k] == mcr_names[j][k])
					{
						count++;
					}
				}
				
				if(count == strlen(mcr_names[j]))
				{
					flag2 = true;
					fprintf(new_file, "%s", mcr_content[j]);
					count = 0;
					break;
				}
				count = 0;
			}
		}
		
		if(flag == false)
		{
			if(flag2 == false)
			{
				fprintf(new_file, "%s", buffer);
			}
		}
		flag2 = false;
	}
	
	for(i = 0; i < value_count; i++)
	{
	
		fprintf(new_file, "%s", values[i]);
	}
	
	if(value_count > 0)
	{
		free(values[0]);
	}
}









