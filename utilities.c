/** ******************
* This file contains functions that are used for creating structs from data
* read from a data file and printing information of matching tree nodes in
* the KD-Tree for both nearest neighbor search and radius search.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 2
******************* **/

#include "header.h"

/* Create a structure containing data of a company, 
* which is obtained from the data file.*/ 

void make_struct(int column, company_t *companies, char *token){
	
	if(column == 0){
		companies->census_year = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->census_year != NULL);
		strcpy(companies->census_year, token);
	}
	
	if(column == 1){
		companies->block_id = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->block_id != NULL);
		strcpy(companies->block_id, token);
	}
	
	if(column == 2){
		companies->property_id = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->property_id != NULL);
		strcpy(companies->property_id, token);
	}
	
	if(column == 3){
		companies->base_prop_id = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->base_prop_id != NULL);
		strcpy(companies->base_prop_id, token);
	}
	
	if(column == 4){
		companies->small_area = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->small_area != NULL);
		strcpy(companies->small_area, token);
	}
	
	if(column == 5){
		companies->name = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->name != NULL);
		strcpy(companies->name, token);
	}
	
	if(column == 6){
		companies->industry_code = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->industry_code != NULL);
		strcpy(companies->industry_code, token);
	}
	
	if(column == 7){
		companies->description =(char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->description != NULL);
		strcpy(companies->description, token);
	}
	
	if(column == 8){
		companies->x_coordinate = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->x_coordinate != NULL);
		strcpy(companies->x_coordinate, token);
	}
	
	if(column == 9){
		companies->y_coordinate = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->y_coordinate != NULL);
		strcpy(companies->y_coordinate, token);
	}
	
	if(column == 10){
		companies->location = (char*)malloc((strlen(token)+1)*sizeof(char*));
		assert(companies->location != NULL);
		strcpy(companies->location, token);
	}
}

/* Print the information of the tree node that is the nearest neighbour of
* the queried point to a text file. 
* */


void print_detail(listnode_t *head, char *x, char *y, FILE *file){

	listnode_t *curr_node = head;
	
	while(curr_node != NULL){
		fprintf(file,"%s %s --> ",  x, y);
		fprintf(file,"Census year: %s || ", 
			curr_node->company.census_year);
		fprintf(file,"Block ID: %s || ", 
			curr_node->company.block_id);
		fprintf(file,"Property ID: %s || ", 
			curr_node->company.property_id);
		fprintf(file,"Base property ID: %s || ", 
			curr_node->company.base_prop_id);
		fprintf(file,"CLUE small area: %s || ", 
			curr_node->company.small_area);
		fprintf(file,"Trading Name: %s || ",
			   curr_node->company.name);
		fprintf(file,"Industry (ANZSIC4) code: %s || ", 
			curr_node->company.industry_code);
		fprintf(file,"Industry (ANZSIC4) description: %s || ", 
			curr_node->company.description);
		fprintf(file,"x coordinate: %s || ", 
			curr_node->company.x_coordinate);
		fprintf(file,"y coordinate: %s || ", 
			curr_node->company.y_coordinate);
		fprintf(file,"Location: %s || \n", 
			curr_node->company.location);
		curr_node = curr_node->next;
	}
	fprintf(file,"\n");
}

/* Print the information of the tree nodes that are within the queried radius
* of the queried point to a text file. 
* */
void print_detail_radius(listnode_t *head, char *x, char *y, char *radius, 
	FILE *file){

	listnode_t *curr_node = head;
	
	while(curr_node != NULL){
		fprintf(file,"%s %s %s --> ",  x, y, radius);
		fprintf(file,"Census year: %s || ", 
			curr_node->company.census_year);
		fprintf(file,"Block ID: %s || ", 
			curr_node->company.block_id);
		fprintf(file,"Property ID: %s || ", 
			curr_node->company.property_id);
		fprintf(file,"Base property ID: %s || ", 
			curr_node->company.base_prop_id);
		fprintf(file,"CLUE small area: %s || ", 
			curr_node->company.small_area);
		fprintf(file,"Trading Name: %s || ",
			   curr_node->company.name);
		fprintf(file,"Industry (ANZSIC4) code: %s || ", 
			curr_node->company.industry_code);
		fprintf(file,"Industry (ANZSIC4) description: %s || ", 
			curr_node->company.description);
		fprintf(file,"x coordinate: %s || ", 
			curr_node->company.x_coordinate);
		fprintf(file,"y coordinate: %s || ", 
			curr_node->company.y_coordinate);
		fprintf(file,"Location: %s || \n", 
			curr_node->company.location);
		curr_node = curr_node->next;
	}
}