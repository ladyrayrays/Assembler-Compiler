#include "symbolTable.h"

int main()
{
	struct SymbolTable myTable;
	myTable.head = NULL;
	insertAtEnd(&myTable, "hello", 42);
	insertAtEnd(&myTable, "hi", 84);
	printf("%d\n", contains(&myTable,"hi"));
	printf("%d\n", contains(&myTable,"bye"));
	printtable(&myTable);
	destroytable(&myTable);
	return 0;
}
