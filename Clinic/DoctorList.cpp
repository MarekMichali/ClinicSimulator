#include "DoctorList.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

void DoctorList::addDoctor(DoctorList*& pHead) {
	std::cin >> doc;
	struct tm tm;
	time_t czas = time(0);
	localtime_s(&tm, &czas);
	//unikalne id, szansa na powtorzenie sie pojawia sie dopiero po roku od wprowadzenia pierwszego wpisu
	doc.id = tm.tm_sec + tm.tm_min * 60 + tm.tm_hour * 3600 + tm.tm_mday * 86400 + tm.tm_mon * 2766000;
	DoctorList* tmp = pHead;
	if (pHead) {
		while (tmp) {
			//jest zdarzy sie ze juz jest ktos o takim samym id w bazie, to obecne jest inkrementowane az do stania sie unikalnym
			if (tmp->doc.id == doc.id) {
				tmp = pHead;
				doc.id++;
			}
			else {
				tmp = tmp->pNext;
			}
		}
		tmp = pHead;
		//dodanie lekarza na koniec listy
		while (tmp->pNext) {
			tmp = tmp->pNext;
		}
		tmp->pNext = this;
	}
	else {
		pHead = this;
		this->pNext = nullptr;
	}
}



void DoctorList::getDoctor(int akcja) {
	DoctorList* tmp = this;
	while (tmp) {
		std::cout << tmp->doc.name << ' ' << tmp->doc.surname << ", Specjalizacja: ";
		switch (tmp->doc.specialization) {
		case 1:
			std::cout << "Lekarz podstawowej opieki zdrowotnej, ";
			break;
		case 2:
			std::cout << "Pediatra, ";
			break;
		case 3:
			std::cout << "Lekarz rodzinny, ";
			break;
		case 4:
			std::cout << "Internista, ";
			break;
		}
		std::cout << "Zmiana: " << tmp->doc.shift;
		if (tmp->doc.shift == 1) {
			std::cout << " (8:00 - 15:00)" << std::endl;
		}
		else {
			std::cout << " (11:00 - 18:00)" << std::endl;
		}
		if (akcja == 1) {
			return;
		}
		tmp = tmp->pNext;
	}
}


void DoctorList::removeDoctor(DoctorList*& pHead) {
	DoctorList* tmp = pHead;
	//ListaLekarzy* prev = nullptr;
	int akcja = 0;
	std::string szukane;
	std::cout << "Wprowadz nazwisko lekarza, ktorego chcesz usunac: ";
	std::cin >> szukane;
	while (tmp) {
		if (tmp->doc.surname == szukane) {
			std::cout << std::endl;
			//wypisanie danych lekarza
			tmp->getDoctor(1);
			std::cout << "Czy chcesz usunac tego lekarza czy szukac kolejnej osoby o tym nazwisku? 1/0: ";
			std::cin >> akcja;
			if (akcja == 1) {
				////jesli lekarz jest na poczatku listy
				//if (tmp == pHead) {
				//	pHead = tmp->pNext;
				//	tmp->pNext = nullptr;
				//	delete tmp;
				//	std::cout << "Lekarz zostal usuniety." << std::endl;
				//	return;
				//}
				////jesli lekarz nie jest na poczatku listy
				//else {
				//	prev->pNext = tmp->pNext;
				//	tmp->pNext = nullptr;
				//	delete tmp;
				//	std::cout << "Lekarz zostal usuniety." << std::endl;
				//	return;
				//}
				*tmp -=pHead;	//nowe
				return;	//nowe
			}
			else {
				akcja = 2;
			}
		}
		//prev = tmp;	
		tmp = tmp->pNext;
	}
	if (akcja == 2) {
		std::cout << "Nie znaleziono wiecej lekarzy o takim nazwisku." << std::endl;
	}
	else {
		std::cout << "Nie znaleziono lekarza o takim nazwisku." << std::endl;
	}

}

DoctorList*& DoctorList::operator-=(DoctorList*& pHead) {
	DoctorList* tmp = pHead;
	DoctorList* prev = nullptr;
	if (this == pHead) {
		pHead = this->pNext;
		this->pNext = nullptr;
		delete this;
		std::cout << "Lekarz zostal usuniety." << std::endl;
		
	}
	//jesli lekarz nie jest na poczatku listy
	else {
		while (tmp != this) {
			prev = tmp;
			tmp = tmp->pNext;
		}
		prev->pNext = this->pNext;
		this->pNext = nullptr;
		delete this;
		std::cout << "Lekarz zostal usuniety." << std::endl;
		
		
	}
	return pHead;
}




void DoctorList::saveDoctors(DoctorList*& pHead) {
	if (pHead) {
		DoctorList* tmp = nullptr;
		std::ofstream zapisz("lekarze.txt");
		//zapisywanie lekarzy i zwalnianie pamieci
		while (pHead) {
			//zapisz << pHead->doc.imie << " " << pHead->doc.nazwisko << " " << pHead->doc.specjalizacja << " " << pHead->doc.zmiana << " " << pHead->doc.id << std::endl;
			zapisz << pHead;
			tmp = pHead->pNext;
			pHead->pNext = nullptr;
			delete pHead;
			pHead = tmp;
		}
		zapisz.close();
	}
}

std::ostream& operator<<(std::ostream& out, DoctorList* pHead) {
	std::cout << "Zaisuje";
	out << pHead->doc.name << " " << pHead->doc.surname << " " << pHead->doc.getSpecialization() << " " << pHead->doc.getShift() << " " << pHead->doc.getId() << std::endl;
	return out;
}


bool DoctorList::readDoctors(DoctorList*& pHead) {
	std::ifstream plik("lekarze.txt");
	if (plik) {
		std::string dane;
		DoctorList* tmp = nullptr;
		DoctorList* tmp2 = nullptr;
		int i = 0;
		while (plik >> dane) {
			
			if (i == 0) {
				
				tmp = new DoctorList;
				//1 element wczytany
				if (pHead == nullptr) {
					pHead = tmp;
					tmp->pNext = nullptr;
				}
				else {
					tmp2 = pHead;
					while (tmp2->pNext) {
						tmp2 = tmp2->pNext;
						//tmp2->pNext = nullptr;
					}
					tmp2->pNext = tmp;
				}
				tmp->doc.name = dane;
				i++;
			}
			else if (i == 1) {
				tmp->doc.surname = dane;
				i++;
			}
			else if (i == 2) {
				tmp->doc.specialization = stoi(dane);
				i++;
			}
			else if (i == 3) {
				tmp->doc.shift = stoi(dane);
				i++;
			}
			else if (i == 4) {
				tmp->doc.id = stoi(dane);
				i = 0;
			}
		}
		plik.close();
		return true;
	}
	else {
		return false;
	}
}


DoctorList::DoctorList() {
	pNext = nullptr;
}


DoctorList*& DoctorList::operator+=(DoctorList*& pHead) {
	std::cin >> this->doc;
	struct tm tm;
	time_t czas = time(0);
	localtime_s(&tm, &czas);
	//unikalne id, szansa na powtorzenie sie pojawia sie dopiero po roku od wprowadzenia pierwszego wpisu
	doc.id = tm.tm_sec + tm.tm_min * 60 + tm.tm_hour * 3600 + tm.tm_mday * 86400 + tm.tm_mon * 2766000;
	DoctorList* tmp = pHead;
	if (pHead) {
		while (tmp) {
			//jest zdarzy sie ze juz jest ktos o takim samym id w bazie, to obecne jest inkrementowane az do stania sie unikalnym
			if (tmp->doc.id == doc.id) {
				tmp = pHead;
				doc.id++;
			}
			else {
				tmp = tmp->pNext;
			}
		}
		tmp = pHead;
		//dodanie lekarza na koniec listy
		while (tmp->pNext) {
			tmp = tmp->pNext;
		}
		tmp->pNext = this;
	}
	else {
		pHead = this;
		this->pNext = nullptr;
	}
	return pHead;
}


void DoctorList::operator++() {
	int i = 0;
	DoctorList* tmp =this;
	while (tmp) {
		i++;
		tmp = tmp->pNext;
	}
	std::cout << "Aktualnie w przychodni pracuje " << i << " lekarzy." << std::endl;

}


void DoctorList::operator--() {
	DoctorList* tmp = this;
	DoctorList* prev = this;
	if (tmp) {
		while (tmp->pNext) {
			prev = tmp;
			tmp = tmp->pNext;
		}
		if (prev == tmp) {
			std::cout << "nie usunieto " << tmp->doc.surname << std::endl;
		}
		else {
			std::cout << "usunieto " << tmp->doc.surname << std::endl;
			delete tmp;
			prev->pNext = nullptr;
		}
	}
}

