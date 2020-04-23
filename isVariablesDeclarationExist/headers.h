#ifndef HEADERS_H
#define HEADERS_H

#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <string>
#include <QObject>
#include <QFileInfo>
#include <QTextCodec>
#include <QDataStream>
#include <QDir>
#include <conio.h>
#include <QDate>

void getAndCheckImputDataFromFiles(QString &pathToCodeFile, QString &pathToVariablesFile,
                          QStringList &textOfProgramm, QStringList &namesOfVariables);


#endif // HEADERS_H
