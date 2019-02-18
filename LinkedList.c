/* Operating and maintaing a list */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _book {
  char title[200];
  struct _book *next;
  int Maci;

} Book;

typedef Book *BookPtr;

typedef struct _shelf { /* self-referencing structure */
  char data;
  char name[100];
  int numBooks;
  struct _shelf *nextPtr;
  BookPtr placedBook; 
} Shelf;

//typedef struct _shelf Shelf;
typedef Shelf *ShelfPtr;

void insert(ShelfPtr *, char, char*, int, BookPtr *);
char delete(ShelfPtr *, char, char*, int, BookPtr *);
int isEmpty(ShelfPtr);
void printList(ShelfPtr);
void instructions(void);

int main(void) {
  ShelfPtr startPtr = NULL;
  BookPtr firstPtr = NULL;
  int choice;
  char item;
  char nameOfShelf[100];
  int number;

  instructions(); /* display the menu */
  printf("? ");
  scanf("%d", &choice);

  while (choice != 4) {
    switch (choice)
    {
      case 1:
        printf("Enter a new shelf: ");
        printf("Enter a character: ");
        scanf("\n%c", &item);
        printf("Enter a name: ");
        scanf("\n%s", nameOfShelf);
        //scanf("%[^\n]%*c", nameOfShelf); 
        printf("Enter number of books on the self: ");
        scanf("\n%d", &number);
        insert(&startPtr, item, nameOfShelf, number, &firstPtr);
        printList(startPtr);
        break;
      case 2:
        if (!isEmpty(startPtr)) {
          printf("Enter character to be deleted: ");
          scanf("\n%c", &item);

          if (delete(&startPtr, item, nameOfShelf, number, &firstPtr)) {
            printf("%c deleted. \n", item);
            printList(startPtr);
          } else {
            printf("%c not found.\n\n", item);
          }
        } else {
          printf("List is empty.\n\n");
        }
        break;
      case 3:
        printList(startPtr);
        break;
      default:
        printf("Invalid choice.\n\n");
        instructions();
        break;
    }

    printf("? ");
    scanf("%d", &choice);
  }
  printf("End of run.\n");
  return 0;
}

/* Print the instructions */
void instructions(void) {
  printf("Enter your choice:\n"
         "    1 to insert a shelf into the list.\n"
         "    2 to delete a shelf into the list.\n"
         "    3 to print the list.\n"
         "    4 to end.\n"
         "? ");
}

/* Insert a new _shelf into the list in sorted order */
void insert(ShelfPtr *sPtr, char value, char* nameOfShelf, int number, BookPtr *fPtr) {
  ShelfPtr newPtr, previousPtr, currentPtr;

  newPtr = malloc(sizeof(Shelf));

  if (newPtr != NULL) { /* is space available */
    newPtr->data = value;
    strcpy(newPtr->name,nameOfShelf);
    newPtr->numBooks = number;
    newPtr->placedBook = *fPtr;
    newPtr->nextPtr = NULL;

    previousPtr = NULL;
    currentPtr = *sPtr;

    while(currentPtr != NULL && value > currentPtr->data ){
      previousPtr = currentPtr;         /* walk to ...   */
      currentPtr = currentPtr->nextPtr; /* ... next _shelf */
    }

    if (previousPtr == NULL) {
      newPtr->nextPtr = *sPtr;
      *sPtr = newPtr;
    } else {
      previousPtr->nextPtr = newPtr;
      newPtr->nextPtr = currentPtr;
    }
  } else {
      printf("%c not inserted. No memory available.\n", value);
  }
}

/* Delete a list element */
char delete(ShelfPtr *sPtr, char value, char* nameOfShelf, int number, BookPtr *fPtr) {
  ShelfPtr previousPtr, currentPtr, tempPtr;

  if (value == (*sPtr)->data) {
    tempPtr = *sPtr;
    *sPtr = (*sPtr)->nextPtr;
    free(tempPtr);
    return value;
  } else {
    previousPtr = *sPtr;
    currentPtr = (*sPtr)->nextPtr;

    while (currentPtr != NULL && currentPtr->data != value) {
      previousPtr = currentPtr;         /* walk to ...   */
      currentPtr = currentPtr->nextPtr; /* ... next _shelf */
    }

    if (currentPtr != NULL) {
      tempPtr = currentPtr;
      previousPtr->nextPtr = currentPtr->nextPtr;
      free(tempPtr);
      return value;
    }
  }

  if (fPtr != NULL) {
    free(fPtr);
  }

  return '\0';
}

/* Return 1 if the list is empty, 0 otherwise */
int isEmpty(ShelfPtr sPtr)
{
  return sPtr == NULL;
}

/* Print the list */
void printList(ShelfPtr currentPtr) {
  if (currentPtr == NULL) {
    printf("List is empty.\n\n");
  } else {
    printf("The list is:\n");

    while (currentPtr != NULL) {
      printf("%c: ", currentPtr->data);
      printf("%s, ", currentPtr->name);
      printf("%d, ", currentPtr->numBooks);
      printf("%p,", currentPtr->placedBook);
      printf(" ---> ");
      currentPtr = currentPtr->nextPtr;
    }

    printf("NULL\n\n");
  }
}

