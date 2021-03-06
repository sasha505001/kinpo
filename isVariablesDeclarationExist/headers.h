/**
\file
\brief Данный файл содержит все заголовки
*/
#ifndef HEADERS_H
#define HEADERS_H

//=============================INCLUDES================================
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

/// Решение поставленной задачи

/// Создание списка с ответом для каждой переменной, объявлена ли она в коде программы на языке Си
QStringList createListWithAnswers(QStringList sourceCode, QStringList namesOfVariables);
/// Удаление всех комментариев и всех строковых констант из кода на языке Си
void deleteAllCommentsAndStringConstnts(QStringList &sourceCode);
/// Создать список имен переменных объявленных переменных
void createVariblesList(QString sourceCode, QStringList &creatingList);
/// Дополнить существующий список имен типов, оглашенных в ТЗ, пользовательскими типами
void createTypesList(QString sourceCode, QStringList &creatingList);
/// Найти совпадения из созданного списка имен переменных и име переменных для которых
/// нужно определить, объявлены ли они в коде
void writeAnswerInList(QStringList &variablesList, QStringList const &createdList);

/// Вывод результата

/// Запись результатов в файл
void writeResultsInFile(QStringList &list);
/// запись текста в файл
bool writeFile(const QString &path, QStringList &text);


#endif // HEADERS_H
