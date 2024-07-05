#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

struct Laptop {
    double gains;
    double price;
    double profit;
};

bool byProfit(const Laptop& a, const Laptop& b) {
    return a.profit > b.profit;
}

void initializeVar(int &K, int &N, double &C) {
    cout << "To start the game, input the number of laptops (N): ";
    try {
        if (!(cin >> N) || N <= 0) {
            throw invalid_argument("Error! The amount of laptops you can work with must be equal at least 1 and be an Integer.");
        }
    }
    catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            exit(-1);
    }
 
    cout << "the size of your start capital (C): ";
    try {
        if (!(cin >> C) || C <= 0) {
            throw invalid_argument("Error! Your starting capital should be a value bigger than 0.");
        }
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
        cin.clear();
        exit(-1);
    }
        cout << "the number of laptops you start with (K) is: " << K << endl;
}

void initializeArr(vector<Laptop>& laptops) {
    cout << "\nNow enter the expected gains for each laptop. Remember, that you have " << laptops.size() << " laptops in general:\n";

    for (int i = 0; i < laptops.size(); i++) {
          cout << "Gains for laptop " << (i + 1) << ": ";
          while (true) {
              try {
                  if (!(cin >> laptops[i].gains) || laptops[i].gains <= 0) {
                      throw invalid_argument("Error! Your gains should always be a positive number.");
                  }
                  break;
              }
              catch (const invalid_argument& e) {
                  cout << e.what() << endl;
                  cin.clear();
              }
          }
          
    }

    cout << "\nNow enter the prices of each of " << laptops.size() << " laptops:\n";
    for (int i = 0; i < laptops.size(); i++) {
        while (true) {
            cout << "Price for laptop " << (i + 1) << ": ";
            try {
                if (!(cin >> laptops[i].price) || laptops[i].price <= 0) {
                    throw invalid_argument("Error! Your price should always be a positive number.");
                }
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
            }
        }
    }
}

int main()
{
    srand(time(0));
    int K, N;
    double C;
    K = rand() % 9 + 2;
    vector<Laptop> laptops(K);
    
    cout << "Welcome to the Student's capital maximizer!\n" 
         << "In this CLI application you're making decisions a student who's able to buy, fix and sell laptops.\nYou will enter some improtant start values.\nIn return, you will get the list of the laptops that will provide the biggest income for you.\n\n" 
         << "You will have three month of summer, which will be determined by buying, fixing or selling N distinct laptops.\n" 
         << "C is the amount of capital you have at the start.\n"
         << "K is the amount of laptops you start with, it will be a random number from 2 to 10.\n"
         << "Other values will be given by you.\n\n";
    
    initializeVar(K, N, C);
    initializeArr(laptops);
    double result = C;

    cout << "Now the process is starting! The program will calculate the profit for every laptop... (gains - price)\n";

    for (int i = 0; i < K; i++) {
        cout << "Profit you get for laptop " << (i + 1) << ": ";
        laptops[i].profit = laptops[i].gains - laptops[i].price;
        cout << laptops[i].profit << endl;
    }

    cout << "\nWe will sort the list of the profits so the laptop with the greatest profit would be on the first place and the laptop with the smallest profit - on the last.\n";
    sort(laptops.begin(), laptops.end(), byProfit);
    cout << "Here is the top " << K << " laptop prices, sorted by profit:\n";

    for (int i = 0; i < K; i++) {
        cout << (i + 1) << ": ";
        cout << "Gains: " << laptops[i].gains << " " << "Price: " << laptops[i].price << " " << "Profit: " << laptops[i].profit << endl;
    }
    
    cout << "\n\nIt would be a bad idea to spend time on laptops with the negative or zero profit, that's why we will skip it to maximize your income.\n\n";
    int count = 0;
    bool bought = false;

    for (int i = 0; (i < K) && (count < N); i++) {
        if (result >= laptops[i].price && laptops[i].profit>0) {
            cout << "You're selling a fixed laptop and getting " << laptops[i].profit << " dollars profit from it.\n";
            result += laptops[i].profit;
            count++;
            bought = true;
        }
    }

    if (!bought) {
        cout << "\nUnfortunately, you couldn't afford any laptop at all or no laptops had a positive profit for you.\n";
    }

    cout << "\nThe summer has ended. Your capital is: " << result << " dollars." << endl;
    return 0;
}
