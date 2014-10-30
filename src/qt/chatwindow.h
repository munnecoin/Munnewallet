/*Copyright (C) 2009 Cleriot Simon
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA*/

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QtGui>
#include <QtNetwork>
#include "clientmodel.h"
#include "serveur.h"



namespace Ui
{
    class ChatWindowClass;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    ChatWindow(QWidget *parent = 0);
    ~ChatWindow();
    void setModel(ClientModel *model);
    Serveur * currentTab();
	signals:
		void changeTab();
        void networkError( QNetworkReply::NetworkError err );

	public slots:
		void sendCommande();
        void connecte();
		void closeTab();

		void tabChanged(int index);

		void tabJoined();
		void tabJoining();
        void disconnectFromServer();
        void tabClosing(int index);

        void fetch();
        void finished(QNetworkReply *reply);
        void readyRead();
        void metaDataChanged();
        void error(QNetworkReply::NetworkError);
        void processNetworkResponse(QNetworkReply *finished);


private:
	Ui::ChatWindowClass *ui;
    ClientModel *model;
    QMap<QString,Serveur *> serveurs;
	bool joining;
	void closeEvent(QCloseEvent *event);

    void parseXml(QXmlStreamReader &myxml);
    void getRequest(const QString &url);
    QXmlStreamReader xml;
    QString currentTag;
    QString linkString;
    QString titleString;
    QString content;
    QString date;

    QNetworkAccessManager manager;
    QNetworkReply *currentReply;

};

#endif // CHATWINDOW_H
