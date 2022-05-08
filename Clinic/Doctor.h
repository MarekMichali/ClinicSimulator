#pragma once
#include "Worker.h"


/** Pochodna klasy pracownik. Przechowuje dane lekarzy */
class Doctor : public Worker {
	int specialization;	///< id specjalizacji lekarza
	int shift;		///< godziny pracy lekarza
	friend class DoctorList;
	friend class AppointmentList;
	friend std::istream& operator>>(std::istream& in, Doctor& doc);	///< sluzy do wprowadzania danych lekarzy
public:
	int getSpecialization();
	int getShift();
	Doctor();
};
