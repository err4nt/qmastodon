#ifndef STATUS_H
#define STATUS_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>

#include "mastodonaccount.h"
#include "mastodonattachment.h"
#include "mastodonmention.h"
#include "mastodontag.h"
#include "mastodonapplication.h"

class MastodonStatus : public QObject
{
    Q_OBJECT
    Q_ENUMS(MastodonStatusVisibility)

public:
    explicit MastodonStatus(QObject *parent = 0);
    MastodonStatus(QJsonObject data);

    enum MastodonStatusVisibility
    {
        Direct,
        Private,
        Unlisted,
        Public
    };

    Q_PROPERTY(QString Id MEMBER m_Id NOTIFY IdChanged)
    Q_PROPERTY(QUrl Uri MEMBER m_Uri NOTIFY UriChanged)
    Q_PROPERTY(QUrl Url MEMBER m_Url NOTIFY UrlChanged)
    Q_PROPERTY(MastodonAccount * Account MEMBER m_Account NOTIFY AccountChanged)
    Q_PROPERTY(QString InReplyToId MEMBER m_InReplyToId NOTIFY InReplyToIdChanged)
    Q_PROPERTY(QString InReplyToAccountId MEMBER m_InReplyToAccountId NOTIFY InReplyToAccountIdChanged)
    Q_PROPERTY(MastodonStatus * Reblog MEMBER m_Reblog NOTIFY ReblogChanged)
    Q_PROPERTY(QString Content MEMBER m_Content NOTIFY ContentChanged)
    Q_PROPERTY(QString CreatedAt MEMBER m_CreatedAt NOTIFY CreatedAtChanged)
    Q_PROPERTY(int ReblogsCount MEMBER m_ReblogsCount NOTIFY ReblogsCountChanged)
    Q_PROPERTY(int FavouritesCount MEMBER m_FavouritesCount NOTIFY FavouritesCountChanged)
    Q_PROPERTY(bool IsReblogged MEMBER m_IsReblogged NOTIFY IsRebloggedChanged)
    Q_PROPERTY(bool IsFavourited MEMBER m_IsFavourited NOTIFY IsFavouritedChanged)
    Q_PROPERTY(bool IsSensitive MEMBER m_IsSensitive NOTIFY IsSensitiveChanged)
    Q_PROPERTY(QString SpoilerText MEMBER m_SpoilerText NOTIFY SpoilerTextChanged)
    Q_PROPERTY(MastodonStatus::MastodonStatusVisibility Visibility MEMBER m_Visibility NOTIFY VisibilityChanged)
    Q_PROPERTY(QList<MastodonAttachment> * MediaAttachments MEMBER m_MediaAttachments NOTIFY MediaAttachmentsChanged)
    Q_PROPERTY(QList<MastodonMention> * Mentions MEMBER m_Mentions NOTIFY MentionsChanged)
    Q_PROPERTY(QList<MastodonTag> * Tags MEMBER m_Tags NOTIFY TagsChanged)
    Q_PROPERTY(MastodonApplication * Application MEMBER m_Application NOTIFY ApplicationChanged)

signals:
    void IdChanged();
    void UriChanged();
    void UrlChanged();
    void AccountChanged();
    void InReplyToIdChanged();
    void InReplyToAccountIdChanged();
    void ReblogChanged();
    void ContentChanged();
    void CreatedAtChanged();
    void ReblogsCountChanged();
    void FavouritesCountChanged();
    void IsRebloggedChanged();
    void IsFavouritedChanged();
    void IsSensitiveChanged();
    void SpoilerTextChanged();
    void VisibilityChanged();
    void MediaAttachmentsChanged();
    void MentionsChanged();
    void TagsChanged();
    void ApplicationChanged();

private:
    QString m_Id;
    QUrl m_Uri;
    QUrl m_Url;
    MastodonAccount * m_Account;
    QString m_InReplyToId;
    QString m_InReplyToAccountId;
    MastodonStatus * m_Reblog;
    QString m_Content;
    QString m_CreatedAt;
    int m_ReblogsCount;
    int m_FavouritesCount;
    bool m_IsReblogged;
    bool m_IsFavourited;
    bool m_IsSensitive;
    QString m_SpoilerText;
    MastodonStatus::MastodonStatusVisibility m_Visibility;
    QList<MastodonAttachment> * m_MediaAttachments;
    QList<MastodonMention> * m_Mentions;
    QList<MastodonTag> * m_Tags;
    MastodonApplication * m_Application;

public slots:
};

#endif // STATUS_H
