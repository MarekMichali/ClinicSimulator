#pragma once
#include "Doctor.h"


/** Przechowuje dane wizyty i przypisanego do niej lekarza. */
class Appointment {
	int year;	///< rok wizyty
	int month;	///< miesiac wizyty
	int day;	///< dzien wizyty
	int hour;	///< godzina wizyty
	int minute;	///< minuta wizyty
	int weight;	///< uzywane do sortowania podczas dodawana wizyt, aby byly chronologicznie ulozone w liscie
	int id;		///< id lekarza przypisanego do danej wiyty
	friend class AppointmentList;
	friend std::istream& operator>>(std::istream& in, Appointment& appointment);	///< sluzy do wprowadzania danych wizyty
	Appointment();
};
