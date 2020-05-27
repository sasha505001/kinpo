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

//============================PROTOTIPS=================================

/// Чтение данных

/// Чтение данных из файлов и проверка данных из файла переменных
void getAndCheckImputDataFromFiles(QString &pathToCodeFile, QString &pathToVariablesFile,
                          QStringList &textOfProgramm, QStringList &namesOfVariables);
/// чтение текста из файла
bool readFile(const QString &path, QStringList &text);

/// Проверка входных данных, прочитанных из файла с переменными(чтобы имена переменных
/// не совпадали с ключенвыми словами и чтобы они могли являться переменными)
bool checkingEnterVariables(const QStringList variablesList);

#endif // HEADERS_H
