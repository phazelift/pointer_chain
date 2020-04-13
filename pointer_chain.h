// pointer_chain: A dynamic chain (doubly linked list with lock) that holds pointers to dynamic data
//
// MIT License
//
// Copyright (c) 2019 Dennis Raymondo van der Sluis
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef POINTER_CHAIN_H
#define POINTER_CHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct s_link {
	void* data;
	struct s_link* prev;
	struct s_link* next;
};

struct s_pointer_chain {
	bool stackmode;
	int count;
	struct s_link* first;
	struct s_link* current;
};

#define DEFAULT_LINKS (struct s_pointer_chain){ .count= 0, .first= NULL, .current= NULL }


struct s_pointer_chain* newPointerChain();
struct s_pointer_chain* newStack();
static void addFirstLink( struct s_pointer_chain*, struct s_link* );
static void addNextLink( struct s_pointer_chain*, struct s_link* );
struct s_link* addLink( struct s_pointer_chain*, void* );
#define pushLink addLink
void removeLink( struct s_pointer_chain*, struct s_link** );
void popLink( struct s_pointer_chain* );
void disposeChain( struct s_pointer_chain* );
#define resetChain disposeChain
int getIndex( struct s_pointer_chain* links, struct s_link* link );
int getDataIndex( struct s_pointer_chain* links, const void* );
struct s_link* getLink( struct s_pointer_chain*, int );


#endif // POINTER_CHAIN_H
