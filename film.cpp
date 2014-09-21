#include "film.h"

/*QString Film::toString(bool labeled, QString sep){
	return 
		QString("%1%2%3%4%5%6%7%8%9").arg(m_FilmID).arg(sep).arg(m_Title).arg(sep).arg(m_Director).arg(sep).arg(m_FilmLength).arg(sep).arg(m_releaseDate);
}*/
Film::Film(QStringList& plst) : m_FilmID(plst.takeFirst()),
		m_Title(plst.takeFirst()), m_Direct(plst.takeFirst()),
		m_FilmLength(plst.takeFirst()), m_releaseDate(plst.takeFirst());
{}

Educational::Educational
int main()
{
	return 0;
}