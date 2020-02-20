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

#ifndef TWG8X0KEYGEN_H
#define TWG8X0KEYGEN_H
#include "Keygen.h"

class Twg8x0Keygen: public Keygen {
private:
    unsigned short int var;
    unsigned short int opt_alt_algo;
    
    quint32 prefixes_twg850[4] = { 913, 926, 939, 0 };
    quint32 prefixes_twg870[2] = { 955, 0 };
    quint32 *prefixes = NULL;
    quint32 ssid;

    quint32 generate_upc_ssid(quint32 *sn);
    void generate_upc_psk_twg8x0(quint32 *sn, char *psk);

	QVector<QString> & getKeys();
public:
	Twg8x0Keygen(QString ssid, QString mac, unsigned short int var);
	int getSupportState() const;
};

#endif //  TWG8X0KEYGEN_H
