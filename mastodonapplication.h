#ifndef MASTODONAPPLICATION_H
#define MASTODONAPPLICATION_H

#include <QObject>
#include <QString>
#include <QUrl>

class MastodonApplication : public QObject
{
    Q_OBJECT
public:
    explicit MastodonApplication(QObject *parent = 0);

    Q_PROPERTY(QString Name MEMBER m_Name NOTIFY NameChanged)
    Q_PROPERTY(QUrl Website MEMBER m_Website NOTIFY WebsiteChanged)

signals:
    void NameChanged();
    void WebsiteChanged();

public slots:

private:
    QString m_Name;
    QUrl m_Website;
};

#endif // MASTODONAPPLICATION_H
