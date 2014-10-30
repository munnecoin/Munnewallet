#ifndef NEWS_H
#define NEWS_H

#include "clientmodel.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "json.h"
#include <QWidget>
#include <QListWidget>
#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QBuffer>
#include <QXmlStreamReader>
#include <QTreeWidgetItem>
#include <QUrl>


namespace Ui {
    class News;
}
class ClientModel;

class News : public QWidget
{
    Q_OBJECT

public:
    explicit News(QWidget *parent = 0);
    ~News();

    void setModel(ClientModel *model);

signals:
    void networkError( QNetworkReply::NetworkError err );

public slots:

    // New
    void fetch();
    void finished(QNetworkReply *reply);
    void readyRead();
    void metaDataChanged();
    void itemActivated(QListWidgetItem * item);
    void error(QNetworkReply::NetworkError);
    void processNetworkResponse(QNetworkReply *finished);


private:

    Ui::News *ui;
    ClientModel *model;
    // New
    void parseXmlFB(QXmlStreamReader &myxml);
    void parseXmlWP(QXmlStreamReader &myxml);
    // void getRequest(const QUrl &urlString);
    void getRequest(const QString &url);
    QXmlStreamReader xml;
    QString currentTag;
    QString linkString;
    QString titleString;
    QString content;

    QNetworkAccessManager manager;
    QNetworkReply *currentReply;

};


#endif // NEWS_H
