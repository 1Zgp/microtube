/* $BEGIN_LICENSE

This file is part of Minitube.
Copyright 2009, Flavio Tordini <flavio.tordini@gmail.com>
Copyright 2018, Michał Szczepaniak <m.szczepaniak.000@gmail.com>

Minitube is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Minitube is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Minitube.  If not, see <http://www.gnu.org/licenses/>.

$END_LICENSE */

#include "datautils.h"

QString DataUtils::stringToFilename(const QString &s) {
    QString f = s;
    f.replace('(', '[');
    f.replace(')', ']');
    f.replace('/', ' ');
    f.replace('\\', ' ');
    f.replace('<', ' ');
    f.replace('>', ' ');
    f.replace(':', ' ');
    f.replace('"', ' ');
    f.replace('|', ' ');
    f.replace('?', ' ');
    f.replace('*', ' ');
    f = f.simplified();

    if (!f.isEmpty() && f.at(0) == '.') f = f.midRef(1).trimmed().toString();

    return f;
}

QString DataUtils::regioneCode(const QLocale &locale) {
    QString name = locale.name();
    int index = name.indexOf('_');
    if (index == -1) return QString();
    return name.right(index);
}

QString DataUtils::systemRegioneCode() {
    return regioneCode(QLocale::system());
}

uint DataUtils::parseIsoPeriod(const QString &isoPeriod) {
    uint days = 0, hours = 0, minutes = 0, seconds = 0;

    const int len = isoPeriod.length();
    int digitStart = -1;
    for (int i = 0; i < len; ++i) {
        const QChar c = isoPeriod.at(i);
        if (c.isDigit()) {
            if (digitStart == -1) digitStart = i;
        } else if (digitStart != -1) {
            if (c == 'H') {
                hours = QStringRef(&isoPeriod, digitStart, i - digitStart).toUInt();
            } else if (c == 'M') {
                minutes = QStringRef(&isoPeriod, digitStart, i - digitStart).toUInt();
            } else if (c == 'S') {
                seconds = QStringRef(&isoPeriod, digitStart, i - digitStart).toUInt();
            }
            digitStart = -1;
        }
    }

    uint period = ((days * 24 + hours) * 60 + minutes) * 60 + seconds;
    return period;
}

QString DataUtils::formatDateTime(const QDateTime &dt) {
    const qint64 seconds = dt.secsTo(QDateTime::currentDateTime());
    QString s;
    int f = 60;
    if (seconds < f) {
        s = QCoreApplication::translate("DataUtils", "Just now");
    } else if (seconds < (f *= 60)) {
        s = QCoreApplication::translate("DataUtils", "%n minute(s) ago", Q_NULLPTR, seconds / 60);
    } else if (seconds < (f *= 24)) {
        int n = seconds / (60 * 60);
        s = QCoreApplication::translate("DataUtils", "%n hour(s) ago", Q_NULLPTR, n);
    } else if (seconds < (f *= 7)) {
        int n = seconds / (60 * 60 * 24);
        s = QCoreApplication::translate("DataUtils", "%n day(s) ago", Q_NULLPTR, n);
    } else if (seconds < (f = 60 * 60 * 24 * 30)) {
        int n = seconds / (60 * 60 * 24 * 7);
        s = QCoreApplication::translate("DataUtils", "%n weeks(s) ago", Q_NULLPTR, n);
    } else if (seconds < (f = 60 * 60 * 24 * 365)) {
        int n = seconds / (60 * 60 * 24 * 30);
        s = QCoreApplication::translate("DataUtils", "%n month(s) ago", Q_NULLPTR, n);
    } else {
        s = dt.date().toString(Qt::DefaultLocaleShortDate);
    }
    return s;
}

QString DataUtils::formatDuration(uint secs) {
    uint d = secs;
    QString res;
    uint seconds = d % 60;
    d /= 60;
    uint minutes = d % 60;
    d /= 60;
    uint hours = d % 24;
    if (hours == 0) return res.sprintf("%d:%02d", minutes, seconds);
    return res.sprintf("%d:%02d:%02d", hours, minutes, seconds);
}
