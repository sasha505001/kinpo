#include "functions.cpp"

int main(int argc, char *argv[])
{
    try {

        // Часть необходимая для ввода
        QTextStream cin(stdin);

        // Путь к файлу с кодом
        QString pathToCodeFile;

        // Путь к файлу с переменными
        QString pathToVariablesFile;

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

        // Текст программы
        QStringList textOfProgramm;

        // Список переменных
        QStringList namesOfVariables;

        // Чтение данных из файлов и их проверка
        getAndCheckImputDataFromFiles(pathToCodeFile, pathToVariablesFile, textOfProgramm, namesOfVariables);

        // Решение задачи(создание списка с ответами объявлена ли переменная в программе на языке Си)
        QStringList answerList = createListWithAnswers(textOfProgramm, namesOfVariables);

        // Запись результатов в файл
        writeResultsInFile(answerList);
        printf("Solution was created. Answer is located in folder \"Results\".");

    }  catch (const QString message) {

        QStringList answerList{message};

        // Запись ошибки в файл
        writeResultsInFile(answerList);

        printf("ERROR! Error message is located in folder \"Results\".");
    }
}

