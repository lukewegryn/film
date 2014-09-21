#include "film.h"
#include <QTextStream>
#include <QStream.h>
#include <QStringList>
#include <QList>
#include <iostream>

Film::~Film()
{}

QString Film::toString(bool labeled, QString sep){
	QString lengthString = " ";
	switch(m_FilmLength)
	{
		case Short: 
			lengthString = "Short";
			break;
		case Medium: 
			lengthString = "Medium";
			break;
		case Long: 
			lengthString = "Long";
			break;
	}
	if(!labeled)
		return m_FilmID + sep + m_Title + sep + m_Director + sep + lengthString + sep + m_releaseDate.toString("yy/MM/dd");
	else
		return "ID: " + m_FilmID + sep + "Title: " + m_Title + sep + "Director: " + m_Director + sep + "Length: " + lengthString + sep + "Release Date: " + m_releaseDate.toString("yy/MM/dd");
}

Film::Film(QStringList& plst)
{
		QStringList tempDateStringList;

	    m_FilmID = plst.takeFirst();
		m_Title = plst.takeFirst();
		m_Director = plst.takeFirst();

		quint32 length = plst.takeFirst().toInt();
		if(length < 60)
			m_FilmLength = static_cast<Length>(Short);
		else if(length >= 60 && length <= 120)
			m_FilmLength = static_cast<Length>(Medium);
		else 
			m_FilmLength = static_cast<Length>(Long);

		tempDateStringList = plst.takeFirst().split('/');
		m_releaseDate = QDate(tempDateStringList[0].toInt(), tempDateStringList[1].toInt(), tempDateStringList[2].toInt());

}

Film::Film(QString id, QString title, QString dir, quint32 length, QDate relDate)
{
	    m_FilmID = id;
		m_Title = title;
		m_Director = dir;

		if(length < 60)
			m_FilmLength = static_cast<Length>(Short);
		else if(length >= 60 && length <= 120)
			m_FilmLength = static_cast<Length>(Medium);
		else 
			m_FilmLength = static_cast<Length>(Long);

		m_releaseDate = relDate;
}

QString Film::getID()
{
	return m_FilmID;
}

QString Educational::toString(bool labeled, QString sep){

	QString GradeLevelString = "";
	switch(m_GradeLevel)
	{
		case Elementary: GradeLevelString = "Elementary"; break;
		case Middle: GradeLevelString = "Middle"; break;
		case High: GradeLevelString = "High"; break;
		case College: GradeLevelString = "College"; break;
		default: GradeLevelString = "None"; break;

	}
	if(labeled)
		return Film::toString(1, sep) + sep + "Subject: " + m_Subject + sep + "Grade: " + GradeLevelString;
	else
		return Film::toString(0, sep) + sep + m_Subject + sep + GradeLevelString;
}

Educational::Educational(QStringList& plst) : Film(plst)
{ 

	 m_Subject = plst.takeFirst();
	QString tempString = plst.takeFirst();
	if(tempString == "Elementary")
		m_GradeLevel = static_cast<Grade>(Elementary);
	else if(tempString == "Middle")
		m_GradeLevel = static_cast<Grade>(Middle);
	else if(tempString == "High")
		m_GradeLevel = static_cast<Grade>(High);
	else
		m_GradeLevel = static_cast<Grade>(College);


}

Educational::Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subject, Grade grade) : Film(id, title, dir, len, relDate)
{
	m_Subject = subject;
	m_GradeLevel = grade;
}

QString Entertainment::toString(bool labeled, QString sep){
	QString ratingString = "";
	QString typeString = "";
	switch(m_Rating)
	{
		case G: ratingString = "G"; break;
		case PG: ratingString = "PG"; break;
		case PG13: ratingString = "PG13"; break;
		case R: ratingString = "R"; break;
		default: ratingString = "None"; break;

	}

	switch(m_Type)
	{
		case Action: typeString = "Action"; break;
		case Comedy: typeString = "Comedy"; break;
		case SciFi: typeString = "SciFi"; break;
		case Horror: typeString = "Horror"; break;
		default: typeString = "None"; break;

	}

	if(labeled)
		return Film::toString(1, sep) + sep + "Rating: " + ratingString + sep + "Type: " + typeString;
	else
		return Film::toString(0, sep) + sep + ratingString + sep + typeString;
}

Entertainment::Entertainment(QStringList& plst) : Film(plst)
{ 
	QString typeString = plst.takeFirst();
	QString ratingString = plst.takeFirst();
	if(typeString == "Action")
		m_Type = static_cast<FilmTypes>(Action);
	else if(typeString == "Comedy")
		m_Type = static_cast<FilmTypes>(Comedy);
	else if(typeString == "SciFi")
		m_Type = static_cast<FilmTypes>(SciFi);
	else
		m_Type = static_cast<FilmTypes>(Horror);

	if(ratingString == "G")
		m_Rating = static_cast<MPAARatings>(G);
	else if(ratingString == "PG")
		m_Rating = static_cast<MPAARatings>(PG);
	else if(ratingString == "PG13")
		m_Rating = static_cast<MPAARatings>(PG13);
	else
		m_Rating = static_cast<MPAARatings>(R);
}

Entertainment::Entertainment(QString id, QString title, QString dir, quint32 len, QDate relDate, FilmTypes type, MPAARatings rtng) : Film(id, title, dir, len, relDate)
{
 	m_Type = type;
	m_Rating = rtng;
}

FilmList::~FilmList() {
	qDeleteAll(*this);
	clear();
}

FilmList::FilmList(const FilmList&) : QList<Film*>() {}

FilmList& FilmList::operator=(const FilmList&){
	return *this;
}

/*void FilmList::removeFilm(QString filmID)
{
	Film* theFilm;
	if(findFilm(filmID) != 0)
	{
		theFilm = findFilm(filmID);
		delete theFilm;
	}
}*/

Film* FilmList::findFilm(QString filmID)
{
	for(int i = 0; i < size(); i++)
	{
		if(at(i)->getID() == filmID)
			return at(i);
	}
	return 0;
}

void FilmList::addFilm(Film* film)
{
	//qout << film->getID();
	if(findFilm(film->getID()) == 0)
		append(film);
}


int main()
{
	QStringList plst, eplist, eeplist;
	plst << "001" << "Pirates of the Carribean" << "Johnny Depp" << "32" << "2014/02/02";
	eplist << "001" << "Pirates of the Carribean" << "Johnny Depp" << "32" << "2014/02/02" << "Adventure" << "High";
	Film myFilm("movie", "good", "john", 160, QDate(2014, 02, 04));
	//Educational myEducationalFilm("edMovie", "edgood", "edjohn", 32, QDate(2014,02,04), "Antoinette DeFeliz", static_cast<Grade>(Elementary));
	//Film myOtherFilm(plst);
	//Educational myOtherEducationalFilm(eplist);
	eeplist  << "001" << "Pirates of the Carribean" << "Johnny Depp" << "32" << "2014/02/02" << "Comedy" << "PG13";
	Entertainment myEntertainmentFilm("001", "good", "john", 160, QDate(2014, 02, 04), static_cast<FilmTypes>(Action), static_cast<MPAARatings>(R));
	Entertainment myOtherEntertainmentFilm(eeplist);
	//qout << myFilm.toString(1, "\n") << endl;
	//qout << myEducationalFilm.toString(1, "\n") << endl;
	//qout << myOtherFilm.toString(1, "\n") << endl;
	//qout << myOtherEducationalFilm.toString(1,"\n") << endl;
	//qout << myEntertainmentFilm.toString(1, "\n") << endl << endl;
	//qout << myOtherEntertainmentFilm.toString(1, "\n") << endl;
	FilmList myFilmList;
	Film* ref = new Film(plst);
	myFilmList.addFilm(ref);
	//qout << myFilm.toString(0, "\n");
	//qout << myFilm.getID();
	return 0;
}