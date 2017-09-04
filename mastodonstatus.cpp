#include "mastodonstatus.h"

MastodonStatus::MastodonStatus(QObject *parent) : QObject(parent)
{
    m_Account = Q_NULLPTR;
    m_Reblog = Q_NULLPTR;
    m_Application = Q_NULLPTR;

    m_MediaAttachments = new QList<MastodonAttachment>();
    m_Mentions = new QList<MastodonMention>();
    m_Tags = new QList<MastodonTag>();
}

MastodonStatus::MastodonStatus(QJsonObject data)
{
    m_Id = data["id"].toInt();
    m_Uri = QUrl::fromUserInput(data["uri"].toString());
    m_Url = QUrl::fromUserInput(data["url"].toString());
    m_Account = new MastodonAccount(data["account"].toObject());
    // in_reply_to_id, in_reply_to_account_id, and reblog go here

    m_Content = data["content"].toString();
    m_CreatedAt = data["created_at"].toString();
    m_ReblogsCount = data["reblogs_count"].toInt();
    m_FavouritesCount = data["favourites_count"].toInt();
    m_IsSensitive = data["sensitive"].toBool();
    m_SpoilerText = data["spoiler_text"].toString();
}
