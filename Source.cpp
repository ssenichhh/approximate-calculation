#include <iostream>
#include <cmath>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning ( disable 4996 )

using namespace std;
void ReadingFile(double& xstart, double& xend, double& delta, double& E);
void SavingDisplayingFile(double& xstart, double& xend, double& delta, double& E);
void EnterKeyboard(double& xstart, double& xend, double& delta, double& E);
double RecursiveFunction(double x, double calculation, double E, int& n);
double MainFunction(double x);
void WelcomeSession();
void DialogMenu();

// ________________________________Functions of getting data from user_____________________________________
// Function of getting data through the file
void ReadingFile(double& xstart, double& xend, double& delta, double& E) {
    int choice;
    char File_name[100] = "";
    cout << "Enter filename: ";//Entering the name of file from user
    cin >> File_name;
    FILE* options_file;
    fopen_s(&options_file, File_name, "r");

    if (options_file == NULL) //Checking the existence of the file
    {
        cout << "File named " << File_name << " does not exist\n" << endl; //If the file is not found, the function is started again
        ReadingFile(xstart, xend, delta, E);
    }
    else //Otherwise, scan the file for variables
    {
        fscanf_s(options_file, "%lf %lf %lf %lf", &xstart, &xend, &delta, &E);
        if (xstart >= xend || delta <= 0 || E <= 0 || xstart <= 0 || xstart > 2 || xend <= 0 || xend > 2)// Checking if the file data is correct
        { // if the information from the file is incorrect, the function will ask to enter another file
            cout << "Data from file is incorrect" << endl;
            ReadingFile(xstart, xend, delta, E);
        }
        else //Otherwise, displaying the variables and closing the file
        {
            cout << "Gained data from file: " << endl;
            printf("Begin: %lf \n", xstart);
            printf("End: %lf \n", xend);
            printf("Delta: %lf \n", delta);
            printf("E: %lf \n", E);
            fclose(options_file);
        }
        // Choice of actions
        cout << "What you want to do next?(0 - save and display data; 1 - go to main menu): "; cin >> choice;
        if (choice == 0) // The user chooses the further direction of work
        {
            SavingDisplayingFile(xstart, xend, delta, E);
        }
    }
}

// Function of getting data through the keyboard
void EnterKeyboard(double& xstart, double& xend, double& delta, double& E)
{
    int choice;
    cout << "To start enter the information \n"; ///Checking the data under the conditions of the task
    do {///Entering the start point
        cout << "Enter X start point(0 < xstart <= 2): ";
        cin >> xstart;
    } while (xstart <= 0 || xstart > 2);

    do {///Entering the end point
        cout << "Enter X end point(0 < xend <= 2): ";
        cin >> xend;
    } while (xend <= 0 || xend > 2);
    if (xend == xstart) ///Checking variables
    {
        cout << "You did a mistake, try again";
        cout << "Enter X start point(0 < xstart <= 2): ";
        cin >> xstart;
        cout << "Enter X end point(0 < xend <= 2): ";
        cin >> xend;
    }
    if (xend <= xstart) ///Checking variables
    {
        cout << "Enter X start point(0 < xstart <= 2): ";
        cin >> xstart;
        cout << "Enter X end point(0 < xend <= 2): ";
        cin >> xend;
    }
    do {///Entering the delta
        cout << "Enter a delta (delta > 0): ";
        cin >> delta;
    } while (delta <= 0);

    do {///Entering the E
        cout << "Enter E (E > 0): ";
        cin >> E;
    } while (E <= 0);
    cout << "Entered data: " << endl;
    printf("X start: %lf \n", xstart);
    printf("X end: %lf \n", xend);
    printf("Delta: %lf \n", delta);
    printf("E: %lf \n", E);
    cout << "What you want to do next?(0 - save and display data; 1 - go to main menu): "; cin >> choice; /// Choice of actions
    if (choice == 0)
    {
        SavingDisplayingFile(xstart, xend, delta, E); /// The user chooses the further direction of work
    }

}
//___________________________________________________________________________________________________________

// ______________________________Function of saving and displaying the information_________________________
void SavingDisplayingFile(double& xstart, double& xend, double& delta, double& E)
{
    char filename[30];
    cout << "Enter file name: ";/// User enters the name of file(It is highly recommended to enter the file in the format: _filename_.txt)
    cin >> filename;
    FILE* options_file1;
    fopen_s(&options_file1, filename, "a+");/// Opening the file
    printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    printf("\n|       Xn |        Recursive(y) |      Calculation(y) |      Absolute Error |  Steps |");
    printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    fprintf(options_file1, "\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    fprintf(options_file1, "\n|       Xn |        Recursive(y) |      Calculation(y) |      Absolute Error |  Steps |");
    fprintf(options_file1, "\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    for (xstart; xstart <= xend; xstart += delta) /// Continue the cycle until the conditions are met
    {
        int n = 0;
        double calculation = xstart - 1;
        double RecursiveSum = RecursiveFunction(xstart, calculation, E, n); /// The value of the recursive function
        double CalculationSum = MainFunction(xstart); ///The value of the function
        double AbsoluteError = abs(CalculationSum - RecursiveSum);/// Absolute error of functions
        printf("\n| %8.2f | %19.10f | % 19.10f | %19.10f | %5d  |", xstart, RecursiveSum, CalculationSum, AbsoluteError, n);
        printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
        fprintf(options_file1, "\n| %8.2f | %19.10f | % 19.10f | %19.10f | %5d  |", xstart, RecursiveSum, CalculationSum, AbsoluteError, n);
        fprintf(options_file1, "\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    }
    fprintf(options_file1, "\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
    fclose(options_file1); /// Closing the file
}
//___________________________________________________________________________________________________________

// _____________________________________Functions of calculating __________________________________________
double MainFunction(double xstart)/// Counting the value of functions
{
    double y = log(xstart);
    return y;
}

double RecursiveFunction(double x, double calculation, double E, int& n)/// Counting the value of recursive functions
{
    if (abs(calculation) > E) /// Continue the cycle until the conditions are met
    {
        ++n;
        double  q = -(((n) * (x - 1)) / (n + 1));
        return calculation + RecursiveFunction(x, calculation * q, E, n); ///Recursive function output
    }
    return 0;
}
///_________________________________________________________________________________________________________

/// _________________________________Dialog functions with the user_________________________________________
void WelcomeSession() /// Welcoming the new user
{
    cout << "|Welcome to the programme, which counts the value of the function Ln(x)|" << endl;
    cout << "|Enjoy using|" << endl;
}


void DialogMenu() /// Giving the user a choice of further actions
{
    cout << endl;
    cout << "1 - Entering parameters from the file" << endl;
    cout << "2 - Entering parameters from the keyboard" << endl;
    cout << "3 - Exit" << endl;
    cout << endl;
}
///_________________________________________________________________________________________________________________

/// _________________________________________Main function__________________________________________________
int main()
{
    double xstart = 0;
    double xend = 0;
    double E = 0;
    double delta = 0;
    int choice = 0;
    WelcomeSession();
    while (choice != 3)
    {
        DialogMenu();
        cout << "Choose a command: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            ReadingFile(xstart, xend, delta, E);
            break;
        case 2:
            EnterKeyboard(xstart, xend, delta, E);
            break;
        default:
            break;
        }
    }
}
///___________________________________________________________________________________________________________