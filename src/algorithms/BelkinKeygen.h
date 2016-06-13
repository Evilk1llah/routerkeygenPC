/*
 * AxtelKeygen.h
 *
 *  Created on: 5 de Ago de 2012
 *      Author: ruka
 */

#ifndef BELKINKEYGEN_H_
#define BELKINKEYGEN_H_

#include "Keygen.h"

#define NUMBERS_OF_ORDERS   4

class BelkinKeygen: public Keygen {
public:
    BelkinKeygen(QString ssid, QString mac);
    int getSupportState() const;

private:
    const static int ORDERS[NUMBERS_OF_ORDERS][8];
    const static QString CHARSETS[2];
    QVector<QString> & getKeys() ;
    void generateKey(QString mac, QString charset, int order[8]);
    QString addOneToMac(QString mac);

};

#endif /* BELKINKEYGEN_H_ */
