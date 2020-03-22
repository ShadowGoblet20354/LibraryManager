#include <stdio.h>
#include <string.h>

#define MAX_LIBRARY_SIZE 50
#define MAX_B_TITLE_LEN 40
#define MAX_B_AUTHOR_LEN 30

typedef struct {
	short day;
	short month;
	short year;
} date;

typedef struct {
	char title[MAX_B_TITLE_LEN];
	char author[MAX_B_AUTHOR_LEN];
	int isbn;
	short year_published;
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
void new_date_lent(book library[], short position);
void new_date_received(book library[], short position);
void clear_stdin_stream();


int main()
{
	book library[MAX_LIBRARY_SIZE];
	short shelf_pointer, found_index;
	short input;

	print_help();

	do {
		putchar('>');
		scanf("%hd", &input);
		clear_stdin_stream();

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
					printf("Error: no book was found with such isbn\n");
				}
				break;

			case 4:
				found_index = title_lookup(library, shelf_pointer);
				if (found_index != -1){
					print_book(library[found_index]);
				}
				else{
					printf("Error: no book was found with such title\n");
				}
				break;

			case 5:
				new_title(library, shelf_pointer);
				break;
			
			case 6:
				delete_book(library, &shelf_pointer);
				break;
			
			case 7:
				new_date_lent(library, shelf_pointer);
				break;
			
			case 8:
				new_date_received(library, shelf_pointer);
				break;
			
			case 9:
				print_help();
				break;
			
			case 0:
				printf("Terminating...\n\n");
				break;				
		}
	} while (input != 0);

	return 0;
}


void print_help()
{
	putchar('\n');
	printf("****BIBLIOTECA DO IST****\n");
	printf("1 - Inserir novo livro\n");
	printf("2 - Listar livros\n");
	printf("3 - Procurar livro por isbn\n");
	printf("4 - Procurar livro por título\n");
	printf("5 - Alterar título do livro\n");
	printf("6 - Apagar livro pelo isbn\n");
	printf("7 - Registar data de empréstimo de um livro pelo isbn\n");
	printf("8 - Registar data de retorno de um livro pelo isbn\n");
	printf("9 - Mostrar ajuda\n");
	printf("0 - Sair\n");
	printf("*************************\n");
	putchar('\n');
}


book read_book()
{
	book b_in;
	date lent = {1, 1, 1970}, received = {1, 1, 1970};

	putchar('\n');
	printf("Title: ");
	fgets(b_in.title, MAX_B_TITLE_LEN, stdin);

	printf("Author: ");
	fgets(b_in.author, MAX_B_AUTHOR_LEN, stdin);

	printf("ISBN: ");
	scanf("%d", &b_in.isbn);

	printf("Year published: ");
	scanf("%hd", &b_in.year_published);
	putchar('\n');

	clear_stdin_stream();

	b_in.date_lent = lent;
	b_in.date_received = received;

	return b_in;
}


void print_book(book b){
	putchar('\n');
	printf("Title: %s", b.title);
	printf("Author: %s", b.author);
	printf("ISBN: %d\n", b.isbn);
	printf("Year published: %hd\n", b.year_published);
	printf("Lent on: %02hd-%02hd-%04hd\n", b.date_lent.day, b.date_lent.month, b.date_lent.year);
	printf("Received on: %02hd-%02hd-%04hd\n", b.date_received.day, b.date_received.month, b.date_received.year);
	putchar('\n');
}


void list_books(book library[], short position){
	short k;

	putchar('\n');

	if (position == 0){
		puts("There are no books at the moment.\n");
		return;
	}

	puts("* * * Books * * *");

	for (k = 0; k < position; k++){
		printf("%s", library[k].title);
	}
	putchar('\n');
}


short isbn_lookup(book library[], short position){
	int isbn;
	short i;

	putchar('\n');
	printf("ISBN: ");
	scanf("%d", &isbn);

	clear_stdin_stream();

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

	putchar('\n');
	printf("Title: ");
	fgets(title, MAX_B_TITLE_LEN, stdin);

	for (i = 0; i < position; i++)
	{
		if (!strcmp(library[i].title, title))
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
		printf("Error: no book was found with such title\n\n");
		return;
	}

	printf("New title: ");
	fgets(library[index].title, MAX_B_TITLE_LEN, stdin);
	putchar('\n');
}


void delete_book(book library[], short *position){
	short index;

	index = isbn_lookup(library, *position);

	if (index == -1){
		printf("Error: no book was found with such isbn\n\n");
		return;
	}

	library[index] = library[--*position];
	putchar('\n');
}


void new_date_lent(book library[], short position){
	date d_lent;
	short index;

	index = title_lookup(library, position);

	if (index == -1){
		printf("Error: no book was found with such title\n\n");
		return;
	}

	printf("Day: ");
	scanf("%hd", &d_lent.day);

	printf("Month: ");
	scanf("%hd", &d_lent.month);

	printf("Year: ");
	scanf("%hd", &d_lent.year);
	putchar('\n');

	clear_stdin_stream();

	library[index].date_lent = d_lent;	
}



void new_date_received(book library[], short position){
	date d_received;
	short index;

	index = title_lookup(library, position);

	if (index == -1)
	{
		printf("Error: no book was found with such title\n\n");
		return;
	}

	printf("Day: ");
	scanf("%hd", &d_received.day);

	printf("Month: ");
	scanf("%hd", &d_received.month);

	printf("Year: ");
	scanf("%hd", &d_received.year);
	putchar('\n');

	clear_stdin_stream();

	library[index].date_received = d_received;
}


void clear_stdin_stream(){
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}