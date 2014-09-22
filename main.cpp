#include "film.h"
#include "film.cpp"

enum Choices {ADD, FIND, REMOVE, GETID, QUIT};
enum TypeOfFilm{EDUCATIONAL, ENTERTAINMENT};
Choices nextTask() {
   int choice;
   QString response;
   do {
      
        qout << ADD << ". Add items to the Library.\n"
           << FIND << ". Find by ID and display results.\n"
           << REMOVE << ". Remove an item from the Library.\n"
           << GETID << ". Get ID by Title\n"
           << QUIT << ". Exit from this program.\n"
           << "Your choice: " << flush;
     response = qin.readLine();
     choice = response.toInt();
   } while(choice < ADD or choice > QUIT);
   return static_cast<Choices>(choice);
}

QStringList promptEntertainment(){
qout << "Enter the following information" << endl << flush;
QStringList retList;
QStringList questionList;
questionList << "ID" << "Title" << "Director" << "Length (integer)" << "Date (YYYY/MM/DD)" << "FilmType (Action, Comedy, SciFi or Horror)" << "Rating (G, PG, PG13 or R)";
QString inputData;
	for(int i = 0; i < questionList.size(); i++)
	{
		qout << questionList.at(i) << ": " << flush;
		inputData = qin.readLine();
		retList.append(inputData);
	}

	return retList;
}

QStringList promptEducational(){
	qout << "Enter the following information" << endl << flush;
	QStringList retList;
	QStringList questionList;
	questionList << "ID" << "Title" << "Director" << "Length (integer)" << "Date (YYYY/MM/DD)" << "Subject" << "Grade (Elementary, Middle, High or College)";
	QString inputData;
	for(int i = 0; i < questionList.size(); i++)
	{
		qout << questionList.at(i) << ": " << flush;
		inputData = qin.readLine();
		retList.append(inputData);
	}

	return retList;
}

void findPrompt(FilmList& filmList)
{
	qout << "Enter the ID of the Film: " << flush;
	QString id = qin.readLine();
	Film* myFilm = filmList.findFilm(id);
	if(myFilm != NULL)
	{
		qout << myFilm->toString(1, "\n") << flush;
	}
	qout << "\n" << flush;
}

bool addPrompt(FilmList& myFilmList)
{
	int choice;
	do {
		qout << "Follow the instructions to add a Film" << endl << flush;
		qout << "What kind of film is it?" << endl << flush;
		qout << EDUCATIONAL << ". Educational\n" << ENTERTAINMENT << ". Entertainment\n" << flush;
		qout << "Your choice: " << flush;
		choice = qin.readLine().toInt();
	} while(choice < EDUCATIONAL or choice > ENTERTAINMENT);
	TypeOfFilm type = static_cast<TypeOfFilm>(choice);

	switch(type)
	{
		case EDUCATIONAL: 
		{
			QStringList myList = promptEducational();
			Educational* refEnt = new Educational(myList); 
			myFilmList.addFilm(refEnt);
			break;
		}
		case ENTERTAINMENT: 
		{
			QStringList myList = promptEntertainment();
			Entertainment* refEnt = new Entertainment(myList); 
			myFilmList.addFilm(refEnt);
			break;
		}
	}

	return true;
}



int main()
{
	/*QStringList plst, eplist, eeplist;
	plst << "001" << "Pirates of the Carribean" << "Johnny Depp" << "32" << "2014/02/02";
	eplist << "001" << "Pirates of the Carribean" << "Johnny Depp" << "32" << "2014/02/02" << "Adventure" << "High";
	Film myFilm("movie", "good", "john", 160, QDate(2014, 02, 04));
	eeplist  << "001" << "Pirates of the Carribean" << "Johnny Depp" << "32" << "2014/02/02" << "Comedy" << "PG13";

	FilmList myFilmList;
	Film* ref = new Film(plst);
	Entertainment* refEnt = new Entertainment(eeplist);
	myFilmList.addFilm(ref);
	myFilmList.addFilm(refEnt);
	Film* trial = myFilmList.findFilm("001");
	qout << trial->toString(1, "\n");
	//qout << myFilm.toString(0, "\n");
	//qout << myFilm.getID();
	return 0;*/

	bool isFinished = false;
	FilmList myFilmList;

	while (!isFinished)
	{
		switch(nextTask())
		{
			case ADD: addPrompt(myFilmList); break;
			case FIND: findPrompt(myFilmList); break;
			case REMOVE: qout << "Remove Something\n"; break;
			case GETID: qout << "Get ID of something\n"; break;
			case QUIT: isFinished = true;
		}
	}
}