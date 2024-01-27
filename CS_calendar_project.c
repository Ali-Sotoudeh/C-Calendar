#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int days_in_persian_month[] = {0, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29, 29};

void clear()
{
    system("cls");
}

void days_of_month(int year, int month)
{
    printf("\033[%dmSH    \033[m", 32);
    printf("\033[%dmYE    \033[m", 32);
    printf("\033[%dmDO    \033[m", 32);
    printf("\033[%dmSE    \033[m", 32);
    printf("\033[%dmCH    \033[m", 32);
    printf("\033[%dmPA    \033[m", 32);
    printf("\033[%dmJO\033[m\n", 32);

    int number_of_days = ((year * 365) + (year / 4) + 1) % 7;

    for (int i = 1; i < month; i++)
    {
        number_of_days = (number_of_days + days_in_persian_month[i]) % 7;
    }
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0 && year % 100 == 0))
        days_in_persian_month[12] = 30;
    else
    {
        days_in_persian_month[12] = 29;
    }
    number_of_days = number_of_days + days_in_persian_month[12];

    for (int day = 1; day <= number_of_days; day++)
    {
        printf(" ");
    }
    for (int day = 1; day <= days_in_persian_month[month]; day++)
    {
        printf("%-6d", day);

        if ((day + number_of_days) % 7 == 0 || day == days_in_persian_month[month])
            printf("\n");
    }
}

struct tm finding_time()
{
    time_t t = time(NULL);
    struct tm current_date = *localtime(&t);
    return current_date;
}

int LeapYear(int year)
{
    if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
        return 1;
    else
        return 0;
}

void christian_to_persian(int year, int month, int day, int *sYear, int *sMonth, int *sDay)
{
    int countDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i, dayYear;
    int newMonth, newYear, newDay;

    dayYear = 0;
    for (i = 1; i < month; i++)
    {
        dayYear = dayYear + countDays[i - 1];
    }
    dayYear = dayYear + day;

    if (LeapYear(year) && month > 2)
        dayYear = dayYear + 1;

    if (dayYear <= 79)
    {
        if ((year - 1) % 4 == 0)
        {
            dayYear = dayYear + 11;
        }
        else
        {
            dayYear = dayYear + 10;
        }

        newYear = year - 622;
        if (dayYear % 30 == 0)
        {
            newMonth = (dayYear / 30) + 9;
            newDay = 30;
        }
        else
        {
            newMonth = (dayYear / 30) + 10;
            newDay = dayYear % 30;
        }
    }
    else
    {
        newYear = year - 621;
        dayYear = dayYear - 79;

        if (dayYear <= 186)
        {
            if (dayYear % 31 == 0)
            {
                newMonth = dayYear / 31;
                newDay = 31;
            }
            else
            {
                newMonth = (dayYear / 31) + 1;
                newDay = dayYear % 31;
            }
        }
        else
        {
            dayYear = dayYear - 186;

            if (dayYear % 30 == 0)
            {
                newMonth = (dayYear / 30) + 7;
                newDay = 30;
            }
            else
            {
                newMonth = (dayYear / 30) + 8;
                newDay = dayYear % 30;
            }
        }
    }

    *sYear = newYear;
    *sMonth = newMonth;
    *sDay = newDay;
}

void persian_to_christian(int y, int m, int d, int *gYear, int *gMonth, int *gDay)
{
    int sumPersian[] = {31, 62, 93, 124, 155, 186, 216, 246, 276, 306, 336, 365};
    int christianDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int yy, mm, dayCount;
    dayCount = d;
    if (m > 1)
        dayCount = dayCount + sumPersian[m - 2];
    yy = y + 621;
    dayCount = dayCount + 79;

    if (LeapYear(yy) == 1)
    {
        if (dayCount > 366)
        {
            dayCount = dayCount - 366;
            yy = yy + 1;
        }
    }
    else if (dayCount > 365)
    {
        dayCount = dayCount - 365;
        yy = yy + 1;
    }

    if (LeapYear(yy) == 1)
        christianDays[1] = 29;

    mm = 0;
    while (dayCount > christianDays[mm])
    {
        dayCount = dayCount - christianDays[mm];
        mm = mm + 1;
    }

    *gYear = yy;
    *gMonth = mm + 1;
    *gDay = dayCount;
}

void calculate_age(int birth_year, int birth_month, int birth_day)
{
    clear();
    struct tm current_date = finding_time();

    int current_christian_year = current_date.tm_year + 1900;
    int current_christian_month = current_date.tm_mon;
    int current_christian_day = current_date.tm_mday;

    int current_year, current_month, current_day;
    christian_to_persian(current_christian_year, current_christian_month, current_christian_day,
                         &current_year, &current_month, &current_day);

    int age_years = current_year - birth_year;
    int age_months = current_month - birth_month;
    int age_days = current_day - birth_day;

    if (age_days < 0)
    {
        age_months--;
        age_days += days_in_persian_month[current_month];
    }

    if (age_months < 0)
    {
        age_years--;
        age_months += 12;
    }
    int number_of_days = (birth_year * 365 + (birth_year / 4) + 1) % 7;

    for (int i = 1; i < birth_month; i++)
        number_of_days = (number_of_days + days_in_persian_month[i]) % 7;

    int birthdate_number_of_days = number_of_days;
    int day_of_week_index = (birthdate_number_of_days + birth_day - 1) % 7;

    printf("\nYour Age: %d years, %d months, %d days\n", age_years, age_months, age_days);

    char *days_of_week[] = {"SHANBE", "YEKSHANBE", "DOSHANBE", "SESHANBE", "CHAHARSHANBE", "PANJSHANBE", "JOMEH"};
    printf("\nYou were born on %s\n", days_of_week[day_of_week_index]);

    int gYear, gMonth, gDay;
    persian_to_christian(birth_year, birth_month, birth_day, &gYear, &gMonth, &gDay);

    birth_year = gYear;
    birth_month = gMonth;
    birth_day = gDay;

    time_t birth_time = mktime(&(struct tm){0, 0, 0, birth_day, birth_month - 1, birth_year - 1900, 0, 0, -1});
    time_t current_time = mktime(&current_date);

    int seconds_lived = difftime(current_time, birth_time);
    int days_lived = seconds_lived / (60 * 60 * 24);

    printf("\nNumber of days passed since your birth: %d\n", days_lived);

    printf("Christian birth date: %d/%02d/%02d\n", gYear, gMonth, gDay);

    printf("----------------------------------------------");
    menu();
}

int months(int year)
{
    printf("Enter Month: ");
    int month;
    scanf("%d", &month);
        if (month <= 0 || month > 12)
        {
            printf("\e[31mInvalid Input!\e[m\n");
            months(year);
        }
}

void calendar()
{
    printf("\n[0] Back to menu\n");
    for (int i = 0; i < 5; i++)
        printf("-----");
    printf("\nEnter Year: ");
    int year;
    scanf("%d", &year);
    if (year == 0)
        menu();
    else if (year >= 1206 && year <= 1498)
    {
        int month = months(year);
        if (month <= 0 || month > 12)
        {
            printf("\e[31mInvalid Input!\e[m");
            calendar();
        }
        else
        {
            switch (month)
            {
            case 1:
                printf("\033[%dm               Farvardin              \033[m\n", 100);
                break;
            case 2:
                printf("\033[%dm              Ordibehesht             \033[m\n", 100);
                break;
            case 3:
                printf("\033[%dm                Khordad               \033[m\n", 100);
                break;
            case 4:
                printf("\033[%dm                  Tir                 \033[m\n", 100);
                break;
            case 5:
                printf("\033[%dm                 Mordad               \033[m\n", 100);
                break;
            case 6:
                printf("\033[%dm               Shahrivar              \033[m\n", 100);
                break;
            case 7:
                printf("\033[%dm                  Mehr                \033[m\n", 100);
                break;
            case 8:
                printf("\033[%dm                  Aban                \033[m\n", 100);
                break;
            case 9:
                printf("\033[%dm                  Azar                \033[m\n", 100);
                break;
            case 10:
                printf("\033[%dm                  Dey                 \033[m\n", 100);
                break;
            case 11:
                printf("\033[%dm                 Bahman               \033[m\n", 100);
                break;
            case 12:
                printf("\033[%dm                 Esfand               \033[m\n", 100);
                break;
            }
            days_of_month(year, month);
        }
        calendar();
    }
    else
    {
        clear();
        printf("\e[31mInvalid Input!\e[m");
        calendar();
    }
}

void age()
{
    printf("\n[0] Back to menu\n");
    for (int i = 0; i < 5; i++)
        printf("-----");
    printf("\nEnter your Birth year: ");
    int year;
    scanf("%d", &year);
    if (year == 0)
        menu();
    else if (year >= 1206 && year <= 1498)
    {
        printf("Enter your Birth month: ");
        int month;
        scanf("%d", &month);
        if (month <= 0 || month > 12)
        {
            printf("Invalid Input!");
            age();
        }
        else
        {
            int day;
            printf("Enter your Birth day: ");
            scanf("%d", &day);
            if (day < 1 || day > 31)
            {
                printf("Invalid input!");
                age();
            }
            else
            {
                calculate_age(year, month, day);
            }
        }
    }
    else
        age();
}

void conversion()
{
    int choice, gYear, gMonth, gDay;
    printf("\n[0] Back to menu\n");
    printf("[1] Persian to Christian\n");
    printf("[2] Christian to Persian\n");
    for (int i = 0; i < 5; i++)
        printf("-----");
    printf("\nWhich operation do you want? ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("\nEnter Year: ");
        int year;
        scanf("%d", &year);
        if (year == 0)
            menu();
        else if (year >= 1206 && year <= 1498)
        {
            printf("Enter Month: ");
            int month;
            scanf("%d", &month);
            if (month <= 0 || month > 12)
            {
                printf("Invalid Input!");
                conversion();
            }
            else
            {
                int day;
                printf("Enter Day: ");
                scanf("%d", &day);
                if (day > 31 || day < 1)
                {
                    printf("Invalid Input!");
                    conversion();
                }
                else
                {
                    clear();
                    persian_to_christian(year, month, day, &gYear, &gMonth, &gDay);
                    printf("\nConverted Christian date: %d/%02d/%02d\n", gYear, gMonth, gDay);
                    conversion();
                }
            }
        }
    }
    else if (choice == 2)
    {
        printf("\nEnter Year: ");
        int year;
        scanf("%d", &year);
        if (year == 0)
            menu();
        else if (year >= 1826 && year <= 2119)
        {
            printf("Enter Month: ");
            int month;
            scanf("%d", &month);
            if (month <= 0 || month > 12)
            {
                printf("Invalid Input!");
                conversion();
            }
            else
            {
                int day;
                printf("Enter Day: ");
                scanf("%d", &day);
                if (day > 31 || day < 1)
                {
                    printf("Invalid Input!");
                    conversion();
                }
                else
                {
                    clear();
                    christian_to_persian(year, month, day, &gYear, &gMonth, &gDay);
                    printf("\nConverted Persian date: %d/%02d/%02d\n", gYear, gMonth, gDay);
                    conversion();
                }
            }
        }
    }

    else
        menu();
}

void menu()
{
    for (int i = 0; i < 5; i++)
        printf("-----");
    printf("\n[0] Quit\n[1] Calendar\n[2] Age\n[3] Conversion\n");
    for (int i = 0; i < 5; i++)
        printf("-----");
    printf("\nSelect Option: ");
    int input;
    scanf("%d", &input);
    if (input == 0)
    {
        clear();
        printf("\x1B[1mBye!\x1B[0m");
    }
    else if (input == 1)
    {
        calendar();
    }
    else if (input == 2)
    {
        age();
    }
    else if (input == 3)
    {
        conversion();
    }
    else
    {
        printf("Invalid input!\n");
        menu();
    }
}

int main()
{
    menu();
}