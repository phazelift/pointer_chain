#ifndef NODES_H
#define NODES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// #include "../string/string.h"


struct s_node {
	void* data;
	struct s_node* prev;
	struct s_node* next;
};

struct s_nodes {
	bool stackmode;
	int count;
	struct s_node* first;
	struct s_node* current;
};

#define DEFAULT_NODES (struct s_nodes){ .count= 0, .first= NULL, .current= NULL }


struct s_nodes* newNodes();
struct s_nodes* newStack();
static void addFirstNode( struct s_nodes*, struct s_node* );
static void addNextNode( struct s_nodes*, struct s_node* );
struct s_node* addNode( struct s_nodes*, void* );
#define pushNode addNode
void removeNode( struct s_nodes*, struct s_node** );
void popNode( struct s_nodes* );
void disposeNodes( struct s_nodes* );
#define resetNodes disposeNodes
int getIndex( struct s_nodes* nodes, struct s_node* node );
int getDataIndex( struct s_nodes* nodes, const void* );
struct s_node* getNode( struct s_nodes*, int );


#endif // NODES_H
