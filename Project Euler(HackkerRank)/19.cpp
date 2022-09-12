/*** 
 * Project Euler #19: Counting Sundays
 * Approach : Calendar has a cycle of 400 years.
 * i.e : dd-mm-(yyyy) and dd-mm-(yyyy+400) has same day.
 * Shift Initial years and brute force it.
***/


#include <bits/stdc++.h>
using namespace std;

#define yes "Yes"
#define no "No"
#define ll long long
#define ull unsigned long long
const int mod = (int)1e9 + 7;

struct day_date {
    int day;
    int date;
    int month;
    ull year;

    day_date() {}

    day_date(int dt, int m, ull y, int d) {
        date = dt;
        month = m;
        year = y;
        day = d;
    }

    void get() {
        cin >> year >> month >> date;
    }

    bool is_same(day_date &d) {
        if (d.date == date && d.month == month && d.year == year)
            return true;
        return false;
    }

};

class Calendar {

    int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    string name[13] = {"", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"};
    const ull per_shift_count = 688;


    day_date start_day;

    bool is_leap_year(ull year) {
        if (year % 4 == 0 && year % 100 != 0) return true;
        if (year % 400 == 0) return true;
        return false;
    }

    void print(day_date &d) {
        std::cout << d.date << " " << name[d.month] << " " << d.year << ", " << days[d.day] << std::endl;
    }

    public:

    Calendar() {
        start_day = day_date(1, 1, 1900, 1);
    }

    void next(day_date &d) {
        int lastDate = month[d.month];

        if (lastDate == 28 && is_leap_year(d.year)) lastDate++;

        d.day = (d.day + 1) % 7;
        d.date++;
        if (d.date > lastDate) {
            d.date = 1;
            d.month++;
        }
        if (d.month > 12) {
            d.month = 1;
            d.year++;
        }
    }

    ull shifted_years(ull start) {
        ull val = start - 1900;
        ull div = val / 400;
        val = div * 400 + 1900;
        return val;
    }

    ull Solve(day_date start, day_date end) {
        
        start_day.year = shifted_years(start.year);
        day_date curr = traverse_to(start);

        ull counter = 0;
        if (!curr.day && curr.date == 1) counter++;

        while (true) {
            if (curr.is_same(end)) break;
            next(curr);
            if (!curr.day && curr.date == 1)
                counter++;
        }

        return counter;
    }

    day_date traverse_to(day_date end) {
        day_date known = start_day;
        int counter = 0;
        while (true) {
            if (known.is_same(end)) break;
            next(known);
            if (!known.day && known.date == 1)
                counter++;
        }
        return known;
    }
};


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int testcases; cin >> testcases;
    while(testcases--) {
        Calendar cal;
        day_date d1, d2;
        d1.get();
        d2.get();
        ull x = cal.Solve(d1, d2);
        std::cout << x << std::endl;
    }
}
