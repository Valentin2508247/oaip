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

    int getTime() {
        string hour, min;
        hour = time.substr(0, 2);
        min = time.substr(3, 2);
        return stoi(hour) * 100 + stoi(min);
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

void bubble_sort(Flight* a, int n)
{
    int i, j;
    Flight t;
    for (i = 1; i < n; i++)
        for (j = n - 1; j >= i; j--)
            if (a[j - 1].getTime() > a[j].getTime())
            {
                t = a[j - 1];
                a[j - 1] = a[j];
                a[j] = t;
            }
}

void quick_sort(Flight* st, int n)
{

    struct
    {
        int l;
        int r;
    } stack[20];

    int i, j, left, right, x, s = 0;
    Flight t;
    stack[s].l = 0; stack[s].r = n - 1;
    while (s != -1)
    {
        left = stack[s].l; right = stack[s].r;
        s--;
        while (left < right)
        {
            i = left; j = right; x = st[(left + right) / 2].getTime();
            while (i <= j)
            {
                while (st[i].getTime() < x) i++;
                while (st[j].getTime() > x) j--;
                if (i <= j) {
                    t = st[i]; st[i] = st[j]; st[j] = t;
                    i++; j--;
                }
            }
            if ((j - left) < (right - i))
            {
                if (i < right) { s++; stack[s].l = i; stack[s].r = right; }
                right = j;
            }
            else {
                if (left < j) { s++; stack[s].l = left; stack[s].r = j; }
                left = i;
            }
        }
    }
}

int find(Flight* a, int n, int target)
{
    for (int i = 0; i < n; i++)
        if (a[i].getTime() == target) return i;
    return -1;
}

int find_interpol(Flight* a, int n, int target)
{
    int i = 0, j = n - 1, m;
    while (i < j)
    {
        if (a[i].getTime() == a[j].getTime()) // Предотвращение деления на нуль
            if (a[i].getTime() == target) return i;
            else return -1;
        m = i + (j - i) * (target - a[i].getTime()) / (a[j].getTime() - a[i].getTime());
        if (a[m].getTime() == target) return m;
        else
            if (target > a[m].getTime()) i = m + 1; else j = m - 1;
    }
    return -1;
}

int main()
{
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


    // sort
    //bubble_sort(flights, n);
    quick_sort(flights, n);
    for (int i = 0; i < n; i++) {
        flights[i].print();
    }

    // search
    int target = 1400;
    //int result = find(flights, n, target);
    int result = find_interpol(flights, n, target);
    if (result != -1) {
        cout << "Flight found: ";
        flights[result].print();
    }
    else {
        cout << "No flight found";
    }

    delete[] flights;
    return 0;
}
