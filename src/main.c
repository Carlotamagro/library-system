#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define MAX_BOOKS 300;

typedef struct{
   int ID;
   char title[50];
   char author [50];
   char ISBN [14];
   char genre [20];
   bool read;
} book;

book books[MAX_BOOKS]

int books_total = 0;

void read_data() {
   FILE *f_books;
        
   f_books = fopen("books.csv", "r"); 
    
   if (f_books == NULL) {
        printf("Error opening the file!");
        return; //early return, so p/ sair da funcao mais cedo
   }

   int read_temp; //variavel temporaria para ler bool

   for (int i=0;i<MAX_BOOKS;i++){
      if (fscanf(f_books,"%d,%s,%s,%s,%s,%d", &books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].genre, &read_temp)!=6){
         break;
      }
      books[i].read = (bool)read_temp;
      books_total++;
   }

   fclose(f_books);

}

void list_books(){
   printf("===BOOKS===\n");

   for (int i=0;i<books_total;i++){ 
      printf("ID:%d | Title:%s | Author:%s | ISBN:%s | Genre:%s | Read: %s", books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].genre, books[i].read ? "read" : "unread");
   }
}

void write_data(){
   FILE *f_books;
        
   f_books = fopen("books.csv", "w"); 
    
   if (f_books == NULL) {
        printf("Error writing on the file!");
        return;
   }

   for (int i=0;i<books_total;i++){
      fprintf(f_books, "%d,%s,%s,%s,%s,%d\n", books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].genre, (int)books[i].read);
   }

   fclose(f_books);

}

void verify_isbn(char *ISBN){
   if (strlen(ISBN)>14) printf("Erro! ISBN muito grande");
}

//list books by genre/unread/title/author
//stats


int main() {
   
}