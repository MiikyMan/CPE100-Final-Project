# CPE-100 Final Project
This project is database management of library that have function as follows

- Add and Remove books in library
- Editing book details
- Searching book's name or/and author name
- borrow book system
- All data save into file automatically
## Files in Project
We have 4 main files 

- main.c
- function.c
-  function.h
-  library.txt

---



## Files 

- ### main.c
  - This is the main file we used to call entire functions from _'function.c'_ to management library system.
- ### function.c
  - This file contain all function commands for _'main.c'_ to run the commands
- ### function.h
  - This is header file we generally contain several function declarations including define the structure.
- ### library.txt
  - This is database file that stores data in structured form about books in library.
  - This file type is __" Text file "__
  -  we collect the data with stores every information about the book in 1 line and saperate each data with __","__

This is example of "library.txt" file.

~~~c
phuris,pimpat,5555,1,-phuris-phuris-
 
toey toey,hed yung,2020,0,-BOOM-

BANGMOD,MOD,1988,1,-  
~~~

And this is the database table of "library.txt" file
| Book's name  | Author's name|Publish year| Status |Borrower|Returner|
| ------------ | ------------ | ---------- |------- |--------|--------|
| phuris       | pimpat       |      5555  |   1    | phuris | phuris |
| toey toey    | hed yung     |       2020 |   0    | BOOM   |  -     |
| BANGMOD      | MOD          |       1988 |   1    |   -    |        |


---

## Structure Design
- The main point to design this structure is store all information of the book. We definition the field that must have for library system.
~~~c
typedef struct {
  
  char bookname[MAX]; // a character array to storing the name of the book.
  
  char borrowhistory[MAX]; // a character array storing the borrowing history of the book.
  
  char authorname[MAX]; // a character array storing the name of the author of the book.
  
  char publish[MAX]; // we use this when 'int publishyear' is bug 

  int publishyear; // an integer representing the year in which the book was published.
  
  int status; // an integer representing the status of the book (available, borrowed).
  
  char charstatus[MAX]; // we use this when 'int status' is bug
  
  char history[MAX]; //a character array storing a history of the book (who borrowed it, who was returned it).
} BOOK_T;
~~~

## Limitation of Program
- book's name have maximum 1024 character to input.
- author's name have maximum 1024 character to input.
- special character only ' , ' and ' - ' must __not__ be input.

## Function.c
In 'function.c', this file contain all necessary function such as, 

- ### Addbook function
This function add a new book to a library database stored in a text file called "library.txt". It takes a structure called BOOK_T as an argument, which is used to store the book's name, author's name, and publication year.

1. The function opens the "library.txt" file in append mode using the _'fopen()'_
~~~c
FILE *fp = fopen("library.txt", "a");//Open "library.txt" as "append"
~~~

2. It reads the book's name from standard input using _'fgets()'_ and stores it in the _'bookname'_ field of the structure.

3. The function prompts the user to enter the title, author's name, and publication year of the book and reads the input using _'fgets()'_ and _'scanf()'_ respectively. It stores the entered values in the corresponding fields of the structure
~~~c
      fgets(book.bookname, MAX, stdin);

      printf("Enter title: ");
      fgets(book.bookname, MAX, stdin);//Enter new book's name
      if (book.bookname[strlen(book.bookname) - 1] == '\n') {
        book.bookname[strlen(book.bookname) - 1] = '\0';//delete \n from buffer
      }

      printf("Author Name: ");
      fgets(book.authorname, MAX, stdin);//Enter new book's author name
      if (book.authorname[strlen(book.authorname) - 1] == '\n') {
        book.authorname[strlen(book.authorname) - 1] = '\0';//delete \n from buffer
      }
      printf("Publish year: ");
      scanf("%d",&book.publishyear);//Enter new book's publish year
~~~

4. The function checks if the last character of the entered book name and author name is a new line character _('\n')_ and replaces it with a null character ('\0') to remove the new line from the strings.
~~~c
if (book.bookname[strlen(book.bookname) - 1] == '\n') {
        book.bookname[strlen(book.bookname) - 1] = '\0';//delete \n from buffer
  }
  
~~~

5. The function writes the book's information to the _"library.txt"_ file using _'fprintf()'_ and followed by the values _"1"_ and _"-"_ which represent the availability and borrower information of the book.
~~~c
fprintf(fp, "\n%s,%s,%d,1,-", book.bookname, book.authorname,
              book.publishyear);  //Append all new book's information to "library.txt"
~~~

6. The function closes the file using _'fclose()'_.
~~~c
fclose(fp);}  //close file

~~~

---
- ### Remove book function
This function removes a book from a library database stored in a file called "library.txt" 

1. thr function first reads in a line from "library.txt" and stores it in the _'qty'_ variable. Then uses _'sscanf'_ to parse an integer from _'qty'_ and store it in _'quantity'_.
~~~c
fgets(bookname, MAX, stdin);
      FILE *fp1 = fopen("library.txt", "r");  //Open "library.txt" as "read"
      
      fgets(qty, MAX, fp1);  //read first line from "library.txt" and store it in 'qty'
      sscanf(qty,"%d",&quantity);  //scan %d from 'qty' and store it in 'quantity'
~~~

2. Next, the function allocates memory for two character arrays, _'history'_ and _'buffer'_, using the _'calloc'_. Then opens a file called _"copy.c"_ in write mode and writes _'quantity'_ to the first line of the file.
~~~c
char* history = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'history' by calloc
      char* buffer = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'buffer' by calloc
      
      FILE *fp2 = fopen("copy.c", "w");  //Open "copy.c" as "write"
      fprintf(fp2,"%d",quantity);  //write value of 'quantity' to the first line of "copy.c"
~~~

3. The function then prompts the user to enter the title of the book to be removed and reads the input into the _'bookname'_ array. It removes the newline character at the end of the input string if present.
~~~c
printf("Enter title to be remove: ");
      fgets(bookname, MAX, stdin);  //enter the book name to be remove
      if (bookname[strlen(bookname) - 1] == '\n') {
        bookname[strlen(bookname) - 1] = '\0';  //delete '\n' from buffer
      }
~~~

4. The function then reads lines from _'library.txt'_ one by one and stores them in the _'buffer'_ array. It uses _'sscanf'_ to parse the book name from each line and compares it to the book name the user entered. If the book names do not match, the function writes the current line to "copy.c".
~~~c
while (!feof(fp1)){
        fgets(buffer, quantity*MAX*sizeof(char), fp1);
        if(buffer[strlen(buffer)-1]=='\n')
        {
          buffer[strlen(buffer)-1]='\0';  //delete '\n' from buffer
        }
        sscanf(buffer, "%39[^,]", book.bookname);  //search for book name from each line
        if (strcmp(book.bookname, bookname) != 0){
          fprintf(fp2,"\n%s", buffer);  //copy all the data from "library.txt" to "copy.c"
        }
      }
~~~

5. Finally, the function closes both "library.txt" and "copy.c", renames "copy.c" to "library.txt", and frees the memory allocated for the file pointers.
~~~c
fclose(fp1);  //close "library.txt"
      fclose(fp2);  //close "copy.c"
      rename("copy.c", "library.txt");  //rename from "copy.c" to "library.txt"
  free(fp1);  //free memories
  free(fp2);  //free memories
}
~~~


---
- ### Edit book function

This function allow user to edit the book's details that already had in database.

1. Dynamically allocates memory for two character arrays _'history'_ and _'buffer'_.
~~~c
 char* history = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'history' by calloc
      char* buffer = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'buffer' by calloc
~~~

2. Writes the value of the _'quantity'_ variable to the first line of _'copy.c'_.
~~~c
 FILE *fp2 = fopen("copy.c", "w");   //Open "copy.c" as "write"
      
      fprintf(fp2, "%d\n",quantity);  //write value of 'quantity' to the first line of "copy.c"
~~~
3. Begins a loop that reads lines from _'library.txt'_ and stores them in the _'buffer'_ variable and uses _'sscanf'_ to parse the contents of _'buffer'_ and extract the values of the structure.
~~~c
while (!feof(fp1)) {
        fgets(buffer, quantity*MAX*sizeof(char) , fp1);  //store all the line data to 'buffer'
        sscanf(buffer, "\n%39[^,],%39[^,],%39[^,],%39[^,],%39[^,]", book.bookname, book.authorname,book.publish, book.charstatus,history);  //seperate each data type
~~~

4. If the value of the _'bookname'_ matches the _'bookname'_ entered by the user, the function prompts the user to enter new values for the newbook. If the user enters a new value, the function updates in the structure with the new value.
~~~c
 if (strcmp(book.bookname, bookname) == 0) {
          printf("New title (leave blank to retain old value): ");
          fgets(newbookname, MAX,stdin);//Enter new book's name

          if (newbookname[0] != '\n') {
            if(newbookname[strlen(newbookname)-1]=='\n'){
              newbookname[strlen(newbookname)-1]='\0';  //delete '\n' from buffer
            }
            strcpy(book.bookname,newbookname);  //copy 'newbookname' value into 'book.bookname'
          }
~~~

5. Writes the updated values of the _'bookname'_, _'authorname'_, _'publishyear'_, _'charstatus'_, and _'history'_ to _'copy.c'_.

6. Finally, this function update the details of a book by reading and parsing the data from _'library.txt'_ and writing the update data to _'copy.c'_.
~~~c
fprintf(fp2, "%s,%s,%s,%s,%s", book.bookname, book.authorname,
                book.publish, book.charstatus, history);  //write all data to "copy.c"
      }
      fclose(fp1);//close "library.txt"
      fclose(fp2);//close "copy.c"
      rename("copy.c", "library.txt");//rename from "copy.c" to "library.txt"
  free(fp1);//free memories
  free(fp2);//free memories
}
~~~



---
- ### Show all book function


Meaning as it seen, This function show every book that already had data in database file, we don't only show the book's details but also who borrowed.

first, we have to allocate the menories to read all the texts in each line

~~~c
FILE *fp = fopen("library.txt","r");
  fgets(qty, MAX, fp);
  sscanf(qty,"%d",&quantity);
  char* history = (char*)calloc(quantity*MAX,sizeof(char));
  char* buffer = (char*)calloc(quantity*MAX,sizeof(char));
      

~~~
Then we'll read all texts in _"library.txt"_ and keep it in _"buffer"_ factor, after that we'll display all factor to monitor
~~~c
while(!feof(fp)){
  fgets(buffer, MAX, fp);
  sscanf(buffer, "%39[^,],%39[^,],%d,%d,%s", book.bookname,
                       book.authorname, &book.publishyear, &book.status,
                       history);
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

~~~
To show the borrowed history we use _"strtok"_ to separate
returner and borrower with '-' 
~~~c
 char *token = strtok(book.borrowhistory, "-");        
    while (token != NULL){
      if(borrow == 0){
      printf("   -Borrowed by %s\n", token);
      borrow = 1;
      } else if(borrow == 1){
          printf("   -Returned by %s\n", token);
          borrow = 0;
        }     		
    token = strtok(NULL, "-");
    }

      
~~~


---
- ### book Searching function

This code provides a function for searching a library's database for books based on their title and/or author name. The user is prompted to enter a title and/or author name to search for, and the function searches a file called _"library.txt"_ for matching entries.

This code has the steps to work as follows:
1. Users have to enter the books name and authors name.
~~~c
fgets(bookname, MAX, stdin);

      printf("Enter title (leave blank to include all titles): ");
      fgets(bookname, MAX, stdin);  //enter book's name for searching

      printf("Enter author name (leave blank to include all author names: ");
      fgets(authorname, MAX, stdin);  //enter author's name for searching
      
~~~
2. The function reads in the user's search criteria and then opens the file in read mode. 
~~~c
FILE *fp = fopen("library.txt", "r");  //open "library.txt" as "read"
  fgets(qty, MAX, fp);  //read first line from "library.txt" and store it in 'qty'
  sscanf(qty,"%d",&quantity);  //scan %d from 'qty' and store it in 'quantity'
  char* history = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'history' by calloc
  char* buffer = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'buffer' by calloc
  bookspace = isspace(bookname[0]);  //check if 'bookname' is just a white-space charactor
  authorspace = isspace(authorname[0]);  //check if 'authorname' is just a white-space charactor
~~~
3. Then enter a loop that continues untill the end of the file is reached. In each iteration of the loop the function reads in a line from the file and uses the _'sscanf'_ function to parse the values in the line and store them in a _'book'_ struct.
~~~c
while (!feof(fp)) {
  fgets(buffer,quantity*MAX*sizeof(char), fp);  //store all the line data to 'buffer'
  sscanf(buffer, "%39[^,],%39[^,],%d,%d,%s",book.bookname,book.authorname, &book.publishyear, &book.status, history);  //seperate each data type
~~~
3.1.  check if 'bookspace' is white-space character or not
~~~c
if (bookspace == 0 && authorspace != 0) {  //run this function when 'authorspace' is white-space character
  if (strstr(book.bookname, bookname) != NULL) {  //check if there is a 'bookname' string in 'book.bookname'
~~~
3.2.  check if 'authorspace' is white-space character or not
~~~c
else if (authorspace == 0 && bookspace != 0) {  //run this function when 'authorspace' is white-space character
  if (strstr(book.authorname, authorname) != NULL) {  //check if there is a 'authorname' string in 'book.authorname'
~~~
3.3. check if both is not a white-space charactor
~~~c
else if (authorspace == 0 && bookspace == 0) {  //run this function when both is not white-space character 
  if (strstr(book.bookname, bookname) != NULL || strstr(book.authorname, authorname) != NULL) {  //check if there is a 'bookname' string in 'book.bookname' or there is a 'authorname' string in 'book.authorname'
~~~
4. After all the gates have passed, this function will show all books that relate to user's input
~~~c
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
  while (token != NULL){
    if(borrow == 0){
      printf("   -Borrowed by %s\n", token);
      borrow = 1;
    } else if(borrow == 1){
        printf("   -Returned by %s\n", token);
        borrow = 0;
      }
        token = strtok(NULL, "-");
  }
    borrow = 0;
    printf("\n");
    count++;  //do the same as "Showbook" function
~~~
---
- ### book borrowing/returning function

These two functions will turn a fourth parameter of line user chooses from 1 to 0 and from 0 to 1 (depends on users purpose), that means that book will transforms itself from available to unavailable and from unavailable to available. 

This code has the steps to work as follows:
1. Users have to enter the books name and authors name.
~~~c
 printf("Enter title to be borrow/return: ");
      fgets(bookname, MAX, stdin);
      fgets(bookname, MAX, stdin);  //enter book's name to be borrow
      if (bookname[strlen(bookname) - 1] == '\n') {
        bookname[strlen(bookname) - 1] = '\0';  //delete '\n' in buffer
      }
      printf("Enter your name: ");
      fgets(username, MAX, stdin);  //enter user's name
      if (username[strlen(username) - 1] == '\n') {
        username[strlen(username) - 1] = '-';  //delete '\n' in buffer
      }
~~~

2. We will allocate the memories to read all the texts in each line.
~~~c
FILE *fp1 = fopen("library.txt", "r");  //Open "library.txt" as "read"

      fgets(qty, MAX,fp1);  //read first line from "library.txt" and store it in 'qty'
      sscanf(qty,"%d", &quantity);  //scan %d from 'qty' and store it in 'quantity'
      quantity++;  //increase size for every each line
      char* history = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'history' by calloc
      char* buffer = (char*)calloc(quantity*MAX,sizeof(char));  //allocate memories for 'buffer' by calloc
~~~

3. We will open _"copy.c"_ as "write" to edit text from _"library.txt"_.
~~~c
FILE *fp2 = fopen("copy.c", "w");  //open file as "write"

~~~

4. We will read all the texts from _"library.txt"_ and copy all of them to _"copy.c"_.
~~~c
fprintf(fp2, "%d",quantity);  //write the 'quantity' value onto the first line of "copy.c"
      
  while (!feof(fp1)) {
  fgets(buffer,quantity*MAX*sizeof(char), fp1);  //store all the line data to 'buffer'
  sscanf(buffer, "%39[^,], %39[^,],%d,%d,%s", book.bookname,
               book.authorname, &book.publishyear, &book.status,
               history);
~~~

  4.1. Except the line that matched to the book name that user enters, because we've to change the 'book.status' to 0/1 (depends on users purpose) and save the name of borrower/returner to database by using "strcat" function from <string.h> library.
~~~c
  if (strcmp(book.bookname, bookname) == 0) {  //check if 'bookname' value is equal to 'book.bookname'
  if (book.status == 0) {  //check if 'book.status' is false
    book.status = 1;  //turn it to true
    strcat(history, username);  //concat 'username' to 'history'
  } else {
      printf("This book is unavilable/ This book doesn't been borrow yet");
    }
  }
~~~

5. Closes of the files and rename the "copy.c" to "library.txt" and free the memories to finish the progress. 
~~~~c
fclose(fp1);  //close file
      fclose(fp2);  //close file
      rename("copy.c", "library.txt");  //rename "copy.c" to "library.txt"
  free(buffer);  //free memories
  free(history);  //free memories
~~~~