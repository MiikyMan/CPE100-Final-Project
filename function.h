#ifndef FUNCTION_H
#define FUNCTION_H
#define MAX 1024

typedef struct {
  int quantity;
  char bookname[MAX];
  char borrowhistory[MAX];
  char authorname[MAX];
  char publish[MAX];
  int publishyear;
  int status;
  char charstatus[MAX];
  char history[MAX];
} BOOK_T;
void menu();
void Addbook(BOOK_T book);
void Removebook(BOOK_T book);
void Editbook(BOOK_T book);
void Showbook(BOOK_T book);
void Searchbook(BOOK_T book);
void Borrowbook(BOOK_T book);
void Returnbook(BOOK_T book);
int validatestring(char* s);
int isduplicate(char* name);
int isinteger(char* s);

#endif