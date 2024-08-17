#include "function.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  printf("Welcome to CPE Library Manage "
         "System\n====================================\n");

  BOOK_T book;
  FILE *filepointer1 = fopen("library.txt", "r"); // open "library.txt" as
                                                  // "read"
  if (filepointer1 == NULL) { // if "library.txt" doesn't exist
    printf("\nThis library is empty\nLet's create your first book\n\n");
    FILE *filepointer2 = fopen("copy.c", "w"); // open "copy.c" as "write"
    printf("Enter title: ");
    fgets(book.bookname, MAX, stdin); // enter book's name
    if (book.bookname[strlen(book.bookname) - 1] == '\n') {
      book.bookname[strlen(book.bookname) - 1] = '\0'; // delete '\n' from
                                                       // buffer
    }
    printf("Author Name: ");
    fgets(book.authorname, MAX, stdin); // enter author's name
    if (book.authorname[strlen(book.authorname) - 1] == '\n') {
      book.authorname[strlen(book.authorname) - 1] =
          '\0'; // delete '\n' from buffer
    }
    printf("Publish year: ");
    scanf("%d", &book.publishyear); // enter publish year

    fprintf(filepointer2, "1\n%s,%s,%d,1,-", book.bookname, book.authorname,
            book.publishyear);
    fclose(filepointer2);            // close file
    rename("copy.c", "library.txt"); // rename it to "library.txt"
  } else {                           // if "library.txt" is created
    fclose(filepointer1);            // close file
  }

  int m = 0;
  char tmp[MAX];

  while (m != 8) {
    menu();
    scanf("%s", tmp);      // enter menu
    sscanf(tmp, "%d", &m); // filter input

    if (strlen(tmp) > 1) {
      m = 0;
    }
    if (isdigit(tmp[0]) == 0 || m > 8 || m <= 0) { // Input validation
      printf("Only 1-8 number allow!\n");
    }
    if (m == 1) {
      Addbook(book);
    }
    if (m == 2) {
      Removebook(book);
    }
    if (m == 3) {
      Editbook(book);
    }
    if (m == 4) {
      Showbook(book);
    }
    if (m == 5) {
      Searchbook(book);
    }
    if (m == 6) {
      Borrowbook(book);
    }
    if (m == 7) {
      Returnbook(book);
    }
  }

  printf("THANK YOU\n");
  return 0;
}