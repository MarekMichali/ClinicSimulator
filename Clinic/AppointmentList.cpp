#include "AppointmentList.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>


bool AppointmentList::addAppointment(AppointmentList*& pHead2, DoctorList* pHead) {
	int specialization = 0;
	int id = 0;
	int decision = 0;
	appointment.id = 0;
	int taken = 0;
	DoctorList* docList = pHead;
	AppointmentList* appList = pHead2;
	AppointmentList* takenPointer = pHead2;
	std::cout << "Czas wizyty to 15 minut i sa umawiane tylko na pelne kwadranse, \naby obsluzyc jak najwiecej klientow w ciagu dnia unikajac niepotrzebnych okienek. \nGodziny otwarcia 8-18 pon-piatek" << std::endl << std::endl;
	std::cout << "Wprowadz numer z menu do jakiego specjalisty chce sie umowic pacjent:\n1. Podstawowej opieki zdrowotnej \n2. Pediatra \n3. Rodzinny \n4. Internista" << std::endl;
	std::cin >> specialization;
	std::cin >> appointment;
	//waga do sortowania
	appointment.weight = appointment.minute + appointment.hour * 60 + appointment.day * 1440 + appointment.month * 46100 + appointment.year * 600000;
	if (pHead2) {
		std::cout << "Dostepni lekarze: " << std::endl;
		//szukanie wolnego lekarza o wybranej specjalizacji na dany dzien i godzine
		while (docList) {
			//jesli znaleziono lekarza o danej specjalizacji
			if (docList->doc.specialization == specialization) {
				//jesli jego godziny pracy zgadzaja sie z umawiana wizyta
				if (appointment.hour < 15 && appointment.hour >= 11) {
					takenPointer = pHead2;
					while (takenPointer) {
						//jesli znaleziony lekarz ma juz wtedy inna wizyte to nalezy wysukac kolejnego
						if (takenPointer->appointment.weight == appointment.weight && takenPointer->appointment.id == docList->doc.id) {
							taken = 1;
							break; 
						}
						takenPointer = takenPointer->pNext;
					}
					//jesli znaleziony lekarz ma juz wtedy inna wizyte to nalezy wysukac kolejnego i nie wypisac jeo danych
					if (taken == 1) {
						taken = 0;
					}
					//lekarz u ktorego jest wolny termin i mozna sie u niego umowic
					else {
						std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
						appointment.id = 1;
					}
				}
				else if (appointment.hour < 11 && docList->doc.shift == 1) {
					takenPointer = pHead2;
					while (takenPointer) {
						if (takenPointer->appointment.weight == appointment.weight && takenPointer->appointment.id == docList->doc.id) {
							taken = 1;
							break; 
						}
						takenPointer = takenPointer->pNext;
					}
					if (taken == 1) {
						taken = 0;
					}
					else {
						std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
						appointment.id = 1;
					}
				}
				else if (appointment.hour >= 15 && docList->doc.shift == 2) {
					takenPointer = pHead2;
					while (takenPointer) {
						if (takenPointer->appointment.weight == appointment.weight && takenPointer->appointment.id == docList->doc.id) {
							taken = 1;
							break; 
						}
						takenPointer = takenPointer->pNext;
					}
					if (taken == 1) {
						taken = 0;
					}
					else {
						std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
						appointment.id = 1;
					}
				}
			}
			docList = docList->pNext;
		}
		//jesli nie udalo sie umowic nalezy wyswietlic wizyty z danego dnia u lekarzy wybranej specjalizacji i sprobowac umowic pacjenta w wolne godziny
		if (appointment.id == 0) {
			struct tm tm;
			time_t czas = time(0);
			localtime_s(&tm, &czas);
			int weight = 0;
			int compare = 0;
			docList = pHead; //lista lekrzy
			appList = pHead2; //lista wizyt
			std::cout << "Sprobuj umowic pacjenta gdzies pomiedzy zajete godziny. " << std::endl;
			compare = appointment.weight - appointment.hour * 60 - appointment.minute;
			while (appList) {
				if (appList->appointment.weight - appList->appointment.hour * 60 - appList->appointment.minute == compare) {
					docList = pHead;
					while (docList) {
						if (docList->doc.id == appList->appointment.id && docList->doc.specialization == specialization) {
							std::cout << appList->appointment.hour << ":" << appList->appointment.minute << " " << docList->doc.name << " " << docList->doc.surname << " Zmiana: " << docList->doc.shift << std::endl;
							break;
						}
						docList = docList->pNext;
					}
				}
				appList = appList->pNext;
			}
			//	}
			std::cout << "Niestety nie ma zadnych dostepnych lekarzy na ta godzine." << std::endl;
			delete this;
			return false;
		}
		docList = pHead;
		takenPointer = pHead2;
		taken = 0;
		AppointmentList* insert = pHead2;
		AppointmentList* previous = pHead2;
		//po wyswietleniu dostepnych lekarzy nalezyz dac mozliwosc wyboru do ktorego pacjent chce sie umowic
		while (docList) {
			if (docList->doc.specialization == specialization) {
				//jesli znaleziono lekarza o danej specjalizacji i jego zakres godzin pracy miesci sie w godzinie wizyty
				if (appointment.hour < 15 && appointment.hour >= 11) {
					takenPointer = pHead2;
					//sprawdzanie czy nie ma innej wizyty na tamta godzine
					while (takenPointer) {
						if (takenPointer->appointment.weight == appointment.weight && takenPointer->appointment.id == docList->doc.id) {
							taken = 1;
							break; 
						}
						takenPointer = takenPointer->pNext;
					}
					//jesli lekarz mial juz wizyte to nalezy wyszukac kolejnego lekarza o takiej samej specjalizacji
					if (taken == 1) {
						taken = 0;
					}
					else {
						std::cout << "Czy pacjent chce sie umowic do ";
						std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
						std::cin >> decision;
						if (decision == 1) {
							//wstawianie wizyty na poczatek listy
							if (appointment.weight <= pHead2->appointment.weight) {
								appointment.id = docList->doc.id;
								this->pNext = pHead2;
								pHead2 = this;
								return true;
							}
							//wstawianie wizyty gdzies w liste
							else {
								while (insert && insert->appointment.weight < appointment.weight) {
									previous = insert;
									insert = insert->pNext;
								}
								appointment.id = docList->doc.id;
								previous->pNext = this;
								this->pNext = insert;
								return true;
							}
						}
						else {
							appointment.id = 0;

						}
					}
				}
				else if (appointment.hour < 11 && docList->doc.shift == 1) {
					takenPointer = pHead2;
					while (takenPointer) {
						if (takenPointer->appointment.weight == appointment.weight && takenPointer->appointment.id == docList->doc.id) {
							taken = 1;
							break; 
						}
						takenPointer = takenPointer->pNext;
					}
					if (taken == 1) {
						taken = 0;
					}
					else {
						std::cout << "Czy pacjent chce sie umowic do ";
						std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
						std::cin >> decision;
						if (decision == 1) {
							if (appointment.weight <= pHead2->appointment.weight) {
								appointment.id = docList->doc.id;
								this->pNext = pHead2;
								pHead2 = this;
								return true;
							}
							else {
								while (insert && insert->appointment.weight < appointment.weight) {
									previous = insert;
									insert = insert->pNext;
								}
								appointment.id = docList->doc.id;
								previous->pNext = this;
								this->pNext = insert;
								return true;
							}
						}
						else {
							appointment.id = 0;

						}
					}
				}
				else if (appointment.hour >= 15 && docList->doc.shift == 2) {
					takenPointer = pHead2;
					while (takenPointer) {
						if (takenPointer->appointment.weight == appointment.weight && takenPointer->appointment.id == docList->doc.id) {
							taken = 1;
							break; 
						}
						takenPointer = takenPointer->pNext;
					}
					if (taken == 1) {
						taken = 0;
					}
					else {
						std::cout << "Czy pacjent chce sie umowic do ";
						std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
						std::cin >> decision;
						if (decision == 1) {
							if (appointment.weight <= pHead2->appointment.weight) {
								appointment.id = docList->doc.id;
								this->pNext = pHead2;
								pHead2 = this;
								return true;
							}
							else {
								while (insert && insert->appointment.weight < appointment.weight) {
									previous = insert;
									insert = insert->pNext;
								}
								appointment.id = docList->doc.id;
								previous->pNext = this;
								this->pNext = insert;
								return true;
							}
						}
						else {
							appointment.id = 0;

						}
					}
				}
			}
			docList = docList->pNext;
		}
		//jesli pacejent nie zostal nigdzie umowowiony
		if (appointment.id == 0) {
			std::cout << "Nie umowiono" << std::endl;
			delete this;
			return false;
		}
		
	}
	//to samo co pierwszy warunek tyle ze dla pustej listy 
	else {
		std::cout << "Dostepni lekarze: " << std::endl;
		while (docList) {
			if (docList->doc.specialization == specialization) {
				if (appointment.hour < 15 && appointment.hour >= 11) {
					std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
					appointment.id = 1;
				}
				else if (appointment.hour < 11 && docList->doc.shift == 1) {
					std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
					appointment.id = 1;
				}
				else if (appointment.hour >= 15 && docList->doc.shift == 2) {
					std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
					appointment.id = 1;
				}
			}
			docList = docList->pNext;
		}
		if (appointment.id == 0) {
			std::cout << "Niestety nie ma zadnych dostepnych lekarzy na ta godzine." << std::endl;
			pHead2 = nullptr;
			delete this;
			return false;
		}
		docList = pHead;
		while (docList) {
			if (docList->doc.specialization == specialization) {
				if (appointment.hour < 15 && appointment.hour >= 11) {
					std::cout << "Czy pacjent chce sie umowic do ";
					std::cout << docList->doc.name << " " << docList->doc.surname << "? 1/0" << std::endl;
					std::cin >> decision;
					if (decision == 1) {
						appointment.id = docList->doc.id;
						this->pNext = nullptr;
						pHead2 = this;
						return true;
					}
					else {
						appointment.id = 0;
					}
				}
				else if (appointment.hour < 11 && docList->doc.shift == 1) {
					std::cout << "Czy pacjent chce sie umowic do ";
					std::cout << docList->doc.name << " " << docList->doc.surname << "? 1/0" << std::endl;
					std::cin >> decision;
					if (decision == 1) {
						appointment.id = docList->doc.id;
						this->pNext = nullptr;
						pHead2 = this;
						return true;
					}
					else {
						appointment.id = 0;
					}
				}
				else if (appointment.hour >= 15 && docList->doc.shift == 2) {
					std::cout << "Czy pacjent chce sie umowic do ";
					std::cout << docList->doc.name << " " << docList->doc.surname << "? 1/0" << std::endl;
					std::cin >> decision;
					if (decision == 1) {
						appointment.id = docList->doc.id;
						this->pNext = nullptr;
						pHead2 = this;
						return true;
					}
					else {
						appointment.id = 0;
					}
				}
			}
			docList = docList->pNext;
		}
		if (appointment.id == 0) {
			std::cout << "Nie umowiono" << std::endl;
			pHead2 = nullptr;
			delete this;
			return false;
		}

	}
	return false;
}



void AppointmentList::getAppointment(DoctorList* pHead, int akcja) {
	AppointmentList* appList = this;
	DoctorList* docList = pHead;
	int wasFound = 0;
	while (appList) {
		std::cout << appList->appointment.hour << ":" << appList->appointment.minute << " " << appList->appointment.day << "." << appList->appointment.month << "." << appList->appointment.year << " u ";
		docList = pHead;
		wasFound = 0;
		while (docList) {
			if (appList->appointment.id == docList->doc.id) {
				std::cout << docList->doc.name << " " << docList->doc.surname << std::endl;
				wasFound = 1;
				if (akcja == 1) {
					return;
				}
				break;
			}
			docList = docList->pNext;
		}
		//jesli by sie zdarzylo ze zostal usuniety doktor, a wizyty ktore byly do niego umowione nadal istnieja w bazie
		if (wasFound == 0) {
			std::cout << "Blad! Doktor o takim id nie istnieje. Nalezy edytowac lub usunac wizyte." << std::endl;
			if (akcja == 1) {
				return;
			}
		}
		appList = appList->pNext;
	}
}

void AppointmentList::saveAppointments(AppointmentList*& pHead2) {
	if (pHead2) {
		AppointmentList* appList = nullptr;
		std::ofstream saveToFile("wizyty.txt");
		//zapisywanie wizyt i zwalnianiue pamieci
		while (pHead2) {
			saveToFile << pHead2->appointment.year << " " << pHead2->appointment.month << " " << pHead2->appointment.day << " " << pHead2->appointment.hour << " " << pHead2->appointment.minute << " " << pHead2->appointment.weight << " " << pHead2->appointment.id << std::endl;
			appList = pHead2->pNext;
			pHead2->pNext = nullptr;
			delete pHead2;
			pHead2 = appList;
		}
		saveToFile.close();
	}
}

bool AppointmentList::getAppointment(AppointmentList*& pHead2) {
	std::ifstream readFromFile("wizyty.txt");
	if (readFromFile) {
		std::string data;
		AppointmentList* appList = nullptr;
		AppointmentList* tmpAppList = nullptr;
		int i = 0;
		while (readFromFile >> data) {
			if (i == 0) {
				appList = new AppointmentList;
				//1 element listy wczytany z pliku
				if (pHead2 == nullptr) {
					pHead2 = appList;
					appList->pNext = nullptr;
				}
				else {
					tmpAppList = pHead2;
					while (tmpAppList->pNext) {
						tmpAppList = tmpAppList->pNext;
					}
					tmpAppList->pNext = appList;
					appList->pNext = nullptr;
				}
				appList->appointment.year = stoi(data);
				i++;
			}
			else if (i == 1) {
				appList->appointment.month = stoi(data);
				i++;
			}
			else if (i == 2) {
				appList->appointment.day = stoi(data);
				i++;
			}
			else if (i == 3) {
				appList->appointment.hour = stoi(data);
				i++;
			}
			else if (i == 4) {
				appList->appointment.minute = stoi(data);
				i++;
			}
			else if (i == 5) {
				appList->appointment.weight = stoi(data);
				i++;
			}
			else if (i == 6) {
				appList->appointment.id = stoi(data);
				i = 0;;
			}
		}
		readFromFile.close();
		return true;
	}
	else {
		return false;
	}
}

void AppointmentList::removeAppointment(DoctorList* pHead, AppointmentList*& pHead2) {
	AppointmentList* appList = pHead2;
	AppointmentList* previous = nullptr;
	int date[5];
	int weight = 0;
	int action = 0;
	std::cout << "Podaj date i godzine wizyty, ktora ma zostac usunieta" << std::endl;
	std::cout << "Podaj rok: ";
	std::cin >> date[0];
	std::cout << "Podaj miesiac: ";
	std::cin >> date[1];
	std::cout << "Podaj dzien: ";
	std::cin >> date[2];
	std::cout << "Podaj godzine: ";
	std::cin >> date[3];
	std::cout << "Podaj minute: ";
	std::cin >> date[4];
	weight = date[4] + date[3] * 60 + date[2] * 1440 + date[1] * 46100 + date[0] * 600000;
	while (appList) {
		if (appList->appointment.weight == weight) {
			appList->getAppointment(pHead, 1);
			std::cout << "Czy chcesz usunac ta wizyte czy wyszukac kolejna  1/0: ";
			std::cin >> action;
			if (action == 1) {
				if (appList == pHead2) {
					pHead2 = appList->pNext;
					appList->pNext = nullptr;
					delete appList;
					std::cout << "Wizyta zostala usunieta." << std::endl;
					return;
				}
				else {
					previous->pNext = appList->pNext;
					appList->pNext = nullptr;
					delete appList;
					std::cout << "Wizyta zostala usunieta." << std::endl;
					return;
				}
			}
		}
		previous = appList;
		appList = appList->pNext;
	}
}


void AppointmentList::editAppointment(AppointmentList*& pHead2, DoctorList* pHead) {
	AppointmentList* appList = pHead2;
	AppointmentList* previous = nullptr;
	int date[5];
	int weight = 0;
	int action = 0;
	std::cout << "Podaj date i godzine wizyty, ktora chcesz edytowac" << std::endl;
	std::cout << "Podaj rok: ";
	std::cin >> date[0];
	std::cout << "Podaj miesiac: ";
	std::cin >> date[1];
	std::cout << "Podaj dzien: ";
	std::cin >> date[2];
	std::cout << "Podaj godzine: ";
	std::cin >> date[3];
	std::cout << "Podaj minute: ";
	std::cin >> date[4];
	weight = date[4] + date[3] * 60 + date[2] * 1440 + date[1] * 46100 + date[0] * 600000;
	while (appList) {
		if (appList->appointment.weight == weight) {
			appList->getAppointment(pHead, 1);
			std::cout << "Czy chcesz edytowac ta wizyte czy wyszukac kolejna  1/0: ";
			std::cin >> action;
			if (action == 1) {
				if (appList == pHead2) {
					pHead2 = appList->pNext;
					AppointmentList* wizyta = new AppointmentList;
					if (wizyta->addAppointment(pHead2, pHead)) {
						std::cout << "Wizyta zostala zmieniona." << std::endl;
						appList->pNext = nullptr;
						delete appList;
						return;
					}
					else {
						std::cout << "Wizyta nie zostala zmieniona." << std::endl;
						pHead2 = appList;
						return;
					}
					
				}
				else {
					previous->pNext = appList->pNext;
					AppointmentList* wizyta = new AppointmentList;
					if (wizyta->addAppointment(pHead2, pHead)) {
						std::cout << "Wizyta zostala zmieniona." << std::endl;
						appList->pNext = nullptr;
						delete appList;
						return;
					}
					else {
						std::cout << "Wizyta nie zostala zmieniona." << std::endl;
						previous->pNext = appList;
						return;
					}
				}
			}
		}
		previous = appList;
		appList = appList->pNext;
	}
}


void AppointmentList::clearPastAppointments(AppointmentList*& pHead2) {
	struct tm tm;
	time_t timeNow = time(0);
	localtime_s(&tm, &timeNow);
	int waga = tm.tm_min + tm.tm_hour * 60 + tm.tm_mday * 1440 + (tm.tm_mon + 1) * 46100 + (tm.tm_year + 1900) * 600000;
	AppointmentList* tmp = pHead2;
	if (pHead2) {
		while (pHead2->appointment.weight < waga) {
			tmp = pHead2->pNext;
			delete pHead2;
			pHead2 = tmp;
		}
		std::cout << "Usunieto stare wizyty. " << std::endl;
	}
}



AppointmentList::AppointmentList() {
	pNext = nullptr;
}

void AppointmentList::deleteAllDoctorsAndAppointmentsWithoutSaving(DoctorList*& pHead, AppointmentList*& pHead2) {
	DoctorList* docList = nullptr;
	AppointmentList* appList = nullptr;
	while (pHead) {
		docList = pHead->pNext;
		delete pHead;
		pHead = docList;
	}
	while (pHead2) {
		appList = pHead2->pNext;
		delete pHead2;
		pHead2 = appList;
	}
}


void AppointmentList::operator++() {
	int i = 0;
	AppointmentList* appList = this;
	while (appList) {
		i++;
		appList = appList->pNext;
	}
	std::cout << "Aktualnie jest w bazie " << i << " wizyt." << std::endl;

}

void AppointmentList::operator--() {
	AppointmentList* appList = this;
	AppointmentList* previous = this;
	if (appList) {
		while (appList->pNext) {
			previous = appList;
			appList = appList->pNext;
		}
		if (previous == appList) {
			std::cout << "nie usunieto " << appList->appointment.weight << std::endl;
		}
		else {
			std::cout << "usunieto " << appList->appointment.weight << std::endl;
			delete appList;
			previous->pNext = nullptr;
		}
	}
}