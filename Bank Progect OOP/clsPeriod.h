#pragma once
#include "clsDate.h"
#include <iostream>
using namespace std;



class clsPeriod
{

private:

	clsDate _StartPeriod;
	clsDate _EndPeriod;


public:
	

	clsPeriod(clsDate StratPeriod , clsDate EndPeriod) {

		_StartPeriod = StratPeriod;
		_EndPeriod = EndPeriod;
	}

	static bool isOverleapPeriods(clsPeriod Period1, clsPeriod Period2) {

		return !(clsDate::CompareDates(Period1._StartPeriod, Period2._EndPeriod) == clsDate::enDateCompare::After
			||
			clsDate::CompareDates(Period1._EndPeriod, Period2._StartPeriod) == clsDate::enDateCompare::Before);
	}
	bool isOverLeapWith(clsPeriod PeriodToCompare) {

		return isOverleapPeriods(*this, PeriodToCompare);
	}

	static bool isDateInPeriod(clsPeriod Period, clsDate DateToCheck) {

		return !(
			clsDate::CompareDates(DateToCheck, Period._StartPeriod) == clsDate::enDateCompare::Before
			||
			clsDate::CompareDates(DateToCheck, Period._EndPeriod) == clsDate::enDateCompare::After
			);
	}
	bool isDateInPeriod(clsDate DateToCheck) {

		return isDateInPeriod(*this, DateToCheck);
	}

	static int PeriodLengthInDays(clsPeriod Period, bool IncludeEndDay = false) {

		return clsDate::GetDifferenceInDays(Period._StartPeriod, Period._EndPeriod, IncludeEndDay);
	}
	int PeriodLengthInDays(bool IncludeEndDay = false) {

		return PeriodLengthInDays(*this, IncludeEndDay);
	}

	static short CountOverleapDays(clsPeriod Period1, clsPeriod Period2, bool IncludeEndDay = false) {

		int Period1LengthInDays = clsDate::GetDifferenceInDays(Period1._StartPeriod, Period1._EndPeriod,IncludeEndDay);
		int Period2LengthInDays = clsDate::GetDifferenceInDays(Period2._StartPeriod, Period2._EndPeriod, IncludeEndDay);
		short CounterOfOverleapDays = 0;

		if (!isOverleapPeriods(Period1, Period2))
			return 0;


		if (Period1LengthInDays < Period2LengthInDays) {

			while (clsDate::isDate1BeforeDate2(Period1._StartPeriod,Period1._EndPeriod))
			{
				if (isDateInPeriod(Period2,Period1._StartPeriod))
					CounterOfOverleapDays++;

				Period1._StartPeriod.IncreaseDateByOneDay();
			}
		}
		else {

			while (clsDate::isDate1BeforeDate2(Period2._StartPeriod, Period2._EndPeriod))
			{
				if (isDateInPeriod(Period1, Period2._StartPeriod))
					CounterOfOverleapDays++;

				Period2._StartPeriod.IncreaseDateByOneDay();
			}
		}

		return CounterOfOverleapDays;
	}
	short CountOverleapDays(clsPeriod PeriodToCheck, bool IncludeEndDay = false) {

		return CountOverleapDays(*this, PeriodToCheck, IncludeEndDay);
	}


	void Print()
	{
		cout << "Period Start: ";
		_StartPeriod.Print();

		cout << "Period End: ";
		_EndPeriod.Print();

	}

};

