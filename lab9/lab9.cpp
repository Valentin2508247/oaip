
// lab9
#include <iostream>


//        2 * 2   4 * 4   6 * 6         2n * 2n
//y  =    ----- * ----- * ----- * ... * -------------------
//        1 * 3   3 * 5   5 * 7         (2n - 1) * (2n + 1)

double y(int n) {
    double result = 1.;
    for (int i = 1; i <= n; i++) {
        double k = (double)i;
        result *= 4. * k * k / (2. * k - 1) / (2. * k + 1);
    }
    return result;
}

double recursion(double result, int current, int finish) {
    double n = (double)current;
    result *= 2. * n * 2. * n / (2. * n - 1.) / (2. * n + 1.);
    if (current >= finish)
        return result;
    else
        return recursion(result, current + 1, finish);
}

double rec_y(int n) {
    return recursion(1., 1, n);
}



using namespace std;
int main()
{
    cout << "Enter n:";
    int n;
    cin >> n;
    double res = y(n), res_recursion = rec_y(n);
    cout << "y(" << n << ") = " << res << endl;
    cout << "y_rec(" << n << ") = " << res_recursion << endl;
}

