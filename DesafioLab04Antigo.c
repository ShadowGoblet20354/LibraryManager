#include <stdio.h>
#include <string.h>

#define MAX_LIBRARY_SIZE 50
#define MAX_B_TITLE_LEN 40
#define MAX_B_AUTHOR_LEN 20

typedef struct {
	short day;
	short month;
	short year;
} date;

typedef struct {
	char title[MAX_B_AUTHOR_LEN];
	char author[MAX_B_TITLE_LEN];
	int isbn;
	short year_published;
	short copy_number;
	date date_lent;
	date date_received;
} book;


void print_help();
book read_book();
void print_book(book b);
void list_books(book library[], short position);
short isbn_lookup(book library[], short position);
short title_lookup(book library[], short position);
void new_title(book library[], short position);
void delete_book(book library[], short* position);
void new_date_lent(book library[]);
void new_date_received(book library[]);


int main()
{
	book library[MAX_LIBRARY_SIZE];
	short shelf_pointer, found_index;
	short input;

	print_help();

	do {
		putchar('>');
		scanf("%hd", &input);

		switch (input){
			case 1:
				library[shelf_pointer++] = read_book();
				break;
			
			case 2:
				list_books(library, shelf_pointer);
				break;

			case 3:
				found_index = isbn_lookup(library, shelf_pointer);
				if (found_index != -1){
					print_book(library[found_index]);
				}
				else {
					puts("Error: no book with such isbn found\n");
				}
				break;

			case 4:
				found_index = title_lookup(library, shelf_pointer);
				if (found_index != -1){
					print_book(library[found_index]);
				}
				else{
					puts("Error: no book with such title found\n");
				}
				break;

			case 5:
				new_title(library, shelf_pointer);
				break;
			
			case 6:
				delete_book(library, &shelf_pointer);
				break;
			
			case 7:
				new_date_lent(library);
				break;
			
			case 8:
				new_date_received(library);
				break;
			
			case 9:
				print_help();
				break;
			
			case 0:
				puts("\nTerminating...\n");
				break;				
		}
	} while (input != 0);

	return 0;
}


void print_help()
{
	puts("****BIBLIOTECA DO IST****\n");
	puts("1 - Inserir novo livro\n");
	puts("2 - Listar livros\n");
	puts("3 - Procurar livro por isbn\n");
	puts("4 - Procurar livro por título\n");
	puts("5 - Alterar título do livro\n");
	puts("6 - Apagar livro pelo isbn\n");
	puts("7 - Registar data de empréstimo de um livro pelo isbn\n");
	puts("8 - Registar data de retorno de um livro pelo isbn\n");
	puts("9 - Mostrar ajuda\n");
	puts("0 - Sair\n");
	puts("*************************\n");
}


book read_book()
{
	book b_in;
	date lent = {1, 1, 1970}, received = {1, 1, 1970};

	puts("Title:");
	scanf("%39s", b_in.title);

	puts("Author:");
	scanf("%19s", b_in.author);

	puts("ISBN:");
	scanf("%d", &b_in.isbn);

	puts("Year published:");
	scanf("%hd", &b_in.year_published);

	puts("Copy number:");
	scanf("%hd", &b_in.copy_number);

	b_in.date_lent = lent;
	b_in.date_received = received;

	return b_in;
}


void print_book(book b){
	puchar('\n');
	printf("Title: %s", b.title);
	printf("Author: %s", b.author);
	printf("ISBN: %d\n", b.isbn);
	printf("Year published: %hd\n", b.year_published);
	printf("Copy number: %hd\n", b.copy_number);
	printf("Lent on: %2hd-%2hd-%4hd\n", b.date_lent.day, b.date_lent.month, b.date_lent.year);
	printf("Received on: %2hd-%2hd-%4hd\n", b.date_received.day, b.date_received.month, b.date_received.year);
	putchar('\n');
}


void list_books(book library[], short position){
	short k;

	for (k = 0; k < position; k++){
		puts(library[k].title);
	}
	putchar('\n');
}


void short_lookup(book library[], short position){
	int isbn;
	short i;

	puts("ISBN:");
	scanf("%d", &isbn);

	for (i = 0; i < position; i++){
		if (library[i].isbn == isbn){
			return i;
		}
	}
	return -1;
}


short title_lookup(book library[], short position){
	char title[MAX_B_TITLE_LEN];
	short i;

	puts("Title:");
	scanf("%39s", title);

	for (i = 0; i < position; i++)
	{
		if (strcmp(library[i].title, title))
		{
			return i;
		}
	}
	return -1;
}


void new_title(book library[], short position){
	short index;

	index = title_lookup(library, position);

	if (index == -1){
		puts("Error: no book with such title found\n");
		return;
	}

	puts("New title:");
	scanf("%39s", library[index].title);
}