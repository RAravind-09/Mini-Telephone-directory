5//!!Telephone Directory!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct Node Creation using Double Linked List
struct node {
  char name[50];
  char phone[15];
  struct node *prev;
  struct node *next;
} *head = NULL, *stack[25]; // Declaring head = NULL
// !!Declaring all Necessary Functions!!
int top = -1;
void insert_contact(char *name, char *phone);
void display_directory();
int delete_contact(char *name);
void update_contact(char *name);
void search_by_name(char *name);
void search_by_number(char *phone);
int check_number(char *phone);
int check_phone(char *phone);
int check_name(char *name);
void save_directory(struct node *root);
int delete_phone(char *phone);
void recycle_bin();
void push(char *name, char *phone);
int main() {
  printf("\t\t\t\t!!!!Enter First Letter in Capital and No White Spaces!!!!\n");
  char name[50];
  char phone[15];
  char c;
  int ch;
  // Inserting random Contacts in Directory.
  insert_contact("Chaitu", "1234567890");
  insert_contact("Ganesh", "1234567890");
  insert_contact("Dileep", "1234567890");
  insert_contact("Aravind", "1234567890");
  insert_contact("Anil", "1234567890");

  printf("Enter Choice\n");
  printf("1.Add(To Create Contact)\n2.Delete(To Delete "
         "Contact)\n3.Update\n4.Search\n5.Display\n6.Recyle Bin\n0.Exit\n");
  while (1) { //! Infinity Loop!
    printf("Enter choice : ");
    scanf("%d", &ch);
    switch (ch) {
    case 1: // To insert a new Contact!
      printf("Enter Name to create Contact  : ");
      scanf("%s", name);
      printf("Enter Phone Number to Contact : ");
      scanf("%s", phone);
      insert_contact(&name, &phone);
      printf("Contact Created Sucessfully!!\n");
      break;
    case 2: // To Delete a Contact!
      printf("Do You want to Delete by Name or Phone(N/P) : ");
      scanf("%s", &c);
      if (c == 'N' || c == 'n') {
        printf("Enter Name to Delete Contact in Directory : ");
        scanf("%s", name);
        int c = delete_contact(&name);
        if (c == 1) {
          printf("Conatct Deleted Sucessfully\n");
        }
      } else if (c == 'P' || c == 'p') {
        printf("Enter Phone Number to Delete contact in Directory : ");
        scanf("%s", phone);
        delete_phone(&phone);
        if (c == 1) {
          printf("Conatct Deleted Sucessfully\n");
        }
      } else {
        printf("Wrong Choice Try Again!!\n");
      }
      break;
    case 3:
      printf("Enter previous name to update contact : ");
      scanf("%s", name);
      update_contact(&name);
      break;
    case 4: // To Search a contact
      printf("Do You want to search by Name or Number(N/P) : ");
      scanf("%s", &c);
      if (c == 'N' || c == 'n') {
        printf("Enter Name to search in Directory : ");
        scanf("%s", name);
        search_by_name(&name);
      } else if (c == 'P' || c == 'p') {
        printf("Enter Phone Number to search in Directory : ");
        scanf("%s", phone);
        search_by_number(&phone);
      } else {
        printf("Wrong Choice Try Again!!\n");
      }
      break;
    case 5: // To display contact!
      display_directory();
      break;
    case 6:
      recycle_bin();
      break;
    case 0:
      printf("Do you want to save the Directory in the file{y/n) : ");
      scanf("%s", &c);
      if (c == 'Y' || c == 'y') {
        save_directory(head);
      }
      printf("!!!Thank you:)!!!");
      exit(0);
      break;
    default:
      printf("!!Invaild Choice!!");
    }
  }

  return 0;
}
// Function to insert a new node in the Directory.
void insert_contact(char *name, char *phone) {
  if (check_number(phone) !=
      1) // Checking weather Phone Number is valid or not.
  {
    printf("Invalid Phone Number.Try again!!!\n");
    return;
  }
  if (check_phone(phone) ==
      1) // Checking weather Phone Number is present in Directory.
  {
    printf("Phone Number alreaday exists!!!\n");
    return;
  }
  struct node *new_node = (struct node *)malloc(sizeof(struct node));
  strcpy(new_node->name, name);
  strcpy(new_node->phone, phone);
  new_node->prev = NULL;
  new_node->next = NULL;

  // If list is empty, make new node as head.
  if (head == NULL) {
    head = new_node;
    return;
  }

  // Inserting the Contact in Alphabetical order.
  struct node *temp = NULL, *current = head;
  while (current != NULL && strcmp(current->name, name) < 0) {
    temp = current;
    current = current->next;
  }

  if (temp == NULL) {
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  } else {
    temp->next = new_node;
    new_node->prev = temp;
    new_node->next = current;
    if (current != NULL) {
      current->prev = new_node;
    }
  }
}

// Function to display the directory.
void display_directory() {
  struct node *temp = head;
  for (int i = 0; i <= 31; i++) {
    printf("~~");
  }
  printf("\n");
  while (temp != NULL) {
    printf("{");
    printf("\tName\t:\t%s\tPhone\t:\t%s\t}\n", temp->name, temp->phone);
    temp = temp->next;
  }
  for (int i = 0; i <= 31; i++) {
    printf("~~");
  }
  printf("\n");
}
// Function to Delete Contact in the Directory.
int delete_contact(char *name) {
  char phone[15];
  char prev_name[50];
  char prev_phone[15];
  if (check_name(name) > 1) // Checking the name has Repetations are not.
  {
    printf("Repetation Names are found\n");
    printf("Enter Phone Number to Delete in Directory : ");
    scanf("%s", phone);
    int c = delete_phone(&phone);
    return;
  }
  struct node *temp = head;

  while (temp != NULL) {
    if (strcmp(temp->name, name) == 0) {
      strcpy(prev_name, temp->name);
      strcpy(prev_phone, temp->phone);
      if (temp->prev == NULL) { // Checking if only one node exists.
        head = temp->next;
        if (temp->next != NULL) {
          temp->next->prev = NULL;
        }
      } else { // More than One node exists.
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
          temp->next->prev = temp->prev;
        }
      }
      push(&prev_name, &prev_phone);
      free(temp);
      return 1;
    }
    temp = temp->next;
  }
  printf("Name not found in the directory\n");
  return 0;
}
// Function to Delete Contact through Phone Number.
int delete_phone(char *phone) {
  char prev_name[50];
  char prev_phone[15];
  struct node *temp = head;
  // char phone[15];
  while (temp != NULL) {
    if (strcmp(temp->phone, phone) == 0) {
      strcpy(prev_name, temp->name);
      strcpy(prev_phone, temp->phone);
      if (temp->prev == NULL) { // Checking if only one node exists.
        head = temp->next;
        if (temp->next != NULL) {
          temp->next->prev = NULL;
        }
      } else { // More than One node exists.
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
          temp->next->prev = temp->prev;
        }
      }
      push(&prev_name, &prev_phone);
      free(temp);
      return 1;
    }
    temp = temp->next;
  }
  printf("Phone Number not found in the directory\n");
  return 0;
}
// Function to Search Contact By Name.
void search_by_name(char *name) {
  struct node *temp = head;
  char phone[15];
  if (check_name(name) > 1) // Checking the name has Repetations are not.
  {
    printf("Duplicates Names are found\n");
    printf("Enter Phone Number to search in Directory : ");
    scanf("%s", phone);
    search_by_number(&phone);
    return;
  }

  while (temp != NULL) {
    if (strcmp(temp->name, name) == 0) {
      for (int i = 0; i <= 23; i++) {
        printf("~~");
      }
      printf("\n");
      printf("\tName: %s\tPhone: %s\t\n", temp->name, temp->phone);

      for (int i = 0; i <= 23; i++) {
        printf("~~");
      }
      printf("\n");
      return;
    }

    temp = temp->next;
  }
  printf("Name not found in the directory\n");
}
// Function to Search Contact By Number.
void search_by_number(char *phone) {
  struct node *temp = head;
  for (int i = 0; i <= 23; i++) {
    printf("~~");
  }
  printf("\n");
  while (temp != NULL) {
    if (strcmp(temp->phone, phone) == 0) {
      printf("\tName: %s\tPhone: %s\t\n", temp->name, temp->phone);
      for (int i = 0; i <= 23; i++) {
        printf("~~");
      }
      printf("\n");
      return;
    }
    temp = temp->next;
  }
  printf("Phone number not found in the directory\n");
}
// Function to check weather the Phone Number is correct or Not.
int check_number(char *phone) {
  int check = strlen(phone);
  if (check == 10) {
    return 1;
  }
  return 0;
}
// Function to check the duplicates Name in Directory.
int check_name(char *name) {
  int count = 0;
  struct node *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->name, name) == 0) {
      count = count + 1;
    }
    temp = temp->next;
  }
  if (count > 1) {
    return count;
  }
  return 1;
}
// Function to Check the duplicate Phone numbers.
int check_phone(char *phone) {
  struct node *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->phone, phone) == 0) {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}
// Function to save the Directory in a File.
void save_directory(struct node *root) {
  // printf("In save function\n");
  FILE *p;
  // Opening the file in write mode.
  p = fopen("directory.txt", "w");
  fputs("NAME\t", p);
  fputs("PHONE NUMBER\n", p);
  // writing the name in file until the directory is empty!!
  while (root != NULL) {
    fputs(root->name, p);
    fputs("\t\t", p);
    fputs(root->phone, p);
    fputs("\n", p);
    root = root->next;
  }
  printf("Saved in Directory.text file\n");
}
// Function to update the Contact in the Directory.
void update_contact(char *name) {
  struct node *temp = head;
  char new_name[50];
  char new_phone[15];
  while (temp != NULL) {
    if (strcmp(temp->name, name) == 0) {
      printf("Enter new name to update contact : ");
      scanf("%s", new_name);
      strcpy(new_phone, temp->phone);
      int c = delete_contact(temp->name);
      insert_contact(&new_name, &new_phone);
      printf("Name sucessfully Updated\n");
      return;
    }
    temp = temp->next;
  }
  printf("Name not found in directory\n");
}
// Function to Push the node into the Stack.
void push(char *name, char *phone) {
  struct node *temp = malloc(sizeof(struct node *));
  strcpy(temp->name, name);
  strcpy(temp->phone, phone);
  temp->next = NULL;
  temp->prev = NULL;
  top = top + 1;
  stack[top] = temp;
}
// Function to pop the top node from the stack.
struct node *pop() {
  struct node *temp = stack[top];
  top = top - 1;
  return temp;
}
// Function to Print the Recycle Bin Contacts.
void recycle_bin() {
  if (top == -1) {
    printf("!!Recycle Bin is Empty!!\n");
    return;
  }
  printf("!!Recycle Bin Contacts!!\n");
  for (int i = top; i != -1; i--) {
    struct node *temp = pop();
    printf("\tName: %s\tPhone: %s\t\n", temp->name, temp->phone);
    // printf("Do u want to restore the contact in the directory : ");
    insert_contact(temp->name, temp->phone);
  }
  printf("Contacts Restored Sucessfully\n");
}
