#include <iostream>
#include <ctime>
#include <array>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <unistd.h>
using namespace std;

class Month
{
private:
    int monthNum;
    int year;
    double income;
    double needsSpending;
    double wantsSpending;
    double saving;
    vector<string> transactions;

public:
    Month(int a, int b, double c, double d, double e, double f, vector<string> g)
    {
        monthNum = a;
        year = b;
        income = c;
        needsSpending = d;
        wantsSpending = e;
        saving = f;
        transactions = g;
    }
    void addDescription(string d)
    {
        transactions.push_back(d);
    }
    void addIncome(double amount)
    {
        income += amount;
    }
    void addNeeds(double amount)
    {
        needsSpending += amount;
    }
    void addWants(double amount)
    {
        wantsSpending += amount;
    }
    void addSavings(double amount)
    {
        saving += amount;
    }
    void getPercents()
    {
        double needsPercent = needsSpending / income * 100;
        double wantsPercent = wantsSpending / income * 100;
        double savingPercent = saving / income * 100;
        cout << "" << endl;
        if (needsPercent + wantsPercent + savingPercent > 100)
        {
            cout << "You overspent this month!" << endl;
        }
        if (needsPercent + wantsPercent + savingPercent < 100)
        {
            cout << "You still have money to use this month!" << endl;
        }
        if (needsPercent + wantsPercent + savingPercent == 100)
        {
            cout << "You used exactly 100% of your income this month" << endl;
        }
        if (needsPercent > 50)
        {
            cout << "Your needs spending is " << needsPercent << "% of your income, spend less on needs!" << endl;
        }
        if (needsPercent < 50)
        {
            cout << "Your needs spending is " << needsPercent << "% of your income" << endl;
        }
        if (needsPercent == 50)
        {
            cout << "Your needs spending is " << needsPercent << "% of your income, nice work!" << endl;
        }
        if (wantsPercent > 30)
        {
            cout << "Your wants spending is " << wantsPercent << "% of your income, spend less on wants!" << endl;
        }
        if (wantsPercent < 30)
        {
            cout << "Your wants spending is " << wantsPercent << "% of your income" << endl;
        }
        if (wantsPercent == 30)
        {
            cout << "Your wants spending is " << wantsPercent << "% of your income, nice work!" << endl;
        }
        if (savingPercent > 20)
        {
            cout << "Your savings is " << savingPercent << "% of your income" << endl;
        }
        if (savingPercent < 20)
        {
            cout << "Your savings is " << savingPercent << "% of your income, save more!" << endl;
        }
        if (savingPercent == 20)
        {
            cout << "Your savings is " << savingPercent << "% of your income, nice work!" << endl;
        }
    }
    void printInfo()
    {
        cout << monthNum << endl;
        cout << year << endl;
        cout << wantsSpending << endl;
        cout << needsSpending << endl;
        cout << income << endl;
        cout << saving << endl;
    }
    void writeInfo(string fileName)
    {
        ofstream MyFile(fileName);
        MyFile << "Month: " << monthNum << endl;
        MyFile << "Year: " << year << endl;
        MyFile << "Income: $" << income << endl;
        MyFile << "Needs Spending: $" << needsSpending << endl;
        MyFile << "Wants Spending: $" << wantsSpending << endl;
        MyFile << "Savings: $" << saving << endl;
        for (auto &s : transactions)
        {
            MyFile << s << endl;
        }
        MyFile.close();
    }
};
int getMonth()
{
    int year;
    int month;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = ltm->tm_year + 1900;
    int currentMonth = ltm->tm_mon + 1;
    string inputYear = "";
    string inputMonth = "";
    cout << "" << endl;
    cout << "Enter the year you want to edit (if current year, just press enter) ";

    getline(cin, inputYear);
    if (inputYear.length() == 0)
    {
        year = currentYear;
    }
    while (inputYear.length() != 0 && (stoi(inputYear) < 2020 || stoi(inputYear) > currentYear))
    {
        cout << "Please enter a valid year after 2019 and not in the future. ";

        getline(cin, inputYear);
    }
    if (inputYear.length() != 0)
    {
        year = stoi(inputYear);
    }
    cout << "" << endl;
    cout << "Please enter the month you want to edit [1 for Jan., 12 for Dec.] (if current month, just press enter) ";

    getline(cin, inputMonth);
    if (inputMonth.length() == 0)
    {
        month = currentMonth;
    }
    while (inputMonth.length() != 0 && (stoi(inputMonth) < 1 || stoi(inputMonth) > 12))
    {
        cout << "Please enter a valid month (1-12). ";

        getline(cin, inputMonth);
    }
    if (inputMonth.length() != 0)
    {
        month = stoi(inputMonth);
    }
    return (year - 1) * 12 + month;
}
string convertMonthToFileName(int monthNumber)
{
    int year = monthNumber / 12 + 1;
    int month = monthNumber % 12 - 1;
    string yearString = "";
    string monthString = "";
    string returnString = "";
    array<string, 12> months = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec",
    };
    monthString = months[month];
    yearString = to_string(year);
    returnString = monthString + yearString;
    return returnString;
}
bool checkMonth(string fileName)
{
    ifstream ifile;
    ifile.open(fileName);
    if (ifile)
    {
        return true;
    }
    else
    {
        return false;
    }
}
Month monthExistsConstructor(string fileName)
{
    ifstream MyFile(fileName);
    string monthString = "";
    string yearString = "";
    string incomeString = "";
    string needsString = "";
    string wantsString = "";
    string savingsString = "";
    string transactionString = "";
    vector<string> transactions;
    getline(MyFile, monthString);
    getline(MyFile, yearString);
    getline(MyFile, incomeString);
    getline(MyFile, needsString);
    getline(MyFile, wantsString);
    getline(MyFile, savingsString);
    while (getline(MyFile, transactionString))
    {
        transactions.push_back(transactionString);
    }
    monthString = monthString.substr(7);
    yearString = yearString.substr(6);
    incomeString = incomeString.substr(9);
    needsString = needsString.substr(17);
    wantsString = wantsString.substr(17);
    savingsString = savingsString.substr(10);
    int a = stoi(monthString);
    int b = stoi(yearString);
    double c = stod(incomeString);
    double d = stod(needsString);
    double e = stod(wantsString);
    double f = stod(savingsString);
    Month newMonth(a, b, c, d, e, f, transactions);
    MyFile.close();

    return newMonth;
}
Month monthDNEConstructor(string fileName, int monthNumber)
{
    int year = monthNumber / 12 + 1;
    int month = monthNumber % 12;
    vector<string> empty = vector<string>();
    Month newMonth(month, year, 0.0, 0.0, 0.0, 0.0, empty);
    ofstream MyFile(fileName);
    MyFile << "Month: " << month << endl;
    MyFile << "Year: " << year << endl;
    MyFile << "Income: $" << 0 << endl;
    MyFile << "Needs Spending: $" << 0 << endl;
    MyFile << "Wants Spending: $" << 0 << endl;
    MyFile << "Savings: $" << 0 << endl;
    MyFile.close();
    return newMonth;
}
void transactions(Month &monthToEdit)
{
    string transactionNumber = "";
    cout << "" << endl;
    cout << "Would you like to record Income [1], Needs [2], Wants[3], or Savings [4]? ";
    getline(cin, transactionNumber);
    while (stoi(transactionNumber) > 4 || stoi(transactionNumber) < 1)
    {
        cout << "" << endl;
        cout << "Please enter a valid transaction number, [1-4] ";
        getline(cin, transactionNumber);
    }
    int transactionNumber1 = stoi(transactionNumber);
    if (transactionNumber1 == 1)
    {
        string incomeAmount = "";
        string description1 = "";
        string description2 = "";
        cout << "" << endl;
        cout << "What is the date of this transaction? ";
        getline(cin, description1);
        cout << "Enter a description of this transaction: ";
        getline(cin, description2);
        cout << "How much $ was this transaction? ";
        getline(cin, incomeAmount);
        double amount1 = stod(incomeAmount);
        string description = description1 + ": " + description2;
        monthToEdit.addDescription(description);
        monthToEdit.addIncome(amount1);
    }
    if (transactionNumber1 == 2)
    {
        string needsAmount = "";
        string description1 = "";
        string description2 = "";
        cout << "" << endl;
        cout << "What is the date of this transaction? ";
        getline(cin, description1);
        cout << "Enter a description of this transaction: ";
        getline(cin, description2);
        cout << "How much $ was this transaction? ";
        getline(cin, needsAmount);
        double amount1 = stod(needsAmount);
        string description = description1 + ": " + description2;
        monthToEdit.addDescription(description);
        monthToEdit.addNeeds(amount1);
    }
    if (transactionNumber1 == 3)
    {
        string wantsAmount = "";
        string description1 = "";
        string description2 = "";
        cout << "" << endl;
        cout << "What is the date of this transaction? ";
        getline(cin, description1);
        cout << "Enter a description of this transaction: ";
        getline(cin, description2);
        cout << "How much $ was this transaction? ";
        getline(cin, wantsAmount);
        double amount1 = stod(wantsAmount);
        string description = description1 + ": " + description2;
        monthToEdit.addDescription(description);
        monthToEdit.addWants(amount1);
    }
    if (transactionNumber1 == 4)
    {
        string savingAmount = "";
        string description1 = "";
        string description2 = "";
        cout << "" << endl;
        cout << "What is the date of this transaction? ";
        getline(cin, description1);
        cout << "Enter a description of this transaction: ";
        getline(cin, description2);
        cout << "How much $ was this transaction? ";
        getline(cin, savingAmount);
        double amount1 = stod(savingAmount);
        string description = description1 + ": " + description2;
        monthToEdit.addDescription(description);
        monthToEdit.addSavings(amount1);
    }
}
int main()
{
    vector<Month> months; //uses a stack of months 
    while (true)
    {
        int month = getMonth();
        string fileName = convertMonthToFileName(month) + ".txt";
        bool monthExists = checkMonth(fileName);
        if (monthExists)
        {
            months.push_back(monthExistsConstructor(fileName));
        }
        else
        {
            months.push_back(monthDNEConstructor(fileName, month));
        }
        Month monthToEdit = months[months.size() - 1];
        while (true)
        {
            transactions(monthToEdit);
            cout << "" << endl;
            cout << "Enter 'y' to record another transaction, otherwise enter 'n': ";
            string response = "";
            getline(cin, response);
            if (response.compare("n") == 0)
            {
                monthToEdit.writeInfo(fileName);
                cout << "" << endl;
                cout << "Your breakdown for the month: " << endl;
                monthToEdit.getPercents();
                break;
            }
        }
        cout << "" << endl;
        cout << "Enter 'y' to edit another month, otherwise enter 'n': ";
        string response = "";
        getline(cin, response);
        if (response.compare("n") == 0)
        {
            break;
        }
        months.pop_back();
    }
    cout << "" << endl;
    cout << "THANK YOU, HAVE NICE DAY!" << endl;
    return 0;
}
