#include "project.h"

/**********************************************
 * main function for project.c
**********************************************/
int main(int argc, char* argv[max])
{
	
	FILE *file;
	char file_name[max];
	FILE *pre_assembler_file;
	char pre_assembler_file_name[max];
	FILE *first_run_file;
	FILE *second_run_file;
	char second_run_file_name[max];
	FILE *label_file;
	FILE *fp_extern;
	char fp_extern_name[max];
	FILE *fp_entry;
	char fp_entry_name[max];
	FILE *extern_dec;
   FILE *extern_words;
	int i;
	
	for(i = 1; i < argc; i++)
	{
		
		sprintf(file_name, "%s.as", argv[i]);
		file = fopen(file_name, "r");
		sprintf(pre_assembler_file_name, "%s.am", argv[i]);
		pre_assembler_file = fopen(pre_assembler_file_name, "wa");
		first_run_file = fopen("first_run_file", "wa");
		sprintf(second_run_file_name, "%s.ob", argv[i]);
		second_run_file = fopen(second_run_file_name, "wa");
		label_file = fopen("label_file", "wa");
		sprintf(fp_extern_name, "%s.ext", argv[i]);
		fp_extern = fopen(fp_extern_name, "wa");
		sprintf(fp_entry_name, "%s.ent", argv[i]);
		fp_entry = fopen(fp_entry_name, "wa");
		extern_dec = fopen("extern_dec", "wa");
		extern_words = fopen("extern_words", "wa");

		identify_mcr(file, pre_assembler_file);

		fclose(pre_assembler_file);

		pre_assembler_file = fopen(pre_assembler_file_name, "r");

		find_label(pre_assembler_file, first_run_file, label_file, extern_words, extern_dec, fp_extern, fp_entry);
		
		fclose(extern_words);
		fclose(extern_dec);
		fclose(label_file);
		fclose(first_run_file);
		fclose(fp_extern);
		fclose(fp_entry);
	
		extern_words = fopen("extern_words", "r");
		extern_dec = fopen("extern_dec", "r");
		label_file = fopen("label_file", "r");
		first_run_file = fopen("first_run_file", "r");
	
		fseek(pre_assembler_file, 0, SEEK_SET);
	
		add_missing_labels(pre_assembler_file, first_run_file, second_run_file, label_file, fp_extern);
	
		fclose(file);
		fclose(first_run_file);
		fclose(pre_assembler_file);
		fclose(second_run_file);
		fclose(fp_extern);

	}

	return 1;
}























