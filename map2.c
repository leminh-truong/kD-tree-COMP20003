/** *************************************
* The main file of the program, which creates a KD-Tree from data read from 
* an external data file and and after performing radius search for the queried
* point, outputs the information of points that are within the queried radius 
* of the queried point to a text file.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 2
***************************************** **/

#include "header.h"

int main(int argc, char* argv[]){
	
	char *trading_name,*buffer_str, *token;
	char *filename;
	char *output;
	char *x, *y, *radius;
	company_t companies;
	tree_t *company_tree;
	int column, token_num = 0, quote = 0, i = 0, counter = 0, missing = 0;
	size_t len;
	FILE *company_file, *output_file;
	
	buffer_str = (char*)malloc(BUFFER_SIZE*sizeof(buffer_str));
	assert(buffer_str != NULL);
	trading_name = (char*)malloc(MAX_CHAR*sizeof(trading_name));
	assert(trading_name != NULL);
	x = (char*)malloc(MAX_CHAR*sizeof(x));
	assert(x != NULL);
	y = (char*)malloc(MAX_CHAR*sizeof(y));
	assert(y != NULL);
	radius = (char*)malloc(MAX_CHAR*sizeof(radius));
	assert(radius != NULL);
	company_tree = make_empty_tree();
	
	/* Obtain names of the data file (e.g. csv file) and the output file 
	* respectively. */
	filename = argv[1];
	output = argv[2];
	
	/* Check if the output file is properly opened. */
	if((output_file = fopen(output,"w")) == NULL){
		fprintf(stderr, "cannot write to %s\n", output);
		exit(EXIT_FAILURE);
	}
	
	/* Check if the data file is properly opened. */
	if((company_file = fopen(filename, "r")) == NULL){
		fprintf(stderr, "cannot read from %s\n",filename);
		exit(EXIT_FAILURE);
	}
	else{
		/* Loop through every line of information in the data file 
		* (e.g. csv file) and  process them. */
		while(fgets(buffer_str,BUFFER_SIZE,company_file) != NULL){
			counter++;
			
			/* Skip the first line, which contains only the field names. */
			if(counter == 1){
				continue;
			}
			
			i = 0;
			column = 0;
			
			
			/* Check to see if the data line being read is missing line 
			* terminators such as "\r" and "\n", and process the line based on
			* what is missing as well as assigning tags based on what is 
			* missing. */
			len = strlen(buffer_str);
			if(len>0 && buffer_str[len-1] != '\n'&& buffer_str[len-1]!= '\r'){
				missing = 2;
				strcat(buffer_str, "\r");
				strcat(buffer_str, "\n");
			}else if(len>0 && buffer_str[len-1] != '\n' && 
				buffer_str[len-1] == '\r'){
				missing = 1;
				strcat(buffer_str,"\n");
			}else if(len>0 && buffer_str[len -1] == '\n' && 
				buffer_str[len-2] != '\r'){
				missing = 3;
			}
			
			token = (char*)malloc((len+1)*sizeof(token));
			assert(token != NULL);
			
			/*Partition the data line into values and add them into the 
			* predefined structure "companies" based on what fields they belong 
			* to in the data file. */
			while(buffer_str[i]){
				token[token_num++] = buffer_str[i];
				
				/*Process the values based on the warning tags assigned above, 
				and add them to the predefined structure "companies".*/
				if(!quote && (buffer_str[i] == ',' || buffer_str[i] == '\n' || 
					buffer_str[i] == '\0')){
					if((missing == 1||missing == 3) && column == 10){
						token[token_num - 1] = '\0';
						token_num = 0;
					} else if(missing == 2 && column == 10){
						token[token_num - 2] = '\0';
						token_num = 0;
					} else if (missing == 0 && column == 10){
						token[token_num-2] = '\0';
						token_num = 0;
					} else{
						token[token_num - 1] = '\0';
						token_num = 0;
					}
					make_struct(column++, &companies, token);
				}
				
				/* Process values contained in double quotes. */
				if(buffer_str[i] == '"' && buffer_str[i+1] != '"'){
					token_num--;
					quote = !quote;
				}
				
				/*Process values contained in double quotes that also
				* have double quotes. */
				if(buffer_str[i] == '"' && buffer_str[i+1] == '"'){
					i++;
				}
				
				i++;
			}
			
			free(token);
			/* ==============================================================
			* The above sequence of code is designed by Robert Torok on 
			* September 14th, 2018 in the website "codingboost: Parsing CSV 
			* Files in C" 
			
			* See https://codingboost.com/parsing-csv-files-in-c) for more
			* information
			
			* The sequence of code has been modified for the purpose of this 
			* assignment, and the modifications are my own personal work.
			================================================================= */
			company_tree = insert_into_tree(company_tree, &companies);
		}
	}
	
	fclose(company_file);
	
	/* Read inputs from users and process them into keys to search the 
	* KD-Tree with. */
	
	while(fgets(trading_name, MAX_CHAR+1, stdin) != NULL){
		int comparisons = 0;
		if(trading_name[0] == ' ' || trading_name[0] == '\n'){
			continue;
		}
		
		len = strlen(trading_name);
		if(len >0 && trading_name[len-1] == '\n'){
			trading_name[--len] = '\0';
		}
		
		/* Perform radius search for the queried point with the queried
		* radius. */
		if(sscanf(trading_name,"%s %s %s", x, y, radius) == 3){
			radius_search_tree(company_tree, x, y, radius, &comparisons, 
				output_file);
		}
		printf("%s %s %s --> %d\n", x, y, radius, comparisons);
	}
	
	fclose(output_file);
	
	/* Free every allocated memory in the main function. */
	free(buffer_str);
	free(trading_name);
	free(x);
	free(y);
	free(radius);
	free_tree(company_tree);
	return 0;
}