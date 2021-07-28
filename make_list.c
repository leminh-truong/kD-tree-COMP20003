/** **************************************
* This file includes functions that create an empty linked list
* and chain duplicate data to one tree node in the form of a
* linked list.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 2
* ***********************************/

#include "header.h"

/*Create and empty linked list
* */
list_t
*make_empty_list(void){
	list_t *list;
	list = malloc(sizeof(*list));
	assert(list != NULL);
	
	list->head = NULL;
	list->foot = NULL;
	
	return list;
}


/* Free the memory allocated for the linked list as well as memory
* allocated for every node in the linked list. */
void free_list(list_t *list) {

	listnode_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev->company.census_year);
		free(prev->company.block_id);
		free(prev->company.property_id);
		free(prev->company.base_prop_id);
		free(prev->company.small_area);
		free(prev->company.name);
		free(prev->company.industry_code);
		free(prev->company.description);
		free(prev->company.x_coordinate);
		free(prev->company.y_coordinate);
		free(prev->company.location);
		free(prev);
	}
	free(list);
}


/* Insert data read from data file into the linked list to chain
* duplicate data into one tree node.
* */
list_t *insert_into_list(list_t *list, company_t value) {

	listnode_t *new;
	new = (listnode_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->company = value;
	new->next = NULL;
	if (list->foot==NULL) {
		 /*(this is the first insertion into the list)*/
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

/* =============================================================================
   Functions above are written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974. 
   
   These functions have been modified for the purpose of this assignment. All 
   modifications made are my own personal work.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ========================================================================== */
