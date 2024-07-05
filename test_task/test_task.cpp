#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

//structure that describes every existing laptop. Each laptop has three parameters which are set individually.
struct Laptop {
    double gains;
    double price;
    double profit;
};

//bool function that is used to describe the quality, which defines how the laptops should be sorted.
bool byProfit(const Laptop& a, const Laptop& b) {
    return a.profit > b.profit;
}

//function for user input of the variables K, N and C with error handling (only correct values are being accepted)
void initializeVar(int &K, int &N, double &C) {
    cout << "To start the game, input the number of laptops (N): ";
    try {
        if (!(cin >> N) || N <= 0) {
            throw invalid_argument("Error! The amount of laptops you can work with must be equal at least 1 and be an Integer."); //error case
        }
    }
    catch (const invalid_argument& e) {
            cout << e.what() << endl; //printing a thrown error message
            cin.clear();
            exit(-1); //stopping the program
    }
 
    cout << "the size of your start capital (C): ";
    try {
        if (!(cin >> C) || C <= 0) {
            throw invalid_argument("Error! Your starting capital should be a value bigger than 0."); //error case
        }
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl; //printing a thrown error message
        cin.clear();
        exit(-1); //stopping the program
    }
        cout << "the number of laptops you start with (K) is: " << K << endl; //printing the randomly generated value of K
}

//function for user input of the arrays for prices and gains with the correct input check
void initializeArr(vector<Laptop>& laptops) {
    cout << "\nNow enter the expected gains for each laptop. Remember, that you have " << laptops.size() << " laptops in general:\n";

    for (int i = 0; i < laptops.size(); i++) {
          cout << "Gains for laptop " << (i + 1) << ": ";
          while (true) { //program asks for the argument repeatedly without exiting the process until it fulfills the requirements
              try {
                  if (!(cin >> laptops[i].gains) || laptops[i].gains <= 0) {
                      throw invalid_argument("Error! Your gains should always be a positive number."); //error case
                  }
                  break;
              }
              catch (const invalid_argument& e) {
                  cout << e.what() << endl; //printing a thrown error message
                  cin.clear();
              }
          }
          
    }

    cout << "\nNow enter the prices of each of " << laptops.size() << " laptops:\n";
    for (int i = 0; i < laptops.size(); i++) {
        while (true) { //program asks for the argument repeatedly without exiting the process until it fulfills the requirements
            cout << "Price for laptop " << (i + 1) << ": ";
            try {
                if (!(cin >> laptops[i].price) || laptops[i].price <= 0) {
                    throw invalid_argument("Error! Your price should always be a positive number."); //error case
                }
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl; //printing a thrown error message
                cin.clear();
            }
        }
    }
}

int main()
{
    srand(time(0)); //to create a true random number generation, the program takes the current amount of seconds on the clock
    int K, N;
    double C;
    K = rand() % 9 + 2; //generating a random number from 2 to 10
    vector<Laptop> laptops(K); //creating a vector array of laptops where every element has a Laptop structure type 
    
    //explaining of the rules
    cout << "Welcome to the Student's capital maximizer!\n" 
         << "In this CLI application you're making decisions a student who's able to buy, fix and sell laptops.\nYou will enter some improtant start values.\nIn return, you will get the list of the laptops that will provide the biggest income for you.\n\n" 
         << "You will have three month of summer, which will be determined by buying, fixing or selling N distinct laptops.\n" 
         << "C is the amount of capital you have at the start.\n"
         << "K is the amount of laptops you start with, it will be a random number from 2 to 10.\n"
         << "Other values will be given by you.\n\n";
    
    initializeVar(K, N, C); //calling the function to input the variables
    initializeArr(laptops); //calling the function to input the arrays
    double result = C; //variable for counting the resulting capital

    cout << "Now the process is starting! The program will calculate the profit for every laptop... (gains - price)\n";

    //counting the profit for every laptop (gains - price)
    for (int i = 0; i < K; i++) {
        cout << "Profit you get for laptop " << (i + 1) << ": ";
        laptops[i].profit = laptops[i].gains - laptops[i].price;
        cout << laptops[i].profit << endl;
    }

    cout << "\nWe will sort the list of the profits so the laptop with the greatest profit would be on the first place and the laptop with the smallest profit - on the last.\n";
    sort(laptops.begin(), laptops.end(), byProfit); //the vector is being sorted from the biggest profit to the lowest
    cout << "Here is the top " << K << " laptop prices, sorted by profit:\n";

    //printing all of the avaliable information for every laptop
    for (int i = 0; i < K; i++) {
        cout << (i + 1) << ": ";
        cout << "Gains: " << laptops[i].gains << " " << "Price: " << laptops[i].price << " " << "Profit: " << laptops[i].profit << endl;
    }
    
    cout << "\n\nIt would be a bad idea to spend time on laptops with the negative or zero profit, that's why we will skip it to maximize your income.\n\n";
    int count = 0; //the amount of the bought/selled laptops 
    bool bought = false; //flag that becomes true if the student bought at least one of the laptops

    //the selling continues while the amount of selled laptops is lower than N
    for (int i = 0; (i < K) && (count < N); i++) {
        if (result >= laptops[i].price && laptops[i].profit>0) { 
            cout << "You're selling a fixed laptop and getting " << laptops[i].profit << " dollars profit from it.\n"; //buying and selling only the laptops that have an afordable price and non-zero profit
            result += laptops[i].profit; //the resulting capital becomes bigger from the profit
            count++;
            bought = true;
        }
    }

    //if no laptops were bought, the program gives this message
    if (!bought) {
        cout << "\nUnfortunately, you couldn't afford any laptop at all or no laptops had a positive profit for you.\n";
    }

    //final message with the resulting capital
    cout << "\nThe summer has ended. Your capital is: " << result << " dollars." << endl;
    return 0;
}
