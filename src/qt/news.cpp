
#include "news.h"
#include "ui_news.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include "json.h"
#include <QDesktopServices>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <QMessageBox>


QString urlNews1 = "http://api.munnecoin.com/coindesk/feed";
QString urlNews2 = "http://api.munnecoin.com/cryptocoinsnews/feed";
QString urlNews1Name = "CoinDesk";
QString urlNews2Name = "CryptoCoinNews";
QString urlNewsAll = QObject::tr("All");


News::News(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::News)
{
    ui->setupUi(this);
    setFixedSize(720, 600);
    fetch();
    // Add resources
    ui->listSources->addItem(new QListWidgetItem(urlNewsAll));
    ui->listSources->addItem(new QListWidgetItem(urlNews1Name));
    ui->listSources->addItem(new QListWidgetItem(urlNews2Name));


    // Obj connections
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processNetworkResponse(QNetworkReply *)));

    // UI connections
    connect(ui->newsList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                this, SLOT(itemActivated(QListWidgetItem*)));
    connect(ui->startButton, SIGNAL(pressed()), this, SLOT( fetch()));
    connect(ui->listSources, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
                this, SLOT(fetch()));
}



void News::getRequest(const QString &urlString )
{
    QUrl url (urlString);
    QNetworkRequest req(url);
    manager.get(req);
}

void News::processNetworkResponse(QNetworkReply *finished )
{

    QUrl what = finished->url();
    if (finished->error() != QNetworkReply::NoError)
    {
        // A communication error has occurred
        qDebug() << "Connection error" << finished->errorString();
        emit networkError( finished->error() );
        return;
    }
    
    QString data = finished->readAll();
    
    // Check which feed
    if (what == urlNews1)
    {
        //qDebug() << data;
        xml.addData(data);
    	parseXmlFB(xml);
    }
    
    if (what == urlNews2)
    {
    	xml.addData(data);

        parseXmlWP(xml);
    }
}    

void News::fetch()
{


    ui->newsList->clear();
    xml.clear();


     // Check selected
     QString selected = "";
     if (ui->listSources->currentItem() == NULL)
     {

     }else{
         selected = ui->listSources->currentItem()->text();
     }

     if (selected == urlNews1Name)
     {
        getRequest(urlNews1);
     }else if(selected == urlNews2Name)
     {
        getRequest(urlNews2);
     }else
     {
        getRequest(urlNews1);
        getRequest(urlNews2);
     }



}

void News::metaDataChanged()
{
     QUrl redirectionTarget = currentReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
     if (redirectionTarget.isValid()) 
     {
         getRequest(redirectionTarget.toString());
     }
}


void News::readyRead()
{

    int statusCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 200 && statusCode < 300) 
    {
        QByteArray data = currentReply->readAll();
        xml.addData(data);
        if (data.indexOf("coindesk") > 0)
        {
            parseXmlFB(xml);
        }else
        {
            parseXmlWP(xml);
        }
        xml.clear();
    }
}

void News::finished(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    // UI Changes
}

void News::parseXmlFB(QXmlStreamReader &myxml)
{
    QListWidgetItem *item;

    while (!myxml.atEnd())
    {
        myxml.readNext();
        // Parse each news
        if (myxml.isStartElement())
        {
            if (myxml.name() == "item")
            {
                linkString = myxml.attributes().value("rss:about").toString();
            }
            currentTag = myxml.name().toString();

         } else if (myxml.isEndElement())
         {
            if (myxml.name() == "item")
            {

                // Remove Images from content
                content.remove(QRegExp("<img[^>]*>"));
                // Remove first title
                titleString.remove("CoinDesk");
                // UI Changes
                item = new QListWidgetItem();
                item->setText("Coindesk - " + QString(titleString).trimmed().mid(0, 72) + "...");
                content.replace("<a", "<a style='color:#111;text-transform:uppercase;font-weight:800;text-decoration:none;'");
                item->setData(1, content);
                ui->newsList->addItem(item);

                titleString.clear();
                linkString.clear();
                content.clear();
            }

         } else if (myxml.isCharacters() && !myxml.isWhitespace())
         {
             if (currentTag == "title")
             {
                titleString += myxml.text().toString();
             }
             else if (currentTag == "link")
             {
                linkString += myxml.text().toString();
             }else if(currentTag == "encoded")
             {
                 content += myxml.text().toString();
             }

         }
        // While

     }
     if (myxml.error() && myxml.error() != QXmlStreamReader::PrematureEndOfDocumentError)
     {
         qWarning() << "XML ERROR: " << myxml.lineNumber() << ": " << myxml.errorString();
     }
     myxml.clear();
}


void News::parseXmlWP(QXmlStreamReader &myxml)
{
    QListWidgetItem *item;

    while (!myxml.atEnd())
    {
        myxml.readNext();
        // Parse each news
        if (myxml.isStartElement())
        {
            if (myxml.name() == "item")
            {
                linkString = myxml.attributes().value("rss:about").toString();
            } 
            currentTag = myxml.name().toString();
            
         } else if (myxml.isEndElement())
         {
            if (myxml.name() == "item")
            {

                // Remove Images from content
                content.remove(QRegExp("<img[^>]*>"));
                // Remove first title
                titleString.remove("CryptoCoinsNews");
                // UI Changes
                item = new QListWidgetItem();
                item->setText("Cryptocoinsnews - " + QString(titleString).mid(0, 63) + "...");
                content.replace("<a", "<a style='color:#111;text-transform:uppercase;font-weight:800;text-decoration:none;'");
                item->setData(1, content);
                ui->newsList->addItem(item);

                titleString.clear();
                linkString.clear();
                content.clear();
            }

         } else if (myxml.isCharacters() && !myxml.isWhitespace())
         {
             if (currentTag == "title")
             {
                titleString += myxml.text().toString();
             }
			 else if (currentTag == "link")
			 {
                linkString += myxml.text().toString();
             }else if(currentTag == "description")
             {
                 content += myxml.text().toString();
             }
         }
        // While

     }
     if (myxml.error() && myxml.error() != QXmlStreamReader::PrematureEndOfDocumentError)
     {
         qWarning() << "XML ERROR: " << myxml.lineNumber() << ": " << myxml.errorString();
     }
     myxml.clear();
}


void News::itemActivated(QListWidgetItem * item)
{

    if (item != NULL)
    {
        ui->newsView->setHtml(item->data(1).toString());
    }

}

void News::error(QNetworkReply::NetworkError)
{
    qWarning() << tr("Error reading RSS");
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
}


void News::setModel(ClientModel *model)
{
    this->model = model;
}

News::~News()
{
    delete ui;
}
