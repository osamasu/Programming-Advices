#pragma once
#include <iostream>
#include <string>
#include "clsString.h"

using namespace std;


#pragma warning (disable : 4996)
class clsDate
{

private:

	short _Year;
	short _Month;
	short _Day;

public:

	static clsDate GetSystemDate() {

		clsDate Date = clsDate(2022, 2, 2);
		time_t t = time(0);   // get time now 


		// converting now to tm struct for UTC date/time 
		tm* gmtm = gmtime(&t);

		Date._Year = gmtm->tm_year + 1900;
		Date._Month = gmtm->tm_mon + 1;
		Date._Day = gmtm->tm_mday;

		return Date;
	}

	static string GetSystemDateFullTimeInString() {

		clsDate Date = clsDate(2022, 2, 2);
		time_t t = time(0);   // get time now 


		// converting now to tm struct for UTC date/time 
		tm* gmtm = gmtime(&t);

		Date.Year = gmtm->tm_year + 1900;
		Date._Month = gmtm->tm_mon + 1;
		Date.Day= gmtm->tm_mday;
		short Hour = gmtm->tm_hour + 1;
		short Minute = gmtm->tm_min + 1;
		short Second = gmtm->tm_sec;


		string DateInString = DateToString(Date) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
		return DateInString;
	}

	clsDate() {

		*this = GetSystemDate();
	}
	clsDate(short Year, short Month, short Day) {

		_Year = Year;
		_Month = Month;
		_Day = Day;
	}
	clsDate(string DateString) {

		vector <string> vDate = clsString::Split(DateString, "/");

		_Year = stoi(vDate[0]);

		_Month = stoi(vDate[1]);

		_Day = stoi(vDate[2]);

	}
	clsDate(short DaysFromBeggingOfTheYear, short Year) {

		*this = ConvertRemainingDaysToADATE(Year, DaysFromBeggingOfTheYear);
	}


	void SetYear(short Year) {

		_Year = Year;
	}
	short GetYear() {

		return _Year;
	}
	__declspec(property(put = SetYear, get = GetYear)) short Year;

	void SetMonth(short Month) {

		_Month = Month;
	}
	short GetMonth() {

		return _Month;
	}
	__declspec(property(put = SetMonth, get = GetMonth)) short Month;

	void SetDay(short Day) {

		_Day = Day;
	}
	short GetDay() {

		return _Day;
	}
	__declspec(property(put = SetDay, get = GetDay)) short Day;


	static bool isLeapYear(short Year) {

		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}
	bool isLeapYear() {

		return isLeapYear(_Year);
	}

	static bool isValidYear(short Year) {

		return (Year >= 0);
	}
	bool isValidYear() {

		return isValidYear(_Year);
	}

	static bool isValidMonth(short Month) {

		return (Month >= 1 && Month <= 12);
	}
	bool isValidMonth() {

		return isValidMonth(_Month);
	}

	static bool isValidDay(clsDate Date) {

		return  (Date._Day <= NumberOfDaysInMonth(Date._Year, Date._Month) && Date._Day >= 1);
	}
	bool isValidDay() {

		return isValidDay(*this);
	}
	// Number Of DHMS in Year ===========================

	static short NumberOfDaysInYear(short Year) {

		return isLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInYear() {

		return NumberOfDaysInYear(_Year);
	}

	static short NumberOfHoursInYear(short Year) {

		return NumberOfDaysInYear(Year) * 24;
	}
	short NumberOfHoursInYear() {

		return NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInYear(short Year) {

		return NumberOfHoursInYear(Year) * 60;
	}
	int NumberOfMinutesInYear() {

		return NumberOfMinutesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short Year) {

		return NumberOfMinutesInYear(Year) * 60;
	}
	int NumberOfSecondsInYear() {

		return NumberOfSecondsInYear(_Year);
	}

	//=================================================




	// Number Of DHMS in Month ========================

	static short NumberOfDaysInMonth(short Year, short Month) {

		short DaysOfMonths[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return !isValidMonth(Month) ? 0 : ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : DaysOfMonths[Month - 1]);
	}
	short NumberOfDaysInMonth() {

		return NumberOfDaysInMonth(_Year, _Month);
	}

	static short NumberOfHoursInMonth(short Year, short Month) {

		return NumberOfDaysInMonth(Year, Month) * 24;
	}
	short NumberOfHoursInMonth() {

		return NumberOfHoursInMonth(_Year, _Month);
	}

	static unsigned short NumberOfMinutesInMonth(short Year, short Month) {

		return NumberOfHoursInMonth(Year, Month) * 60;
	}
	unsigned short NumberOfMinutesInMonth() {

		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month) {

		return NumberOfMinutesInMonth(Year, Month) * 60;
	}
	int NumberOfSecondsInMonth() {

		return NumberOfSecondsInMonth(_Year, _Month);
	}

	//==================================================






	static short DayOfWeekOrder(clsDate Date)
	{
		short a = (14 - Date._Month) / 12;
		short y = Date._Year - a;
		short m = Date._Month + (12 * a) - 2;

		return (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOfWeekOrder() {

		return DayOfWeekOrder(*this);
	}
	static short DayOfWeekOrder(short Year, short Month, short Day)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static string ShortDayName(short DayOfWeekOrder)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder];
	}
	string ShortDayName() {

		return ShortDayName(DayOfWeekOrder());
	}

	static string DayShortName(short Day, short Month, short Year)
	{

		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[DayOfWeekOrder(Day, Month, Year)];

	}



	static string MonthShortName(short MonthNumber)
	{
		string arrMonthNames[12] = { "Jan", "Feb", "Mar","Apr", "May", "Jun","Jul", "Aug", "Sep","Oct", "Nov", "Dec" };

		return arrMonthNames[MonthNumber - 1];
	}
	string MonthShortName() {

		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Year, short Month) {

		printf("  _______________%s_______________ \n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat \n");

		short DayOrder = DayOfWeekOrder(Year, Month, 1);

		short i;
		for (i = 0; i < DayOrder; i++) {

			printf("     ");
		}

		short DaysInMonth = NumberOfDaysInMonth(Year, Month);

		for (short j = 1; j <= DaysInMonth; j++) {

			printf("%5d", j);

			if (++i == 7) {

				i = 0;
				cout << endl;
			}
		}

		printf("\n  _________________________________");
	}
	void PrintMonthCalendar() {

		PrintMonthCalendar(_Year, _Month);
	}

	static void PrintYearCalendar(short Year) {

		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", Year);
		printf("  _________________________________\n");

		for (short i = 1; i <= 12; i++) {

			PrintMonthCalendar(Year, i);
			printf("\n\n\n");
		}
	}
	void PrintYearCalendar() {

		PrintYearCalendar(_Year);
	}

	static short NumberOfDaysFromBeggingOfTheYear(clsDate Date) {

		short DaysFromBeggingOfTheYear = 0;

		for (short i = 1; i < Date._Month; i++) {

			DaysFromBeggingOfTheYear += NumberOfDaysInMonth(Date._Year, i);
		}

		return DaysFromBeggingOfTheYear += Date._Day;
	}
	static short NumberOfDaysFromBeggingOfTheYear(short Year, short Month, short Days) {

		short DaysFromBeggingOfTheYear = 0;

		for (short i = 1; i < Month; i++) {

			DaysFromBeggingOfTheYear += NumberOfDaysInMonth(Year, i);
		}

		return DaysFromBeggingOfTheYear += Days;
	}
	short NumberOfDaysFromBeggingOfTheYear() {

		return NumberOfDaysFromBeggingOfTheYear(_Year, _Month, _Day);
	}

	static clsDate ConvertRemainingDaysToADATE(short Year, short RemainingDays) {

		short DaysOfMonth;
		clsDate Date;
		Date._Year = Year;
		Date._Month = 1;
		Date._Day = 1;

		while (true)
		{
			DaysOfMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

			if (RemainingDays >= DaysOfMonth) {

				RemainingDays -= DaysOfMonth;
				Date._Month++;
			}
			else {

				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}
	void ConvertRemainingDaysToADATE(short RemainingDays) {

		*this = ConvertRemainingDaysToADATE(_Year, RemainingDays);
	}

	static clsDate AddDays(clsDate Date, short NumberOfDaysToAdd) {


		short TotalDays = NumberOfDaysToAdd + NumberOfDaysFromBeggingOfTheYear(Date._Year, Date._Month, Date._Day);
		short MonthDays = 0;

		while (true) {

			MonthDays = NumberOfDaysInMonth(Date._Year, Date._Month);

			if (TotalDays > MonthDays) {

				TotalDays -= MonthDays;
				Date._Month++;

				if (Date._Month > 12) {

					Date._Year++;
					Date._Month = 1;
				}
			}

			else {

				Date._Day = TotalDays;
				break;
			}
		}

		return Date;
	}
	void AddDays(short NumberOfDaysToAdd) {

		*this = AddDays(*this, NumberOfDaysToAdd);
	}

	static bool isDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return (Date1._Year < Date2._Year) ? true : (Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month) ? true : (Date1._Month == Date2._Month ? (Date1._Day < Date2._Day) : false) : false;
	}
	bool isDate1BeforeDate2(clsDate DateToCompare) {

		return isDate1BeforeDate2(*this, DateToCompare);
	}

	static bool isDate1EqualsDate2(clsDate Date1, clsDate Date2) {

		return (Date1._Year == Date2._Year) ? (Date1._Month == Date2._Month) ? (Date1._Day == Date2._Day) : false : false;
	}
	bool isDate1EqualsDate2(clsDate DateToCompare) {

		return isDate1EqualsDate2(*this, DateToCompare);
	}

	static bool isLastDayInMonth(clsDate Date) {

		return (Date._Day == NumberOfDaysInMonth(Date._Year, Date._Month));
	}
	bool isLastDayInMonth() {

		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short Month) {

		return (Month == 12);
	}
	bool isLastMonthInYear() {

		return isLastMonthInYear(_Month);
	}





	// Increase Date Methods ===========================

	static clsDate IncreaseDateByOneDay(clsDate Date) {

		if (isLastDayInMonth(Date)) {

			if (isLastMonthInYear(Date._Month)) {

				Date._Year++;
				Date._Month = 1;
				Date._Day = 1;
			}

			else {

				Date._Day = 1;
				Date._Month++;
			}
		}

		else
			Date._Day++;


		return Date;
	}
	void IncreaseDateByOneDay() {

		*this = IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate Date, short NumberOfDaysToIncrease) {

		for (short i = 0; i < NumberOfDaysToIncrease; i++) {

			Date.IncreaseDateByOneDay();
		}

		return Date;
	}
	void IncreaseDateByXDays(short NumberOfDaysToIncrease) {

		*this = IncreaseDateByXDays(*this, NumberOfDaysToIncrease);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date) {

		return Date = IncreaseDateByXDays(Date, 7);
	}
	void IncreaseDateByOneWeek() {

		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, short NumberOfWeeksToIncrease) {

		for (short i = 0; i < NumberOfWeeksToIncrease; i++) {

			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}
	void IncreaseDateByXWeeks(short NumberOfWeeksToIncrease) {

		*this = IncreaseDateByXWeeks(*this, NumberOfWeeksToIncrease);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date) {

		if (isLastMonthInYear(Date._Month)) {

			Date._Year++;
			Date._Month = 1;
		}
		else {
			Date._Month++;
		}


		// This is For Check Days 
		short MonthDays = NumberOfDaysInMonth(Date._Year, Date._Month);

		if (Date._Day > MonthDays) {

			Date._Day = MonthDays;
		}


		return Date;
	}
	void IncreaseDateByOneMonth() {

		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, short NumberOfMonthsToIncrease) {

		for (short i = 0; i < NumberOfMonthsToIncrease; i++) {

			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}
	void IncreaseDateByXMonths(short NumberOfMonthsToIncrease) {

		*this = IncreaseDateByXMonths(*this, NumberOfMonthsToIncrease);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date) {

		return Date = IncreaseDateByXMonths(Date, 12);
	}
	void IncreaseDateByOneYear() {

		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate Date, short NumberOfYearsToIncrease) {

		for (short i = 0; i < NumberOfYearsToIncrease; i++) {

			IncreaseDateByOneYear(Date);
		}

		return Date;
	}
	void IncreaseDateByXYears(short NumberOfYearsToIncrease) {

		*this = IncreaseDateByXYears(*this, NumberOfYearsToIncrease);
	}

	//==================================================




	// Decrease Date Methods ===========================

	static clsDate DecreaseDateByOneDay(clsDate Date) {

		if (Date._Day == 1) {

			if (Date._Month == 1) {

				Date._Month = 12;
				Date._Year--;
			}
			else
				Date._Month--;


			Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
		}

		else {

			Date._Day--;
		}


		return Date;
	}
	void DecreaseDateByOneDay() {

		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate Date, short NumberOfDaysToDecrease) {

		for (short i = 0; i < NumberOfDaysToDecrease; i++) {

			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}
	void DecreaseDateByXDays(short NumberOfDaysToDecrease) {

		*this = DecreaseDateByXDays(*this, NumberOfDaysToDecrease);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date) {

		return Date = DecreaseDateByXDays(Date, 7);
	}
	void DecreaseDateByOneWeek() {

		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, short NumberOfWeeksToDecrease) {

		for (short i = 0; i < NumberOfWeeksToDecrease; i++) {

			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}
	void DecreaseDateByXWeeks(short NumberOfWeeksToDecrease) {

		*this = DecreaseDateByXWeeks(*this, NumberOfWeeksToDecrease);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date) {

		if (Date._Month == 1) {

			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;


		// Thia Is For Days After minusing it 

		short MonthDays = NumberOfDaysInMonth(Date._Year, Date._Month);

		if (Date._Day > MonthDays) {

			Date._Day = MonthDays;
		}

		return Date;
	}
	void DecreaseDateByOneMonth() {

		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, short NumberOfMonthsToDecrease) {

		for (short i = 0; i < NumberOfMonthsToDecrease; i++) {

			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}
	void DecreaseDateByXMonths(short NumberOfMonthsToDecrease) {

		*this = DecreaseDateByXMonths(*this, NumberOfMonthsToDecrease);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date) {

		return Date = DecreaseDateByXMonths(Date, 12);
	}
	void DecreaseDateByOneYear() {

		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate Date, short NumberOfYearsToDecrease) {

		for (short i = 0; i < NumberOfYearsToDecrease; i++) {

			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}
	void DecreaseDateByXYears(short NumberOfYearsToDecrease) {

		*this = DecreaseDateByXYears(*this, NumberOfYearsToDecrease);
	}

	//==================================================




	static void SwapDates(clsDate& Date1, clsDate& Date2) {

		clsDate* DateTemp = new clsDate;

		*DateTemp = Date1;
		Date1 = Date2;
		Date2 = *DateTemp;

		delete DateTemp;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {

		int DifferenceInDays = 0; short SwapFlagValue = 1;

		if (!isDate1BeforeDate2(Date1, Date2)) {

			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (isDate1BeforeDate2(Date1, Date2)) {

			DifferenceInDays++;
			Date1.IncreaseDateByOneDay();
		}

		return (((IncludeEndDay) ? ++DifferenceInDays : DifferenceInDays) * SwapFlagValue);
	}
	int GetDifferenceInDays(clsDate DateToCompare, bool IncludeEndDay = false) {

		return GetDifferenceInDays(*this, DateToCompare, IncludeEndDay);
	}

	static int MyAgeInDays(clsDate Date, bool IncludeEndDay = false) {

		return GetDifferenceInDays(Date, GetSystemDate(), IncludeEndDay);
	}
	int MyAgeInDays(bool IncludeEndDay = false) {

		return MyAgeInDays(*this, IncludeEndDay);
	}

	static bool isEndOfWeek(clsDate Date) {

		return (DayOfWeekOrder(Date) == 6);
	}
	bool isEndOfWeek() {

		return isEndOfWeek(*this);
	}

	static bool isWeekend(clsDate Date) {

		short DayIndex = DayOfWeekOrder(Date);
		return (DayIndex == 5 || DayIndex == 6);
	}
	bool isWeekend() {

		return isWeekend(*this);
	}

	static bool isBusinessDay(clsDate Date) {

		return !isWeekend(Date);
	}
	bool isBusinessDay() {

		return isBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date) {

		return 6 - DayOfWeekOrder(Date);
	}
	short DaysUntilTheEndOfWeek() {

		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date) {

		return NumberOfDaysInMonth(Date._Year, Date._Month) - Date._Day;
	}
	short DaysUntilTheEndOfMonth() {

		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date) {

		return NumberOfDaysInYear(Date._Year) - NumberOfDaysFromBeggingOfTheYear(Date);
	}
	short DaysUntilTheEndOfYear() {

		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateBusinessDays(clsDate StartVication, clsDate EndVication) {

		short VacationDays = 0;

		while (isDate1BeforeDate2(StartVication, EndVication)) {

			if (!isWeekend(StartVication)) {

				VacationDays++;
			}
			IncreaseDateByOneDay(StartVication);
		}

		return VacationDays;
	}
	short CalculateBusinessDays(clsDate EndVication) {

		return CalculateBusinessDays(*this, EndVication);
	}


	static short CalculateVicationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}
	short CalculateVicationDays(clsDate EndVication) {

		return CalculateVicationDays(*this, EndVication);
	}


	static clsDate CalculateVicationReturnDate(clsDate DateFrom, short VicationDays) {

		short WeekEndCounter = 0;

		while (VicationDays > 0 || isWeekend(DateFrom))
		{
			if (isBusinessDay(DateFrom)) {

				VicationDays--;
			}

			DateFrom.IncreaseDateByOneDay();
		}

		return DateFrom;
	}
	void CalculateVicationReturnDate(short VicationDays) {

		*this = CalculateVicationReturnDate(*this, VicationDays);
	}

	static bool isDate1AfterDate2(clsDate Date1, clsDate Date2) {

		return !isDate1BeforeDate2(Date1, Date2) && !isDate1EqualsDate2(Date1, Date2);
	}
	bool  isDate1AfterDate2(clsDate DateToCompare) {

		return isDate1AfterDate2(*this, DateToCompare);
	}



	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {

		if (isDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (isDate1AfterDate2(Date1, Date2))
			return enDateCompare::After;

		return enDateCompare::Equal;
	}
	enDateCompare CompareDates(clsDate DateToCompare) {

		return CompareDates(*this, DateToCompare);
	}



	static	bool IsValidDate(clsDate Date)
	{
		return isValidYear(Date._Year) ? (isValidMonth(Date._Month) ? isValidDay(Date) : false) : false;
	}
	bool IsValid()
	{
		return IsValidDate(*this);
	}

	static char* LocalTime() {

		time_t Time = time(NULL);
		char* pLocTime = (ctime(&Time));
		return pLocTime;
	}

	static char* GMT_Time() {

		time_t Time = time(NULL);
		tm* GMT_Time = gmtime(&Time);
		char* pGMT_Time = asctime(GMT_Time);
		return pGMT_Time;
	}

	static bool isDateBetween(clsDate DateToCompare, clsDate StartPeriod, clsDate EndPeriod) {

		if (isDate1BeforeDate2(EndPeriod, StartPeriod)) {

			SwapDates(EndPeriod, StartPeriod);
		}

		return !(CompareDates(DateToCompare, StartPeriod) == enDateCompare::Before
			||
			CompareDates(DateToCompare, EndPeriod) == enDateCompare::After);
	}


	bool isDateBetween(clsDate StartPeriod, clsDate EndPeriod) {

		return isDateBetween(*this, StartPeriod, EndPeriod);
	}


	static string DateToString(clsDate Date)
	{
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString()
	{
		return  DateToString(*this);
	}


	static string FormatString(clsDate Date, string DateFormatting = "yyyy/mm/dd") {

		DateFormatting = clsString::ReplaceWord(DateFormatting, "yyyy", to_string(Date._Year));
		DateFormatting = clsString::ReplaceWord(DateFormatting, "mm", to_string(Date._Month));
		DateFormatting = clsString::ReplaceWord(DateFormatting, "dd", to_string(Date._Day));

		return DateFormatting;
	}
	string FormatString(string DateFormatting = "yyyy/mm/dd") {

		return FormatString(*this, DateFormatting);
	}

	void Print()
	{
		cout << DateToString() << endl;
	}
};