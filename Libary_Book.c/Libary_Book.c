

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define SIZE 100


typedef struct {
	int id;
	int code;
	char name[40];
	char author[40];
	char status[10];

} Book;

typedef struct {

	Book book;
	char dateBorrow[20];
	char dateReturn[20];

} Transaction;

void removeBookInLibaryByCode(Book* books, int* size, int code);

void findTransactionByDateBorrow(Transaction* trans, int size, Transaction* result, int* found, char* date);

void findTransactionByDateReturn(Transaction* trans, int size, Transaction* result, int* found, char* date);

void sortTransactionByBookName(Transaction* trans, int size);

void sortTransactionByStatus(Transaction* trans, int size);

void sortBookInLibaryByCode(Book* books, int size);

void sortBookInLibaryByName(Book* books, int size);

void swapTransaction(Transaction* tran, Transaction* tranOther);

void swapBook(Book* book, Book* bookOther);

void findBookInLibaryByName(Book* books, int size, Book* result, int* found, char* name);

void findTransactionByBookCode(Transaction* trans, int size, Transaction* result, int* found, int code);

void showHistoryTransaction(Transaction* trans, int size);

int checkBookToBorrowByName(Book* book, int size, char* name);

int checkBookToReturnByCode(Book* books, int size, int code);

int findTransactionBorrow(Transaction* trans, int size, int code);

void getBookInfo(Book* book);

void showBooksInfo(Book* books, int size);

int findBookInLibaryByCode(Book* books, int size, int code);

void trimTail(char* str);

void trimHead(char* str);

void trimMidle(char* str);

void removeSpaceInName(char* str);

void toSentenceCase(char* str);


int main() {

	int choice = 0; 

	Book books[SIZE];

	Transaction trans[SIZE];

	int sizeOfBooks = 0;

	int sizeOfTrans = 0;

	do {

		printf("\n\t===============================>  MENU History Transacstons <================================");
		printf("\n\t1.  Add new book in libary.");
		printf("\n\t2.  Display all of books in libary.");
		printf("\n\t3.  Borrow book by code.");
		printf("\n\t4.  Return book by code.");
		printf("\n\t5.  Update status's book by code.");
		printf("\n\t6.  Search history transaction's by book code.");
		printf("\n\t7.  Search books in libary by name.");
		printf("\n\t8.  Display all of history transction borrow and return book.");
		printf("\n\t9.  Sort listed Books in libary by ascending code.");
		printf("\n\t10. Sort listed Books in libary by ascending name a-z.");
		printf("\n\t11. Sort history transactions by name's book.");
		printf("\n\t12. Sort history transactions by status.");
		printf("\n\t13. Find history transactions by date of borrowed.");
		printf("\n\t14. Find history transactions by date of returned.");
		printf("\n\t15. Remove book in libary books by code.");
		printf("\n\t0.  Exit.");
		printf("\n\t=============================================================================================\n");

		printf("\nYour choice? ");
		scanf("%d", &choice);

		switch (choice) {
		case 0:
		{
			printf("\nThanks for using!");
			break;
		}
		case 1:
		{
			int code;
			printf("\nEnter code's book that you want to add in liabary: ");
			scanf("%d", &code);

			int index = findBookInLibaryByCode(books, sizeOfBooks, code);

			if (index != -1) {
				printf("\nThe code arleady exist. Please enter code other.");
			}
			else {
				books[sizeOfBooks].id = sizeOfBooks;
				books[sizeOfBooks].code = code;
				getBookInfo(&books[sizeOfBooks]);
				sizeOfBooks++;
			}
				 
			break;
		}
		case 2:
		{
			if (sizeOfBooks > 0) {

				showBooksInfo(books, sizeOfBooks);
			}
			else {
				printf("\nThe listed books in libary is empty. Please add book first!");
			}
			break;
		}
		case 3:
		{
			if (sizeOfBooks > 0) {
				char name[40];
				printf("\nEnter the name's book that you want to borrow: ");
				scanf("%*c");
				scanf("%39[^\n]", name);
				removeSpaceInName(name);
				toSentenceCase(name);

				int index = checkBookToBorrowByName(books, sizeOfBooks, name);

				if (index == -1) {

					printf("\nDon't find the book. Please try again!");
				}
				else {

					strcpy(books[index].status, "Borrowed");

					
					trans[sizeOfTrans].book = books[index];
					char date[20];

					printf("\nEnter date borrow (dd/mm/yyyy): ");
					scanf("%*c");
					scanf("%19[^\n]", date);

					strcpy(trans[sizeOfTrans].dateBorrow, date);
					strcpy(trans[sizeOfTrans].dateReturn, "00/00/0000");
				
					sizeOfTrans++;
					

				}

			}
			else {
				printf("\nThe listed books in libary is empty. Please add book first!");
			}
			break;
		}
		case 4:
		{
			if (sizeOfBooks > 0) {
				int code;
				printf("\nEnter code's book that you want to return: ");
				scanf("%d", &code);

				int index = checkBookToReturnByCode(books, sizeOfBooks, code);

				if (index == -1) {

					printf("\nDon't find the book. Plase try again!");
				}
				else {

					int indexOther = findTransactionBorrow(trans, sizeOfTrans, code); 

					

					strcpy(books[index].status, "DEFAULT");
					trans[sizeOfTrans].book = books[index];

					strcpy(trans[sizeOfTrans].dateBorrow, trans[indexOther].dateBorrow);

					char date[20];
					printf("\nEnter date return (dd/mm/yyyy): ");
					scanf("%*c");
					scanf("%19[^\n]", date);

					strcpy(trans[sizeOfTrans].dateReturn, date);

					sizeOfTrans++;
				}

			}
			else {
				printf("\nThe listed books in libary is empty. Please add book first!");
			}
			break;
			
		}
		case 5:
		{
			if (sizeOfBooks > 0) {
				int code;

				printf("\nEnter code's book that you want to update status: ");
				scanf("%d", &code);

				int index = findBookInLibaryByCode(books, sizeOfBooks, code);

				if (index == -1) {
					printf("\nDon't find book has code: %d in listed.", code);
					printf("\nPlease try again!");
				}
				else {
					int option = 0;
					do {
						printf("\n\t-------------------------------");
						printf("\n\t1. Update status  is 'Default'.");
						printf("\n\t2. Update status  is 'Borrowed'.");
						printf("\n\t0. Exit.");
						printf("\n\t-------------------------------");

						printf("\nYour option? ");
						scanf("%d", &option);

						switch (option) {
						case 0:
							break;
						case 1:
						{
							strcpy(books[index].status, "DEFAULT");
							printf("\nUpdate new status complete.");
							break;
						}
						case 2:
						{
							strcpy(books[index].status, "Borrowed");
							printf("\nUpdate new status complete.");
							break;
						}
						
						default:
							break;
						}



					} while (option != 0);
				}
			}
			else {
				printf("\nThe listed Books in libary is empty. Please add book first!");
			}
			break;
		}
		case 6:
		{
			if (sizeOfTrans > 0) {
				int found = 0;
				Transaction result[SIZE];
				int code;

				printf("\nEnter book code that you want to search history transactions: ");
				scanf("%d", &code);

				findTransactionByBookCode(trans, sizeOfTrans, result, &found, code);

				if (found > 0) {
					showHistoryTransaction(result, found);
				}
				else {
					printf("\nDon't find history transaction has book code: %d in listed.", code);
					printf("\nPleae try again!");
				}
			}
			else {
				printf("\nThe listed history transactions is empty. Please add transaction first!");
			}
			break;

		}
		case 7:
		{
			if (sizeOfBooks > 0) {
				Book* result[SIZE];
				int found = 0;
				char name[40];
				printf("\nEnter the name book that you want to search in libary: ");
				scanf("%*c");
				scanf("%39[^\n]", name);
				removeSpaceInName(name);
				toSentenceCase(name);

				findBookInLibaryByName(books, sizeOfBooks, result, &found, name);

				if (found > 0) {
					showBooksInfo(result, found);
				}
				
				else {
					printf("\nDon't find book has name: %s in libary.", name);
					printf("\nPlease try again!");
				}
			}
			else {
				printf("\nThe listed Books in libary is empty. Please add book first!");
			}
			break;
		}
		case 8:
		{
			if (sizeOfTrans > 0) {

				showHistoryTransaction(trans, sizeOfTrans);
			}
			else {
				printf("\nThe listed history transaction's is empty. Please add transactions first!");
			}
			break;
		}
		case 9:
		{
			if (sizeOfBooks > 0) {
				sortBookInLibaryByCode(books, sizeOfBooks);

				showBooksInfo(books, sizeOfBooks);
			}
			else {
				printf("\nThe listed Books in libary is empty. Please add book first!");
			}
			break;
		}
		case 10:
		{
			if (sizeOfBooks > 0) {
				sortBookInLibaryByName(books, sizeOfBooks);

				showBooksInfo(books, sizeOfBooks);

			}
			else {
				printf("\nThe listed Books in libary is empty. Please add book first!");
			}
			break;

		}
		case 11:
		{
			if (sizeOfTrans > 0) {

				sortTransactionByBookName(trans, sizeOfTrans);

				showHistoryTransaction(trans, sizeOfTrans);

			}
			else {
				printf("\nThe listed history transactions is empty. Please add transaction first!");
			}
			break;
		}
		case 12:
		{

			if (sizeOfTrans > 0) {
				sortTransactionByStatus(trans, sizeOfTrans);
				showHistoryTransaction(trans, sizeOfTrans);
			}
			else {
				printf("\nThe listed history transactions is empty. Please add transaction first!");
			}

			break;

		}
		case 13:
		{
			if (sizeOfTrans > 0) {

				int found = 0; 

				Transaction result[SIZE];

				char date[20];
				printf("\nEnter the date that you want to search date of borrowed book: ");
				scanf("%*c");
				scanf("%19[^\n]", date);

				findTransactionByDateBorrow(trans, sizeOfTrans, result, &found, date);

				if (found > 0) {
					showHistoryTransaction(result, found);
				}
				else {
					printf("\nDon't find history transaction has date of borrowed: %s in listed.", date);
					printf("\nPlease try again!");
				}

			}
			else {
				printf("\nThe listed history transactions is empty. Please add transaction's first!");
			}
			break;
		}
		case 14:
		{
			if (sizeOfTrans > 0) {
				int found = 0; 
				Transaction result[SIZE];

				char date[20];
				printf("\nEnter the date that you want to search date of returned book: ");
				scanf("%*c");
				scanf("%19[^\n]", date);

				findTransactionByDateReturn(trans, sizeOfTrans, result, &found, date);

				if (date > 0) {
					showHistoryTransaction(result, found);
				}
				else {
					printf("\nDon't find history transaction has date of returned: %s in listed.", date);
					printf("\nPlease try again!");
				}
			}
			else {
				printf("\nThe listed history transactions is empty. Please add transaction first!");
			}
			break;
		}
		case 15:
		{

			if (sizeOfBooks > 0) {
				int code;
				printf("\nEnter book code that you want to remove from libary: ");
				scanf("%d", &code);

				int index = findBookInLibaryByCode(books, sizeOfBooks, code);

				if (index == -1) {
					printf("\nDon't find book has code: %d in listed.", code);
					printf("\nRemove book cancel. Please try again!");
				}
				else {
					removeBookInLibaryByCode(books, &sizeOfBooks, code);
					printf("\nRemove book has cpde: %d complete!", code);
				}
			}
			else {
				printf("\nThe listed books in libary is empty. Please add book first!");
			}
			break;
		}
		
		default:
		{
			printf("\nInvalid choice. Please try again!");
			break;
		}

		}


	} while (choice != 0);


	return 0;
}

void removeBookInLibaryByCode(Book* books, int* size, int code) {

	for (int i = 0; i < *size; i++) {
		if (books[i].code == code) {

			for (int j = i; j < *size; j++) {

				books[j] = books[j + 1];
			}
			(*size)--;
		}
	}
}

void findTransactionByDateBorrow(Transaction* trans, int size, Transaction* result, int* found, char* date) {

	for (int i = 0; i < size; i++) {

		if (strcmp(trans[i].dateBorrow, date) == 0) {

			result[(*found)++] = trans[i];
		}
	}
}

void findTransactionByDateReturn(Transaction* trans, int size, Transaction* result, int* found, char* date) {

	for (int i = 0; i < size; i++) {

		if (strcmp(trans[i].dateReturn, date) == 0) {

			result[*(found)++] = trans[i];
		}
	}
}


void sortTransactionByBookName(Transaction* trans, int size) {

	for (int i = 0; i < size - 1; i++) {
		
		for (int j = size - 1; j > i; j--) {

			if (strcmp(trans[j - 1].book.name, trans[j].book.name) > 0) {

				swapTransaction(&trans[j - 1], &trans[j]);
			}
		}
	}
}

void sortTransactionByStatus(Transaction* trans, int size) {

	for (int i = 0; i < size - 1; i++) {

		for (int j = size - 1; j > i; j--) {

			if (strcmp(trans[j - 1].book.status, trans[j].book.status) > 0) {

				swapTransaction(&trans[j - 1], &trans[j]);
			}
		}
	}
}

void sortBookInLibaryByCode(Book* books, int size) {
	for (int i = 0; i < size - 1; i++) {

		for (int j = size - 1; j > i; j--) {
			if (books[j - 1].code > books[j].code) {

				swapBook(&books[j - 1], &books[j]);
			}

		}
	}
}

void sortBookInLibaryByName(Book* books, int size) {

	for (int i = 0; i < size - 1; i++) {

		for (int j = size -1 ; j > i; j--) {

			if (strcmp(books[j - 1].name, books[j].name) > 0) {

				swapBook(&books[j - 1], &books[j]);
			}

		}
	}
}

void swapTransaction(Transaction* tran, Transaction* tranOther) {
	Transaction tmp = *tran;
	*tran = *tranOther;
	*tranOther = tmp;
}

void swapBook(Book* book, Book* bookOther) {

	Book tmp = *book;
	*book = *bookOther;
	*bookOther = tmp;
}
		

void findBookInLibaryByName(Book* books, int size, Book* result, int* found, char* name) {
	for (int i = 0; i < size; i++) {
		if (strcmp(books[i].name, name) == 0) {
			result[(*found)++] = books[i];
		}
	}
	
}

void findTransactionByBookCode(Transaction* trans, int size, Transaction* result, int* found, int code) {
	for (int i = 0; i < size; i++) {
		if (trans[i].book.code == code) {

			result[(*found)++] = trans[i];
		}
	}
}


int findTransactionBorrow(Transaction* trans, int size, int code) {

	for (int i = 0; i < size; i++) {

		if (trans[i].book.code == code &&
			strcmp(trans[i].book.status, "Borrowed") == 0) {
			return i;
		}
	}
	return -1;
}


void showHistoryTransaction(Transaction* trans, int size) {

	printf("\n\t==========================> History Transactions <=============================\n");

	printf("\n%-20s%-40s%-40s%-20s%-25s%-25s\n",  "Code", "Name", "Author",
		"Status", "Date Borrow", "Date Return");

	for (int i = 0; i < size; i++) {

		printf("%-20d%-40s%-40s%-20s%-25s%-25s\n",
			 trans[i].book.code, trans[i].book.name, trans[i].book.author,
			trans[i].book.status, trans[i].dateBorrow, trans[i].dateReturn);
	}


}

int checkBookToReturnByCode(Book* books, int size, int code) {

	for (int i = 0; i < size; i++) {

		if (books[i].code == code &&
			strcmp(books[i].status, "Borrowed") == 0) {
			return i;
		}
	}
	return -1;
}


int checkBookToBorrowByName(Book* books, int size, char* name) {

	for (int i = 0; i < size; i++) {

		if (strcmp(books[i].name, name) == 0 && 
			strcmp(books[i].status, "DEFAULT") == 0) {

			return i;
		}
	}
	return -1;
}


void getBookInfo(Book* book) {
	printf("\nEnter name's book: ");
	scanf("%*c");
	scanf("%39[^\n]", book->name);
	removeSpaceInName(book->name);
	toSentenceCase(book->name);

	printf("\nEnter author name's book: ");
	scanf("%*c");
	scanf("%39[^\n]", book->author);
	removeSpaceInName(book->author);
	toSentenceCase(book->author);

	strcpy(book->status, "DEFAULT");

}

void showBooksInfo(Book* books, int size) {

	printf("\n\t=============> Libary Books <======================\n");

	printf("\n%-20s%-20s%-40s%-40s%-20s\n", "Order", "Code", "Name", "Author", "Status");

	for (int i = 0; i < size; i++) {

		printf("%-20d%-20d%-40s%-40s%-20s\n", books[i].id, books[i].code, books[i].name,
			books[i].author, books[i].status);

	}
}

int findBookInLibaryByCode(Book* books, int size, int code) {

	for (int i = 0; i < size; i++) {
		if (books[i].code == code) {
			return i;
		}
	}
	return -1;
}


void trimTail(char* str) {
	int n = strlen(str);
	int count = 0;
	int i = n - 1;
	while (isspace(str[i])) {
		count++;
		i--;
	}

	str[n - count] = '\0';
}

void trimHead(char* str) {
	int n = strlen(str);
	int count = 0;
	int  i = 0;
	while (isspace(str[i])) {
		count++;
		i++;
	}

	for (int i = 0; i < n - 1; i++) {
		str[i] = str[i + count];
	}

	str[n - count] = '\0';
}

void trimMidle(char* str) {
	int n = strlen(str);
	
	for (int i = 0; i < n - 1; i++) {
		if (isspace(str[i]) && isspace(str[i + 1])) {

			for (int j = i; j < n - 1; j++) {
				str[j] = str[j + 1];
			}
			str[n - 1] = '\0';
			n--;
			i--;
		}
	}
}

void removeSpaceInName(char* str) {
	trimTail(str);
	trimHead(str);
	trimMidle(str);
}

void toSentenceCase(char* str) {
	int n = strlen(str);
	str[0] = toupper(str[0]);
	for (int i = 0; i < n - 1; i++) {
		if (i < n - 1 && isspace(str[i]) && !isspace(str[i + 1])) {

			str[i + 1] = toupper(str[i + 1]);
		}
	}

}