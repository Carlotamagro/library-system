#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define MAX_BOOKS 300

typedef struct{
   int ID;
   char title[50];
   char author [50];
   char ISBN [14];
   char genre [20];
   bool read;
} book;

book books[MAX_BOOKS];

int books_total = 0;


int comparesIgnoreCase(const char *str1, const char *str2) {
   int i;
    
   for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
      if (tolower((unsigned char)str1[i]) != tolower((unsigned char)str2[i])) {
         return 0; // Encontrou uma letra diferente, logo não são iguais
      }
   }
    
   if (str1[i] == '\0' && str2[i] == '\0') {
      return 1; // São iguais
   }
    
   return 0; // Tinham a mesma base, mas tamanhos diferentes (ex: "Sci" e "Sci Fi")
}

void read_data() {
   FILE *f_books;
        
   f_books = fopen("books.csv", "r"); 
    
   if (f_books == NULL) {
        printf("Error opening the file!");
        return; //early return, so p/ sair da funcao mais cedo
   }

   int read_temp; //variavel temporaria para ler bool

   for (int i=0;i<MAX_BOOKS;i++){
      if (fscanf(f_books,"%d,%49[^,],%49[^,],%13[^,],%19[^,],%d", &books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].genre, &read_temp)!=6){
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
      printf("ID:%d | Title:%s | Author:%s | ISBN:%s | Genre:%s | Status: %s\n", books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].genre, books[i].read ? "read" : "unread");
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

void byGenre(char *genre){

   int found = 0;
   for (int i=0;i<books_total;i++){
        if (comparesIgnoreCase(books[i].genre, genre)==1){ 
            printf("ID:%d | Title:%s | Author:%s | ISBN:%s | Status: %s\n", books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].read ? "read" : "unread");
            found++;
         }
   } 
   

   if (found==0) printf ("No books found!");
   else printf("%d books found!", found);
}

void byAuthorAlphabetically(){

   //fazer uma copia do array dos livros
   book copy[books_total];

   for (int i=0;i<books_total;i++){
      copy[i]=books[i];
   }

   //organizar alfabeticamente por autor - bubble sort
   for (int j=0;j<books_total-1;j++){
      for (int k=0;k<books_total-1-j;k++){
         if (strcasecmp(copy[k].author,copy[k+1].author)>0){
            book temp = copy[k];
            copy[k]=copy[k+1];
            copy[k+1]=temp;
         }
      }
   }

   for (int i=0;i<books_total;i++){
      printf("ID:%d | Title:%s | Author:%s | ISBN:%s | Status: %s\n", copy[i].ID, copy[i].title, copy[i].author, copy[i].ISBN, copy[i].read ? "read" : "unread");
   }

}

void byTitleAlphabetically(){

   //fazer uma copia do array dos livros
   book copyT[books_total];

   for (int i=0;i<books_total;i++){
      copyT[i]=books[i];
   }

   //organizar alfabeticamente por titulo
   for (int j=0;j<books_total-1;j++){
      for (int k=0;k<books_total-1-j;k++){
         if (comparesIgnoreCase(copyT[k].title,copyT[k+1].title)>0){
            book temp = copyT[k];
            copyT[k]=copyT[k+1];
            copyT[k+1]=temp;
         }
      }
   }

   for (int i=0;i<books_total;i++){
      printf("ID:%d | Title:%s | Author:%s | ISBN:%s | Status: %s\n", copyT[i].ID, copyT[i].title, copyT[i].author, copyT[i].ISBN, copyT[i].read ? "read" : "unread");
   }

}

void search(char *target){

   for (int i=0;i<books_total;i++){
      if (comparesIgnoreCase(books[i].author, target)==1 || comparesIgnoreCase(books[i].title, target)==1 || comparesIgnoreCase(books[i].ISBN, target)==1 ){
         printf("ID:%d | Title:%s | Author:%s | ISBN:%s | Status: %s\n", books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].read ? "read" : "unread");
      }
   }
   //is this the rifht book? mark as read if yes

}

void listByStatus(bool isRead){
   for (int i=0;i<books_total;i++){
      if (books[i].read == isRead){
         printf("ID:%d | Title:%s | Author:%s | ISBN:%s | Status: %s\n", books[i].ID, books[i].title, books[i].author, books[i].ISBN, books[i].read ? "read" : "unread");
      }
   }
}

void addBook(char* title, char* author, char* isbn, char* genre, int temp) {

   if (books_total >= MAX_BOOKS) {
      printf("Not enough space for more books\n");
      return;
   }
   books[books_total].ID = books_total + 1;

   strcpy(books[books_total].title, title);
   strcpy(books[books_total].author, author);
   strcpy(books[books_total].ISBN, isbn);
   strcpy(books[books_total].genre, genre);
   books[books_total].read = temp;

   books_total++;

   write_data();
}

//stats?
int main() {
   read_data();
   int id;
   char title[50], author[50], isbn[14];
   char genre[50], status[20];
   bool read;
   int temp;
   int c;
   char target[50];

   bool validOption = false;

   do {
      printf("Do you want to see your read or unread books?\n");
      scanf("%19s", status);

      if (comparesIgnoreCase(status, "read")) {
         listByStatus(true);
         validOption = true;
      } 
      else if (comparesIgnoreCase(status, "unread")) {
         listByStatus(false);
         validOption = true;
      } 
      else {
         printf("Erro! Escreve apenas 'read' ou 'unread'.\n");
      }

   } while (validOption == false);

   int opcao;

   do {
      printf("\n=== Welcome to your library ===\n");
      printf("1. List library\n");
      printf("2. Add book\n");
      printf("3. Register read\n");
      printf("4. Delete book\n");
      printf("5. List Read/Unread books\n");
      printf("6. List books alphabetically (by title).\n");
      printf("7. List books alphabetically (by author).\n");
      printf("8. List books of a certain genre.\n");
      printf("9. Sair do programa\n");
      printf("Opcao: ");
      scanf("%d", &opcao);
      
      //limpar o buffer
      while ((c = getchar()) != '\n' && c != EOF);

      switch (opcao) {
         case 1:
            list_books();
            break;
         case 2: {
            printf("Title: ");
            fgets(title,sizeof(title),stdin);
            title[strcspn(title, "\n")] = '\0';

            printf("Author: ");
            fgets(author,sizeof(author),stdin);
            author[strcspn(author, "\n")] = '\0';

            do {printf("ISBN (10 or 13 digits): ");
            fgets(isbn,sizeof(isbn),stdin);
            isbn[strcspn(isbn, "\n")] = '\0';
            
            } while (strlen(isbn)>14);

            printf("Genre: ");
            fgets(genre,sizeof(genre),stdin);
            genre[strcspn(genre, "\n")] = '\0';
            
            do{
            printf("Read(1)/Unread(0):");
            scanf("%d", &temp);
            }while (temp!=1 && temp!=0);
            
            addBook(title, author, isbn, genre, temp);
            
            break;
         }
         case 3: {
            printf("Search the book you want to mark as read:");
            fgets(target,sizeof(target),stdin);
            search(target);

         break;
         }
         case 4: {
         
         break;
         }
         case 5:
         
         case 6: {
         
         }
         case 7: {

         }
         case 8:
            printf("A sair...\n");
            break;

         default:
            printf("Opcao invalida.\n");
         }
} while (opcao != 8);

}