#include "project.h"

/***
 * @function: find_label
 * @description: gets all of the labels and put them in label_file
***/
void find_label(FILE *file, FILE *out_file, FILE *label_file, FILE *extern_words, FILE *extern_dec, FILE *fp_extern, FILE *fp_entry)
{

	int i;
	int j;
	char *label_names[max];
	int label_address[max];
	char buffer[max];
	bool end_flag = false;
	int count = 100;
	int label_count = 0;
	int found_ext;
	int found_ent;
	int found_data;
	int found_str;
	char c[max];

	while(fgets(buffer, max, file) != NULL)
	{
		
		found_ent = compile_entry(buffer, fp_entry, count);
		found_ext = compile_extern(buffer, extern_words, extern_dec, count);
		found_data = compile_data(buffer, out_file);
		found_str = compile_string(buffer,  out_file);
		
		fclose(extern_words);
		fclose(extern_dec);
		
		extern_words = fopen("extern_words", "r");
		extern_dec = fopen("extern_dec", "r");
		
		collect_usages(buffer, extern_words, extern_dec, count, fp_extern);
		
		
		if(found_str == -1)
		{
			return;
		}
		
		if(found_ext == 0 && found_ent == 0  && strchr(buffer, ';') == NULL)
		{
			for(i = 0; i < strlen(buffer); i++)
			{

				/*if its a legal start of a label*/
				if((buffer[i] >= 65 && buffer[i] <= 90) || (buffer[i] >= 97 && buffer[i] <= 122))
				{
					for(j = i; j < strlen(buffer); j++)
					{

						/*if its a legal end of a label*/
						if(buffer[j] == ':')
						{
					
							end_flag = true;
							break;
						}
				
						if(!((buffer[j] >= 65 && buffer[j] <= 90) || (buffer[j] >= 97 && buffer[j] <= 122) || (buffer[j] >= 48 && buffer[j] <= 57)))
						{
							break;
						}
					}

					/*saves the label in label_names and label_address*/
					if(end_flag == true)
					{
						label_names[label_count] = (char *)malloc(max * sizeof(char));
						strcpy(c, buffer);
						strcpy(label_names[label_count], strtok(c, ":"));
						label_address[label_count] = (count << 2) + 2;
						end_flag = false;
						label_count++;
					}
			
					break;
				}
			}
			
			/*starting to go over the line if there is no data or string in it*/
			if(found_str == 0 && found_data == 0)
			{
				count += opcode(buffer, out_file, label_names, label_address, label_count) + 1;
			}
		}
		
		/*if there is an extern saves it in label_names and label_address*/
		else if(found_ext == 1 && found_ent == 0 && found_data == 0 && found_str == 0)
		{
			label_names[label_count] = (char *)malloc(max * sizeof(char));
			strcpy(c, buffer);
			strcpy(label_names[label_count], strstr(strtok(c, "\n"), ".extern") + 8);
			label_address[label_count] = 1;
			label_count++;
		}
	}

	/*printing all of the labels to label_file*/
	for(i = 0; i < label_count; i++)
	{
	
		fprintf(label_file, "%d\t%s\n", label_address[i], label_names[i]);
	}

	/*freeing allocations*/
	if(label_count > 0)
	{
		free(label_names[0]);
	}
}

/***
 * @function: opcode
 * @return: the number of lines added in the binary code
 * @description: if there is an operator in buffer it will put the numeral representation in output_line
***/
int opcode(char buffer[max], FILE *out_file, char *label_names[max], int label_address[max], int label_count)
{

	const char arr[16][4] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
	int i;
	short output_line = 0;
	int line_count = 0;

	for(i = 0; i < 16; i++)
	{

		if(strstr(buffer, arr[i]) != NULL)
		{
			output_line = (i << 6);
			break;
		}
	}


	line_count += source_direction(buffer, out_file, arr, output_line, label_names, label_address, label_count);
	return line_count;
}

/***
 * @function: source_direction
 * @return: the number of lines added in the binary code
 * @description: if there is a source operand it will make a new line in which the numeral representation will be and it will add the number of the direct (miun) in the output_line
***/
int source_direction(char buffer[max], FILE *out_file, const char arr[16][4], int output_line, char *label_names[max], int label_address[max], int label_count)
{

	char c[max] = "";
	short direct_val = 0;
	int i;
	int j;
	int instruction_group = -1;
	int extra_lines = 0;
	short extra_line_content = 0;
	char token[max] = "r";
	bool flag = false;
	bool reg_flag = false;
	bool operand_flag = false;
	char temp[max] = "";
	char count;
	int line_count = 0;

	strcpy(temp, buffer);
	
	/*checks what is the operator and group it in the group of operators that can use the same directs*/
	for(j = 0; j < 16; j++)
	{

		if(strstr(buffer, arr[j]) != NULL)
		{
			if(j <= 3)
			{
				instruction_group = 0;
			}

			else if(j == 6)
			{
				instruction_group = 1;
			}

			strcpy(c, strstr(strtok(temp, ","), arr[j]) + 4);
			break;
		}
	}

	/*operators: mov, cmp, add, sub. possible directs for operators: 0, 1, 3*/
	if(instruction_group == 0)
	{
		/*direct 0*/
		if(strchr(c, '#') != NULL)
		{
			direct_val = 0;
			extra_lines++;
			extra_line_content = atoi(strchr(c, '#') + 1) << 2;
			operand_flag = true;
		}

		else
		{
			i = 0;
			for(count = '0'; count < '8'; count++)
			{	
				/*direct 3*/
				token[1] = count;
				if(strstr(c, token) != NULL)
				{
					direct_val = 3;
					extra_lines++;
					extra_line_content = i << 8;
					reg_flag = true;
					flag = true;
					operand_flag = true;
					break;
				}
				
				i++;
				token[1] = '\0';
			}
			
			/*direct 1*/
			if(flag == false)
			{
				
				for(i = 0; i < label_count; i++)
				{

					if(strstr(c, label_names[i]) != NULL)
					{
						direct_val = 1;
						extra_lines++;
						extra_line_content = label_address[i];
						operand_flag = true;
						break;
					}
				}
				
				/*if the operand is an unfound label*/
				if(operand_flag == false && c != NULL && strcmp(c, "\n") != 0)
				{
					direct_val = 1;
					extra_lines++;
					/*putting 3 as a flag for the second run*/
					extra_line_content = 3;
				}
			}
		}
	}

	/*operator: lea.posible directs for operator: 1*/
	else if(instruction_group == 1)
	{
		/*direct 1*/
		for(i = 0; i < label_count; i++)
		{
		
			if(strstr(c, label_names[i]) != NULL)
			{
				direct_val = 1;
				extra_lines++;
				extra_line_content = label_address[i];
				operand_flag = true;
				break;
			}
		}
		
		/*if the operand is an unfound label*/
		if(operand_flag == false && c != NULL && strcmp(c, "\n") != 0)
		{
			direct_val = 1;
			extra_lines++;
			/*putting 3 as a flag for the second run*/
			extra_line_content = 3;
		}
	}
	
	output_line += (direct_val << 4);
	line_count += target_direction(buffer, out_file, arr, output_line, label_names, label_address, label_count, extra_lines, extra_line_content, reg_flag);
	return line_count;
}





























