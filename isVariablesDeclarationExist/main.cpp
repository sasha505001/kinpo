#include "headers.h"

int main(int argc, char *argv[])
{
    try {
    // Часть необходимая для ввода
    QTextStream cin(stdin);

    // Путь к файлу с кодом
    QString pathToCodeFile;

    // Путь к файлу с переменными
    QString pathToVariablesFile;

    // передача параметров через командную строку
    // Если параметры были переданы через командную строку
    if(argc == 3){
        // передача через параметры командной строки
        // путь к файлу с кодом
        pathToCodeFile = argv[1];
        // путь к файлу с именами переменных
        pathToVariablesFile = argv[2];
    }
    else{
        // запрос на ввод пути к файлу с кодом
        printf("Enter the path to the code file:\n");
        cin >> pathToCodeFile;
        // запрос на ввод пути к файлу с переменными
        printf("Enter the path to the variable file:\n");
        cin >> pathToVariablesFile;
    }
    // чтение файлов и их проверка

    // Решение задачи(создание списка с ответами объявлена ли переменная в программе на языке Си)

    // Запись результатов в файл
    }  catch (const QString message) {

    }

}

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

    // Чтение из файлов

    // Удаление пустых строчек в коде программы

    // Проверка имен переменных
}
