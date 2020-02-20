/*
 * Copyright 2020 Alex Stanev <alex@stanev.org>
 *
 * Based on https://github.com/jclehner/upc-twg8x0
 *
 * This file is part of Router Keygen.
 *
 * Router Keygen is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Router Keygen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Router Keygen.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Twg8x0Keygen.h"
#include <QRegExp>

Twg8x0Keygen::Twg8x0Keygen(QString ssid, QString mac, unsigned short int var) :
		Keygen(ssid, mac) {
    kgname = "twg8x0";
    opt_alt_algo = 0;
    
    switch (var) {
        case 0:
            // twg850
            this->ssid = ssid.right(6).toUInt();
            prefixes = prefixes_twg850;
            break;
        case 1:
            // twg870
            this->ssid = ssid.right(7).toUInt();
            prefixes = prefixes_twg870;
            break;
        default:
            throw ERROR;
    }

    this->var = var;
}

int Twg8x0Keygen::getSupportState() const{
    if (   getSsidName().contains(QRegExp("^UPC[0-9]{6,7}$"))
        || getSsidName().contains(QRegExp("^CPC[0-9]{7}$")) )
        return SUPPORTED;
    return UNLIKELY;
}

quint32 Twg8x0Keygen::generate_upc_ssid(quint32 *sn) {
	quint32 ssid;

	if (this->opt_alt_algo == 1) {
	    if (this->var == 0) {
	        // twg850
	        ssid = sn[0] *  4 + sn[1] * sn[1] * sn[1] + sn[2] * 7 + sn[3] * 2047 +              (sn[4] % 93) * (sn[4] % 93);
	    } else {
	        // twg870
		    ssid = sn[0] * 47 + sn[1] * sn[1] * sn[1] + sn[2] * 7 + sn[3] * 2047 +  sn[4] * 5 + (sn[4] % 93) * (sn[4] % 93);
		}
	} else {
	    if (this->var == 0) {
	        // twg850
	        ssid = sn[0] *  3 + sn[1] * sn[1] + sn[2] * 9 + sn[3] * 1023 + sn[4] * 3 + 1;
	    } else {
	        // twg870
		    ssid = sn[0] * 37 + sn[1] * sn[1] + sn[2] * 9 + sn[3] * 1023 + sn[4] * 3 + 1;
		}
	}

	return ssid % 9999999 + 1;
}

void Twg8x0Keygen::generate_upc_psk_twg8x0(quint32 *sn, char *psk) {
	char base[9];
	snprintf(base, 9, "%08d", (sn[1] * 1000 + sn[2] * 10 + sn[3]) * sn[4] * 11 % 100000000);

	unsigned short int i = 0;
	for (i = 0; i < 8; i++) {
		psk[i] = base[i] * base[(i + 1) % 8] % 26 + 0x41;
	}
}

QVector<QString> & Twg8x0Keygen::getKeys() {
    quint32 sn[6] = { 0 };
	quint32 *sn0, *sn1, *sn2, *sn3, *sn4;
	char psk[9];

    sn0 = sn;
	sn1 = sn + 1;
	sn2 = sn + 2;
	sn3 = sn + 3;
	sn4 = sn + 4;

	for (unsigned short int i = 0; prefixes[i]; ++i) {
		*sn0 = prefixes[i];
		for (*sn1 = 0; *sn1 <=    9; *sn1 += 1)
		for (*sn2 = 0; *sn2 <=   99; *sn2 += 1)
		for (*sn3 = 0; *sn3 <=    9; *sn3 += 1)
		for (*sn4 = 0; *sn4 <= 9999; *sn4 += 1) {
		    if (this->ssid != generate_upc_ssid(sn)) {
		        continue;
	        }

            generate_upc_psk_twg8x0(sn, psk);
            results.append(psk);
		}
	}

    return results;   
}
