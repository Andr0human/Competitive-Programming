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
#define ull unsigned long long
const int mod = (int)1e9 + 7;

struct day_date
{
    int date;
    int month;
    uint64_t year;
    int day;

    day_date() {}

    day_date(int dt, int m, ull y, int d)
    : date(dt), month(m), year(y), day(d) {}

    void
    get()
    { cin >> year >> month >> date; }

    bool
    is_same(const day_date &d) const
    { return d.date == date and d.month == month and d.year == year; }
};

class Calendar
{
  private:
    const int month[13] = {
        0, 31, 28, 31, 30, 31,
        30, 31, 31, 30, 31, 30, 31
    };
    const string days[7] = {
        "Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday", "Saturday"
    };
    string name[13] = {
        "", "January", "February", "March",
        "April", "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    
    const static ull per_shift_count = 688;
    day_date start_day;

    bool
    is_leap_year(ull year) const
    { return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0); }

    void
    print(const day_date &d) const
    { cout << d.date << " " << name[d.month] << " " << d.year << ", " << days[d.day] << endl; }

  public:
    Calendar() :
    start_day(1, 1, 1900, 1) {}

    void
    next(day_date d)
    {
        int lastDate = month[d.month];
        if ((lastDate == 28) and is_leap_year(d.year)) lastDate++;

        d.day = (d.day + 1) % 7;
        d.date++;
        if (d.date > lastDate)
        {
            d.date = 1;
            d.month++;
        }
        if (d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }

    ull
    shifted_years(ull start) const
    { return static_cast<ull>((start - 1900) / 400) * 400 + 1900; }

    ull
    Solve(const day_date start, const day_date end)
    {    
        start_day.year = shifted_years(start.year);
        day_date curr = traverse_to(start);

        ull counter = 0;
        if (!curr.day && curr.date == 1) counter++;

        while (true)
        {
            if (curr.is_same(end))
                break;
            next(curr);
            if (!curr.day && curr.date == 1)
                counter++;
        }

        return counter;
    }

    day_date
    traverse_to(const day_date end)
    {
        day_date known = start_day;
        int counter = 0;
        while (true)
        {
            if (known.is_same(end)) break;
            next(known);
            if (!known.day && known.date == 1)
                counter++;
        }
        return known;
    }
};


int main()
{
    int testcases;
    cin >> testcases;
    
    while(testcases--)
    {
        Calendar cal;
        day_date d1, d2;
        d1.get();
        d2.get();
        ull x = cal.Solve(d1, d2);
        cout << x << endl;
    }
}
