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


book read_book(void);
void print_book(book b);
void list_books(book library[]);
short isbn_lookup(int isbn, book library[]);
short title_lookup(char title[], book library[]);
void new_title(char new_title[], short position, book library[]);
void delete_book(short position, book library[]);
void new_date_lent(date date_lent, short position, book library[]);
void new_date_received(date date_received, short position, book library[]);


int main(){
	book library[MAX_LIBRARY_SIZE];
	short shelf_pointer;

}