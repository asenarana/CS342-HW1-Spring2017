#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// glabal variable
bool empty;

// tree node
struct treeNode
{
	char theWord[50];
	struct treeNode *leftChild;
	struct treeNode *rightChild;
	struct treeNode *parent;
};

// function headers
int fileToList( void *filename, struct treeNode *root);
int listToFile( void *filename, struct treeNode *root);
void insert( char word[], struct treeNode *cur);
void remove(char *word[], struct treeNode *cur);

// ze main
int main(int argc, char *argv[])
{
	struct treeNode *root;
	// input check
	if( argc != 3)
	{
		printf("\nArguments should be in form: <infile> <outfile>\n");
		return -1;
	}
	// tree construction
	root = malloc(sizeof(struct treeNode));
	root -> parent = NULL;
	root -> leftChild = NULL;
	root -> rightChild = NULL;
	empty = true;
	// sorting
	if( fileToList( argv[1], root) == -1)
	{
		printf("Could not open input file\n");
		return -1;
	}
	if( listToFile( argv[2], root) == -1)
	{
		printf ("Oops!\n");
		return -1;
	}
	return 0;
}

int fileToList( void *filename, struct treeNode *root)
{
	FILE *file;
	char word[50];

	file = fopen(filename, "r");
	if( file != NULL)
	{
		while(!feof(file))
		{
			fscanf(file, "%s", &word);
			// first word
			if( empty)
			{
				strcpy(root -> theWord, word);
				empty = false;
			}
			else
			{
				insert( word, root);
			}
		}
		fclose(file);
		return 0;
	}
	else
	{
		return -1;
	}
}

int listToFile( void *filename, struct treeNode *root)
{
	FILE *file;
	char word[50];

	file = fopen(filename, "a");
	if( file != NULL)
	{
		while(!empty)
		{
			remove(&word, root);
			fputs(word, file);
			fputs("\n", file);
		}
		fclose(file);
		return 0;
	}
	else
	{
		return -1;
	}
}

void insert( char word[], struct treeNode *cur)
{
	struct treeNode *newNode;
	
	// recursion!!
	if( strcmp(word, cur -> theWord) >= 0)
	{
		if( cur -> rightChild == NULL)
		{
			// insert
			newNode = malloc(sizeof(struct treeNode));
			newNode -> parent = cur;
			newNode -> leftChild = NULL;
			newNode -> rightChild = NULL;
			strcpy(newNode -> theWord, word);
			cur -> rightChild = newNode;
		}
		else
		{
			// keep looking
			insert( word, cur -> rightChild);
		}
	}
	else if( strcmp(word, cur -> theWord) < 0)
	{
		if( cur -> leftChild == NULL)
		{
			// insert
			newNode = malloc(sizeof(struct treeNode));
			newNode -> parent = cur;
			newNode -> leftChild = NULL;
			newNode -> rightChild = NULL;
			strcpy(newNode -> theWord, word);
			cur -> leftChild = newNode;
		}
		else
		{
			// keep looking
			insert( word, cur -> leftChild);
		}
	}
	return;
}

void remove(char *word[], struct treeNode *cur)
{
	struct treeNode *parent;
	
	if( cur -> rightChild != NULL)
	{
		remove( &word, cur -> rightChild);
	}
	else if( cur -> leftChild != NULL)
	{
		remove( &word, cur -> leftChild);
	}
	else
	{
		// remove from tree
		parent = cur -> parent;
		if( parent == NULL)
		{
			empty = true;
		}
		else
		{
			if( parent -> rightChild != NULL)
				parent -> rightChild = NULL;
			else
				parent -> leftChild = NULL;
		}
		// get word
		strcpy( word, cur -> theWord);
		// deallocate
		free(cur);
	}
	return;
}

