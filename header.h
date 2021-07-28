/** ************************************ 
* This file is the header file of the program, which contains
* all the necessary declarations for the program to function.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 2
**************************************** */

#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX_CHAR 128      /* Maximum characters of a value in a single field. */
#define MAX_COMPANIES 19117   /* Maximum number of data lines in a data file. */
#define BUFFER_SIZE 500 /* Maximum size of a data line when read as a string. */
#define EPSILON 1.0e-9    /* Tolerance for comparing double values' equality. */
#define DIMENSION 2                 /* Number of dimensions of the KD - Tree. */

/*Structure of a single company read from the data file.*/
typedef struct{
	char *census_year, *block_id, *property_id, *base_prop_id, *industry_code;
	char *x_coordinate, *y_coordinate;
	char *small_area, *name, *description, *location;
}company_t;


/** The following structures are structures of the KD - Tree and the linked list. 
* These structure are defined by Alistair Moffat, as an example for the book 
* 'Programming, Problem Solving, and Abstraction with C', Pearson Custom Books, 
* Sydney, Australia, 2002; revised edition 2012, ISBN 9781486010974.

* These structures have been modified for the purpose of this assignment. The
* modifications are my own personal work.

* See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
  information.

* Prepared December 2012 for the Revised Edition. 
**/
typedef struct listnode listnode_t;

struct listnode{
	company_t company;
	listnode_t *next;
};

typedef struct{
	listnode_t *head;
	listnode_t *foot;
}list_t;

typedef struct treenode treenode_t;

struct treenode {
	int depth;
	double x, y;
	list_t *chain;
	treenode_t *right;
	treenode_t *left;
};

typedef struct {
	treenode_t *root;
}tree_t;

/** *********************************************************** **/

/** Function prototypes for functions contained in files 'make_tree.c', 
* 'utilities.c'  and 'make_dict.c'. 
**/

/* Function prototypes for file 'utilities.c'. These are used for creating
* structures of functions and print details of data chained to the same node.
*/
void make_struct(int column, company_t *companies, char *token);
void print_detail(listnode_t *head, char *x, char *y, FILE *filename);
void print_detail_radius(listnode_t *head, char *x, char *y, char *radius, 
	FILE *file);

/* Function prototypes for file 'make_tree.c'. These are used for creating,
* searching and freeing KD-Tree for both stage 1 and stage 2 of the 
* assignment. 
*/
double compare(double key1, double key2, double query1, double query2);
tree_t *make_empty_tree(void);
tree_t *insert_into_tree(tree_t *tree, company_t *value);
treenode_t *fill_tree(treenode_t *node, treenode_t *insert, company_t *value, 
	int depth);
void search_tree(tree_t *tree, char *x, char *y, int *comparisons, FILE *file);
treenode_t *recursive_search_tree(treenode_t *root, treenode_t *nearest, 
	double x, double y, double* dist, int* comparisons);
void radius_search_tree(tree_t *tree, char *x, char *y, char *radius, 
	int *comparisons, FILE *file);
treenode_t *radius_recursive_search_tree(treenode_t *root, treenode_t *nearest, 
	char *x, char *y, char *radius, int *comparisons, int *found, FILE *file);
void free_tree(tree_t *tree);
void recursive_free_tree(treenode_t *root);

/* Function prototypes for file 'make_dict.c'. These are used for creating
* linked lists to chain data with duplicate coordinates to a tree node.
*/
list_t *make_empty_list(void);
list_t *insert_into_list(list_t *list, company_t value);
void free_list(list_t *list);

#endif