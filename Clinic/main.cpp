#include <iostream>
#include <crtdbg.h>
#include <Windows.h>
#include "DoctorList.h"
#include "AppointmentList.h"



int main() {
	DoctorList* docList = nullptr;
	DoctorList* doctor = nullptr;
	AppointmentList* appList = nullptr;
	AppointmentList* appointment = nullptr;
	int action = 0;
	std::cout << "--------------========== Instrukcja ==========--------------" << std::endl;
	std::cout << "Jesli program oczekuje odpowiedzi tak lub nie, to wprowadzenie 1 oznacza tak \na wprowadzenie 0 oznacza nie.";
	std::cout << std::endl << std::endl;
	std::cout << "Czy chcesz wczytac dane lekarzy i wizyt z plikow? 1/0: " << std::endl;
	std::cin >> action;
	if (action == 1) {
		if (docList->readDoctors(docList)) {
			std::cout << "Wczytano dane lekarzy." << std::endl;
			if (appList->getAppointment(appList)) {
				std::cout << "Wczytano liste wizyt." << std::endl;
			}
			else {
				std::cout << "Nie udalo sie wczytac listy wizyt." << std::endl;
			}
		}
		else {
			std::cout << "Nie udalo sie wczytac zadnych danych." << std::endl;
		}
	}
	action = 0;
	std::cout << std::endl << std::endl;
	while (true) {
		std::cout << std::endl << std::endl;
		std::cout << "Wybierz numer z menu aby podjac akcje: \n1. Wypisz liste lekarzy. \n2. Usun lekarza \n3. Dodaj lekarza. \n4. Wypisz liste wizyt. \n5. Usun wizyte \n6. Dodaj wiyte. \n7. Usun stare wizyty. \n8. Edytuj wizyte. \n9. Zapisz i zamknij program. \n10. Wyjdz bez zapisywania." << std::endl;
		std::cin >> action;
		std::cout << std::endl;
		
		if (action == 3) {
			doctor = new DoctorList;
			*doctor += docList;
			action = 0;
		}
		else if (action == 2) {
			docList->removeDoctor(docList);
			action = 0;
		}
		else if (action == 1) {
			docList->getDoctor();
			action = 0;
		}
		else if (action == 6) {
			appointment = new AppointmentList;
			appointment->addAppointment(appList, docList);
			action = 0;
		}
		else if (action == 5) {
			appList->removeAppointment(docList, appList);
		}
		else if (action == 4) {
			appList->getAppointment(docList);
			action = 0;
		}
		else if (action == 7) {
			appList->clearPastAppointments(appList);
			action = 0;
		}
		else if (action == 8) {
			appList->editAppointment(appList, docList);
			action = 0;
		}
		else if (action == 9) {
			appList->saveAppointments(appList);
			docList->saveDoctors(docList);
			std::cout << "Zakonczono dzialanie programu.";
			_CrtDumpMemoryLeaks();
			return 0;
		}
		else if(action==10) {
			appList->deleteAllDoctorsAndAppointmentsWithoutSaving(docList, appList);
			std::cout << "Zakonczono dzialanie programu.";
			_CrtDumpMemoryLeaks();
			return 0;
		}
		else {
			action = 0;
			std::cout << "Taka akcja nie istnieje!" << std::endl;
		}
	}


	return 0;
};