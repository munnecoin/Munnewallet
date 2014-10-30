
#include "currencies.h"
#include "ui_currencies.h"
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
#include <QMovie>



QString baseAPIRank = "http://api.munnecoin.com/ranking";



class InTableWidgetItem : public QTableWidgetItem
{
    public:
        bool operator <(const QTableWidgetItem &other) const
        {
            return text().toInt() < other.text().toInt();
        }
};

class MoTableWidgetItem : public QTableWidgetItem
{
    public:
        bool operator <(const QTableWidgetItem &other) const
        {
            return text().replace(",", "").replace(" $", "").toDouble() < other.text().replace(",", "").replace(" $", "").toDouble();
        }
};

class PeTableWidgetItem : public QTableWidgetItem
{
    public:
        bool operator <(const QTableWidgetItem &other) const
        {
            return text().replace(",", "").replace("%", "").toDouble() < other.text().replace(",", "").replace("%", "").toDouble();
        }
};

Currencies::Currencies(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Currencies)
{
    ui->setupUi(this);
    setFixedSize(720, 550);
    // First request to API
	startRequest();
    QObject::connect(&conex, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkResponse(QNetworkReply*)));
    // Update data when button is pressed
    connect(ui->startButtonCurrencies, SIGNAL(pressed()), this, SLOT( startRequest()));
    movie = new QMovie(":/images/res/icons/ajax-loader.gif");

}

void Currencies::getRequest( const QString &urlString )
{
    QUrl url(urlString);
    QNetworkRequest req (url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    conex.get(req);
    movie = new QMovie(":/images/res/icons/ajax-loader.gif");
}

void Currencies::startRequest()
{
    // Start request
    getRequest(baseAPIRank);
    ui->lblLoading->show();
    ui->lblLoading->setMovie(movie);
    movie->start();


}

QString Currencies::parseNumber(QString number)
{
    QStringList parts = number.split(".");
    QString integer = parts.at(0);
    QString result = "";
    int i, max = integer.length();
    int rest = max % 3;
    for(i = 0; i < max; i = i + 1)
    {
        result += integer.at(i);
        if (((i + 1 - rest) % 3 == 0 && i > rest && (i+1) < max)
                || ((i + 1) == rest && max > 2))
        {
            result += ",";
        }
    }
    if (parts.length() > 1)
    {
        result += "." + parts.at(1);
    }
    return result;
}

void Currencies::parseDataAPI(QString &data)
{
    // Stop loading
    ui->lblLoading->hide();
    movie->stop();

    // Process data
    bool noError;
    QtJson::JsonArray result = QtJson::parse(data, noError).toList();
    if (noError)
    {    

        // Change UI
        while (ui->tableRanking->rowCount() > 0)
        {
            ui->tableRanking->removeRow(0);
        }
        // Prev: result["markets"].toList().count()
        ui->tableRanking->setRowCount(100);
        ui->tableRanking->setColumnCount(6);
        QStringList m_TableHeader;
        m_TableHeader<<"#"<<tr("Name")<<tr("Price")<<tr("Net Value") << tr("Volume 24h") << tr("Change 24h");
        ui->tableRanking->setHorizontalHeaderLabels(m_TableHeader);
        ui->tableRanking->verticalHeader()->setVisible(false);

        int count = 0;
        QtJson::JsonObject currency;
        QtJson::JsonObject priceData;
        QtJson::JsonObject marketData;
        QtJson::JsonObject volumeData;
        QtJson::JsonObject changeData;
        QTableWidgetItem *it0;
        QTableWidgetItem *it1;
        QTableWidgetItem *it2;
        QTableWidgetItem *it3;
        QTableWidgetItem *it4;
        QTableWidgetItem *it5;

        foreach (QVariant currencyData, result)
        {
            if (count < 100)
            {
                currency = currencyData.toMap();
                priceData = currency["price"].toMap();
                marketData = currency["market_cap"].toMap();
                volumeData = currency["volume"].toMap();
                //changeData = currency["change"].toMap();

                it0 = new InTableWidgetItem();
                it0->setText(currency["position"].toString());
                it1 = new QTableWidgetItem();
                it1->setText(currency["name"].toString());
                it2 = new MoTableWidgetItem();
                it2->setText(QString::number(priceData["usd"].toString().toDouble(), 'f', 5) + " $");
                it3 = new MoTableWidgetItem();
                it3->setText(parseNumber(QString::number(marketData["usd"].toString().toDouble(),'f', 2)) + " $");
                it4 = new MoTableWidgetItem();
                it4->setText(parseNumber(volumeData["usd"].toString()) + " $");
                it5 = new PeTableWidgetItem();
                it5->setText(currency["change"].toString() + " %");
                if (currency["change"].toDouble() > 0)
                {
                    it5->setTextColor( QColor(7, 93, 31, 255));

                }else if(currency["change"].toDouble() < 0)
                {
                    it5->setTextColor( Qt::red);
                }else
                {
                    it5->setText(currency["change"].toString() + " %");
                }

                ui->tableRanking->setItem(count, 0, it0);
                ui->tableRanking->setItem(count, 1, it1);
                ui->tableRanking->setItem(count, 2, it2);
                ui->tableRanking->setItem(count, 3, it3);
                ui->tableRanking->setItem(count, 4, it4);
                ui->tableRanking->setItem(count, 5, it5);
                count++;
            }
        }
        ui->tableRanking->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
        ui->tableRanking->verticalHeader()->setResizeMode(QHeaderView::Stretch);

    }


}


void Currencies::parseNetworkResponse(QNetworkReply *finished)
{
	QUrl whatURL = finished->url();
    if (finished->error() != QNetworkReply::NoError)
    {
        // A communication error has occurred
        emit networkError( finished->error() );
        return;
    }
	// Start checking for appropiate handler
    if (whatURL == baseAPIRank)
    {
        QString data = finished->readAll();
        parseDataAPI(data);
    }

}


void Currencies::setModel(ClientModel *model)
{
    this->model = model;
}

Currencies::~Currencies()
{
    delete ui;
}
