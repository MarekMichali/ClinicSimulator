#pragma once
#include <string>

/** Podstawowa klasa pracowników przychodni. */
class Worker {
public:
	std::string name;	///< imie pracownika
	std::string surname;	///< nazwisko pracownika
	Worker();
	int getId();
private:
	int id;		///< unikalny identyfikator pracownika
	friend class DoctorList;
	friend class AppointmentList;
	

};