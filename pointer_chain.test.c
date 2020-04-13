#include <assert.h>
#include <stdbool.h>
#include "../string/string.h"
#include "./pointer_chain.h"


char** createStrings()
{
	char** strPtrArr = (char**) malloc( sizeof(char*) * 3 );
	strPtrArr[0] = createString( "Hola" );
	strPtrArr[1] = createString( "Mundo" );
	strPtrArr[2] = createString( "!" );
	return strPtrArr;
}


//
//	TESTS ARE IN SEQUENTIAL ORDER, APPLY CHANGE WITH CARE
//

void testChainInitialized( struct s_pointer_chain* chain )
{
	assert(
		chain->count == 0 &&
		chain->first == NULL &&
		__func__
	);
}



void loopChain( struct s_pointer_chain* chain )
{
	const struct s_link* link = chain->first;
	unsigned int times = chain->count;

	for ( int i = 0; i < times; i++ )
	{
		// printf( "looping -> %d == %s\n", i, link->data );
		assert(
			link->next->prev == link &&
			link->prev->next == link &&
			link->data &&
			__func__
		);
		link = link->next;
	}
}



void testStackMode()
{
	puts( "starting test stackmode" );

	char** str = createStrings();

	struct s_pointer_chain* chain = newStack();

	pushLink( chain, str[0] );
	assert(
		chain->current == chain->first &&
		chain->current == chain->first->prev &&
		chain->current == chain->first->next &&
		__func__
	);
	pushLink( chain, str[1] );
	assert(
		chain->current == chain->first->next &&
		chain->current == chain->first->prev &&
		__func__
	);

	pushLink( chain, str[2] );
	assert(
		chain->current == chain->first->next->next &&
		chain->current == chain->first->prev &&
		__func__
	);

	//
	// start removing chain
	//
	popLink( chain );
	puts( chain->current->data );
	assert(
		chain->current == chain->first->prev &&
		__func__
	);

	popLink( chain );
	puts( chain->current->data );
	assert(
		chain->current == chain->first->prev &&
		__func__
	);

	printf( "-->>> %d, %s\n", chain->count, chain->current->data );
	popLink( chain );
	assert(
		chain->count == 0 &&
		__func__
	);

	for ( int i = 0; i < 3; i++ ) free( str[i] );
	free( chain );
	puts( "done testing stackmode\n" );
}




void testAddFirstLink( struct s_pointer_chain* chain, char* str )
{
	struct s_link* link = addLink( chain, str );
	bool dataIsApplied = isEqualString( str, chain->first->data );
	dataIsApplied = dataIsApplied && isEqualString( str, link->data );
	assert(
		dataIsApplied &&
		chain->count == 1 &&
		link->prev == link &&
		link->next == link &&
		 __func__
	);
	loopChain( chain );
}


void testAddSecondLink( struct s_pointer_chain* chain, char* str )
{
	struct s_link* link = addLink( chain, str );
	bool dataIsApplied = isEqualString( str, chain->first->next->data );
	dataIsApplied = dataIsApplied && isEqualString( str, link->data );
	assert(
		dataIsApplied &&
		chain->count == 2 &&
		// current should not move to the newly created link
		chain->first->next == link &&
		chain->first->prev == link &&
		link->prev == chain->first &&
		link->next == chain->first &&
		 __func__
	);
	loopChain( chain );
}


void testAddThirdLink( struct s_pointer_chain* chain, char* str )
{
	struct s_link* link = addLink( chain, str );
	bool dataIsApplied = isEqualString( str, chain->first->prev->data );
	dataIsApplied = dataIsApplied && isEqualString( str, link->data );
	assert(
		dataIsApplied &&
		chain->count == 3 &&
		chain->first->next->next == link &&
		chain->first->prev == link &&
		link->prev == chain->first->prev->prev &&
		link->next == chain->first &&
		 __func__
	);
	loopChain( chain );
}


void testGetIndex( struct s_pointer_chain* chain )
{
		struct s_link* p = chain->first;
		int index;
		for ( int i = 0; i < chain->count; i++ )
		{
			index = getIndex( chain, p );
			assert( index == i );
			p = p->next;
		}
		if ( p != chain->first ) puts( __func__ );
}


//
// TODO:
//
// void testDisposeLink()
// {
// 	struct s_pointer_chain* chain = newPointerChain();
// 	char* str = createString( "HELLO WORLD!" );
// 	struct s_link* link = addLink( chain, str );
// 	disposeLink( &link );
// 	assert(
// 		link == NULL &&
// 		str != NULL &&
// 		__func__
// 	);
// 	free( chain );
// }


void testRemoveLink( struct s_pointer_chain* chain, struct s_link** link )
{
	struct s_link* prev = *link;

	removeLink( chain, link );
	assert(
		getIndex( chain, prev ) == -1 &&
		__func__
	);
	loopChain( chain );
}


void testGetDataIndex( struct s_pointer_chain* chain )
{
	int index0 = getDataIndex( chain, chain->first->data );
	char* failStr = createString( "" );
	int indexFail = getDataIndex( chain, failStr );
	assert(
		index0 == 0 &&
		indexFail == -1 &&
		__func__
	);
	free( failStr );
}


void testGetLink( struct s_pointer_chain* chain )
{
	struct s_link* link = getLink( chain, 1 );
	assert(
		link == chain->first->next &&
		link == chain->first->prev->prev &&
		__func__
	);
}


void testResetChain( struct s_pointer_chain* chain )
{
	resetChain( chain );
	assert(
		chain->count == 0 &&
		// chain->first == NULL &&
		__func__
	);
}



void testChain()
{
	puts( "start testing chain" );

	struct s_pointer_chain* chain = newPointerChain();

	testChainInitialized( chain );

	char** str = createStrings();

	puts( "starting to test adding chain.." );
	testAddFirstLink( chain, str[0] );
	loopChain( chain );
	testAddSecondLink( chain, str[1] );
	loopChain( chain );
	testAddThirdLink( chain, str[2] );
	loopChain( chain );
	puts( "done adding chain" );

	testGetIndex( chain );

	puts( "starting to remove chain.." );
	printf( "count before remove: %u, first is: %s\n", chain->count, chain->first->data );

	testRemoveLink( chain, &(chain->first) );
	printf( "count after remove: %u, first is now: %s\n", chain->count, chain->first->data );

	testRemoveLink( chain, &(chain->first) );
	printf( "count after remove: %u, first is now: %s\n", chain->count, chain->first->data );

	testRemoveLink( chain, &(chain->first) );
	printf( "count after remove last: %d\n", chain->count );
	puts( "testing removal of non-existing link, a warning should show on the next line" );
	testRemoveLink( chain, &(chain->first) );

	testAddFirstLink( chain, str[0] );
	testAddSecondLink( chain, str[1] );
	testAddThirdLink( chain, str[2] );

	testGetDataIndex( chain );
	testGetLink( chain );
	loopChain( chain );

	testResetChain( chain );

	loopChain( chain );

	// // cleanup strings
	for ( int i = 0; i < 3; i++ ) free( str[i] );
	free( chain );
	puts( "done testing chain\n" );
}


int main()
{

	testStackMode();
	testChain();

	puts( "Gratz, all tests completed successfully!" );
	return 0;
}
