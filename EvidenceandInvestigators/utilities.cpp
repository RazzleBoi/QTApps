#include "utilities.h"

int strToInt(string inputString)
{
    int i = 0;
    for (i = 0; i < inputString.size(); i++)
        if (inputString[i] < '0' || inputString[i]>'9')
            return -1;
    return stoi(inputString);
}

date stringToDate(string dateString)
{
    date aDate;
    aDate.month = stoi(dateString.substr(0, dateString.find_first_of("-")));
    aDate.day = stoi(dateString.substr(dateString.find_first_of("-") + 1, dateString.find_last_of("-") - dateString.find_first_of("-")));
    aDate.year = stoi(dateString.substr(dateString.find_last_of("-") + 1));
    return aDate;
}
