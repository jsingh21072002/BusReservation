#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h> // For getch()

using namespace std;

const string BUS_LIST[] = {"Cardiff Express", "Belfast Express", "Derby Express", "Chester Express", "Newport Express", "Truro Express"};
const int BUS_COUNT = sizeof(BUS_LIST) / sizeof(BUS_LIST[0]);

vector<string> names(32);
vector<int> numbers(32);
int trno;

void bus(); // for list of bus
void name_number(int booking, const string& numstr);
void booking(); // for booking the tickets
int read_number(int trno); // for reading the number from the file
void read_name(int trno); // for reading the name from the file
void status(); // for printing the status by user input
void status_1(int trno); // for printing the status while booking ticket
void cancel();
void login();

int main() {
    login();
    int num;
    do {
        system("cls");
        cout << "\n\n\n";
        cout << "====================================== WELCOME TO BUS RESERVATION SYSTEM ======================================\n\n\n";
        cout << "\t\t\t\t\t[1]=> View Bus List\n";
        cout << "\n";
        cout << "\t\t\t\t\t[2]=> Book Tickets\n";
        cout << "\n";
        cout << "\t\t\t\t\t[3]=> Cancel Booking\n";
        cout << "\n";
        cout << "\t\t\t\t\t[4]=> Bus Status Board\n";
        cout << "\n";
        cout << "\t\t\t\t\t[5]=> Exit\n\n";
        cout << "===============================================================================================================\n\n";
        cout << "\t\t\tEnter Your Choice:: ";
        cin >> num;
        switch(num) {
        case 1:
            bus(); // for list of bus
            break;
        case 2:
            booking(); // for booking the tickets
            break;
        case 3:
            cancel();
            break;
        case 4:
            status();
            break;
        }
        getch();
    } while(num != 5);
    
    system("cls");
    cout << "\t----------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\tThank You For Using This System\t\t\t\t\t\t\n";
    cout << "\t----------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t Brought To You By code-projects.org";
    getch();
    return 0;
}

void bus() {
    system("cls");
    cout << "\n\n\n";
    cout << "=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n";
    for (int i = 0; i < BUS_COUNT; ++i) {
        cout << "\t\t\t\t\t[" << (i + 1) << "]  =>  " << BUS_LIST[i] << "\n";
        cout << "\n";
    }
}

void booking() {
    int booking = 0;
    string numstr;
    system("cls");
    cout << "=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n";
    bus(); // for seeing train list
    cout << "Enter the Bus number:--->";
    cin >> trno;
    system("cls");
    cout << "=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n";
    cout << "Your Bus Number is " << trno << " ********** " << BUS_LIST[trno - 1] << endl;
    status_1(trno);
    
    ifstream file;
    ofstream outfile;
    string filename = "tr" + to_string(trno) + ".txt";
    
    file.open(filename);
    string str1;
    getline(file, str1);
    file.close();
    
    int seat1 = stoi(str1);
    if (seat1 <= 0) {
        cout << "There is no blank seat in this bus ";
    } else {
        cout << "\n\n\n\t\t\t\tAvailable Seats:------>" << seat1 << "\n";
        cout << "\n\t\t\t\tNumber of Tickets:----->";
        cin >> booking;
        cout << "\n";

        seat1 -= booking;
        numstr = to_string(trno);
        name_number(booking, numstr);
        cout << "\n\t\t\t\tThe Total booking amount is " << 200 * booking << endl;
        
        outfile.open(filename);
        outfile << seat1;
        outfile.close();
    }
}

void name_number(int booking, const string& numstr) {
    string tempstr1 = "status" + numstr + ".txt";
    string tempstr2 = "number" + numstr + ".txt";
    ofstream a(tempstr1, ios::app);
    ofstream b(tempstr2, ios::app);
    
    for (int i = 0; i < booking; ++i) {
        int number;
        cout << "============================Enter the details for ticket no " << (i + 1) << "============================\n\n\n";
        cout << "\t\t\t\tEnter the seat number:--->";
        cin >> number;
        cout << "\t\t\t\tEnter the name of person:--->";
        cin >> names[number - 1];
        cout << "\n======================================================================================================\n\n";
        cout << "\n";
        b << number << " ";
        a << names[number - 1] << " ";
    }
}

int read_number(int trno) {
    string filename = "number" + to_string(trno) + ".txt";
    ifstream a(filename);
    int i = 0;
    while (a >> numbers[i]) {
        ++i;
    }
    a.close();
    return i;
}

void read_name(int trno) {
    string filename = "status" + to_string(trno) + ".txt";
    ifstream b(filename);
    int i = 0;
    while (b >> names[i]) {
        ++i;
    }
    b.close();
}

void status() {
    system("cls");
    cout << "=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n";
    int index = 0;
    int trno;
    cout << "Enter the number of bus:---->";
    cin >> trno;
    read_number(trno);
    read_name(trno);
    
    cout << "____________________________________________________________________________________________________________________\n";
    cout << "                                      Bus.no--> " << trno << " ----> " << BUS_LIST[trno - 1] << "                                                            \n";
    cout << "____________________________________________________________________________________________________________________\n";
    
    vector<string> tempname(33, "Empty ");
    for (int i = 0; i < 32; ++i) {
        if (i < names.size() && numbers[i] > 0) {
            tempname[numbers[i]] = names[i];
        }
    }
    
    for (int i = 0; i < 8; ++i) {
        cout << "\t\t\t\t";
        for (int j = 0; j < 4; ++j) {
            cout << index + 1 << "." << tempname[index + 1] << "\t";
            ++index;
        }
        cout << "\n";
    }
}

void status_1(int trno) {
    cout << "Your Bus Number is " << trno << " ********** " << BUS_LIST[trno - 1] << endl;
    system("cls");
    cout << "=========================================== BUS RESERVATION SYSTEM ============================================\n\n\n";
    int index = 0;
    read_number(trno);
    read_name(trno);
    
    vector<string> tempname(33, "Empty ");
    for (int i = 0; i < 32; ++i) {
        if (i < names.size() && numbers[i] > 0) {
            tempname[numbers[i]] = names[i];
        }
    }
    
    for (int i = 0; i < 8; ++i) {
        cout << "\t\t\t\t";
        for (int j = 0; j < 4; ++j) {
            cout << index + 1 << "." << tempname[index + 1] << "\t";
            ++index;
        }
        cout << "\n";
    }
}

void cancel() {
    int seat_no;
    cout << "Enter the bus number:---->";
    cin >> trno;
    string numstr = to_string(trno);
    string tempstr1 = "status" + numstr + ".txt";
    string tempstr2 = "number" + numstr + ".txt";
    read_number(trno);
    read_name(trno);
    status_1(trno);
    
    cout << "Enter the seat number:--->";
    cin >> seat_no;
    
    ofstream a(tempstr1);
    ofstream b(tempstr2);
    
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (numbers[i] == seat_no) {
            for (size_t j = 0; j < numbers.size(); ++j) {
                if (numbers[j] != seat_no && numbers[j] != 0) {
                    b << numbers[j] << " ";
                    a << names[j] << " ";
                } else if (numbers[j] == seat_no && numbers[j] != 0) {
                    names[j] = "Empty ";
                }
            }
        }
    }
    a.close
