#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

struct todolist {
  int id;
  string task;
};

int ID;

void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();

int main() {
  system("clear");
  while (true) {
    banner();
    cout << "\n\t1. Add Task";
    cout << "\n\t2. Show Task";
    cout << "\n\t3. Search Task";
    cout << "\n\t4. Delete Task";
    cout << "\n\t5. Update Task";

    int choice;
    cout << "\n\tEnter Choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      addTask();
      break;

    case 2:
      showTask();
      break;

    case 3:
      searchTask();
      break;

    case 4:
      deleteTask();
      break;

    case 5:
      updateTask();
      break;

    default:
      break;
    }
  }

  return 0;
}
void banner() {
  cout << "________________________________________" << endl;
  cout << "\t      MY TODO" << endl;
  cout << "________________________________________" << endl;
}
void addTask() {
  system("clear");
  banner();
  todolist todo;
  cout << " Enter New Task : " << endl;
  cin.get();
  getline(cin, todo.task);
  char save;
  cout << "Save? (y/n): ";
  cin >> save;
  if (save == 'y') {
    ID++;
    ofstream fout;
    fout.open("todo.txt", ios::app);
    fout << "\n" << ID;
    fout << "\n" << todo.task;
    fout.close();

    char more;
    cout << " Add more Task? (y/n): ";
    cin >> more;

    if (more == 'y') {
      addTask();
    } else

    {
      system("clear");
      cout << "Added Sucessfully !" << endl;
      return;
    }
  }
  system("clear");
}

void showTask() {
  system("clear");
  banner();
  todolist todo;
  ifstream fin;
  fin.open("todo.txt");
  cout << "Task:" << endl;

  while (!fin.eof()) {
    fin >> todo.id;
    fin.ignore();
    getline(fin, todo.task);
    if (todo.task != "") {
      cout << "\t" << todo.id << ": " << todo.task << endl;
    } else {
      cout << "\tEmpty!" << endl;
    }
  }
  fin.close();
  char exit;
  cout << "Exit? (y/n) : ";
  cin >> exit;
  if (exit == 'y') {
    banner();
  }
  system("clear");
}

int searchTask() {
  system("clear");
  banner();
  int id;
  cout << "Enter task id: ";
  cin >> id;
  todolist todo;
  ifstream fin("todo.txt");
  while (!fin.eof()) {
    fin >> todo.id;
    fin.ignore();
    getline(fin, todo.task);
    if (todo.id == id) {
      system("clear");
      cout << "\t" << todo.id << ": " << todo.task << endl;
      return id;
    }
  }
  system("clear");
  cout << "Not Found!" << endl;
  return 0;
}

void deleteTask() {
  system("clear");
  int id = searchTask();
  if (id != 0) {
    char del;
    cout << "\n\tDelete? (y/n): ";
    cin >> del;
    if (del == 'y') {
      todolist todo;
      ofstream tempFile;
      tempFile.open("temp.txt");
      ifstream fin;
      fin.open("todo.txt");
      int index = 1;
      while (!fin.eof()) {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if (todo.id != id) {
          tempFile << "\n" << index;
          tempFile << "\n" << todo.task;
          index++;
          ID--;
        }
      }
      fin.close();
      tempFile.close();
      remove("todo.txt");
      rename("temp.txt", "todo.txt");
      cout << "\n\tDeleted succesfully!" << endl;
    } else {
      system("clear");
      cout << "\n\t Not Deleted!" << endl;
    }
  }
}
void updateTask() {
  system("clear");
  int id = searchTask();
  cout << "\n\tYou want to update this task (y/n) : ";
  char choice;
  cin >> choice;

  if (choice == 'y') {
    todolist todo;
    todolist updatedTodo;
    updatedTodo.id = id;

    cout << "\n\tEnter updated task : ";
    cin.get(); // Consume the newline character left in the buffer
    getline(cin, updatedTodo.task);

    ofstream tempFile;
    tempFile.open("temp.txt");

    ifstream fin;
    fin.open("todo.txt");

    while (fin >> todo.id) {
      fin.ignore();
      getline(fin, todo.task);

      if (todo.id != id) {
        tempFile << todo.id << "\n" << todo.task << "\n";
      } else {
        tempFile << updatedTodo.id << "\n" << updatedTodo.task << "\n";
      }
    }

    fin.close();
    tempFile.close();

    remove("todo.txt");
    rename("temp.txt", "todo.txt");

    cout << "\n\tTask updated successfully";
  } else {
    cout << "\n\tRecord not updated";
  }
}
