#ifndef FILM_H
#define FILM_H
#include <QString>
#include <QStringList>
#include <QDate>
#include <QList>

enum FilmTypes {Action, Comedy, SciFi, Horror};
enum MPAARatings{G,PG, PG13, R};
enum Grade {Elementary, Middle, High, College};
enum Length {Short, Medium, Long};

class Film {
	public:
		virtual ~Film();
		Film(QString id, QString title, QString dir, quint32 length, QDate relDate);
		Film(QStringList& propList);
		virtual QString toString(bool labeled, QString sepchar);
		QString getID();
		QString getTitle();
	private:
		QString m_FilmID;
		QString m_Title;
		QString m_Director;
		Length m_FilmLength;
		QDate m_releaseDate;

};

class Educational : public Film {
	public:
		Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subject, Grade grade);
		Educational(QStringList& propList);
		QString toString(bool labeled, QString sepchar);
	private:
		QString m_Subject;
		Grade m_GradeLevel;

};

class Entertainment : public Film {
	private:
		FilmTypes m_Type;
		MPAARatings m_Rating;
	public:
		Entertainment(QString id, QString title, QString dir, quint32 len, QDate relDate, FilmTypes type, MPAARatings rtng);
		Entertainment(QStringList& propList);
		QString toString(bool labeled, QString sepchar);
};

class FilmList : public QList<Film*>
{
	public:
		FilmList() {}
		~FilmList();
		QString toString();
		Film* findFilm(QString id);
		Film* findFilmByTitle(QString title);
		QStringList getID(QString title);
		void addFilm(Film* film);
		void removeFilm(QString filmID);
	private:
		FilmList(const FilmList&);
		FilmList& operator=(const FilmList&);


};

#endif