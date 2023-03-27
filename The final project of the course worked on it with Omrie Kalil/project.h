/*Including all the libraries are using in the project*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


#define max 80 /*Defines the constant max to 80*/

/*The function identifies all the macros and their names inside the file and then transfers the open macros to the new file */
void identify_mcr(FILE *file, FILE *new_file);

/*The function identifies all the macros in the file and their content*/
void find_mcr_content(FILE *file, char *mcr_content);

/*The function opens up in the new file all the macros*/
void open_mcr(FILE *file, FILE *new_file, char *mcr_names[max], char *mcr_content[max], int mcr_count);

/*The function finds all the labels, entry declarations, and the extern declarations in the files and catalogs them in order to print them later */
void find_label(FILE *file, FILE *out_file, FILE *label_file, FILE *extern_words, FILE *extern_dec, FILE *fp_extern, FILE *fp_entry);

/*The function inserts to the machine code the right opcode name in binary*/
int opcode(char buffer[max], FILE *out_file, char *label_names[max], int label_address[max], int label_count);

/*The function inserts to the machine code the right mioun type of the source operand*/
int source_direction(char buffer[max], FILE *out_file, const char arr[16][4], int output_line, char *label_names[max], int label_address[max], int label_count);

/*The function inserts to the machine code the right mioun type of the target operand*/
int target_direction(char buffer[max], FILE *out_file, const char arr[16][4], int output_line, char *label_names[max], int label_address[max], int label_count, int extra_lines, int source_extra_line_content, bool reg_flag);

/*The function prints out the result of the file after the first run */
void print_first_run(FILE *out_file, int output_line, int extra_lines, int first_extra_line_content, int second_extra_line_content, int third_extra_line_content);

/*The function adds all the missing labels to the file*/
void add_missing_labels(FILE *pre_assembler_file, FILE * first_run_file, FILE *second_run_file, FILE *label_file, FILE *fp_extern);

/*The function translates all the file into the correct machine language in "./" code */
void translate_to_computer_language(int buffer, FILE *translated_file, int line_count);

/*The function gets the FILE fp2 and outputs all the data declared as ".data" to the file*/
int compile_data(char buffer[max] , FILE *fp2);

/*The function gets the FILE fp2 and outputs all the data declared as ".string" to the file*/
int compile_string(char buffer[max], FILE *fp2);

/*The function collects all the names of the declared ".entry" words and saves them in the FILE entry_words*/
int compile_entry(char buffer[max], FILE *fp_entry, int line_num);

/*The function collects all the names of the words declared as ".extern" and saves them in the FILE extern_words and also saves the place (line) each extern was declared at */
int compile_extern(char buffer[max], FILE *extern_words, FILE *extern_dec, int line_num);

/*The function outputs to the FILE usages all the places in the code were we used one of the words declared as ".extern" and also prints out where we used them at*/
void collect_usages(char main_buffer[max], FILE *words, FILE *declarations, int line_num, FILE *usages);

