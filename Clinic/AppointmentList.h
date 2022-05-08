#pragma once
#include "Appointment.h"
#include "DoctorList.h"

/** Sluzy do tworzenia listy jednokierunkowej wizyt. */
class AppointmentList {
	Appointment appointment;	///< pojedyncza wizyta
	AppointmentList* pNext;	///< wskaznik na kolejna wizyte chronologicznie
public:
	/** Metoda dodaje nowa wizyte do listy.
	@param  pHead2 wskaznik na poczatek listy wizyt
	@param  pHead wskaznik na poczatek listy lekarzy
	@return czy powiodlo sie dodanie wizyty
	*/
	bool addAppointment(AppointmentList*& pHead2, DoctorList* pHead);	
	/** Metoda usuwa wybrana wizyte z listy.
	@param  pHead wskaznik na poczatek listy lekarzy
	@param  pHead2 wskaznik na poczatek listy wizyt
	*/
	void removeAppointment(DoctorList* pHead, AppointmentList*& pHead2);
	/** Metoda wypisuje wizyty z listy.
	@param  pHead wskaznik na poczatek listy lekarzy
	@param  akcja jesli 0 to wyswietla wszytkie wizyty, jesli 1 wyswietla tylko jedna wybrana
	*/
	void getAppointment(DoctorList* pHead, int akcja = 0);
	/** Metoda wczytuje dane wizyt z pliku txt do programu
	@param  pHead2 wskaznik na poczatek listy wizyt
	@return czy powiodlo sie wczytanie danych 
	*/
	bool getAppointment(AppointmentList*& pHead2);
	/** Metoda zapisuje dane wizyt do pliku txt.
	@param  pHead2 wskaznik na poczatek listy wizyt
	*/
	void saveAppointments(AppointmentList*& pHead2);
	/** Metoda pozwala edytowac wybrana wizyte.
	@param  pHead2 wskaznik na poczatek listy wizyt
	*/
	void editAppointment(AppointmentList*& pHead2, DoctorList* pHead);
	/** Metoda usuwa wszystkie wizyty ktore juz mialy miejsce w czasie.
	@param  pHead2 wskaznik na poczatek listy wizyt
	*/
	void clearPastAppointments(AppointmentList*& pHead2);
	/** Metoda usuwa listy wizyt i lekarzy bez zapisywania.
	@param  pHead wskaznik na poczatek listy lekarzy
	@param  pHead2 wskaznik na poczatek listy wizyt
	*/
	void deleteAllDoctorsAndAppointmentsWithoutSaving(DoctorList*& pHead, AppointmentList*& pHead2);
	//zlicza ilosc lekarzy
	void operator++();
	//usuwa ostatniego lekarza w liscie
	void operator--();
	AppointmentList();
};