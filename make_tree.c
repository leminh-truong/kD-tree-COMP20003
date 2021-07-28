/** *********
* This file contains functions that enable the creation of an empty KD - tree,
* the insertion of new data in the form of structures into the tree and the 
* searching of information in the tree using standard inputs as keys to find
* the queried points' nearest neighbor or data points within a queried
* radius.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 2
******* */

#include "header.h"

/** The following functions are shared by codes both stage 1 and stage 2 of 
the assignment. 
* */

/* Calculate the squared distance between coordinates of queried points
* and coordinates of the current tree node. */
double compare(double key1, double key2, double query1, double query2){
	
	double dist_x = pow(key1-query1,DIMENSION);
	double dist_y = pow(key2-query2,DIMENSION);
	double dist = sqrt(dist_x + dist_y);
	
	return dist;
}

/* Create an empty KD - Tree. */
tree_t
*make_empty_tree(void){
	
	tree_t *tree;
	
	tree = malloc(sizeof(*tree));
	assert(tree!=NULL);
	
	tree->root = NULL;
	
	return tree;
}

/* Insert new data as nodes into KD - Tree. 
* */
tree_t 
*insert_into_tree(tree_t *tree, company_t *value){
	
	treenode_t *new;
	new = malloc(sizeof(*new));
	assert(new!= NULL && tree != NULL);
	
	new->x = atof(value->x_coordinate);
	new->y = atof(value->y_coordinate);
	new->left = NULL;
	new->right = NULL;
	new->chain = NULL;
	
	tree->root = fill_tree(tree->root, new, value, 0);
	
	return tree;
}

/* Recursive function to insert new data as nodes into KD - Tree recursively.
* */
treenode_t
*fill_tree(treenode_t *node, treenode_t *insert, company_t *value, int depth){
	
	/* Insert the new data as a node into the KD - Tree when an empty node is
	found. */
	if(node == NULL){
		insert->depth = depth;
		insert->x = atof(value->x_coordinate);
		insert->y = atof(value->y_coordinate);
		
		/* Create a linked list with the new data as the first member for
		chaining duplicate data. */ 
		insert->chain = make_empty_list();
		insert->chain = insert_into_list(insert->chain, *value);
		return insert;
	}
	
	/* Compare x or y depending on the depth of the node being visited, and 
	traverse to the suitable branch based on the x or y of the node being 
	inserted and the node being visited. */
	else if(depth % DIMENSION == 0){
		if(fabs(node->x - insert->x) < EPSILON){
			if(fabs(node->y - insert->y) < EPSILON){
				
				/* Chain duplicates into a linked list. */
				node->chain = insert_into_list(node->chain, *value);
				free(insert);
			}else{
				node->right = fill_tree(node->right, insert, value, depth + 1);
			}
		}
		else if(insert->x < node->x){
			node->left = fill_tree(node->left, insert, value, depth+1);
		}
		else{
			node->right = fill_tree(node->right, insert, value, depth+1);
		}
	}
	else if(depth % DIMENSION != 0){
		if(fabs(node->y - insert->y) < EPSILON){
			if(fabs(node->x- insert->x) < EPSILON){
				
				/* Chain duplicates into a linked list. */
				node->chain = insert_into_list(node->chain, *value);
				free(insert);
			}else{
				node->right = fill_tree(node->right, insert, value, depth + 1);
			}
		}
		else if(insert->y < node->y){
			node->left = fill_tree(node->left, insert, value, depth + 1);
		}
		else{
			node->right = fill_tree(node->right, insert, value, depth + 1);
		}
	}
	return node;
}

/* Search the KD - Tree to find the nearest neighbor of the queried point.
* */
void search_tree(tree_t *tree, char *x, char *y, int *comparisons, FILE *file){
	assert(tree != NULL);
	treenode_t *nearest;
	double dist;
	dist = compare(tree->root->x, tree->root->y,atof(x), atof(y));
	nearest = tree->root;
	*comparisons = *comparisons + 1;
	
	/* Compare the root's key to the query to decide which branch of the root
	to proceed. */
	if(fabs(tree->root->x - atof(x)) > dist){
		
		/* Go either branch depending on whether the query is greater or less
		* than the root's key. */
		if(atof(x) < tree->root->x){
			nearest = recursive_search_tree(tree->root->left, nearest, atof(x), 
				atof(y), &dist, comparisons);
		}else if(atof(x) >= tree->root->x){
			nearest = recursive_search_tree(tree->root->right, nearest, atof(x),
				atof(y), &dist, comparisons);
		}
	}
	else{
		/* Proceed down both branches of the root node. */
		nearest = recursive_search_tree(tree->root->left, nearest, atof(x), 
			atof(y), &dist, comparisons);
		nearest = recursive_search_tree(tree->root->right, nearest, atof(x), 
			atof(y), &dist, comparisons);
	}
	print_detail(nearest->chain->head, x, y, file);
}

/* Search the KD - Tree to find the nearest neighbor of the queried point 
* via recursion.
*/
treenode_t *recursive_search_tree(treenode_t *root, treenode_t *nearest, 
	double x, double y, double* dist, int *comparisons){
	
	if(root == NULL){
		return nearest;
	}
	double new_dist;
	new_dist = compare(x, y, root->x, root->y);
	*comparisons += 1;
	
	/* Save the current nearest distance and the current nearest neighbor. */
	if(new_dist < *dist){
		*dist = new_dist;
		nearest = root;
	}
	
	/* Based on the current node's depth, compare the distance between the
	* current node's key and the query and the current best distance. */
	if(root->depth % 2 == 0){
		if(fabs(root->x - x) > *dist){
			
			/* Proceed down either branch depending on whether the query is 
			* greater or less than the current node's key.*/
			if(x < root->x){
				nearest = recursive_search_tree(root->left, nearest, 
					x, y, dist, comparisons);
			}
			else if(x >= root->x){
				nearest = recursive_search_tree(root->right, nearest, 
					x, y, dist, comparisons);
			}
		}
		else{
			
			/* Proceed down both branches if the distance between the current
			* node's key and the query is lower or equal to the current best 
			* distance. */
			nearest = recursive_search_tree(root->left, nearest, 
				x, y, dist, comparisons);
			nearest = recursive_search_tree(root->right, nearest, 
				x, y, dist, comparisons);
		}
	}
	
	else if(root->depth%2 != 0){
		if(fabs(root->y - y) > *dist){
			
			/* Go either branch depending on whether the query is greater or
			* less than the current node's key.*/
			if(y < root->y){
				nearest = recursive_search_tree(root->left, nearest, 
					x, y, dist, comparisons);
			}
			else if(y >= root->y){
				nearest = recursive_search_tree(root->right, nearest, 
					x, y, dist, comparisons);
			}
		}
		else{
			
			/* Proceed down both branches if the distance between the current
			* node's key and the query is lower or equal to the current best 
			* distance. */
			nearest = recursive_search_tree(root->left, nearest, 
				x, y, dist, comparisons);
			nearest = recursive_search_tree(root->right, nearest, 
				x, y, dist, comparisons);
		}
	}
	return nearest;
}

/* Search the KD - Tree to find all data points that are within the queried
* radius of the queried point.
*/
void radius_search_tree(tree_t *tree, char *x, char *y, char *radius, 
	int *comparisons, FILE *file){
	assert(tree != NULL);
	treenode_t *nearest;
	int found = 0;
	nearest = NULL;
	
	nearest = radius_recursive_search_tree(tree->root, nearest, x, y, radius, 
		comparisons, &found, file);
	
	if(found == 0){
		fprintf(file,"%s %s %s --> NOT FOUND\n", x, y, radius);
	}
	fprintf(file, "\n");
}

/* Search the KD - Tree to find all data points that are within the queried
* radius of the queried point via recursion.
*/
treenode_t *radius_recursive_search_tree(treenode_t *root, treenode_t *nearest,
	char *x, char *y, char *radius, int *comparisons, int *found, FILE *file){

	if(root == NULL){
		return nearest;
	}
	
	*comparisons = *comparisons + 1;
	double new_dist;
	new_dist = compare(atof(x), atof(y), root->x, root->y);
	
	if(new_dist <= atof(radius)){
		*found = 1;
		nearest = root;
		
		/* Print the details of all the data at every node whose distance 
		* is smaller than the queried radius. */
		print_detail_radius(nearest->chain->head, x, y, radius, file);
		
		/* Proceed down both branches of the current node when if it is a
		* matching node. */
		nearest = radius_recursive_search_tree(root->left, nearest, 
			x, y, radius, comparisons, found, file);
		nearest = radius_recursive_search_tree(root->right, nearest, 
			x, y, radius, comparisons, found, file);
	}
	
	/* If the current node is not within the queried radius to the queried
	* point, depending on the its depth, compare the distance between the 
	* current node's key and the query with the radius.*/
	else if(root->depth % DIMENSION == 0){
		if(fabs(root->x - atof(x)) > atof(radius)){
			
			/*Proceed down either branch depending on whether the query is 
			* less or greater than the current node's key. */
			if(atof(x) < root->x){
				nearest = radius_recursive_search_tree(root->left, nearest, 
					x, y, radius, comparisons, found, file);
			}
			else if(atof(x) >= root->x){
				nearest = radius_recursive_search_tree(root->right, nearest, 
					x, y, radius, comparisons, found, file);
			}
		}
		else if(fabs(root->x - atof(x)) <= atof(radius)){
			
			/* Proceed down both branches if the distance between the current
			* node's key and the query is lower or equal to the radius. */
			nearest = radius_recursive_search_tree(root->left, nearest, 
				x, y, radius, comparisons, found, file);
			nearest = radius_recursive_search_tree(root->right, nearest, 
				x, y, radius, comparisons, found, file);
		}
	}
	
	else if(root->depth % DIMENSION != 0){
		if(fabs(root->y - atof(y)) > atof(radius)){
			
			/*Proceed down either branch depending on whether the query is 
			* less or greater than the current node's key. */
			if(atof(y) < root->y){
				nearest = radius_recursive_search_tree(root->left, nearest, 
					x, y, radius, comparisons, found, file);
			}
			else if(atof(y) >= root->y){
				nearest = radius_recursive_search_tree(root->right, nearest, 
					x, y, radius, comparisons, found, file);
			}
		}
		else if(fabs(root->y - atof(y)) <= atof(radius)){
			
			/* Proceed down both branches if the distance between the current
			* node's key and the query is lower or equal to the radius. */
			nearest = radius_recursive_search_tree(root->right, nearest, 
				x, y, radius, comparisons, found, file);
			nearest = radius_recursive_search_tree(root->left, nearest, 
				x, y, radius, comparisons, found, file);
		}
	}
	return nearest;
}
/* Free the memory allocated to the KD - Tree.
* */
void free_tree(tree_t *tree){
	assert(tree != NULL);
	recursive_free_tree(tree->root);
	free(tree);
}

/* Free every node in the KD - Tree via recursion.
*/
void recursive_free_tree(treenode_t *root){
	if(root){
		recursive_free_tree(root->left);
		recursive_free_tree(root->right);
		if(root->chain->head != NULL){
			/* Free the linked list in every tree node. */
			free_list(root->chain);
			root->chain = NULL;
		}
		free(root);
	}
}

/* =============================================================================
   Functions above are based on functions written by Alistair Moffat, as an 
   example for the book "Programming, Problem Solving, and Abstraction with C", 
   Pearson Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974. 
   
   These functions have been modified for creating and operating on KD - Trees,
   which is the purpose of this assignment. All modifications made are my own 
   personal work.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ========================================================================== */
