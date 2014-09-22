#include "film.h"
#include "film.cpp"

enum Choices {ADD, FIND, REMOVE, GETID, QUIT};
enum TypeOfFilm{EDUCATIONAL, ENTERTAINMENT, FILM};
Choices nextTask() {
   int choice;
   QString response;
   do {
      
        qout << ADD << ". Add items to the Film List.\n"
           << FIND << ". Find by ID and display results.\n"
           << REMOVE << ". Remove an item from the Film List.\n"
           << GETID << ". Get theID by Title.\n"
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

QStringList promptFilm(){
	qout << "Enter the following information" << endl << flush;
	QStringList retList;
	QStringList questionList;
	questionList << "ID" << "Title" << "Director" << "Length (integer)" << "Date (YYYY/MM/DD)";
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

void findByTitlePrompt(FilmList& filmList)
{
	qout << "Enter the Title of the Film: " << flush;
	QString title = qin.readLine();
	Film* myFilm = filmList.findFilmByTitle(title);
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
		qout << EDUCATIONAL << ". Educational\n" << ENTERTAINMENT << ". Entertainment\n" << FILM << ". Film\n" << flush;
		qout << "Your choice: " << flush;
		choice = qin.readLine().toInt();
	} while(choice < EDUCATIONAL or choice > FILM);
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

		case FILM:
		{
			QStringList myList = promptFilm();
			Film* refEnt = new Film(myList); 
			myFilmList.addFilm(refEnt);
			break;
		}
	}

	return true;
}

void removePrompt(FilmList& myFilmList)
{
	qout << "Enter the ID of the Film: " << flush;
	QString id = qin.readLine();
    myFilmList.removeFilm(id);
}



int main()
{

	bool isFinished = false;
	FilmList myFilmList;

	while (!isFinished)
	{
		switch(nextTask())
		{
			case ADD: addPrompt(myFilmList); break;
			case FIND: findPrompt(myFilmList); break;
			case REMOVE: removePrompt(myFilmList); break;
			case GETID: findByTitlePrompt(myFilmList); break;
			case QUIT: isFinished = true;
		}
	}
}