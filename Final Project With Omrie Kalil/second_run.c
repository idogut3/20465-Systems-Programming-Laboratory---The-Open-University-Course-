#include "project.h"

/***
 * @function: add_missing_labels
 * @description: checks if there is a numeral representation of a label that is missing in first_run_file and corrects it
***/
void add_missing_labels(FILE *pre_assembler_file, FILE * first_run_file, FILE *second_run_file, FILE *label_file, FILE *fp_extern)
{

	int i;
	int j;
	int k;
	int z;
	int l;
	char first_run_buffer[max];
	char pre_assembler_buffer[max];
	char label_buffer[max];
	char extern_buffer[max];
	char c[max] = "";
	char *label_names[max];
	char *first_run[max];
	int *label_address;
	char token[max] = "";
	char *token2;
	bool reg_flag = false;
	int count = 0;
	char temp;
	char *temp2;
	int line1_val = 0;
	int line2_val = 0;
	int line3_val = 0;
	int label_count = 0;
	int extern_count = 0;
	int first_run_count = 0;
	int line_count = 100;

	/*taking apart label_file for easy use*/
	while(fgets(label_buffer, max, label_file) != NULL)
	{
	
		temp2 = strtok(label_buffer, "\t\n");
		
		label_names[label_count] = (char *)malloc(max * sizeof(char));
		
		if(label_count == 0)
		{
			label_address = (int *)malloc(sizeof(int));
		}
		
		else
		{
			label_address = (int *)realloc(label_address, (label_count + 1) * sizeof(int));
		}
		
		label_address[label_count] = atoi(temp2);
		temp2 = strtok(NULL, "\t\n");
		strcpy(label_names[label_count], temp2);
		label_count++;
	}
	
	fseek(label_file, 0, SEEK_SET);
	
	/*finding how mach .extern labels are in the code*/
	while(fgets(extern_buffer, max, fp_extern) != NULL)
	{
		extern_count++;
	}
	
	fseek(fp_extern, max, SEEK_SET);

	/*taking apart first_run_file for easy use*/
	while(fgets(first_run_buffer, max, first_run_file) != NULL)
	{
		first_run[first_run_count] = (char *)malloc(max * sizeof(char));
		strcpy(first_run[first_run_count], strtok(first_run_buffer, "\n"));
		first_run_count++;
	}
	
	fseek(first_run_file, 0, SEEK_SET);
	
	for(z = 0; z < first_run_count;)
	{
	
		/*when count equel to 0 we go down a line in pre_assembler_file but if not count is minus 1 and everithing else stay the same*/ 
		if(count == 0)
		{
			strcpy(pre_assembler_buffer, "");
			if(fgets(pre_assembler_buffer, max, pre_assembler_file) != NULL)
			{
				count = 3;
			}
			else
			{
				break;
			}

			/*if the pre_assembler_file is empty the loop is over*/
			if(strcmp(pre_assembler_buffer, "") == 0)
			{
				break;
			}
		}

		/*getting past a defenition of a label*/
		if(strchr(pre_assembler_buffer, ':') != NULL)
		{
			temp2 = strtok(pre_assembler_buffer, ":");
			temp2 = strtok(NULL, ":");
			strcpy(c, temp2 + 1);
		}

		else
		{
			strcpy(c, pre_assembler_buffer);
		}

		if(strstr(c, ".") == NULL)
		{
			/*if there is a mising label*/
			if((atoi(first_run[z]) & 3) == 3)
			{
				for(k = 0; k < label_count; k++)
				{

					if(strstr(c, label_names[k]) != NULL)
					{
						count = 0;

						/*checking if it direct 2*/
						if((atoi(first_run[z]) & 2 << 2) == (2 << 2))
						{
							line1_val = atoi(first_run[z]) - 3;
							line2_val = label_address[k];
							token2 = strtok(c, "(,)");
							token2 = strtok(NULL, "(,)");
				
							/*"source" direct 0 in direct 2*/
							if(strchr(token2, '#') != NULL)
							{
								line3_val = atoi(strchr(token2, '#') + 1) << 2;
							}
				
							/*"source" direct 1 in direct 2*/
							for(j = 0; j < label_count; j++)
							{

								if(strstr(token2, label_names[j]) != NULL)
								{
									line1_val += 1 << 12;
									line3_val = label_address[j];
									break;
								}
							}

							/*"source" direct 3 in direct 2*/
							temp = '0';
							for(i = 0; i < 8; i++)
							{

								token[0] = 'r';
								token[1] = temp;
		
								if(strstr(token2, token) != NULL)
								{
									line1_val += 3 << 12;
									line3_val = i << 8;
									reg_flag = true;
									break;
								}
				
								temp++;
								token[1] = '\0';
							}
			
							token2 = strtok(NULL, "(,)");

							/*"target" direct 0 in direct 2*/
							if(strchr(token2, '#') != NULL)
							{
								translate_to_computer_language(line1_val, second_run_file, line_count);
								line_count++;
								translate_to_computer_language(line2_val, second_run_file, line_count);
								line_count++;
								translate_to_computer_language(line3_val, second_run_file, line_count);
								line_count++;
								translate_to_computer_language(atoi(strchr(token2, '#') + 1) << 2, second_run_file, line_count);
								line_count++;
							}

							/*"target" direct 1 in direct 2*/
							for(j = 0; j < label_count; j++)
							{

								if(strstr(token2, label_names[j]) != NULL)
								{
									line1_val += 1 << 10;
									translate_to_computer_language(line1_val, second_run_file, line_count);
									line_count++;
									translate_to_computer_language(line2_val, second_run_file, line_count);
									line_count++;
									translate_to_computer_language(line3_val, second_run_file, line_count);
									line_count++;
									translate_to_computer_language(label_address[j], second_run_file, line_count);
									line_count++;
									break;
								}
							}

							/*"target" direct 3 in direct 2*/
							temp = '0';
							for(i = 0; i < 8; i++)
							{

								token[0] = 'r';
								token[1] = temp;
	
								if(strstr(token2, token) != NULL)
								{
									line1_val += 3 << 10;
									if(reg_flag == true)
									{
										line3_val += (i << 2);
										translate_to_computer_language(line1_val, second_run_file, line_count);
										line_count++;
										translate_to_computer_language(line2_val, second_run_file, line_count);
										line_count++;
										translate_to_computer_language(line3_val, second_run_file, line_count);
										line_count++;
									}
						
									else
									{
										translate_to_computer_language(line1_val, second_run_file, line_count);
										line_count++;
										translate_to_computer_language(line2_val, second_run_file, line_count);
										line_count++;
										translate_to_computer_language(line3_val, second_run_file, line_count);
										line_count++;
										translate_to_computer_language(i << 2, second_run_file, line_count);
										line_count++;
									}
									
									break;
								}
					
								temp++;
								token[1] = '\0';
							}
							z++;
							break;
						}
			
						/*if its direct 1*/
						else if((atoi(first_run[z]) & 1 << 2) == (1 << 2))
						{
							translate_to_computer_language(atoi(first_run[z]) - 3, second_run_file, line_count);
							line_count++;
							z++;
							
							/*if the missing label is a source operand*/
							if(atoi(first_run[z + 1]) == 3)
							{
								translate_to_computer_language(atoi(first_run[z]), second_run_file, line_count);
								line_count++;
								z++;
								translate_to_computer_language(label_address[k], second_run_file, line_count);
								line_count++;
							}
							
							/*if the missing label is a target operand*/
							else
							{
								translate_to_computer_language(label_address[k], second_run_file, line_count);
								line_count++;
							}
							z++;
							count = 0;
							break;
						}
					}
				}

				count = 0;
			}
		
			/*if there are no missing labels in the line*/
			else
			{
				translate_to_computer_language(atoi(first_run[z]), second_run_file, line_count);
				line_count++;
				count--;
				z++;
			}
		}

		/*if there is extern or entry skip the line*/
		else if(strstr(c, ".extern") != NULL || strstr(c, ".entry") != NULL)
		{
			count = 0;
		}
		
		/*if there is string or data its the only things that are left and the rest of the file can be printed as in the first run*/
		else if(strstr(c, ".data") != NULL || strstr(c, ".string") != NULL)
		{
			for(l = z; l < first_run_count; l++)
			{
				translate_to_computer_language(atoi(first_run[l]), second_run_file, line_count);
				line_count++;
			}
			
			break;
		}
	}

	/*freeing allocations*/
	if(label_count > 0)
	{
		free(label_names[0]);
		free(label_address);
	}
	
	if(first_run[0] != NULL)
	{
	
		free(first_run[0]);
	}
}

/***
 * @function: translate_to_computer_language
 * @description: prints the complete binary code to translated_file
***/
void translate_to_computer_language(int buffer, FILE *translated_file, int line_count)
{

	short i;
	
	fprintf(translated_file, "%d\t", line_count);
	
	for(i = 1 << 13; i > 0; i = i / 2)
	{
	
		(buffer & i) ? fprintf(translated_file, "/") : fprintf(translated_file, ".");
	}
	
	fprintf(translated_file, "\t%d\n", buffer);
}
















