/*********************************************************************** Matr.-Nr: 3133115
Nachname/Surname: Jaffer
Vorname/Given name: Hayyan
Uni-Email: hayyan.jaffer@stud.uni-due.de
Studiengang/Course of studis: Bsc Computer Engineering(Software)
***********************************************************************/
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct City {
  string name = "";
  string addition = NULL;
  City *Next;
};
// we have used this because here in this case of linked list we have  lots of
// cities hence we will be needing a ostream operator.you can see this in the
// lecture notes provided by professor that how to make a linked list for

ostream &operator<<(ostream &out, City *city) {
  while (city != nullptr) {
    out << city->name;
    if (city->addition[0] != ',') {
      out << " " << city->addition;
    } else {
      out << city->addition;
    }
    if (city->Next != nullptr) {
      out << " | ";
    }
    city = city->Next;
  }
  return out;
}
// Part 3
void print(City *cities[], int length, int from, int to) {
  for (int i = from; i <= to; i++) {
    if (cities[i] != nullptr) {
      cout << i << " ";
      std::cout << cities[i] << endl;
    } else {
      //  cout << "cities is null here" ;
    }
  }
}
// Part 4
void readFile(string file_name, City *array[], int length) {
  ifstream inFile;
  inFile.open(file_name);
  if (inFile) {
    string mychar;
    string line = "";
    getline(inFile, line);

    line = "";
    while (getline(inFile, line)) {
      // Create a Node
      City *n = new City{"", "", NULL};
      // Input the random data
      string cityname;
      string addition;
      int postalcode;
      stringstream inputString(line);
      string tempString;
      getline(inputString, cityname, ';');
      getline(inputString, addition, ';');
      getline(inputString, tempString, ';');
      postalcode = atoi(tempString.c_str());
      n->name = cityname;
      n->addition = addition;
      // cout << postalcode << " " << cityname << " " << addition <<  endl;
      line = "";
      n->Next = nullptr;
      // If the node is first
      if (array[postalcode] == nullptr) {
        array[postalcode] = n;
      } else {
        City *temp = array[postalcode];
        while (temp->Next != nullptr)
          temp = temp->Next;
        temp->Next = n;
      }
      postalcode = 0;
    }
  } else {
    std::cout << "The file cannot be opened" << endl;
  }
}
void showMenu() {
  cout << "******Menu******" << endl;
  cout << "c .city" << endl;
  cout << "f .from to" << endl;
  cout << "w. Write to file" << endl;
  cout << "q. Exit" << endl;
  cout << "************" << endl;
}

// Task 2
void print_html(string file_name, City *cd[], int length, int from, int to) {
  string toString = to_string(to);
  string fromString = to_string(from);
  string templateCode = "<!DOCTYPE html> <title> PLZ in Germany from " +
                        to_string(from) + " to + " + to_string(to) +
                        "</title> <head> <h1> From " + to_string(from) +
                        " to " + to_string(to) + "</h1>" +
                        "<table border='1'> <tr><th>PLZ</th><th>Area</th></tr>";
  ofstream hayyan;
  hayyan.open(file_name);

  if (!hayyan.is_open()) {
    cout << "File can't be opened";
  } else {
    cout << "Writing to file" << endl;
    hayyan << templateCode;
    for (int i = from; i <= to; i++) {
      if (cd[i] != nullptr) {
        hayyan << "<tr> <td>" << to_string(i) + "</td> <td>  " << cd[i]
               << " </td> </tr>" << endl;
      }
    }

    hayyan.close();
    cout << "written to file " << file_name;
  }
}

void printRange(City* cities[], string zipCode){
    int zip_length = zipCode.length();
        
    int x = stoi(zipCode);
    print(cities, zip_length, x, x);
}

int main() {
  // Creating a linked Lists for cities
  City **city = new City *[100000];

  // Creating a Menu
  string filename;
  // showMenu();
  cout << "Please input file name" << endl;
  cin >> filename;
  readFile(filename, city, 100);
  // print(city, 100, 47057, 76006);
  cout << "file has been read";
  char choice;
  do {
    showMenu();
    cin >> choice;
    switch (choice) {
        case 'c':{
          cout << "please input zip code: ";
          string zipCode;
          cin >> zipCode;
          while(zipCode.length() != 5){
              cout << "Wrong zip code! Enter again:";
              cin >> zipCode;
          }
          printRange(city, zipCode);
          break;
            }
        case 'f':
          cout << "Please input from ";
          int from, to;
          cin >> from;
          cout << "Please input to ";
          cin >> to;
          print(city, 100000, from, to);
          break;
        case 'w': {
          string file_name;
          int from, to;
          cout << "Input file name ";
          cin >> file_name;
          cout << "Please input from " << endl;
          cin >> from;
          cout << "Please input to ";
          cin >> to;
          print_html(file_name, city, 100000, from, to);
      }
    }

  } while (choice != 'q');

  /*
  switch(filename){
      case 1 : cout << "The name of file is " << filename << endl; break; case 2
  : cout << "city name";

      char c;
      cin >> c;

      break;
      case 3 : cout << "from to";
      char f;
      cin >> f;
      break;
    default
      cout << "Exit" << endl;
  */
}
