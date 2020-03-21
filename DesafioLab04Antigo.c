#include <stdio.h>

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


void print_help(void);
book read_book(void);
void print_book(book b);
void list_books(book library[]);
short isbn_lookup(int isbn, book library[]);
int read_isbn(void);
short title_lookup(char title[], book library[]);
void new_title(char new_title[], short position, book library[]);
void delete_book(short position, book library[]);
void new_date_lent(date date_lent, short position, book library[]);
void new_date_received(date date_received, short position, book library[]);


int main(){
	book library[MAX_LIBRARY_SIZE];
	short shelf_pointer, position;
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
				list_books(library);
				break;
			
			case 3:
				position = isbn_lookup(read_isbn(), library);
				if (position != -1){
					print_book(library[position]);
				}
				else {
					puts("Error: book not found.");
				}
				break;

			
				
		}
	} while (input != 0);

}

void print_help(void){
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


book read_book(void)
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