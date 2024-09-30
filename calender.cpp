/**
 *
 * @file calendar.cpp
 * @author Gideon Kobea
 * @collaborators
 * @date 09/19/2024
 * IDEA: The idea is to create some functions and call them to reuse them again
 * First: I created a leap year function which calculates if a year is a leap year returns true by using the conditions for it
 * and also a function for month_checker which check the number of days in month taking into account when a year is leap year
 * Using calc_first_day function, I calculate the total number of days from the reference year (1900) to the input the user type (which is year and month)
 * I calculate the total days before the actual day in my function so that I don't double count the first day
 * After the total days is calculated, I find the modulus of the total day with 7 to find the first day of the month.
 * Finally, I use the calendar_display function to display the calendar
 */
#include <iostream>
#include <string>

using namespace std;

const unsigned short MONTHS_PER_YEAR = 12;

const unsigned short DAYS_PER_MONTH[MONTHS_PER_YEAR] =
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const string MONTH_NAMES[MONTHS_PER_YEAR] =
    {"January",   "February", "March",    "April",
     "May",       "June",     "July",     "August",
     "September", "October",  "November", "December"};

 bool leap_year(int year) {
  if(year % 400 == 0) {
        return true;
    } else if (year % 100 == 0) {
        return false;
    } else if (year % 4 == 0) {
        return true;
    } else {
        return false;
    }
    }
 int month_checker(int month, int year_num) {
    if(month == 2 ){
        if (leap_year(year_num)){
            return 29;
        }
        return DAYS_PER_MONTH[month-1];
 }      return DAYS_PER_MONTH[month-1];
 }
int calc_first_day(int day, int Month, int Year){
    int ref_year = 1900;
    int ref_day_of_week =5; // this is to make sure that i'm indexing the days of the week very well... with monday being sunday being 0, monday being 1 and so on
    int total_days =1;
    for(int i = 0; i < Year; i++){
        if (leap_year(i)){
            total_days += 366;
        } else{
            total_days += 365;
        }
    }
    for(int i =1; i < Month; i++){        // the indexing is 1 because of how months are named, and I only want to add the number of days before the actual month
        total_days += month_checker(i, Year);

    }
    total_days += day-1; //  so I subtracted 1 because I want to add all the days before the actual day, i.e, i don't want to include the actual day
    int day_of_week = (ref_day_of_week + total_days) % 7; // formula to get the first day of the specified month

    return day_of_week;
}
void calendar_display(int month, int year){
    int days_in_month = month_checker(month, year);
    int first_day = calc_first_day(1, month, year);

    cout << " " << MONTH_NAMES[month - 1] << " " << year << endl;
    cout <<"Su  M  T  W Th  F Sa"<<endl;

    int current_day= 1;

    for (int week = 0; week < 6; week++) {
       bool printed_any_day = false;
        for (int day = 0; day < 7; day++) {
            if (week == 0 && day < first_day) {
                cout << "   ";
            }
                else {
                printed_any_day = true;
                if (current_day < 10) {
                    cout << " " << current_day;
                } else if(current_day<= days_in_month) {
                    cout << current_day;
                }
                current_day++;
                if (day < 6 && current_day <= days_in_month) { // the idea is to only print space if the day is less than 6 or it's less than the total days in the month
                    cout << " ";
                }

            }
        }

        if (printed_any_day && current_day <= days_in_month) {
            cout << endl;
        }
    }
}

// Controls operation of the program.
int main(){
    int month=0;
    int year=0;
    cout<< "Enter the month: ";
    cin>> month;
    cout<<"Enter the year:";
    cin >> year;
    if (month < 1 || month > 12 || year < 0) {
        cout << "Invalid month or year." << endl;
        return 1;
    }
    calendar_display(month, year);

    cout << endl;

    return 0;
}