#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

template <typename T>

void get_user_input(T &user){
    cout << endl;
    cout << "---> ";
    cin >> user;
}

void display();
void displayTasks(ifstream& readTasks);
void addTasks(ofstream& writeTasks);
void removeTasks(ifstream &readTasks, ofstream& writeTasks, const string filename);
void checkTasks(ifstream& readTasks, ofstream& writeTasks, const string done, const string nDone, const string filename);
void write_Tasks(ofstream& writeTasks, const string done, const string nDone, const string filename);

int main(){

    char userInput = '0';
    bool running = true;
    const string filename = "e:tasks.txt"; //!!!Update the filepath to your filepath!!!!
    const string done = "-done";
    const string nDone = "-not done";

    display();

    while(running){

        get_user_input(userInput);
        while(userInput < 'a' && userInput > 'd' && userInput != 'x'){
            get_user_input(userInput);
            tolower(userInput);
        }

        if(userInput == 'a'){
            ifstream readTasks(filename);
            displayTasks(readTasks);
        }
        else if(userInput == 'b'){
            ofstream writeTasks;
            write_Tasks(writeTasks, done, nDone, filename);
        }
        else if(userInput == 'c'){
            ifstream readTasks;
            ofstream writeTasks;
            removeTasks(readTasks, writeTasks, filename);
        }
        else if(userInput == 'd'){
            ifstream readTasks;
            ofstream writeTasks;
            checkTasks(readTasks, writeTasks, done, nDone, filename);
        }
        else if(userInput == 'x'){
            cout << "Thank you for using this TO-DO List App." << endl;
            running = false;
        }
    }


	return 0;
}
void display(){
    time_t now = time(0);
    char* date_time = ctime(&now);
	cout << "\t\t\t Welcome to TO DO App" << endl;
	cout << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << endl;
	cout << "1. Enter (a) to display the tasks for today" << endl;
	cout << "2. Enter (b) to add tasks for today" << endl;
	cout << "3. Enter (c) to remove tasks from today's tasks" << endl;
	cout << "4. Enter (d) to check the task which are done" << endl;
    cout << "5. Enter (x) to exit the program" << endl;
	cout << endl;
    cout << "Date/Time: " << date_time << endl;
	cout << "--------------------------------------------------------------" << endl;
}
void displayTasks(ifstream& readTasks){
    string task;
    int serial = 1;

    while(getline(readTasks, task)){
        cout << serial << ". " << task << endl;
        serial++;
    }
    readTasks.close();
}
void removeTasks(ifstream &readTasks, ofstream& writeTasks, const string filename){

    string task, line;
    int n = 1;

    while(getline(readTasks, line)){
        cout << n << ". " << line << endl;
    }

    cout << "Enter the task which you want to remove: ";
    cin.ignore();
    getline(cin, task);

    readTasks.open(filename);
    writeTasks.open("e:test.txt");
    while(getline(readTasks, line)){
        if(line != task){
            writeTasks << line << endl;
        }
    }
    writeTasks.close();
    readTasks.close();

    string temp;
    ofstream fout(filename);
    ifstream fin("e:test.txt");
    while(getline(fin, temp)){
        fout << temp << endl;
    }
    fin.close();
    fout.close();

    cout << "The Task has been removed" << endl;

}
void checkTasks(ifstream& readTasks, ofstream& writeTasks, const string done, const string nDone, const string filename){  
    readTasks.open(filename);
    writeTasks.open("e:test.txt");
    string dTask;
    cout << "Enter the task which you have done: ";
    cin.ignore();
    getline(cin, dTask);

    string temp;
    while(getline(readTasks, temp)){
        if(temp == dTask){
            writeTasks << dTask + done << endl;
        }
        else{
            writeTasks << temp << endl;
        }
    }
    readTasks.close();
    writeTasks.close();

    ifstream fin("e:test.txt");
    ofstream fout(filename);
    string temp2;
    while(getline(fin, temp2)){
        fout << temp2 << endl;
    }
    fin.close();
    fout.close();
}
void write_Tasks(ofstream& writeTasks, const string done, const string nDone, const string filename){
    writeTasks.open(filename, ios::app);
    char user, temp;
    bool run = true;
    while(run){
        cout << "Do you want to enter 1 task or multiple tasks(o/m): ";
        get_user_input(user);
        if(user == 'o' || user == 'm'){
            run = false;
            break;
        }
    }
    
    if(user == 'o'){
        string temp;
        cout << "Enter the task: ";
        cin.ignore();
        getline(cin, temp);
        writeTasks << temp << endl;
        writeTasks.close();
        cout << "Task has been added to the list." << endl;
    }
    else if(user == 'm'){
        int number;
        cout << "How many tasks do you want to enter: ";
        cin >> number;
        string *pTasks = new string[number];
        cout << "Enter the tasks: ";
        cin.ignore();
        for(int i = 0; i < number; i++){
            getline(cin, pTasks[i]);
            writeTasks << pTasks[i] << endl;
        }
        writeTasks.close();
        cout << "Task have been added to the list." << endl;
        delete[] pTasks;
    }
    else{
        cout << "Enter valid Input" << endl;
    }
}