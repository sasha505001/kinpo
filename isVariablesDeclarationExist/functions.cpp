#include "headers.h"

/**
    \brief Чтение данных из командной строки, их проверка, чтение из файлов и проверка данных из файла переменных
    \param[in] pathToCodeFile - путь к файлу с текстом программы на языке Си
    \param[in] pathToVariablesFile - путь к файлу с переменными
    \param[out] textOfProgramm - текст программы на языке Си
    \param[out] namesOfVariables - имена переменных, которые нужно проверить
    \throw Если файл с кодом не .txt
    \throw Если файл с переменным не .txt
*/
void getAndCheckImputDataFromFiles(QString &pathToCodeFile, QString &pathToVariablesFile,
                          QStringList &textOfProgramm, QStringList &namesOfVariables){

    // Проверка расширения обоих конечных файлов указанных в пути
    // Проверка пути к файлу с кодом
    int lastPoint = pathToCodeFile.lastIndexOf('.');
    // Файл с кодом может иметь расшерения ".cpp" и ".txt"
    if(!(pathToCodeFile.mid(lastPoint) == ".txt")){
        throw QString("Error: File with code in the wrong format\n");
    }

    // Проверка пути к файлу с переменными
    lastPoint = pathToVariablesFile.lastIndexOf('.');
    // Файл с именами переменных может иметь тип расшерения ".txt"
    if(!(pathToVariablesFile.mid(lastPoint) == ".txt")){
        throw QString("Error: File with variables in the wrong format\n");
    }

    // Чтение из файлов

    // Удаление пустых строчек в коде программы

    // Проверка имен переменных
}

