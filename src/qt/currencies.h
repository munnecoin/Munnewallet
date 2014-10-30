#ifndef CURRENCIES_H
#define CURRENCIES_H

#include "clientmodel.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "json.h"
#include <QWidget>
#include <QListWidget>
#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QMovie>



double getBlockHardness(int);
double getTxTotalValue(std::string);
double convertCoins(int64_t);
double getTxFees(std::string);
int getBlockTime(int);
int getBlocknBits(int);
int getBlockNonce(int);
int blocksInPastHours(int);
int getBlockHashrate(int);
std::string getInputs(std::string);
std::string getOutputs(std::string);
std::string getBlockHash(int);
std::string getBlockMerkle(int);
bool addnode(std::string);
const CBlockIndex* getBlockIndex(int);
int64_t getInputValue(CTransaction, CScript);


namespace Ui {
    class Currencies;
}
class ClientModel;

class Currencies : public QWidget
{
    Q_OBJECT

public:
    explicit Currencies(QWidget *parent = 0);
    ~Currencies();

    void setModel(ClientModel *model);

private:
    void getRequest( const QString &url );
    QString parseNumber (QString number);

signals:
    void networkError( QNetworkReply::NetworkError err );

public slots:
    void parseNetworkResponse(QNetworkReply *finished );
    void parseDataAPI(QString &data);
    void startRequest();


private:
    QNetworkAccessManager conex;
    Ui::Currencies *ui;
    ClientModel *model;
    QMovie *movie;


};


#endif // CURRENCIES_H
