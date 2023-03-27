#include "project.h"


/***
 * @function: collect_usages
 
 * @param a string called buffer containing A line in a file;
 * @param File words pointing at the file we use to contain words that were declared as extern;
 * @param File declarations - pointing at the file we use to contain the place we declared the words that were declared as extern;
 * @param line_num an int containing the number of which line are we in the binary program;
 * @param usages the file we are going to write all the instances in which we used a word (that was declared as extern) and also where we used it;
 
 * @returns void;
 
 * @description: 
 *	The function gets 2 files - "words" and "declarations" and loops through the words file locating the words that were declared as extern and than searches
 * for these words in our current line (buffer) if found a usage of one of these words it will output were and which word was used to the usages file;
 */


void collect_usages(char main_buffer[max], FILE *words, FILE *declarations, int line_num, FILE *usages){
	char internal_word_buffer[max]; /*The label/word that was already declared in the file using .extern*/
	char internal_dec_buffer[max]; 
	int word_line_num; /*The line that the label/word that was declared at in the file using .extern*/

	
	while (fgets(internal_word_buffer, max, words) != NULL){ /*Loop through our file of label declarations and then search for the word in the main file */
		fgets(internal_dec_buffer, max, declarations);
		word_line_num = atoi(internal_dec_buffer);
		
		if(strstr(main_buffer,internal_word_buffer) != NULL && word_line_num != line_num){ /*Then we have found our label/word that was already declared in the file*/
			fprintf(usages ,"%s\t%d\n", internal_word_buffer, line_num); 
		}
	}
}

/***
 * @function: compile_entry
 
 * @param a string called buffer containing A line in a file;
 * @param File fp_entry pointing at the file we use to contain entry words;
 * @param line_num  an int containing the number of which line are we in the binary program;
 
 * @returns void;
 
 * @description: 
 *	The function locates the first mention of the word ".entry" in the file and then saves the string following it up in the ".entry file"
 * with the number of which line the string was mentioned in; 
 */

int compile_entry(char buffer[max], FILE *fp_entry, int line_num){
	int i;
	int j, found = 0;
	char word[10] = ".entry";
	int index = 0;
	int start_index = -1;

	
   while(buffer[index] != '\0')
   {
        /* If first character of word matches with the given string */
        if(buffer[index] == word[0])
        {
            /* Match entire word with current found index */
            j = 0;
            found = 1;
            while(word[j] != '\0')
            {
                if(buffer[index + j] != word[j])
                {
                    found = 0;
                    break;
                }
                
                j++;
            }
   	  }
        
        /* If the word is found then get out of loop */
        if(found == 1)
        {
            break;
        }
        index++;
    }
    

    if(found == 1) /*The word - ".entry" was found*/
    {
    	
    	for(i = index + strlen(word); i < strlen(buffer); i++){
    	
    		if(start_index == -1 && buffer[i] != ' ' && buffer[i] != '\n'){ /*The word or label started, we need to insert it to the .entry file */
    			start_index = i;
    			fprintf(fp_entry,"%c", buffer[i]); /*Writing the label inside the file*/
    		}
    		
    		else if(start_index != -1 && buffer[i] != ' ' && buffer[i] != '\n'){ /*We continue writing the name of the label*/
    			fprintf(fp_entry,"%c", buffer[i]);
    		}
    	}
  		/*The word ended we need to insert the file and write in which line the declaration was*/
    	fprintf(fp_entry,"\t%d\n", line_num); 
   }
   
   return found;
}







/***
 * @function: compile_extern
 
 * @param a string called buffer containing A line in a file;
 * @param File extern_words pointing at the file we use to contain extern words;
 * @param File extern_dec pointing at the file we use to contain the place we declared extern words;
 * @param line_num  an int containing the number of which line are we in the binary program;
 
 * @returns void;
 
 * @description: 
 *	The function locates the first mention of the word ".extern" in a line and then saves the name of the label/word we declared as .extern in the file- 
 * extern_words and saves the location (whice line) of where we declared the word/label;
 */

int compile_extern(char buffer[max], FILE *extern_words, FILE *extern_dec, int line_num){
	int i;
	int j, found = 0;
	char word[10] = ".extern";
	int index = 0;
	int start_index = -1;

	
   while(buffer[index] != '\0')
   {
        /* If first character of word matches with the given string */
        if(buffer[index] == word[0])
        {
            /* Match entire word with current found index */
            j=0;
            found = 1;
            while(word[j] != '\0')
            {
                if(buffer[index + j] != word[j])
                {
                    found = 0;
                    break;
                }
                
                j++;
            }
   	  }
        
        /* If the word is found then get out of loop */
        if(found == 1)
        {
            break;
        }
        index++;
    }
    

    if(found == 1) /*The word - ".extern" was found*/
    {
    	
    	for(i = index + strlen(word); i < strlen(buffer); i++){
    	
    		if(start_index == -1 && buffer[i] != ' ' && buffer[i] != '\n'){ /*The word or label started, we need to insert it to the .extern file */
    			start_index = i;
    			fprintf(extern_words,"%c", buffer[i]); /*Writing the label inside the file*/
    		}
    		
    		else if(start_index != -1 && buffer[i] != ' ' && buffer[i] != '\n'){ /*We continue writing the name of the label*/
    			fprintf(extern_words,"%c", buffer[i]);
    		}
    	}
    	/*The word ended we need to insert the file and write in which line the declaration was*/
    	fprintf(extern_dec ,"%d\n", line_num); 
   }
   
   return found;
}







/***
 * @function: compile_data
 
 * @param a string called buffer containing A line in a file;
 * @param File fp2 pointing at the file we use to contain .data and .string words;
 
 
 * @returns void;
 
 * @description: 
 *	The function locates the first mention of the word ".data" in the buffer and then saves the data separated by commas line by line; 
 */

int compile_data(char buffer[max], FILE *fp2){
	char *dc_loc;
	char c[max];
	int i;
	char *token;
	int found = 0;
	
	
	if(strstr(buffer,".data") != NULL){ 
		dc_loc = (strstr(buffer,".data") + 5); /*Locating the ".data" word;*/
		strcpy(c, dc_loc);
		token = strtok(c, ",");
		found = 1;
		
		for(i = 0; i < max && token != NULL; i++){
			fprintf(fp2,"%d\n",atoi(token));
			token = strtok(NULL, ",");
		}
		
	}
	return found;
}	

/***
 * @function: compile_string
 
 * @param a string called buffer containing A line in a file;
 * @param File fp2 pointing at the file we use to contain .data and .string words;
 
 
 * @returns void;
 
 * @description: 
 *	The function locates the first mention of the word ".string" in the buffer and then saves the string; 
 */


int compile_string(char buffer[max], FILE *fp2){
	int i;
	int j, found = 0;
	char word[10] = ".string";
	int index = 0;
	int start_index;
	int stop_index;
	int num_of_apo;

	
   while(buffer[index] != '\0')
   {
        /* If first character of word matches with the given string */
        if(buffer[index] == word[0])
        {
            /* Match entire word with current found index */
            j=0;
            found = 1;
            while(word[j] != '\0')
            {
                if(buffer[index + j] != word[j])
                {
                    found = 0;
                    break;
                }
                
                j++;
            }
   	  }
        
        /* If the word is found then get out of loop */
        if(found == 1)
        {
            break;
        }
        index++;
    }
    

    if(found == 1) /*The word - ".string" was found*/
    {
    	num_of_apo = 0;
    	
    	
    	for(i = index + strlen(word); i < strlen(buffer); i++){
    	
    		if(num_of_apo == 2){ /*We already have 2 apostrophe then we start to print the word*/
    			stop_index = i;
    			break;
    		}
    		
    		if(buffer[i] == '"' && num_of_apo == 0){ /*Finding the first apostrophe*/
    			start_index = i;
    		}
    		
    		if(buffer[i] == '"'){ /*Finding an apostrophe*/
    			num_of_apo = num_of_apo + 1;
    		}
    		
    	}
    	
    	if(num_of_apo < 2){
    		printf("Not enough apostrophes\n");
    		return -1;
    	}
    
       for(i = start_index + 1; i < stop_index - 1; i++){  /*Printing the word*/
       	fprintf(fp2,"%d\n", buffer[i]);
       }
     
       
    }
    return found;
}






            







