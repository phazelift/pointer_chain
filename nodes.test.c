#include <assert.h>
#include <stdbool.h>
#include "../string/string.h"
#include "./nodes.h"


//
//	TESTS ARE IN SEQUENTIAL ORDER, APPLY CHANGE WITH CARE
//


void testNodesInitialized( struct s_nodes* nodes )
{
	assert(
		nodes->count == 0 &&
		nodes->first == NULL &&
		__func__
	);
}



void loopNodes( struct s_nodes* nodes )
{
	const struct s_node* p = nodes->first;
	unsigned int times = nodes->count;

	for ( int i = 0; i < times; i++ )
	{
		// printf( "looping -> %d == %s\n", i, p->data );
		assert(
			p->next->prev == p &&
			p->prev->next == p &&
			p->data &&
			__func__
		);
		p = p->next;
	}
}



void testStackMode()
{
	char* str[3] = {
		 createString( "Hola" )
		,createString( "Mundo" )
		,createString( "!" )
	};

	struct s_nodes* nodes = newNodes( true );

	pushNode( nodes, str[0] );
	assert(
		nodes->current == nodes->first &&
		nodes->current == nodes->first->prev &&
		nodes->current == nodes->first->next &&
		__func__
	);
	pushNode( nodes, str[1] );
	assert(
		nodes->current == nodes->first->next &&
		nodes->current == nodes->first->prev &&
		__func__
	);

	pushNode( nodes, str[2] );
	assert(
		nodes->current == nodes->first->next->next &&
		nodes->current == nodes->first->prev &&
		__func__
	);

	//
	// start removing nodes
	//
	popNode( nodes );
	puts( nodes->current->data );
	assert(
		nodes->current == nodes->first->prev &&
		__func__
	);

	popNode( nodes );
	puts( nodes->current->data );
	assert(
		nodes->current == nodes->first->prev &&
		__func__
	);

	printf( "-->>> %d, %s\n", nodes->count, nodes->current->data );
	popNode( nodes );
	assert(
		nodes->count == 0 &&
		__func__
	);

	for ( int i = 0; i < 3; i++ ) free( str[i] );
	free( nodes );
}




void testAddFirstNode( struct s_nodes* nodes, char* str )
{
	struct s_node* node = addNode( nodes, str );
	bool dataIsApplied = isEqualString( str, nodes->first->data );
	dataIsApplied = dataIsApplied && isEqualString( str, node->data );
	assert(
		dataIsApplied &&
		nodes->count == 1 &&
		node->prev == node &&
		node->next == node &&
		 __func__
	);
	loopNodes( nodes );
}


void testAddSecondNode( struct s_nodes* nodes, char* str )
{
	struct s_node* node = addNode( nodes, str );
	bool dataIsApplied = isEqualString( str, nodes->first->next->data );
	dataIsApplied = dataIsApplied && isEqualString( str, node->data );
	assert(
		dataIsApplied &&
		nodes->count == 2 &&
		// current should not move to the newly created node
		nodes->first->next == node &&
		nodes->first->prev == node &&
		node->prev == nodes->first &&
		node->next == nodes->first &&
		 __func__
	);
	loopNodes( nodes );
}


void testAddThirdNode( struct s_nodes* nodes, char* str )
{
	struct s_node* node = addNode( nodes, str );
	bool dataIsApplied = isEqualString( str, nodes->first->prev->data );
	dataIsApplied = dataIsApplied && isEqualString( str, node->data );
	assert(
		dataIsApplied &&
		nodes->count == 3 &&
		nodes->first->next->next == node &&
		nodes->first->prev == node &&
		node->prev == nodes->first->prev->prev &&
		node->next == nodes->first &&
		 __func__
	);
	loopNodes( nodes );
}


void testGetIndex( struct s_nodes* nodes )
{
		struct s_node* p = nodes->first;
		int index;
		for ( int i = 0; i < nodes->count; i++ )
		{
			index = getIndex( nodes, p );
			assert( index == i );
			p = p->next;
		}
		if ( p != nodes->first ) puts( __func__ );
}


// void testDisposeNode()
// {
// 	struct s_nodes* nodes = newNodes();
// 	char* str = createString( "HELLO WORLD!" );
// 	struct s_node* node = addNode( nodes, str );
// 	disposeNode( &node );
// 	assert(
// 		node == NULL &&
// 		str != NULL &&
// 		__func__
// 	);
// 	free( nodes );
// }


void testRemoveNode( struct s_nodes* nodes, struct s_node** node )
{
	struct s_node* prev = *node;

	removeNode( nodes, node );
	assert(
		getIndex( nodes, prev ) == -1 &&
		__func__
	);
	loopNodes( nodes );
}


void testGetDataIndex( struct s_nodes* nodes )
{
	int index0 = getDataIndex( nodes, nodes->first->data );
	char* failStr = createString( "" );
	int indexFail = getDataIndex( nodes, failStr );
	assert(
		index0 == 0 &&
		indexFail == -1 &&
		__func__
	);
	free( failStr );
}


void testGetNode( struct s_nodes* nodes )
{
	struct s_node* node = getNode( nodes, 1 );
	assert(
		node == nodes->first->next &&
		node == nodes->first->prev->prev &&
		__func__
	);
}


void testResetNodes( struct s_nodes* nodes )
{
	resetNodes( nodes );
	assert(
		nodes->count == 0 &&
		// nodes->first == NULL &&
		__func__
	);
}


void testNodes( struct s_nodes* nodes )
{
	testNodesInitialized( nodes );

	char* str[3] = {
		 createString( "Hola" )
		,createString( "Mundo" )
		,createString( "!" )
	};

	puts( "starting to test adding nodes.." );
	testAddFirstNode( nodes, str[0] );
	loopNodes( nodes );
	testAddSecondNode( nodes, str[1] );
	loopNodes( nodes );
	testAddThirdNode( nodes, str[2] );
	loopNodes( nodes );
	puts( "done adding nodes" );

	testGetIndex( nodes );

	puts( "starting to remove nodes.." );
	printf( "count before remove: %u, first is: %s\n", nodes->count, nodes->first->data );

	testRemoveNode( nodes, &(nodes->first) );
	printf( "count after remove: %u, first is now: %s\n", nodes->count, nodes->first->data );

	testRemoveNode( nodes, &(nodes->first) );
	printf( "count after remove: %u, first is now: %s\n", nodes->count, nodes->first->data );

	testRemoveNode( nodes, &(nodes->first) );
	printf( "count after remove last: %d\n", nodes->count );
	puts( "testing removal of non-existing node, a warning should show on the next line" );
	testRemoveNode( nodes, &(nodes->first) );

	testAddFirstNode( nodes, str[0] );
	testAddSecondNode( nodes, str[1] );
	testAddThirdNode( nodes, str[2] );

	testGetDataIndex( nodes );
	testGetNode( nodes );
	loopNodes( nodes );

	testResetNodes( nodes );

	loopNodes( nodes );

	// // cleanup strings
	for ( int i = 0; i < 3; i++ ) free( str[i] );
}


int main()
{
	struct s_nodes* nodes = newNodes( false );

	puts( "starting to test stackmode" );
	testStackMode();
	puts( "done testing stackmode" );

	testNodes( nodes );
	free( nodes );

	puts( "Gratz, all tests completed successfully!" );
	return 0;
}
