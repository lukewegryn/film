#include "film.h"
#include <QTextStream>

QString Film::toString(bool labeled, QString sep){
	return m_FilmID + sep + m_Title + sep + m_Director + '\n'; //+ sep + m_FilmLength + sep + m_releaseDate;
		//QString("%1%2%3%4%5%6%7%8%9").arg(m_FilmID).arg(sep).arg(m_Title).arg(sep).arg(m_Director).arg(sep).arg(m_FilmLength).arg(sep).arg(m_releaseDate);
}

Film::Film(QStringList& plst)
{
		QStringList tempDateStringList;
		QString tempLengthString;

	    m_FilmID = plst.takeFirst();
		m_Title = plst.takeFirst();
		m_Director = plst.takeFirst();

		tempLengthString = plst.takeFirst();
		if(tempLengthString == "Short")
			m_FilmLength = Short;
		else if(tempLengthString == "Medium")
			m_FilmLength = Medium;
		else 
			m_FilmLength = Long;

		tempDateStringList = plst.takeFirst().split('/');
		m_releaseDate = QDate(tempDateStringList[0].toInt(), tempDateStringList[1].toInt(), tempDateStringList[2].toInt());

}

Film::Film(QString id, QString title, QString dir, quint32 length, QDate relDate)
{
	    m_FilmID = id;
		m_Title = title;
		m_Director = dir;

		if(length < 60)
			m_FilmLength = Short;
		else if(length >= 60 && length <= 120)
			m_FilmLength = Medium;
		else 
			m_FilmLength = Long;

		m_releaseDate = relDate;
}

Educational::Educational(QStringList& plst) : Film
{
	Film(plst);
	m_Subject = Comedy;
	m_GradeLevel = A;

}

int main()
{
	Film myFilm("movie", "good", "john", 32, QDate(2014, 02, 04));
	QTextStream(stdout)  << myFilm.toString(1, ",");
	return 0;
}