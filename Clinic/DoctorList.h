#pragma once
#include "Doctor.h"

/** Sluzy do tworzenia listy jednokierunkowej lekarzy. */
class DoctorList {
	Doctor doc;	///< pojedynczy lekarz
	DoctorList* pNext;	///< wskaznik na kolejnego lekarza
	friend class AppointmentList;
public:
	/** Metoda dodaje nowego lekarza do listy.
	@param  pHead wskaznik na poczatek listy lekarzy
	*/
	void addDoctor(DoctorList*& pHead);
	/** Metoda usuwa lekarza z listy.
	@param  pHead wskaznik na poczatek listy lekarzy
	*/
	void removeDoctor(DoctorList*& pHead);
	/** Metoda wypisuje lekarzy z listy.
	@param  akcja jesli 0 to wyswietla wszytkich lekarzy, jesli 1 wyswietla tylko jednego wybranego
	*/
	void getDoctor(int action = 0);
	/** Metoda wczytuje dane lekarzy z pliku txt do programu
	@param  pHead2wskaznik na poczatek listy lekarzy
	@return czy powiodlo sie wczytanie danych
	*/
	bool readDoctors(DoctorList*& pHead);
	/** Metoda zapisuje dane lekarzy do pliku txt.
	@param  pHead wskaznik na poczatek listy lekarzy
	*/
	void saveDoctors(DoctorList*& pHead);
	//dodaje element
	DoctorList*& operator+=(DoctorList *& pHead);
	//odejmuje element
	DoctorList*& operator-=(DoctorList*& pHead);
	//zlicza ilosc lekarzy
	void operator++();
	//usuwa ostatniego lekarza w liscie
	void operator--();
	friend std::ostream& operator<<(std::ostream& out, DoctorList* pHead);
	DoctorList();
};