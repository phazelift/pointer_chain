
#include "nodes.h"



struct s_nodes* newNodes( bool stackmode )
{
	struct s_nodes* nodes = malloc( sizeof(struct s_node) );
	*nodes = DEFAULT_NODES;
	nodes->stackmode = stackmode;
	return nodes;
}


static void addFirstNode( struct s_nodes* nodes, struct s_node* node )
{
	// let all point to the only element
	node->prev = node;
	node->next = node;
	nodes->first = node;
	nodes->current = node;
}

static void addNextNode( struct s_nodes* nodes, struct s_node* node )
{
	node->next = nodes->first;
	node->prev = nodes->first->prev;
	nodes->first->prev->next = node;
	nodes->first->prev = node;
	if ( nodes->stackmode ) nodes->current = node;
}


struct s_node* addNode( struct s_nodes* nodes, void* data )
{
	struct s_node* node = malloc( sizeof(struct s_node) );
	node->data = data;
	( nodes->count ) ? addNextNode(nodes, node) : addFirstNode(nodes, node);
	nodes->count++;
	return node;
}



void removeNode( struct s_nodes* nodes, struct s_node** node )
{
	if ( ! nodes->count ){
		puts( "nodes::removeNode - Warning - cannot remove, nodes is empty" );
		return;
	}

	if ( nodes->count == 1 )
	{
		free( *node );
	}
	else
	{
		struct s_node* prev = (*node)->prev;
		struct s_node* next = (*node)->next;

		prev->next = next;
		next->prev = prev;

		if ( (*node == nodes->current) && ! nodes->stackmode ) nodes->current = next;

		if ( *node == nodes->first || *node == nodes->current )
		{
			free( *node );
			if ( *node == nodes->first ) nodes->first = next;
			if ( nodes->stackmode ) nodes->current = prev;
		}
		else free( *node );
	}
	nodes->count--;
}



void popNode( struct s_nodes* nodes )
{
	removeNode( nodes, &(nodes->current) );
}



void disposeNodes( struct s_nodes* nodes )
{
	struct s_node** pp = &(nodes->first);
	while ( nodes->count > 0 )
	{
		free( *pp );
		nodes->count--;
		*pp = (*pp)->next;
	}
	*nodes = DEFAULT_NODES;
}



// returns the index (n-1) of node relative to the nodes->first index
int getIndex( struct s_nodes* nodes, struct s_node* node )
{
	const struct s_node* p = nodes->first;
	for ( int i = 0; i < nodes->count; i++ ) if ( p == node ) return i; else p =  p->next;
	return -1;
}


// returns the index (n-1) of node relative to the nodes->first index
int getDataIndex( struct s_nodes* nodes, const void* data )
{
	const struct s_node* p = nodes->first;
	for ( int i = 0; i < nodes->count; i++ )
	{
		int equal = memcmp( (const void*)p->data, data, sizeof(data) );
		if ( equal == 0 ) return i;
		p = p->next;
	}
	return -1;
}


struct s_node* getNode( struct s_nodes* nodes, int index )
{
	if ( index > (nodes->count - 1) || (index < 0) )
	{
		puts( "getNode - Warning, index is out of range!" );
		return NULL;
	}

	struct s_node* node = nodes->first;
	for ( int i = 0; i < index; i++ )
	{
		if ( i == index ) break;
		node = node->next;
	}
	return node;
}
