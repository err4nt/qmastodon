#ifndef MASTODONTAG_H
#define MASTODONTAG_H

#include <QObject>
#include <QString>
#include <QUrl>

class MastodonTag : public QObject
{
    Q_OBJECT
public:
    explicit MastodonTag(QObject *parent = 0);

    Q_PROPERTY(QString Name MEMBER m_Name NOTIFY NameChanged)
    Q_PROPERTY(QUrl Url MEMBER m_Url NOTIFY UrlChanged)

signals:
    void NameChanged();
    void UrlChanged();

public slots:

private:
    QString m_Name;
    QUrl m_Url;
};

#endif // MASTODONTAG_H
