#include "pointer_chain.h"



struct s_pointer_chain* newPointerChain()
{
	struct s_pointer_chain* chain = malloc( sizeof(struct s_link) );
	*chain = DEFAULT_LINKS;
	chain->stackmode = false;
	return chain;
}


struct s_pointer_chain* newStack()
{
	struct s_pointer_chain* chain = newPointerChain();
	chain->stackmode = true;
	return chain;
}



static void addFirstLink( struct s_pointer_chain* chain, struct s_link* link )
{
	// let all point to the only element
	link->prev = link;
	link->next = link;
	chain->first = link;
	chain->current = link;
}



static void addNextLink( struct s_pointer_chain* chain, struct s_link* link )
{
	link->next = chain->first;
	link->prev = chain->first->prev;
	chain->first->prev->next = link;
	chain->first->prev = link;
	if ( chain->stackmode ) chain->current = link;
}



struct s_link* addLink( struct s_pointer_chain* chain, void* data )
{
	struct s_link* link = malloc( sizeof(struct s_link) );
	link->data = data;
	( chain->count ) ? addNextLink(chain, link) : addFirstLink(chain, link);
	chain->count++;
	return link;
}



void removeLink( struct s_pointer_chain* chain, struct s_link** link )
{
	if ( ! chain->count ){
		puts( "chain::removeLink - Warning - cannot remove, chain is empty" );
		return;
	}

	if ( chain->count == 1 )
	{
		free( *link );
	}
	else
	{
		struct s_link* prev = (*link)->prev;
		struct s_link* next = (*link)->next;

		prev->next = next;
		next->prev = prev;

		if ( (*link == chain->current) && ! chain->stackmode ) chain->current = next;

		if ( *link == chain->first || *link == chain->current )
		{
			free( *link );
			if ( *link == chain->first ) chain->first = next;
			if ( chain->stackmode ) chain->current = prev;
		}
		else free( *link );
	}
	chain->count--;
}



void popLink( struct s_pointer_chain* chain )
{
	removeLink( chain, &(chain->current) );
}



void disposeChain( struct s_pointer_chain* chain )
{
	struct s_link** pp = &(chain->first);
	while ( chain->count > 0 )
	{
		removeLink( chain, pp );
	}
	*chain = DEFAULT_LINKS;
}



// returns the index (n-1) of link relative to the chain->first index
int getIndex( struct s_pointer_chain* chain, struct s_link* link )
{
	const struct s_link* p = chain->first;
	for ( int i = 0; i < chain->count; i++ ) if ( p == link ) return i; else p =  p->next;
	return -1;
}


// returns the index (n-1) of link relative to the chain->first index
int getDataIndex( struct s_pointer_chain* chain, const void* data )
{
	const struct s_link* p = chain->first;
	for ( int i = 0; i < chain->count; i++ )
	{
		int equal = memcmp( (const void*)p->data, data, sizeof(data) );
		if ( equal == 0 ) return i;
		p = p->next;
	}
	return -1;
}


struct s_link* getLink( struct s_pointer_chain* chain, int index )
{
	if ( index > (chain->count - 1) || (index < 0) )
	{
		puts( "getLink - Warning, index is out of range!" );
		return NULL;
	}

	struct s_link* link = chain->first;
	for ( int i = 0; i < index; i++ )
	{
		if ( i == index ) break;
		link = link->next;
	}
	return link;
}
