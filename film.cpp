#include "film.h"
#include <QTextStream>
#include <QStream.h>
#include <QStringList>
#include <iostream>

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

	return m_FilmID + sep + m_Title + sep + m_Director + sep + lengthString + sep + m_releaseDate.toString("yy/MM/dd");
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
	return Film::toString(1, sep) + sep + m_Subject + sep + GradeLevelString;
}

Educational::Educational(QStringList& plst) : Film(plst)
{ 

	 m_Subject = plst.takeFirst();
	 //QString tempGrade = plst.takeFirst();
	/*if(tempGrade == "Elementary")
		m_GradeLevel = static_cast<Grade>(A);
	else if(tempGrade == "B")
		m_GradeLevel = static_cast<Grade>(B);
	else if(tempGrade == "C")
	 	m_GradeLevel = static_cast<Grade>(C);
	else if (tempGrade == "D")
	 	m_GradeLevel = static_cast<Grade>(D);
	else
	 	m_GradeLevel = static_cast<Grade>(F);*/
	//m_GradeLevel = static_cast<Grade>(plst.takeFirst());

}

Educational::Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subject, Grade grade) : Film(id, title, dir, len, relDate)
{
	m_Subject = subject;
	m_GradeLevel = grade;
}

QString Entertainment::toString(bool labeled, QString sep){
	return "a";
}

Entertainment::Entertainment(QStringList& plst) : Film(plst)
{ 

	 m_Type = Action;
	 m_Rating = R;
}

Entertainment::Entertainment(QString id, QString title, QString dir, quint32 len, QDate relDate, FilmTypes type, MPAARatings rtng) : Film(id, title, dir, len, relDate)
{
 	m_Type = Action;
	 m_Rating = R;
}


int main()
{
	QStringList plst;
	plst << "001" << "Pirates of the Carribean" << "Johnny Depp" << "32" << "2014/02/02";
	Film myFilm("movie", "good", "john", 160, QDate(2014, 02, 04));
	Educational myEducationalFilm("edMovie", "edgood", "edjohn", 32, QDate(2014,02,04), "Antoinette DeFeliz", static_cast<Grade>(Elementary));
	Film myOtherFilm(plst);
	qout << myFilm.toString(1, ",") << endl;
	qout << myEducationalFilm.toString(1, ",") << endl;
	qout << myOtherFilm.toString(1, ":") << endl;
	return 0;
}