#ifndef FILM_H
#define FILM_H
#include <QString>
#include <QDate>
class Film {
	private:
		QString m_FilmID;
		QString m_Title;
		QString m_Director;
		Length m_FilmLength;
		QDate m_releaseDate;
	public:
		Film(QString id, QString title, QString dir, quint32 length, QDate relDate);
		Film(QStringList propList);
		virtual QString toString(bool labeled, QString sepchar);

};

class Educational : public Film {
	private:
		QString m_Subject;
		Grade m_GradeLevel;
	public:
		Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subject, Grade grade);
		Educational(QStringList propList);
		QString toString(bool labeled, QString sepchar);

};

class Entertainment : public Film{
	private:
		FilmTypes m_Type;
		MPAARatings m_Rating;
	public:
		Entertainment(QString id, QString title, QString dir, quint32 len, QDate relDate, Filmtypes type, MPAARatings rtng);
		Entertainment(QStringList propList);
		QString toString(bool labeled, QString sepchar)
};

class FilmList : public QList<Film*>
{
	public:
		QString toString();
		Film* findFilm(QString id);
		QStringList getID(QString title);
		void addFilm(Film* film);
		void removeFilm(QString filmID);
};

#endif