// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

struct Flight {
    public:
        std::string id;
        std::string dest;
        std::string time;

        void print() {  
            cout << "id: " << id << " dest: " << dest << " time: " << time << ";" << endl;
        }
};

void filter(Flight* array, string dest, int n) {
    for (int i = 0; i < n; i++) {
        Flight flight = array[i];
        if (flight.dest == dest) {
            flight.print();
        }
    }
}



int main()
{
    string destination = "Minsk";
    cout << "Enter destination: ";
    cin >> destination;

    std::ifstream infile("input.txt");
   
   
    //file size
    int n = std::count(std::istreambuf_iterator<char>(infile),
        std::istreambuf_iterator<char>(), '\n');
    n++;
    Flight* flights = new Flight[n];


    int i = 0;
    freopen("input.txt", "rb", stdin);
    string delimetr = " ";
    std::string line;
    while (std::getline(std::cin, line)) {  
        int space1 = line.find(delimetr);  
        int space2 = line.find_last_of(delimetr);

        string id, dest, date;
        id = line.substr(0, space1);
        dest = line.substr(space1 + 1, space2 - space1 - 1);
        date = line.substr(space2 + 1, 5);

        Flight flight;
        flight.id = id;
        flight.dest = dest;
        flight.time = date;
        flights[i++] = flight;
    }


    filter(flights, destination, n);

    delete[] flights;
    return 0;
}
