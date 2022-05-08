#include "Doctor.h"
#include <iostream>
#include <string>

std::istream& operator>>(std::istream& in, Doctor& doc) {
	std::cout << "Podaj imie lekarza: ";
	in >> doc.name;
	std::cout << "Podaj nazwisko lekarza: ";
	in >> doc.surname;
	std::cout << "Wybierz specjalizacje lekarza z menu wprowadzajac odpowiedni numer: \n1. Podstawowej opieki zdrowotnej \n2. Pediatra \n3. Rodzinny \n4. Internista" << std::endl;
	in >> doc.specialization;
	if (doc.specialization < 1 || doc.specialization>4) {
		std::cout << "Taka specjalizacja nie istnieje, ustawiono lekarza POZ. " << std::endl;
		doc.specialization = 1;
	}
	std::cout << "Wybierz zmiane lekarza na ktorej ma pracowac: \n1. 8:00 - 15:00 \n2. 11:00-18:00 ";
	in >> doc.shift;
	if (doc.shift < 1 || doc.shift > 2) {
		std::cout << "Taka specjalizacja nie istnieje, ustawiono pierwsza zmiane. " << std::endl;
	}

	return in;
}



Doctor::Doctor() {
	specialization = 0;
	shift = 0;
}

int Doctor::getSpecialization() {
	return specialization;
}

int Doctor::getShift() {
	return shift;
}