#include "poolbrowser.h"
#include "ui_poolbrowser.h"
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
#include <map>
#include <math.h>
#include <QMessageBox>

using namespace json_spirit;
using namespace std;

QString kBaseUrl = "http://api.munnecoin.com/bittrex/marketsummary";
QString kBaseUrl2 = "http://blockchain.info/tobtc?currency=USD&value=1";
QString kBaseUrl3 = "http://api.munnecoin.com/bittrex/orderbook?market=BTC-LTC";
QString kBaseUrl6 = "http://api.munnecoin.com/bittrex/markethistory?market=BTC-LTC";
QString kBaseUrl7 = "http://api.munnecoin.com/mintpal/marketstats?market=LTC/BTC";
QString kBaseUrl8 = "1"; // temp fix
QString kBaseUrl9 = "1"; // temp fix
QString kBaseUrl4 = "http://api.munnecoin.com/mintpal/trades?market=LTC/BTC";
QString kBaseUrl5 = "http://api.munnecoin.com/mintpal/orders?market=LTC/BTC&type=SELL";
QString kBaseUrl10 = "http://api.munnecoin.com/mintpal/orders?market=LTC/BTC&type=BUY";
QString kBaseCurrBi = "http://api.munnecoin.com/bittrex/currencies";
QString kBaseCurrMi = "http://api.munnecoin.com/mintpal/summary";
QString currency = "LTC";
QString previousCurrency = "LTC";
QString currencyMi = "LTC";
QString previousCurrencyMi = "LTC";
QString currenciNa = "LTC";

QString bitcoinp = "";
double bitcoin2;
double lastuG;
QString bitcoing;
QString dollarg;
int mode=1;
int o = 0;
QString lastp = "";
QString lastpp = "";
QString lastpp2 = "";
QString lastpp3 = "";
QString askp = "";
QString bidp = "";
QString highp = "";
QString lowp = "";
QString volumebp = "";
QString volumesp = "";
QString bop = "";
QString sop = "";
QString lastp2 = "";
QString askp2 = "";
QString bidp2 = "";
QString highp2 = "";
QString lowp2 = "";
QString yestp = "";
QString yestp2 = "";

map<string, QString> yestp0;
map<string, QString> yestp1;



QString volumebp2 = "";
QString volumesp2 = "";
QStringList marketdbmint;

QString lastp3 = "";
QString volumebp3 = "";
double volumesp3;




PoolBrowser::PoolBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PoolBrowser)
{
    ui->setupUi(this);
    setFixedSize(400, 480);



    randomChuckNorrisJoke();
    QObject::connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkResponse(QNetworkReply*)));
    connect(ui->startButton, SIGNAL(pressed()), this, SLOT( randomChuckNorrisJoke()));
    connect(ui->startButton_2, SIGNAL(pressed()), this, SLOT( randomChuckNorrisJoke()));

    connect(ui->listCurrencies, SIGNAL(editTextChanged(QString)), this, SLOT(onListCurrencieItemClicked(QString)));
    connect(ui->listCurrencies, SIGNAL(activated(QString)), this, SLOT(onListCurrencieItemClicked(QString)));

    connect(ui->listCurrenciesMi, SIGNAL(editTextChanged(QString)), this, SLOT(onListCurrencieItemClickedMi(QString)));
    connect(ui->listCurrenciesMi, SIGNAL(activated(QString)), this, SLOT(onListCurrencieItemClickedMi(QString)));
    // Tab Names
    ui->tab->setWindowIconText("Overview");
}

void PoolBrowser::egaldo()
{


}


void PoolBrowser::bittrex()
{
    QDesktopServices::openUrl(QUrl("https://www.bittrex.com/Market/Index?MarketName=BTC-SC"));
}

void PoolBrowser::overv()
{
    double yes = (yestp.toDouble()+yestp2.toDouble())/2;
    double average2 = (lastp.toDouble()+lastp2.toDouble()+lastp3.toDouble())/3;
    QString average3 = QString::number((lastp.toDouble()-average2)/(average2/100),'g',2);
    QString average4 = QString::number((lastp2.toDouble()-average2)/(average2/100),'g',2);
    QString average5 = QString::number((lastp3.toDouble()-average2)/(average2/100),'g',2);


    if(average3.toDouble() > 0)
    {
        ui->diff1->setText("<font color=\"green\">+" + average3 + " %</font>");
    } else {
        ui->diff1->setText("<font color=\"red\">" + average3 + " %</font>");
        }
    if(average4.toDouble() > 0)
    {
        ui->diff2->setText("<font color=\"green\">+" + average4 + " %</font>");
    } else {
        ui->diff2->setText("<font color=\"red\">" + average4 + " %</font>");
        }

    if((yestp.toDouble()+yestp2.toDouble()) > 0)
    {
        ui->yest_3->setText("<font color=\"green\">+" + QString::number(ceil(yes*100)/100) + " %</font>");
    } else {
        ui->yest_3->setText("<font color=\"red\">" + QString::number(ceil(yes*100)/100) + " %</font>");
        }


    if(lastp > lastpp)
    {
        ui->last_4->setText("<font color=\"green\">" + lastp + "</font>");
    } else if (lastp < lastp) {
        ui->last_4->setText("<font color=\"red\">" + lastp + "</font>");
        } else {
    ui->last_4->setText(lastp);
    }

    if(lastp2 > lastpp2)
    {
        ui->last_5->setText("<font color=\"green\">" + lastp2 + "</font>");
    } else if (lastp2 < lastpp2) {
        ui->last_5->setText("<font color=\"red\">" + lastp2 + "</font>");
        } else {
    ui->last_5->setText(lastp2);
    }



    lastpp = lastp;
    lastpp2 = lastp2;
    lastpp3 = lastp3;

}

void PoolBrowser::poloniex()
{
    QDesktopServices::openUrl(QUrl("https://poloniex.com/exchange/btc_sc"));
}

void PoolBrowser::randomChuckNorrisJoke()
{




    getRequest(kBaseUrl2);
    getRequest(kBaseUrl);
    getRequest(kBaseUrl3);
    getRequest(kBaseUrl4);
    getRequest(kBaseUrl5);
    getRequest(kBaseUrl6);
    getRequest(kBaseUrl7);
    getRequest(kBaseUrl8);
    getRequest(kBaseUrl9);
    getRequest(kBaseUrl10);
    getRequest(kBaseCurrBi);
    getRequest(kBaseCurrMi);
}
void PoolBrowser::randomChuckNorrisJoke2()
{

}

void PoolBrowser::getRequest( const QString &urlString )
{
    QUrl url ( urlString );
    QNetworkRequest req ( url );
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    m_nam.get(req);
}

// New: New

void PoolBrowser::parseCurrenciesBittrex(QString data)
{
    // Process data
    bool noError;
    QString currencyName;
    QtJson::JsonObject currencie;
    QtJson::JsonObject result = QtJson::parse(data, noError).toMap();
    if (noError)
    {
        // Handle UI
        while (ui->listCurrencies->count() > 0)
        {
            ui->listCurrencies->removeItem(0);
        }
        ui->listCurrencies->addItem(currency);
        foreach(QVariant currencieData, result["result"].toList())
        {
            currencie = currencieData.toMap();
            currencyName = currencie["Currency"].toString();
            if (currencyName != "BTC" && currencyName != currency)
            {
                //ui->listCurrencies->addItem(new QListWidgetItem(currencyName));
                ui->listCurrencies->addItem(currencyName);
            }
        }
        ui->listCurrencies->model()->sort(0);
    }
}

void PoolBrowser::parseCurrenciesMintpal(QString data)
{
    // Process data
    bool noError;
    QString currencyName;
    QString market;
    QtJson::JsonObject currencie;
    QtJson::JsonArray result = QtJson::parse(data, noError).toList();

    if (noError)
    {
        // Handle UI

        while (ui->listCurrenciesMi->count() > 0)
        {
            ui->listCurrenciesMi->removeItem(0);
        }

        ui->listCurrenciesMi->addItem(currencyMi);
        foreach(QVariant currencieData, result)
        {
            currencie = currencieData.toMap();
            currencyName = currencie["code"].toString();
            market = currencie["exchange"].toString();
            if (currencyName != "BTC" && market != "LTC" && currencyName != currencyMi)
            {
                ui->listCurrenciesMi->addItem(currencyName);
            }

        }
        ui->listCurrenciesMi->model()->sort(0);
    }

}

void PoolBrowser::onListCurrencieItemClicked (QString text)
{
    //QString *text = item;
    qDebug() << "Click" << text;
    previousCurrency = currency;
    currency = text;
    ui->label_16->setText("Volume " + currency);
    // New:
    if (currency != "BTC")
    {
        kBaseUrl3 = kBaseUrl3.replace(previousCurrency, currency);
        kBaseUrl6 = kBaseUrl6.replace(previousCurrency, currency);
    }else
    {
        currency = "USD";
        kBaseUrl3 = kBaseUrl3.replace(previousCurrency, currency);
        kBaseUrl6 = kBaseUrl6.replace(previousCurrency, currency);
    }

    qDebug() << kBaseUrl3;
    qDebug() << kBaseUrl6;
    updateCurrencies();
}

void PoolBrowser::onListCurrencieItemClickedMi (QString text)
{
    qDebug() << "Click" << text;
    previousCurrencyMi = currencyMi;
    currencyMi = text;
    ui->label_20->setText("Volume " + currencyMi);
    // New:
    if (currency != "BTC")
    {
        kBaseUrl4 = kBaseUrl4.replace(previousCurrencyMi, currencyMi);
        kBaseUrl5 = kBaseUrl5.replace(previousCurrencyMi, currencyMi);
        kBaseUrl7 = kBaseUrl7.replace(previousCurrencyMi, currencyMi);
        kBaseUrl10 = kBaseUrl10.replace(previousCurrencyMi, currencyMi);
    }else
    {
        currency = "USD";
        kBaseUrl3 = kBaseUrl3.replace(previousCurrencyMi, currencyMi);
        kBaseUrl6 = kBaseUrl6.replace(previousCurrencyMi, currencyMi);
    }

    qDebug() << kBaseUrl4;
    qDebug() << kBaseUrl5;
    qDebug() << kBaseUrl10;
    updateCurrenciesMi();
}

void PoolBrowser::updateCurrencies ()
{
    //ui->Ok->setVisible(true);
    getRequest(kBaseUrl3);
    getRequest(kBaseUrl6);
    getRequest(kBaseUrl);
}

void PoolBrowser::updateCurrenciesMi ()
{
    //ui->Ok->setVisible(true);
    getRequest(kBaseUrl4);
    getRequest(kBaseUrl5);
    getRequest(kBaseUrl7);
    getRequest(kBaseUrl10);
}


void PoolBrowser::parseNetworkResponse(QNetworkReply *finished )
{


    QUrl what = finished->url();

    if ( finished->error() != QNetworkReply::NoError )
    {
        // A communication error has occurred
        emit networkError( finished->error() );
        return;
    }


    if (what == kBaseCurrBi)
    {
        QString data = finished->readAll();
        parseCurrenciesBittrex(data);
    }

    if (what == kBaseCurrMi)
    {
        QString data = finished->readAll();
        if( data.indexOf("null") >= 0 || data.indexOf("error:1") >= 0)
        {
            return;
        }
        parseCurrenciesMintpal(data);
    }


if (what == kBaseUrl) //Bittrexdata
{
    double asku;
    QString askus;
    double lastu;
    QString lastus;
    double bidu;
    QString bidus;
    double volumeu;
    QString volumeus;
    double yestu;
    QString yestus;
    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString data = finished->readAll();

    if (data.indexOf("BTC-" + currency) < 1)
    {
        QMessageBox msgBox;
        msgBox.setText("No data available");
        msgBox.exec();
        return;
    }
    QStringList data2 = data.split("{\"MarketName\":\"BTC-" + currency +"\",\"High\":");
    QStringList high = data2[1].split(",\"Low\":"); // high = high
    QStringList low = high[1].split(",\"Volume\":");
    QStringList volume = low[1].split(",\"Last\":");
    QStringList last = volume[1].split(",\"BaseVolume\":");
    QStringList basevolume = last[1].split(",\"TimeStamp\":\"");
    QStringList time = basevolume[1].split("\",\"Bid\":");
    QStringList bid = time[1].split(",\"Ask\":");
    QStringList ask = bid[1].split(",\"OpenBuyOrders\":");
    QStringList openbuy = ask[1].split(",\"OpenSellOrders\":");
    QStringList opensell = openbuy[1].split(",\"PrevDay\":");
    QStringList yest = opensell[1].split(",\"Created\":");

   // 0.00000978,"Low":0.00000214,"Volume":3718261.74455189,"Last":0.00000558,
   //"BaseVolume":22.42443460,"TimeStamp":"2014-05-13T10:08:06.553","Bid":0.00000558,"Ask":0.00000559,"OpenBuyOrders":42,"OpenSellOrders":42,"PrevDay":0.00000861}
    lastu = last[0].toDouble() * bitcoin2;
    lastuG = lastu;
    lastus = QString::number(lastu);
    dollarg = lastus;
    bitcoing = last[0];

    if(last[0] > lastp)
    {
        ui->last->setText("<font>" + QString::number(last[0].toDouble(), 'f', 6) + "</font>");
        ui->lastu->setText("<font>" + QString::number(lastus.toDouble(), 'f', 6) + " $</font>");
    } else if (last[0] < lastp) {
        ui->last->setText("<font>" + QString::number(last[0].toDouble(), 'f', 6) + "</font>");
         ui->lastu->setText("<font>" + QString::number(lastus.toDouble(), 'f', 6) + " $</font>");
        } else {
    ui->last->setText(QString::number(last[0].toDouble(), 'f', 6));
    ui->lastu->setText(QString::number(lastus.toDouble(), 'f', 6) + " $");
    }

    asku = ask[0].toDouble() * bitcoin2;
    askus = QString::number(asku);

    if(ask[0] > askp)
    {
        ui->ask->setText("<font>" + QString::number(ask[0].toDouble(), 'f', 6) + "</font>");
        ui->asku->setText("<font>" + QString::number(askus.toDouble(), 'f', 6) + " $</font>");
    } else if (ask[0] < askp) {
        ui->ask->setText("<font>" + QString::number(ask[0].toDouble(), 'f', 6) + "</font>");
        ui->asku->setText("<font>" + QString::number(askus.toDouble(), 'f', 6) + " $</font>");
        } else {
    ui->ask->setText(QString::number(ask[0].toDouble(), 'f', 6));
    ui->asku->setText(QString::number(askus.toDouble(), 'f', 6) + " $");
    }

    bidu = bid[0].toDouble() * bitcoin2;
    bidus = QString::number(bidu);

    if(bid[0] > bidp)
    {
        ui->bid->setText("<font>" + QString::number( bid[0].toDouble(), 'f', 6) + "</font>");
        ui->bidu->setText("<font>" + QString::number( bidus.toDouble(), 'f', 6)  + " $</font>");
    } else if (bid[0] < bidp) {
        ui->bid->setText("<font>" + QString::number( bid[0].toDouble(), 'f', 6) + "</font>");
        ui->bidu->setText("<font>" + QString::number( bidus.toDouble(), 'f', 6) + " $</font>");
        } else {
    ui->bid->setText(QString::number( bid[0].toDouble(), 'f', 6));
    ui->bidu->setText(QString::number( bidus.toDouble(), 'f', 6) + " $");
    }
    if(high[0] > highp)
    {
        ui->high->setText("<font>" + high[0] + "</font>");
    } else if (high[0] < highp) {
        ui->high->setText("<font>" + high[0] + "</font>");
        } else {
    ui->high->setText(high[0]);
    }
    if(low[0] > lowp)
    {
        ui->low->setText("<font>" + low[0] + "</font>");
    } else if (low[0] < lowp) {
        ui->low->setText("<font>" + low[0] + "</font>");
        } else {
    ui->low->setText(low[0]);
    }


    if(volume[0] > volumebp)
    {
        ui->volumeb->setText("<font>" + volume[0] + "</font>");

    } else if (volume[0] < volumebp) {
        ui->volumeb->setText("<font>" + volume[0] + "</font>");
        ui->volumeu->setText("<font>" + volumeus + " $</font>");
        } else {
    ui->volumeb->setText(volume[0]);
    ui->volumeu->setText(volumeus + " $");
    }

    volumeu = basevolume[0].toDouble() * bitcoin2;
    volumeus = QString::number(volumeu);

    if(basevolume[0] > volumesp)
    {
        ui->volumes->setText("<font>" + basevolume[0] + "</font>");
        ui->volumeu->setText("<font>" + volumeus + " $</font>");
    } else if (basevolume[0] < volumesp) {
        ui->volumes->setText("<font>" + basevolume[0] + "</font>");
        ui->volumeu->setText("<font>" + volumeus + " $</font>");
        } else {
    ui->volumes->setText(basevolume[0]);
    ui->volumeu->setText(volumeus + " $");
    }

    if(last[0].toDouble() > yest[0].toDouble())
    {
        yestu = ((last[0].toDouble() - yest[0].toDouble())/last[0].toDouble())*100;
        yestus = QString::number(yestu);

        ui->yest->setText("<font color=\"green\"> + " + QString::number(ceil(yestus.toDouble()*100)/100) + " %</font>");


    }else
    {
        yestu = ((yest[0].toDouble() - last[0].toDouble())/yest[0].toDouble())*100;
        yestus = QString::number(yestu);
        ui->yest->setText("<font color=\"red\"> - " + QString::number(ceil(yestus.toDouble()*100)/100) + " %</font>");

    }


    lastp = last[0];
    askp = ask[0];
    bidp = bid[0];
    highp = high[0];
    lowp = low[0];
    volumebp = volume[0];
    volumesp = basevolume[0];
    bop = openbuy[0];
    sop = opensell[0];
    if(last[0].toDouble() > yest[0].toDouble()) yestp = yestus;
    if(last[0].toDouble() < yest[0].toDouble()) yestp = yestus.prepend("-");
}

if (what == kBaseUrl2) //bitcoinprice
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString bitcoin = finished->readAll();
    bitcoin2 = (1 / bitcoin.toDouble());
    bitcoin = QString::number(bitcoin2);
    if(bitcoin > bitcoinp)
    {
        ui->bitcoin->setText("<font color=\"green\">" + bitcoin + " $</font>");
    } else if (bitcoin < bitcoinp) {
        ui->bitcoin->setText("<font color=\"red\">" + bitcoin + " $</font>");
        } else {
    ui->bitcoin->setText(bitcoin + " $");
    }

    bitcoinp = bitcoin;
}
if (what == kBaseUrl3) //Bcurrent orders
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString marketd = finished->readAll();
    //qDebug() << "Leido" << marketd;
    if (marketd.indexOf("INVALID") > 0)
    {
        QMessageBox msgBox;
        msgBox.setText("No data available");
        msgBox.exec();
        return;
    }
    marketd = marketd.replace("{","").replace("}","").replace("\"","").replace("],\"sell\":","").replace(" ","").replace("]","").replace("Quantity:","").replace("Rate:","");
    QStringList marketd2 = marketd.split("["); // marketd2[1] => buy order marketd2[2] => sell
    QStringList marketdb = marketd2[1].split(",");
    QStringList marketds = marketd2[2].split(",");
    int mat = 50;
    if (marketdb.length() > marketds.length()) mat = marketds.length();
    if (marketds.length() > marketdb.length()) mat = marketdb.length();

    int z = 0;
    double highh = 0;
    double loww = 100000;
    double cumul = 0;
    double cumul2 = 0;
    double cumult = 0;
    QVector<double> x(50), y(50);
    QVector<double> x2(50), y2(50);
    ui->sellquan->clear();
    ui->buyquan->clear();
    // ui->sellquan->sortByColumn(0, Qt::AscendingOrder);
    ui->sellquan->setSortingEnabled(false);
    ui->buyquan->setSortingEnabled(false);
    //ui->buyquan->header()->setSectionResizeMode (QHeaderView::Fixed);
    //ui->sellquan->header()->setSectionResizeMode (QHeaderView::Fixed);
       //ui->sellquan->header()->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


       for (int i = 0; i < mat-1; i++) {

           QTreeWidgetItem * item = new QTreeWidgetItem();
           item->setText(0, marketdb[i+1]);
           item->setText(1, QString::number(ceil(marketdb[i].toDouble()*100)/100));

           ui->buyquan->addTopLevelItem(item);
           // New
           ui->buyquan->resizeColumnToContents(0);
           QTreeWidgetItem * item2 = new QTreeWidgetItem();
           item2->setText(0, marketds[i+1]);
           item2->setText(1, QString::number(ceil(marketdb[i].toDouble()*100)/100));
           ui->sellquan->addTopLevelItem(item2);
           //ui->sellquan->resizeColumnToContents(0);

           if (marketds[i+1].toDouble()*100000000 > highh) highh = marketds[i+1].toDouble()*100000000;
           if (marketdb[i+1].toDouble()*100000000 < loww) loww = marketdb[i+1].toDouble()*100000000;


           x[z] = marketdb[i+1].toDouble()*100000000;
           y[z] = cumul;
           x2[z] = marketds[i+1].toDouble()*100000000;
           y2[z] = cumul2;

           cumul = marketdb[i].toDouble() + cumul;
           cumul2 = marketds[i].toDouble() + cumul2;

           i = i + 1;
           z = z + 1;

       }
       if (cumul > cumul2 ) cumult=cumul;
       if (cumul < cumul2 ) cumult=cumul2;




}

if (what == kBaseUrl6) //Bpast orders
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString marketd = finished->readAll();
    if (marketd.indexOf("MARKET") > 1)
    {
        QMessageBox msgBox;
        msgBox.setText("No data available");
        msgBox.exec();
        return;
    }
    marketd = marketd.replace("{\"success\":true,\"message\":\"\",\"result\":[","");
    marketd = marketd.replace(",\"FillType\":\"FILL\"","");
    marketd = marketd.replace(",\"FillType\":\"PARTIAL_FILL\"","");
    marketd = marketd.replace("\"","");
    marketd = marketd.replace("Id:","");
    marketd = marketd.replace("TimeStamp:","");
    marketd = marketd.replace("Quantity:","");
    marketd = marketd.replace("Price:","");
    marketd = marketd.replace("Total:","");
    marketd = marketd.replace("Total:","");
    marketd = marketd.replace("OrderType:","");

    QStringList marketdb = marketd.split("},{");

}

if (what == kBaseUrl7) //Mintpaldata
{
 
    double asku;
    QString askus;
    double lastu;
    QString lastus;
    double bidu;
    QString bidus;
    double volumeu;
    QString volumeus;
    double yestu;
    QString yestus;

    QString data = finished->readAll();
    qDebug() << data;
    if( data.indexOf("null") >= 0 || data.indexOf("error:1") >= 0)
    {
        return;
    }
    QString dataa = data.replace("[{","").replace("}]","").replace("\"","");
    QStringList data2 = dataa.split("last_price:");
    QStringList last = data2[1].split(",yesterday_price:"); // high = high
    QStringList yest = last[1].split(",change:");
    QStringList yestc = yest[1].split(",24hhigh:");
    QStringList high = yestc[1].split(",24hlow:");
    QStringList low = high[1].split(",24hvol:");
    QStringList volume = low[1].split(",top_bid:");
    QStringList bid = volume[1].split(",top_ask:");
    QString ask = bid[1];

    lastu = last[0].toDouble() * bitcoin2;
    lastus = QString::number(lastu);

    if(last[0] > lastp2)
    {
        ui->last_2->setText("<font>" + QString::number( last[0].toDouble(), 'f', 7) + "</font>");
        ui->lastu_2->setText("<font>" + QString::number( lastus.toDouble(), 'f', 6) + " $</font>");
    } else if (last[0] < lastp2) {
        ui->last_2->setText("<font>" + QString::number( last[0].toDouble(), 'f', 7)  + "</font>");
         ui->lastu_2->setText("<font>" + QString::number( lastus.toDouble(), 'f', 6)  + " $</font>");
        } else {
    ui->last_2->setText(QString::number( last[0].toDouble(), 'f', 7));
    ui->lastu_2->setText(QString::number( lastus.toDouble(), 'f', 6) + " $");
    }

    asku = ask.toDouble() * bitcoin2;
    askus = QString::number(asku);

    if(ask > askp2)
    {
        ui->ask_2->setText("<font>" + QString::number( ask.toDouble(), 'f', 7) + "</font>");
        ui->asku_2->setText("<font>" + QString::number( askus.toDouble(), 'f', 6) + " $</font>");
    } else if (ask < askp2) {
        ui->ask_2->setText("<font>" + QString::number( ask.toDouble(), 'f', 7) + "</font>");
        ui->asku_2->setText("<font>" + QString::number( askus.toDouble(), 'f', 6) + " $</font>");
        } else {
    ui->ask_2->setText(QString::number( ask.toDouble(), 'f', 7));
    ui->asku_2->setText(QString::number( askus.toDouble(), 'f', 6) + " $");
    }

    bidu = bid[0].toDouble() * bitcoin2;
    bidus = QString::number(bidu);


    if(bid[0] > bidp2)
    {
        ui->bid_2->setText("<font>" + QString::number( bid[0].toDouble(), 'f', 7) + "</font>");
        ui->bidu_2->setText("<font>" + QString::number( bidus.toDouble(), 'f', 6) + " $</font>");
    } else if (bid[0] < bidp2) {
        ui->bid_2->setText("<font>" + QString::number( bid[0].toDouble(), 'f', 7) + "</font>");
        ui->bidu_2->setText("<font>" + QString::number( bidus.toDouble(), 'f', 6) + " $</font>");
        } else {
    ui->bid_2->setText(QString::number( bid[0].toDouble(), 'f', 7));
    ui->bidu_2->setText(QString::number( bidus.toDouble(), 'f', 6) + " $");
    }
    if(high[0] > highp2)
    {
        ui->high_2->setText("<font>" + high[0] + "</font>");
    } else if (high[0] < highp2) {
        ui->high_2->setText("<font>" + high[0] + "</font>");
        } else {
    ui->high_2->setText(high[0]);
    }

    if(low[0] > lowp2)
    {
        ui->low_2->setText("<font>" + low[0] + "</font>");
    } else if (low[0] < lowp2) {
        ui->low_2->setText("<font>" + low[0] + "</font>");
        } else {
    ui->low_2->setText(low[0]);
    }

    volumeu = volume[0].toDouble() * bitcoin2;
    volumeus = QString::number(volumeu);

    if(volume[0] > volumebp2)
    {
        ui->volumeb_2->setText("<font>" + volume[0] + "</font>");

    } else if (volume[0] < volumebp2) {
        ui->volumeb_2->setText("<font>" + volume[0] + "</font>");
        ui->volumeu_2->setText("<font>" + volumeus + " $</font>");
        } else {
    ui->volumeb_2->setText(volume[0]);
    ui->volumeu_2->setText(volumeus + " $");
    }

    // -----------------------------------------------------------------------------------------
    quint64 basee = volume[0].toDouble()/last[0].toDouble();
    QString basevolume = QString::number(basee);


    if(basevolume > volumesp2)
    {
        ui->volumes_2->setText("<font>" + basevolume + "</font>");
        ui->volumeu_2->setText("<font>" + volumeus + " $</font>");
    } else if (basevolume < volumesp2) {
        ui->volumes_2->setText("<font>" + basevolume + "</font>");
        ui->volumeu_2->setText("<font>" + volumeus + " $</font>");
        } else {
    ui->volumes_2->setText(basevolume);
    ui->volumeu_2->setText(volumeus + " $");
    }



    if(last[0].toDouble() > yest[0].toDouble())
    {
        yestu = ((last[0].toDouble() - yest[0].toDouble())/last[0].toDouble())*100;
        yestus = QString::number(yestu);

        ui->yest_2->setText("<font color=\"green\"> + " + QString::number(ceil(yestus.toDouble()*100)/100) + " %</font>");


    }else
    {
        yestu = ((yest[0].toDouble() - last[0].toDouble())/yest[0].toDouble())*100;
        yestus = QString::number(yestu);
        ui->yest_2->setText("<font color=\"red\"> - " + QString::number(ceil(yestus.toDouble()*100)/100) + " %</font>");

    }

    lastp2 = last[0];
    askp2 = ask;
    bidp2 = bid[0];
    highp2 = high[0];
    lowp2 = low[0];
    volumebp2 = volume[0];
    volumesp2 = basevolume;
    if(last[0].toDouble() > yest[0].toDouble()) yestp2 = yestus;
    if(last[0].toDouble() < yest[0].toDouble()) yestp2 = yestus.prepend("-");
}


if (what == kBaseUrl4) //mintpalprice
{

    QString data = finished->readAll();



    QString dataa = data.replace("\"","");
    QStringList data3 = dataa.split("[{");

    QStringList recent = data3[1].replace("time:","").replace("type:","").replace("price:","").replace("amount:","").replace("total:","").split("},{");



}

if (what == kBaseUrl5) //mintpalbuy
{

    QString data = finished->readAll();
    if( data.indexOf("null") >= 0 || data.indexOf("error:1") >= 0)
    {
        return;
    }
    QString dataa = data.replace("\"","");
    QStringList dataa2 = dataa.split("[{");

    QStringList marketdb =  dataa2[1].replace("price:","").replace("amount:","").replace("total:","").replace("}","").replace("{","").replace("}],buyorders:","").replace("]","").split(","); //sell
    marketdbmint = marketdb;
    o = 0;
}

if (what == kBaseUrl10) //mintpalsell
{
    qDebug() << "Mintpalsell";

    QString data = finished->readAll();
    if( data.indexOf("null") >= 0 || data.indexOf("error:1") >= 0)
    {
        return;
    }
    QString dataa = data.replace("\"","");
    QStringList dataa2 = dataa.split("[{");
    qDebug() << data;
    QStringList marketdb =  dataa2[1].replace("price:","").replace("amount:","").replace("total:","").replace("}","").replace("{","").replace("}],buyorders:","").replace("]","").split(","); //sell
    QStringList marketds = marketdbmint;

    int mat = 50;
    if (marketdb.length() > marketds.length()) mat = marketds.length();
    if (marketds.length() > marketdb.length()) mat = marketdb.length();
    int z = 0;
    double highh2 = 0;
    double loww2 = 100000;
    double cumul = 0;
    double cumul2 = 0;
    double cumult = 0;

    QVector<double> x_3(50), y_3(50);
    QVector<double> x2_3(50), y2_3(50);
    ui->sellquan_2->clear();
    ui->buyquan_2->clear();
     //ui->sellquan_2->sortByColumn(0, Qt::AscendingOrder);
    ui->sellquan_2->setSortingEnabled(false);
    ui->buyquan_2->setSortingEnabled(false);
    //ui->buyquan_2->header()->setSectionResizeMode (QHeaderView::Fixed);
    //ui->sellquan_2->header()->setSectionResizeMode (QHeaderView::Fixed);

       for (int i = 0; i < mat-1; i++) {

           QTreeWidgetItem * item = new QTreeWidgetItem();
           item->setText(0, marketdb[i]);
           item->setText(1, QString::number(ceil(marketdb[i+1].toDouble()*100)/100));
           ui->buyquan_2->addTopLevelItem(item);
           ui->buyquan_2->resizeColumnToContents(0);

           QTreeWidgetItem * item2 = new QTreeWidgetItem();
           item2->setText(0, marketds[i]);
           item2->setText(1, QString::number(ceil(marketds[i+1].toDouble()*100)/100));
           ui->sellquan_2->addTopLevelItem(item2);
           //ui->sellquan_2->resizeColumnToContents(0);

           if (marketds[i].toDouble()*100000000 > highh2) highh2 = marketds[i].toDouble()*100000000;
           if (marketdb[i].toDouble()*100000000 < loww2) loww2 = marketdb[i].toDouble()*100000000;

           cumul = marketdb[i+1].toDouble() + cumul;
           cumul2 = marketds[i+1].toDouble() + cumul2;

           x_3[z] = marketdb[i].toDouble()*100000000;
           y_3[z] = cumul;
           x2_3[z] = marketds[i].toDouble()*100000000;
           y2_3[z] = cumul2;

           i = i + 2;
           z = z + 1;

       }
       if (cumul > cumul2 ) cumult=cumul;
       if (cumul < cumul2 ) cumult=cumul2;





}

if (lastp != 0 && lastp2 != 0 && lastp3 != 0) //ui->Ok->setVisible(false);
if (o == 0)
{

    randomChuckNorrisJoke2();
    o = 1;
    overv();
}

finished->deleteLater();
}


void PoolBrowser::setModel(ClientModel *model)
{
    this->model = model;
}

PoolBrowser::~PoolBrowser()
{
    delete ui;
}
