#include "Appointment.h"
#include <iostream>
#include <fstream>
#include <ctime>


std::istream& operator>>(std::istream& in, Appointment& appointment) {
	struct tm tm;
	time_t timeNow = time(0);
	localtime_s(&tm, &timeNow);
	//doc.id = tm.tm_sec + tm.tm_min * 60 + tm.tm_hour * 3600 + tm.tm_mday * 86400 + tm.tm_mon * 2766000 + tm.tm_year;
	std::cout << "Wprowadz rok: ";
	in >> appointment.year;
	//rok nie moze byc przeszly ale tez nie jakis nierealny dlatego limit roku 3000
	while (true) {
		if (appointment.year >= tm.tm_year + 1900 && appointment.year <= 3000) {
			break;
		}
		else if (appointment.year < tm.tm_year + 1900) {
			std::cout << "Wprowadz rok, ktory nie jest przeszly:  ";
			in >> appointment.year;
		}
		else if (appointment.year > 3000) {
			std::cout << "Do tego czasu moze byc troche za pozno na lekarza, wprowadz bardziej realny rok:  ";
			in >> appointment.year;
		}
	}

	std::cout << "Wprowadz miesiac: ";
	in >> appointment.month;
		while (true) {
		//miesiac musi istniec i nie moze byc przeszly w przypadku aktualnego wybrenego roku
		if (appointment.month > 12 || appointment.month < 1 || (appointment.month < tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900)) {
			std::cout << "Wprowadz miesiac, ktory istnieje, nie jest przeszly i w ktorym jest jeszcze mozliwe umowienie wizyty: ";
			in >> appointment.month;
			continue;
		}
		if (appointment.month == 1 || appointment.month == 3 || appointment.month == 5 || appointment.month == 7 || appointment.month == 8 || appointment.month == 10 || appointment.month == 12) {
			//jesli wybrany miesiac jest aktualnym nalezy sprawdzic czy jest jeszcze mozliwosc umowienia sie w nim na wizyte np. czy wybierajac pazdziernik 
			//jest dzien 31 to sprawdza sie czy nie jest pozniej niz 17,45 bo po tej godzinie konczy sie mozliwosc wizyt w pazdzierniku, albo czy pozostale dni to nie jest juz tylko wekend itd.
			//analogicznie dla kazdego miesiaca
			if (appointment.month == tm.tm_mon + 1 && (tm.tm_mday == 31 && tm.tm_hour > 17 || tm.tm_mday == 31 && tm.tm_hour > 16 && tm.tm_min > 45 || tm.tm_mday == 31 && tm.tm_wday == 6 || tm.tm_mday == 31 && tm.tm_wday == 0 ||
				tm.tm_mday == 30 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 30 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5 || tm.tm_mday == 30 && tm.tm_wday == 6 ||
				tm.tm_mday == 29 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 29 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5)) {
				//nie mozna sie umowic
				std::cout << "Wprowadz miesiac, ktory istnieje, nie jest przeszly i w ktorym jest jeszcze mozliwe umowienie wizyty: ";
				in >> appointment.month;
			}
			else {
				break;
			}

		}
		//rok przestepny miesiac luty
		else if (appointment.month == 2 && ((tm.tm_year + 1900) % 4 == 0 && (tm.tm_year + 1900) % 100 != 0 || (tm.tm_year + 1900) % 400 == 0)) {
			if (appointment.month == tm.tm_mon + 1 && (tm.tm_mday == 29 && tm.tm_hour > 17 || tm.tm_mday == 29 && tm.tm_hour > 16 && tm.tm_min > 45 || tm.tm_mday == 29 && tm.tm_wday == 6 || tm.tm_mday == 29 && tm.tm_wday == 0 ||
				tm.tm_mday == 28 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 28 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5 || tm.tm_mday == 28 && tm.tm_wday == 6 ||
				tm.tm_mday == 27 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 27 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5)) {
				//nie mozna sie umowic
				appointment.month = 20;
				std::cout << "Wprowadz miesiac, ktory istnieje, nie jest przeszly i w ktorym jest jeszcze mozliwe umowienie wizyty: ";
				in >> appointment.month;
			}
			else {
				break;
			}

		}
		else if (appointment.month == 2 && ((tm.tm_year + 1900) % 4 != 0 && (tm.tm_year + 1900) % 100 == 0 || (tm.tm_year + 1900) % 400 != 0)) {
			if (appointment.month == tm.tm_mon + 1 && (tm.tm_mday == 28 && tm.tm_hour > 17 || tm.tm_mday == 28 && tm.tm_hour > 16 && tm.tm_min > 45 || tm.tm_mday == 28 && tm.tm_wday == 6 || tm.tm_mday == 28 && tm.tm_wday == 0 ||
				tm.tm_mday == 27 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 27 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5 || tm.tm_mday == 27 && tm.tm_wday == 6 ||
				tm.tm_mday == 26 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 26 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5)) {
				//nie mozna sie umowic
				std::cout << "Wprowadz miesiac, ktory istnieje, nie jest przeszly i w ktorym jest jeszcze mozliwe umowienie wizyty: ";
				in >> appointment.month;
			}
			else {
				break;
			}

		}
		else if (appointment.month == 4 || appointment.month == 6 || appointment.month == 9 || appointment.month == 11) {
			if (appointment.month == tm.tm_mon + 1 && (tm.tm_mday == 30 && tm.tm_hour > 17 || tm.tm_mday == 30 && tm.tm_hour > 16 && tm.tm_min > 45 || tm.tm_mday == 30 && tm.tm_wday == 6 || tm.tm_mday == 30 && tm.tm_wday == 0 ||
				tm.tm_mday == 29 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 29 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5 || tm.tm_mday == 29 && tm.tm_wday == 6 ||
				tm.tm_mday == 28 && tm.tm_hour > 17 && tm.tm_wday == 5 || tm.tm_mday == 28 && tm.tm_hour > 16 && tm.tm_min > 45 && tm.tm_wday == 5)) {
				//nie mozna sie umowic
				std::cout << "Wprowadz miesiac, ktory istnieje, nie jest przeszly i w ktorym jest jeszcze mozliwe umowienie wizyty: ";
				in >> appointment.month;
			}
			else {
				break;
			}

		}

	}

	std::cout << "Wprowadz dzien: ";
	in >> appointment.day;
	int jaki_dzien = 0;
	int z = 0;
	int c = 0;
	if (appointment.month < 3) {
		z = appointment.year - 1;
		c = 0;
	}
	else {
		z = appointment.year;
		c = 2;
	}
	//obliczane jest czy wybrany dzien w danym miesiacu i roku nie jest weekendem, poniewaz wtedy przychodnia jest zamknieta
	jaki_dzien = (23 * appointment.month / 9 + appointment.day + 4 + appointment.year + z / 4 + z / 100 + z / 400 - c) % 7;
	//rok przestepny miesiac luty
	if (appointment.month == 2 && (appointment.year % 4 == 0 && appointment.year % 100 != 0 || appointment.year % 400 == 0)) {
		//sprawdzanie czy dzien istnieje w miesiacu, czy nie jest weekendem, czy jest jeszcze mozliwosc do umowienia sie na wizyte w tym dniu
		while (appointment.day < tm.tm_mday && appointment.month == tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900 || appointment.day < 1 || appointment.day>29 || jaki_dzien == 4 || jaki_dzien == 5 || appointment.day == tm.tm_mday && tm.tm_hour > 17) {
			std::cout << "Wprowadz dzien, ktory istnieje w danym miesiacu, nie jest dniem weekendu i nie jest przeszly:  ";
			in >> appointment.day;
			jaki_dzien = (23 * appointment.month / 9 + appointment.day + 4 + appointment.year + z / 4 + z / 100 + z / 400 - c) % 7;
		}
	}
	else if (appointment.month == 2 && (appointment.year % 4 != 0 && appointment.year % 100 == 0 || appointment.year % 400 != 0)) {
		while (appointment.day < tm.tm_mday && appointment.month == tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900 || appointment.day < 1 || appointment.day>28 || jaki_dzien == 4 || jaki_dzien == 5 || appointment.day == tm.tm_mday && tm.tm_hour > 17) {
			std::cout << "Wprowadz dzien, ktory istnieje w danym miesiacu, nie jest dniem weekendu i nie jest przeszly:  ";
			in >> appointment.day;
			jaki_dzien = (23 * appointment.month / 9 + appointment.day + 4 + appointment.year + z / 4 + z / 100 + z / 400 - c) % 7;
		}
	}
	else if (appointment.month == 1 || appointment.month == 3 || appointment.month == 5 || appointment.month == 7 || appointment.month == 8 || appointment.month == 10 || appointment.month == 12) {
		while (appointment.day < tm.tm_mday && appointment.month == tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900 || appointment.day < 1 || appointment.day>31 || jaki_dzien == 4 || jaki_dzien == 5 || appointment.day == tm.tm_mday && tm.tm_hour > 17) {
			std::cout << "Wprowadz dzien, ktory istnieje w danym miesiacu, nie jest dniem weekendu i nie jest przeszly:  ";
			in >> appointment.day;
			jaki_dzien = (23 * appointment.month / 9 + appointment.day + 4 + appointment.year + z / 4 + z / 100 + z / 400 - c) % 7;
		}
	}
	else {
		while (appointment.day < tm.tm_mday && appointment.month == tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900 || appointment.day < 1 || appointment.day>30 || jaki_dzien == 4 || jaki_dzien == 5 || appointment.day == tm.tm_mday && tm.tm_mday > 17) {
			std::cout << "Wprowadz dzien, ktory istnieje w danym miesiacu, nie jest dniem weekendu i nie jest przeszly:  ";
			in >> appointment.day;
			jaki_dzien = (23 * appointment.month / 9 + appointment.day + 4 + appointment.year + z / 4 + z / 100 + z / 400 - c) % 7;
		}
	}


	std::cout << "Wprowadz godzine: ";
	in >> appointment.hour;
	while (appointment.hour < tm.tm_hour && appointment.day == tm.tm_mday && appointment.month == tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900 || appointment.hour < 8 || appointment.hour>17 || appointment.hour == tm.tm_hour && tm.tm_min > 45 && appointment.day == tm.tm_mday && appointment.month == tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900) {
		std::cout << "Godzina musi byc z przedzialu 8-17, w przypadku jesli wizyta jest umawiana na ta sama godzine to najpozniej moze byc minuta 45 aby byla mozliwosc umowienia sie, wprowadz godzine jeszcze raz: ";
		in >> appointment.hour;
	}




	std::cout << "Wprowadz kwadrans: ";
	in >> appointment.minute;
	while (appointment.minute < tm.tm_min && appointment.hour == tm.tm_hour && appointment.day == tm.tm_mday && appointment.month == tm.tm_mon + 1 && appointment.year == tm.tm_year + 1900 || appointment.minute != 0 && appointment.minute != 15 && appointment.minute != 30 && appointment.minute != 45) {
		std::cout << "Kwadrans (0, 15, 30, 45) nie moze byc przeszly jesli wizyta jest umawiana wlasnie na to godzine, wprowadz go jeszcze raz:  ";
		in >> appointment.minute;
	}
	return in;
}

Appointment::Appointment() {
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	weight = 0;
	id = 0;
}