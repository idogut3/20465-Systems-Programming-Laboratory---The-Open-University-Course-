#include "project.h"

/***
 * @function: target_direction
 * @return: the number of lines added in the binary code
 * @description: if there is a target operand it will make a new line (or lines) in which the numeral representation will be and it will add the number of the direct (miun) in the output_line
***/
int target_direction(char buffer[max], FILE *out_file, const char arr[16][4], int output_line, char *label_names[max], int label_address[max], int label_count, int extra_lines, int first_extra_line_content, bool reg_flag)
{

	int second_extra_line_content = 0;
	int third_extra_line_content = 0;
	char c[max];
	int instruction_group = -1;
	int i;
	int j;
	int direct_val = 0;
	char token[max] = "";
	char *token2;
	bool flag = false;
	bool operand_flag = false;
	char count = '0';
	char temp[max];
	int line_count = 0;
	
	/*checks what is the operator and group it in the group of operators that can use the same directs, and making sure that the buffer is pointing on the target operand*/
	for(j = 0; j < 16; j++)
	{

		if(strstr(buffer, arr[j]) != NULL)
		{

			if(j == 0 || (j >= 2 && j <= 8) || j == 11)
			{
				instruction_group = 0;
				
				if(strchr(buffer, ',') != NULL)
				{
					strcpy(c, strchr(buffer, ',') + 1);
				}

				else
				{
					strcpy(c, strstr(buffer, arr[j]));
				}
			}

			else if(j == 1 || j == 12)
			{
				instruction_group = 1;
				if(strchr(buffer, ',') != NULL)
				{
					strcpy(c, strchr(buffer, ',') + 1);
				}

				else
				{
					strcpy(c, strstr(buffer, arr[j]));
				}
			}

			else if((j >= 9 && j <= 10) || j == 13)
			{
				instruction_group = 2;
				strcpy(c, strstr(buffer, arr[j]));
			}
			break;
		}
	}

	/*operators: mov, add, sub, not, clr, lea, inc, dec, red. possible directs for operators: 1, 3.*/
	if(instruction_group == 0)
	{
		/*direct 1*/
		for(i = 0; i < label_count; i++)
		{

			if(strstr(c, label_names[i]) != NULL)
			{
			
				direct_val = 1;
				extra_lines++;
				
				if(extra_lines == 2)
				{
					second_extra_line_content = label_address[i];
				}
				
				else
				{
					first_extra_line_content = label_address[i];
				}
				
				flag = true;
				operand_flag = true;
				break;
			}
		}

		/*direct 3*/
		if(flag == false)
		{

			count = '0';
			token[0] = 'r';
			for(i = 0; i < 8; i++)
			{
			
				token[1] = count;
				
				if(strstr(c, token) != NULL)
				{
					direct_val = 3;
					if(reg_flag == false)
					{
						if(extra_lines == 1)
						{
							second_extra_line_content = i << 2;
						}
						
						else
						{
							first_extra_line_content = i << 2;
						}
						
						extra_lines++;
					}
					
					else
					{
						first_extra_line_content += i << 2;
					}
					
					operand_flag = true;
					break;
				}
				
				count++;
				token[1] = '\0';
			}
		}
		
		/*if the operand is an unfound label*/
		if(operand_flag == false && c != NULL && strcmp(c, "\n") != 0)
		{
			direct_val = 1;
			if(extra_lines == 1)
			{
				/*putting 3 as a flag for the second run*/
				second_extra_line_content = 3;
			}
			
			else
			{
				/*putting 3 as a flag for the second run*/
				first_extra_line_content = 3;
			}
			
			output_line += 3;
			extra_lines++;
			line_count += extra_lines;
		}
	}

	/*operators: cmp, prn. possible directs for operators: 0, 1, 3*/
	else if(instruction_group == 1)
	{
		/*direct 0*/
		if(strchr(c, '#') != NULL)
		{
			direct_val = 0;
			extra_lines++;
			if(extra_lines == 2)
			{
				second_extra_line_content = atoi(strchr(c, '#') + 1) << 2;
			}
			
			else
			{
				first_extra_line_content = atoi(strchr(c, '#') + 1) << 2;
			}
			flag = true;
			operand_flag = true;
		}

		/*direct 1*/
		for(i = 0; i < label_count; i++)
		{

			if(strstr(c, label_names[i]) != NULL)
			{
				direct_val = 1;
				extra_lines++;
				if(extra_lines == 2)
				{
					second_extra_line_content = label_address[i];
				}
				
				else
				{
					first_extra_line_content = label_address[i];
				}
				flag = true;
				operand_flag = true;
				break;
			}
		}
		
		/*direct 3*/
		if(flag == false)
		{
			for(i = 0; i < 8; i++)
			{
			
				token[0] = 'r';
				token[1] = count;
				
				if(strstr(c, token) != NULL)
				{

					direct_val = 3;
					if(reg_flag == false)
					{
						if(extra_lines == 1)
						{
							second_extra_line_content = i << 2;
						}
						
						else
						{
							first_extra_line_content = i << 2;
						}
						
						extra_lines++;
					}
					
					else
					{
						first_extra_line_content += i << 2;
					}
					
					operand_flag = true;
					break;
				}
				count++;
				token[1] = '\0';
			}
		}
		
		/*if the operand is an unfound label*/
		if(operand_flag == false && c != NULL && strcmp(c, "\n") != 0)
		{
			direct_val = 1;
			if(extra_lines == 1)
			{
				/*putting 3 as a flag for the second run*/
				second_extra_line_content = 3;
			}
			
			else
			{
				/*putting 3 as a flag for the second run*/
				first_extra_line_content = 3;
			}
			
			/*putting 3 as a flag for the second run*/
			output_line += 3;
			extra_lines++;
		}
	}
	
	/*operators: jmp, bne, jsr. possible directs for operators: 1, 2, 3.*/
	else if(instruction_group == 2)
	{
		for(i = 0; i < label_count; i++)
		{

			if(strchr(c, '(') != NULL)
			{
				/*direct 2*/
				strcpy(temp, c);
				token2 = strtok(temp, "(,)");
				if(strstr(token2, label_names[i]) != NULL)
				{
					extra_lines++;
					first_extra_line_content = label_address[i];
					
					token2 = strtok(NULL, "(,)");
					
					/*"source" direct 0 inside of direct 2*/
					if(strchr(token2, '#') != NULL)
					{
						extra_lines++;
						second_extra_line_content = atoi(strchr(token2, '#') + 1) << 2;
					}
					
					/*"source" direct 1 inside of direct 2*/
					for(i = 0; i < label_count; i++)
					{

						if(strstr(token2, label_names[i]) != NULL)
						{
							second_extra_line_content = label_address[i];
							output_line += (1 << 12);
							break;
						}
					}
					
					/*"source" direct 3 inside of direct 2*/
					count = '0';
					for(i = 0; i < 8; i++)
					{

						token[0] = 'r';
						token[1] = count;
				
						if(strstr(token2, token) != NULL)
						{
							second_extra_line_content = i << 8;
							extra_lines++;
							reg_flag = true;
							output_line += (3 << 12);
							break;
						}
						
						count++;
						token[1] = '\0';
					}
					
					token2 = strtok(NULL, "(,)");

					/*"target" direct 0 inside of direct 2*/
					if(strchr(token2, '#') != NULL)
					{

						extra_lines++;
						third_extra_line_content = atoi(strchr(token2, '#') + 1) << 2;
					}

					/*"target" direct 1 inside of direct 2*/
					for(i = 0; i < label_count; i++)
					{
						if(strstr(token2, label_names[i]) != NULL)
						{
							extra_lines++;
							third_extra_line_content = label_address[i];
							output_line += (1 << 10);
							break;
						}
					}
					
					/*"target" direct 3 inside of direct 2*/
					count = '0';
					for(i = 0; i < 8; i++)
					{
		
						token[0] = 'r';
						token[1]  = count;
			
						if(strstr(token2, token) != NULL)
						{
							if(reg_flag == false)
							{
								third_extra_line_content = i << 2;
								extra_lines++;
							}
							
							else
							{
								second_extra_line_content += i << 2;
							}
							
							output_line += (3 << 10);
							break;
						}
						
						count++;
						token[1] = '\0';
					}
					
					direct_val = 2;
					flag = true;
					operand_flag = true;
					break;
				}
			}
			
			/*direct 1*/
			else if(strstr(c, label_names[i]) != NULL)
			{
				direct_val = 1;
				extra_lines++;
			
				if(extra_lines == 2)
				{
					second_extra_line_content = label_address[i];
				}
			
				else
				{
					first_extra_line_content = label_address[i];
				}
				flag = true;
				operand_flag = true;
				break;
			}
		}
		
		if(flag == false && strchr(c, '(') == NULL)
		{
			
			/*direct 3*/
			count = '0';
			for(i = 0; i < 8; i++)
			{
			
				token[0] = 'r';
				token[1] = count;
				
				if(strstr(c, token) != NULL)
				{

					direct_val = 3;
					if(reg_flag == false)
					{
						if(extra_lines == 1)
						{
							second_extra_line_content = i << 2;
						}
						
						else
						{
							first_extra_line_content = i << 2;
						}
						
						extra_lines++;
					}
					
					else
					{
						first_extra_line_content += i << 2;
					}
					
					operand_flag = true;
					break;
				}
				
				count++;
				token[1] = '\0';
			}
		}
		
		/*if the operand is an unfound label*/
		if(operand_flag == false && c != NULL && strcmp(c, "\n") != 0)
		{
			
			/*direct 2*/
			if(strchr(c, '(') != NULL)
			{
				direct_val = 2;
				line_count += 3;
			}
			
			/*direct 1*/
			else
			{
				direct_val = 1;
				extra_lines++;
				/*putting 3 as a flag for the second run*/
				first_extra_line_content = 3;
				line_count += extra_lines;
			}

			/*putting 3 as a flag for the second run*/
			output_line += 3;
		}
	}
	
	if(operand_flag == true)
	{
		line_count += extra_lines;
	}

	output_line += (direct_val << 2);
	print_first_run(out_file, output_line, extra_lines, first_extra_line_content, second_extra_line_content, third_extra_line_content);
	return line_count;
}

/***
 * @function: print_first_run
 * @description: print the first run of the assembler to the out_file
***/
void print_first_run(FILE *out_file, int output_line, int extra_lines, int first_extra_line_content, int second_extra_line_content, int third_extra_line_content)
{

	fprintf(out_file, "%d\n", output_line);

	if(extra_lines >= 1)
	{
		fprintf(out_file, "%d\n", first_extra_line_content);
	
		if(extra_lines >= 2)
		{
			fprintf(out_file, "%d\n", second_extra_line_content);
			
			if(extra_lines == 3)
			{
				fprintf(out_file, "%d\n", third_extra_line_content);
			}
		}
	}
}

















