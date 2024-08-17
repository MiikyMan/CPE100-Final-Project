#include "function.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu() {
  printf("\nMenu\n1)Add book\n2)Remove book\n3)Edit book\n4)Show all "
         "book\n5)Search book\n6)Borrow book\n7)Return book\n8)Exit\n> ");
}

void Addbook(BOOK_T book) {
  FILE *fp = fopen("library.txt", "a"); // Open "library.txt" as "append"
  char tmp[MAX];
  fgets(book.bookname, MAX, stdin);
  do {

    printf("Enter title: ");
    fgets(book.bookname, MAX, stdin); // Enter new book's name

    if (book.bookname[strlen(book.bookname) - 1] == '\n') {
      book.bookname[strlen(book.bookname) - 1] = '\0'; // delete \n from buffer
    }
    if (isduplicate(book.bookname))
      printf("The book is already exists\n");

  } while ((isduplicate(book.bookname))); // re-enter the title if user enter
                                          // the already exist books

  printf("Author Name: ");
  fgets(book.authorname, MAX, stdin); // Enter new book's author name
  if (book.authorname[strlen(book.authorname) - 1] == '\n') {
    book.authorname[strlen(book.authorname) - 1] = '\0'; // delete \n from
                                                         // buffer
  }

  do {
    printf("Publish year: ");
    scanf("%s", tmp); // Enter new book's publish year
    sscanf(tmp, "%d", &book.publishyear);
    if (!isinteger(tmp)) {
      printf("Please enter an integer numbers only\n");
    }
  } while (!isinteger(tmp));
  fprintf(
      fp, "\n%s,%s,%d,1,-", book.bookname, book.authorname,
      book.publishyear); // Append all new book's information to "library.txt"

  fclose(fp); // close file
}

void Removebook(BOOK_T book) {
  int quantity = 0;
  char bookname[MAX];
  char qty[MAX];
  fgets(bookname, MAX, stdin);
  FILE *fp1 = fopen("library.txt", "r"); // Open "library.txt" as "read"

  fgets(qty, MAX,
        fp1); // read first line from "library.txt" and store it in 'qty'
  sscanf(qty, "%d", &quantity); // scan %d from 'qty' and store it in 'quantity'
  char *history =
      (char *)calloc(quantity * MAX,
                     sizeof(char)); // allocate memories for 'history' by calloc
  char *buffer = (char *)calloc(
      quantity * MAX, sizeof(char)); // allocate memories for 'buffer' by calloc

  FILE *fp2 = fopen("copy.c", "w"); // Open "copy.c" as "write"
  fprintf(fp2, "%d",
          quantity); // write value of 'quantity' to the first line of "copy.c"
  printf("Enter title to be remove: ");
  fgets(bookname, MAX, stdin); // enter the book name to be remove
  if (bookname[strlen(bookname) - 1] == '\n') {
    bookname[strlen(bookname) - 1] = '\0'; // delete '\n' from buffer
  }

  while (!feof(fp1)) {
    fgets(buffer, quantity * MAX * sizeof(char), fp1);
    if (buffer[strlen(buffer) - 1] == '\n') {
      buffer[strlen(buffer) - 1] = '\0'; // delete '\n' from buffer
    }
    sscanf(buffer, "%39[^,]",
           book.bookname); // search for book name from each line
    if (strcmp(book.bookname, bookname) !=
        0) { // check if 'bookname' value equal to 'book.bookname'
      fprintf(fp2, "\n%s",
              buffer); // copy all the data from "library.txt" to "copy.c"
    }
  }

  fclose(fp1);                     // close "library.txt"
  fclose(fp2);                     // close "copy.c"
  rename("copy.c", "library.txt"); // rename from "copy.c" to "library.txt"
  free(history);                   // free memories
  free(buffer);                    // free memories
}

void Editbook(BOOK_T book) {
  int quantity = 0;
  char bookname[MAX];
  char qty[MAX];
  char newbookname[MAX];
  char newauthorname[MAX];
  char newpublishyear[MAX];
  fgets(bookname, MAX, stdin);
  do {
    printf("Enter title to be edit: ");

    fgets(bookname, MAX, stdin); // Enter title to be edit
    if (bookname[strlen(bookname) - 1] == '\n') {
      bookname[strlen(bookname) - 1] = '\0'; // delete '\n' from buffer
    }
    if (!isduplicate(bookname))
      printf("The book doesn't exists in the library\n");
  } while (!isduplicate(bookname));

  FILE *fp1 = fopen("library.txt", "r"); // Open "library.txt" as "read"
  fgets(qty, MAX,
        fp1); // read first line from "library.txt" and store it in 'qty'
  sscanf(qty, "%d", &quantity); // scan %d from 'qty' and store it in 'quantity'
  char *history =
      (char *)calloc(quantity * MAX,
                     sizeof(char)); // allocate memories for 'history' by calloc
  char *buffer = (char *)calloc(
      quantity * MAX, sizeof(char)); // allocate memories for 'buffer' by calloc
  FILE *fp2 = fopen("copy.c", "w");  // Open "copy.c" as "write"

  fprintf(fp2, "%d\n",
          quantity); // write value of 'quantity' to the first line of "copy.c"
  while (!feof(fp1)) {
    fgets(buffer, quantity * MAX * sizeof(char),
          fp1); // store all the line data to 'buffer'
    sscanf(buffer, "\n%39[^,],%39[^,],%39[^,],%39[^,],%39[^,]", book.bookname,
           book.authorname, book.publish, book.charstatus,
           history); // seperate each data type

    if (strcmp(book.bookname, bookname) ==
        0) { // check if 'bookname' value equal to 'book.bookname'

      do {
        printf("New title (leave blank to retain old value): ");
        fgets(newbookname, MAX, stdin); // Enter new book's name
        if (newbookname[strlen(newbookname) - 1] == '\n') {
          newbookname[strlen(newbookname) - 1] = '\0'; // delete '\n' from
                                                       // buffer
        }

        if (strlen(newbookname) == 0) // check if not blank
          break;
        if (isduplicate(newbookname))
          printf("The book is already exists\n");
      } while (isduplicate(newbookname));

      if (strlen(newbookname) != 0) { // check if not blank
        strcpy(book.bookname,
               newbookname); // copy 'newbookname' value into 'book.bookname'
      }

      printf("New author name (leave blank to retain old value): ");
      fgets(newauthorname, MAX, stdin); // Enter new author's name

      if (newauthorname[0] != '\n') {
        if (newauthorname[strlen(newauthorname) - 1] == '\n') {
          newauthorname[strlen(newauthorname) - 1] =
              '\0'; // delete '\n' from buffer
        }
        strcpy(
            book.authorname,
            newauthorname); // copy 'newauthorname' value into 'book.authorname'
      }
      do {
        printf("New publish year (leave blank to retain old value): ");
        fgets(newpublishyear, MAX, stdin); // Enter new book's publish year
        if (newpublishyear[strlen(newpublishyear) - 1] == '\n') {
          newpublishyear[strlen(newpublishyear) - 1] =
              '\0'; // delete '\n' from buffer
        }
        if (strlen(newpublishyear) == 0)
          break;
        if (!isinteger(newpublishyear))
          printf("Please enter an integer number\n");

      } while (!isinteger(newpublishyear));

      if (newpublishyear[0] != '\n') {

        strcpy(
            book.publish,
            newpublishyear); // copy 'newpublishyear' value into 'book.publish'
      }
    }
    fprintf(fp2, "%s,%s,%s,%s,%s", book.bookname, book.authorname, book.publish,
            book.charstatus, history); // write all data to "copy.c"
  }
  fclose(fp1);                     // close "library.txt"
  fclose(fp2);                     // close "copy.c"
  rename("copy.c", "library.txt"); // rename from "copy.c" to "library.txt"
  free(history);                   // free memories
  free(buffer);                    // free memories
}

void Showbook(BOOK_T book) {
  int borrow = 0;
  int count = 1;
  int quantity = 0;
  char qty[MAX];
  FILE *fp = fopen("library.txt", "r"); // Open "library.txt" as "read"
  fgets(qty, MAX,
        fp); // read first line from "library.txt" and store it in 'qty'
  sscanf(qty, "%d", &quantity); // scan %d from 'qty' and store it in 'quantity'
  char *history =
      (char *)calloc(quantity * MAX,
                     sizeof(char)); // allocate memories for 'history' by calloc
  char *buffer = (char *)calloc(
      quantity * MAX, sizeof(char)); // allocate memories for 'buffer' by calloc
  while (!feof(fp)) {
    fgets(buffer, MAX, fp); // store all the line data to 'buffer'

    sscanf(buffer, "%39[^,],%39[^,],%d,%d,%s", book.bookname, book.authorname,
           &book.publishyear, &book.status,
           history); // seperate each data type
    printf("%d.", count);
    printf("Title : %s\n", book.bookname);
    printf("  Author name: %s\n", book.authorname);
    printf("  Publish year: %d\n", book.publishyear);
    if (book.status == 1) { // check if book available or not
      printf("  Status : Available\n");
    } else {
      printf("  Status : Unavailable\n");
    }
    printf("  Borrowing History:\n");
    char *token =
        strtok(history, "-"); // spilt all the strings in 'history' by '-'

    while (token != NULL) {
      if (borrow == 0) {
        printf("   -Borrowed by %s\n", token); // Odd numbers will be a borrower
        borrow = 1;
      } else if (borrow == 1) {
        printf("   -Returned by %s\n", token); // Even numbers will be a
                                               // returner
        borrow = 0;
      }

      token = strtok(NULL, "-");
    }
    borrow = 0;
    printf("\n");
    count++;
  }
  fclose(fp);    // close file
  free(buffer);  // free memories
  free(history); // free memories
}

void Searchbook(BOOK_T book) {
  int borrow = 0;
  int quantity = 0;
  int count = 1;
  int bookspace = 0;
  int authorspace = 0;
  char bookname[MAX];
  char authorname[MAX];
  char qty[MAX];
  fgets(bookname, MAX, stdin);

  printf("Enter title (leave blank to include all titles): ");
  fgets(bookname, MAX, stdin); // enter book's name for searching

  printf("Enter author name (leave blank to include all author names: ");
  fgets(authorname, MAX, stdin); // enter author's name for searching

  FILE *fp = fopen("library.txt", "r"); // open "library.txt" as "read"
  fgets(qty, MAX,
        fp); // read first line from "library.txt" and store it in 'qty'
  sscanf(qty, "%d", &quantity); // scan %d from 'qty' and store it in 'quantity'
  char *history =
      (char *)calloc(quantity * MAX,
                     sizeof(char)); // allocate memories for 'history' by calloc
  char *buffer = (char *)calloc(
      quantity * MAX, sizeof(char)); // allocate memories for 'buffer' by calloc

  bookspace = isspace(
      bookname[0]); // check if 'bookname' is just a white-space charactor
  authorspace = isspace(
      authorname[0]); // check if 'authorname' is just a white-space charactor
  if (bookname[strlen(bookname) - 1] == '\n') {
    bookname[strlen(bookname) - 1] = '\0'; // delete '\n' from buffer
  }
  if (authorname[strlen(authorname) - 1] == '\n') {
    authorname[strlen(authorname) - 1] = '\0'; // delete '\n' from buffer
  }

  while (!feof(fp)) {

    fgets(buffer, quantity * MAX * sizeof(char),
          fp); // store all the line data to 'buffer'
    sscanf(buffer, "%39[^,],%39[^,],%d,%d,%s", book.bookname, book.authorname,
           &book.publishyear, &book.status,
           history); // seperate each data type

    if (bookspace == 0 &&
        authorspace != 0) { // run this function when 'authorspace' is
                            // white-space character
      if (strstr(book.bookname, bookname) !=
          NULL) { // check if there is a 'bookname' string in 'book.bookname'
        printf("%d.", count);
        printf("Title : %s\n", book.bookname);
        printf("  Author name: %s\n", book.authorname);
        printf("  Publish year: %d\n", book.publishyear);
        if (book.status == 1) {
          printf("  Status : Available\n");
        } else {
          printf("  Status : Unavailable\n");
        }
        printf("  Borrowing History:\n");
        char *token = strtok(history, "-");
        while (token != NULL) {
          if (borrow == 0) {
            printf("   -Borrowed by %s\n", token);
            borrow = 1;
          } else if (borrow == 1) {
            printf("   -Returned by %s\n", token);
            borrow = 0;
          }
          token = strtok(NULL, "-");
        }
        borrow = 0;
        printf("\n");
        count++; // do the same as "Showbook" function
      }
    } else if (authorspace == 0 &&
               bookspace != 0) { // run this function when 'bookspace' is
                                 // white-space character
      if (strstr(book.authorname, authorname) !=
          NULL) { // check if there is a 'authorname' string in
                  // 'book.authorname'
        printf("%d.", count);
        printf("Title : %s\n", book.bookname);
        printf("  Author name: %s\n", book.authorname);
        printf("  Publish year: %d\n", book.publishyear);
        if (book.status == 1) {
          printf("  Status : Available\n");
        } else {
          printf("  Status : Unavailable\n");
        }
        printf("  Borrowing History:\n");
        char *token = strtok(history, "-");
        while (token != NULL) {
          if (borrow == 0) {
            printf("   -Borrowed by %s\n", token);
            borrow = 1;
          } else if (borrow == 1) {
            printf("   -Returned by %s\n", token);
            borrow = 0;
          }
          token = strtok(NULL, "-");
        }
        borrow = 0;
        printf("\n");
        count++; // do the same as "Showbook" function
      }
    } else if (authorspace == 0 &&
               bookspace == 0) { // run this function when both is not a
                                 // white-space character
      if (strstr(book.bookname, bookname) != NULL ||
          strstr(book.authorname, authorname) !=
              NULL) { // check if there is a 'bookname' string in
                      // 'book.bookname' or if there is a 'authorname' string in
                      // 'book.authorname'
        printf("%d.", count);
        printf("Title : %s\n", book.bookname);
        printf("  Author name: %s\n", book.authorname);
        printf("  Publish year: %d\n", book.publishyear);
        if (book.status == 1) {
          printf("  Status : Available\n");
        } else {
          printf("  Status : Unavailable\n");
        }
        printf("  Borrowing History:\n");
        char *token = strtok(history, "-");
        while (token != NULL) {
          if (borrow == 0) {
            printf("   -Borrowed by %s\n", token);
            borrow = 1;
          } else if (borrow == 1) {
            printf("   -Returned by %s\n", token);
            borrow = 0;
          }
          token = strtok(NULL, "-");
        }
        borrow = 0;
        printf("\n");
        count++; // do the same as "Showbook" function
      }
    }
  }
  fclose(fp);    // close file
  free(buffer);  // free memories
  free(history); // free memories
}

void Borrowbook(BOOK_T book) {
  int quantity = 0;
  char qty[MAX];
  char bookname[MAX];
  char username[MAX];
  printf("Enter title to be borrow: ");
  fgets(bookname, MAX, stdin);
  fgets(bookname, MAX, stdin); // enter book's name to be borrow
  if (bookname[strlen(bookname) - 1] == '\n') {
    bookname[strlen(bookname) - 1] = '\0'; // delete '\n' in buffer
  }
  printf("Enter your name: ");
  fgets(username, MAX, stdin); // enter user's name
  if (username[strlen(username) - 1] == '\n') {
    username[strlen(username) - 1] = '-'; // delete '\n' in buffer
  }

  FILE *fp1 = fopen("library.txt", "r"); // Open "library.txt" as "read"

  fgets(qty, MAX,
        fp1); // read first line from "library.txt" and store it in 'qty'
  sscanf(qty, "%d", &quantity); // scan %d from 'qty' and store it in 'quantity'
  quantity++;                   // increase size for every each line
  char *history =
      (char *)calloc(quantity * MAX,
                     sizeof(char)); // allocate memories for 'history' by calloc
  char *buffer = (char *)calloc(
      quantity * MAX, sizeof(char)); // allocate memories for 'buffer' by calloc

  FILE *fp2 = fopen("copy.c", "w"); // Open "copy.c" as "write"
  fprintf(
      fp2, "%d",
      quantity); // write the 'quantity' value onto the first line of "copy.c"

  while (!feof(fp1)) {
    fgets(buffer, quantity * MAX * sizeof(char),
          fp1); // store all the line data to 'buffer'
    sscanf(buffer, "%39[^,], %39[^,],%d,%d,%s", book.bookname, book.authorname,
           &book.publishyear, &book.status,
           history); // seperate each data type
    if (strcmp(book.bookname, bookname) ==
        0) { // check if 'bookname' value is equal to 'book.bookname'

      if (book.status == 1) {      // check if 'book.status' is true
        book.status = 0;           // turn it to false
        strcat(history, username); // concat 'username' to 'history'
      } else {
        printf("This book is unavilable");
      }
    }

    fprintf(fp2, "\n%s,%s,%d,%d,%s", book.bookname, book.authorname,
            book.publishyear, book.status,
            history); // copy all the data from "library.txt" to "copy.c"
  }
  fclose(fp1);                     // close file
  fclose(fp2);                     // close file
  rename("copy.c", "library.txt"); // rename "copy.c" to "library.txt"
  free(buffer);                    // free memories
  free(history);                   // free memories
}

void Returnbook(BOOK_T book) {
  int quantity = 0;
  char qty[MAX];
  char bookname[MAX];
  char username[MAX];
  printf("Enter title to be return: ");
  fgets(bookname, MAX, stdin);
  fgets(bookname, MAX, stdin); // enter book's name to be borrow
  if (bookname[strlen(bookname) - 1] == '\n') {
    bookname[strlen(bookname) - 1] = '\0'; // delete '\n' in buffer
  }
  printf("Enter your name: ");
  fgets(username, MAX, stdin); // enter user's name
  if (username[strlen(username) - 1] == '\n') {
    username[strlen(username) - 1] = '-'; // delete '\n' in buffer
  }

  FILE *fp1 = fopen("library.txt", "r"); // Open "library.txt" as "read"

  fgets(qty, MAX,
        fp1); // read first line from "library.txt" and store it in 'qty'
  sscanf(qty, "%d", &quantity); // scan %d from 'qty' and store it in 'quantity'
  quantity++;                   // increase size for every each line
  char *history =
      (char *)calloc(quantity * MAX,
                     sizeof(char)); // allocate memories for 'history' by calloc
  char *buffer = (char *)calloc(
      quantity * MAX, sizeof(char)); // allocate memories for 'buffer' by calloc

  FILE *fp2 = fopen("copy.c", "w"); // Open "copy.c" as "write"
  fprintf(
      fp2, "%d",
      quantity); // write the 'quantity' value onto the first line of "copy.c"

  while (!feof(fp1)) {
    fgets(buffer, quantity * MAX * sizeof(char),
          fp1); // store all the line data to 'buffer'
    sscanf(buffer, "%39[^,], %39[^,],%d,%d,%s", book.bookname, book.authorname,
           &book.publishyear, &book.status,
           history); // seperate each data type
    if (strcmp(book.bookname, bookname) ==
        0) { // check if 'bookname' value is equal to 'book.bookname'

      if (book.status == 0) {      // check if 'book.status' is false
        book.status = 1;           // turn it to true
        strcat(history, username); // concat 'username' to 'history'
      } else {
        printf("This book doesn't been borrow yet");
      }
    }

    fprintf(fp2, "\n%s,%s,%d,%d,%s", book.bookname, book.authorname,
            book.publishyear, book.status,
            history); // copy all the data from "library.txt" to "copy.c"
  }
  fclose(fp1);                     // close file
  fclose(fp2);                     // close file
  rename("copy.c", "library.txt"); // rename "copy.c" to "library.txt"
  free(buffer);                    // free memories
  free(history);                   // free memories
}

int validatestring(char *s) { // check the special char
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == ',' || s[i] == '-') {
      return 0;
    }
  }

  return 1;
}

int isduplicate(char *name) { // check if the book is already in the stock or
                              // not
  FILE *fp = fopen("library.txt", "r");
  int quantity = 0;
  char qty[MAX];
  char buffer[MAX];
  BOOK_T book;
  fgets(qty, MAX, fp);
  while (!feof(fp)) {
    fgets(buffer, MAX, fp);
    // printf("Passed buffer\n");
    sscanf(buffer, "%39[^,], %39[^,],%d,%d,%s", book.bookname, book.authorname,
           &book.publishyear, &book.status, book.borrowhistory);
    // printf("%s",book.bookname);
    if (strcmp(name, book.bookname) == 0) {
      fclose(fp);
      return 1;
    }
  }

  fclose(fp);
  return 0;
}

int isinteger(char *s) {
  for (int i = 0; i < strlen(s); i++) {
    if (!isdigit(s[i]))
      return 0;
  }
  return 1;
}