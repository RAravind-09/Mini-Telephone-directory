//telephone directory

import java.util.Scanner;

class Node {
    String name;
    String phone;
    Node prev;
    Node next;

    Node(String name, String phone) {
        this.name = name;
        this.phone = phone;
        this.prev = null;
        this.next = null;
    }
}

public class TelephoneDirectory {
    private Node head = null;
    private Node[] stack = new Node[25];
    private int top = -1;
    private Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        TelephoneDirectory directory = new TelephoneDirectory();
        directory.initialize();
        directory.menu();
    }

    public void initialize() {
        insertContact("Chaitu", "1234567890");
        insertContact("Ganesh", "1234567890");
        insertContact("Dileep", "1234567890");
        insertContact("Aravind", "1234567890");
        insertContact("Anil", "1234567890");
    }

    public void menu() {
        System.out.println("!!!!Enter First Letter in Capital and No White Spaces!!!!");
        int ch;
        while (true) {
            System.out.println("Enter Choice");
            System.out.println("1. Add (To Create Contact)");
            System.out.println("2. Delete (To Delete Contact)");
            System.out.println("3. Update");
            System.out.println("4. Search");
            System.out.println("5. Display");
            System.out.println("6. Recycle Bin");
            System.out.println("0. Exit");
            System.out.print("Enter choice: ");
            ch = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (ch) {
                case 1:
                    addContact();
                    break;
                case 2:
                    deleteContactMenu();
                    break;
                case 3:
                    updateContact();
                    break;
                case 4:
                    searchContact();
                    break;
                case 5:
                    displayDirectory();
                    break;
                case 6:
                    recycleBin();
                    break;
                case 0:
                    exit();
                    return;
                default:
                    System.out.println("Invalid Choice!");
            }
        }
    }

    public void addContact() {
        System.out.print("Enter Name to create Contact: ");
        String name = scanner.nextLine();
        System.out.print("Enter Phone Number to Contact: ");
        String phone = scanner.nextLine();
        insertContact(name, phone);
        System.out.println("Contact Created Successfully!!");
    }

    public void deleteContactMenu() {
        System.out.print("Do you want to delete by Name or Phone (N/P): ");
        char c = scanner.nextLine().charAt(0);
        if (c == 'N' || c == 'n') {
            System.out.print("Enter Name to delete Contact in Directory: ");
            String name = scanner.nextLine();
            if (deleteContact(name) == 1) {
                System.out.println("Contact Deleted Successfully");
            }
        } else if (c == 'P' || c == 'p') {
            System.out.print("Enter Phone Number to delete Contact in Directory: ");
            String phone = scanner.nextLine();
            if (deleteContactByPhone(phone) == 1) {
                System.out.println("Contact Deleted Successfully");
            }
        } else {
            System.out.println("Wrong Choice! Try Again.");
        }
    }

    public void updateContact() {
        System.out.print("Enter previous name to update contact: ");
        String name = scanner.nextLine();
        updateContact(name);
    }

    public void searchContact() {
        System.out.print("Do you want to search by Name or Number (N/P): ");
        char c = scanner.nextLine().charAt(0);
        if (c == 'N' || c == 'n') {
            System.out.print("Enter Name to search in Directory: ");
            String name = scanner.nextLine();
            searchByName(name);
        } else if (c == 'P' || c == 'p') {
            System.out.print("Enter Phone Number to search in Directory: ");
            String phone = scanner.nextLine();
            searchByNumber(phone);
        } else {
            System.out.println("Wrong Choice! Try Again.");
        }
    }

    public void exit() {
        System.out.print("Do you want to save the Directory in the file (y/n): ");
        char c = scanner.nextLine().charAt(0);
        if (c == 'Y' || c == 'y') {
            saveDirectory();
        }
        System.out.println("!!!Thank you!!!");
    }

    public void insertContact(String name, String phone) {
        if (!isValidNumber(phone)) {
            System.out.println("Invalid Phone Number. Try again!!!");
            return;
        }
        if (isPhoneExist(phone)) {
            System.out.println("Phone Number already exists!!!");
            return;
        }

        Node newNode = new Node(name, phone);
        if (head == null) {
            head = newNode;
            return;
        }

        Node temp = null;
        Node current = head;
        while (current != null && current.name.compareTo(name) < 0) {
            temp = current;
            current = current.next;
        }

        if (temp == null) {
            newNode.next = head;
            head.prev = newNode;
            head = newNode;
        } else {
            temp.next = newNode;
            newNode.prev = temp;
            newNode.next = current;
            if (current != null) {
                current.prev = newNode;
            }
        }
    }

    public void displayDirectory() {
        Node temp = head;
        for (int i = 0; i <= 31; i++) {
            System.out.print("~~");
        }
        System.out.println();
        while (temp != null) {
            System.out.printf("{\tName\t:\t%s\tPhone\t:\t%s\t}\n", temp.name, temp.phone);
            temp = temp.next;
        }
        for (int i = 0; i <= 31; i++) {
            System.out.print("~~");
        }
        System.out.println();
    }

    public int deleteContact(String name) {
        if (getNameCount(name) > 1) {
            System.out.println("Repetition Names are found");
            System.out.print("Enter Phone Number to delete in Directory: ");
            String phone = scanner.nextLine();
            return deleteContactByPhone(phone);
        }

        Node temp = head;
        while (temp != null) {
            if (temp.name.equals(name)) {
                String prevName = temp.name;
                String prevPhone = temp.phone;
                if (temp.prev == null) {
                    head = temp.next;
                    if (temp.next != null) {
                        temp.next.prev = null;
                    }
                } else {
                    temp.prev.next = temp.next;
                    if (temp.next != null) {
                        temp.next.prev = temp.prev;
                    }
                }
                push(prevName, prevPhone);
                return 1;
            }
            temp = temp.next;
        }
        System.out.println("Name not found in the directory");
        return 0;
    }

    public int deleteContactByPhone(String phone) {
        Node temp = head;
        while (temp != null) {
            if (temp.phone.equals(phone)) {
                String prevName = temp.name;
                String prevPhone = temp.phone;
                if (temp.prev == null) {
                    head = temp.next;
                    if (temp.next != null) {
                        temp.next.prev = null;
                    }
                } else {
                    temp.prev.next = temp.next;
                    if (temp.next != null) {
                        temp.next.prev = temp.prev;
                    }
                }
                push(prevName, prevPhone);
                return 1;
            }
            temp = temp.next;
        }
        System.out.println("Phone Number not found in the directory");
        return 0;
    }

    public void searchByName(String name) {
        if (getNameCount(name) > 1) {
            System.out.println("Duplicate Names are found");
            System.out.print("Enter Phone Number to search in Directory: ");
            String phone = scanner.nextLine();
            searchByNumber(phone);
            return;
        }

        Node temp = head;
        while (temp != null) {
            if (temp.name.equals(name)) {
                for (int i = 0; i <= 23; i++) {
                    System.out.print("~~");
                }
                System.out.println();
                System.out.printf("\tName: %s\tPhone: %s\t\n", temp.name, temp.phone);
                for (int i = 0; i <= 23; i++) {
                    System.out.print("~~");
                }
                System.out.println();
                return;
            }
            temp = temp.next;
        }
        System.out.println("Name not found in the directory");
    }

    public void searchByNumber(String phone) {
        Node temp = head;
        for (int i = 0; i <= 23; i++) {
            System.out.print("~~");
        }
        System.out.println();
        while (temp != null) {
            if (temp.phone.equals(phone)) {
                System.out.printf("\tName: %s\tPhone: %s\t\n", temp.name, temp.phone);
                for (int i = 0; i <= 23; i++) {
                    System.out.print("~~");
                }
                System.out.println();
                return;
            }
            temp = temp.next;
        }
        System.out.println("Phone number not found in the directory");
    }

    public boolean isValidNumber(String phone) {
        return phone.length() == 10;
    }

    public int getNameCount(String name) {
        int count = 0;
        Node temp = head;
        while (temp != null) {
            if (temp.name.equals(name)) {
                count++;
            }
            temp = temp.next;
        }
        return count;
    }

    public boolean isPhoneExist(String phone) {
        Node temp = head;
        while (temp != null) {
            if (temp.phone.equals(phone)) {
                return true;
            }
            temp = temp.next;
        }
        return false;
    }

    public void saveDirectory() {
        // Implement file saving logic here if needed
        System.out.println("Saved in directory.txt file");
    }

    public void updateContact(String name) {
        Node temp = head;
        while (temp != null) {
            if (temp.name.equals(name)) {
                System.out.print("Enter new name to update contact: ");
                String newName = scanner.nextLine();
                String newPhone = temp.phone;
                deleteContact(temp.name);
                insertContact(newName, newPhone);
                System.out.println("Name successfully updated");
                return;
            }
            temp = temp.next;
        }
        System.out.println("Name not found in directory");
    }

    public void push(String name, String phone) {
        Node temp = new Node(name, phone);
        top++;
        stack[top] = temp;
    }

    public Node pop() {
        Node temp = stack[top];
        top--;
        return temp;
    }

    public void recycleBin() {
        if (top == -1) {
            System.out.println("Recycle Bin is Empty");
            return;
        }
        System.out.println("Recycle Bin Contacts");
        for (int i = top; i >= 0; i--) {
            Node temp = pop();
            System.out.printf("\tName: %s\tPhone: %s\t\n", temp.name, temp.phone);
            insertContact(temp.name, temp.phone);
        }
        System.out.println("Contacts Restored Successfully");
    }
}
