#include <QtTest>
#include "../isVariablesDeclarationExist/functions.cpp"
// add necessary includes here

class tests : public QObject
{
    Q_OBJECT

public:
    tests();
    ~tests();

private slots:
    // тесты для readFile
    void test_readFile();
    void test_readFile_data();

    // тесты для checkingEnterVariables
    void test_checkingEnterVariables();
    void test_checkingEnterVariables_data();

    // тесты для getAndCheckImputDataFromFiles
    void test_getAndCheckImputDataFromFiles();
    void test_getAndCheckImputDataFromFiles_data();

    // тесты для deleteAllCommentsAndStringConstnts
    void test_deleteAllCommentsAndStringConstnts();
    void test_deleteAllCommentsAndStringConstnts_data();
};

tests::tests()
{

}

tests::~tests()
{

}


// тесты readFile
void tests::test_readFile(){
    QStringList actual;
    QFETCH(QString, path);
    QFETCH(QStringList,expectedRes);
    try {
        readFile(path, actual);
    }  catch (QString message) {
        actual.append(message);
    }

    QCOMPARE(actual == expectedRes, true);
}

void tests::test_readFile_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/readFile/");

    QTest::addColumn<QString>("path");
    QTest::addColumn<QStringList>("expectedRes");

    // Тест 1 : был подан на вход файл, который содержит в себе информацию
    QTest::newRow("1.Simple test")
            << QString(pathToHelpsFile).append("test_1.txt")
            << QStringList{"Hello world!", "Today is sunny day, isn't it."};
    // Тест 2 : был указан пустой путь
    QTest::newRow("2.Empty path")
            << QString("")
            << QStringList{"Error: Path to file is empty"};
    // Тест 3 : на вход был подан пустой файл
    QTest::newRow("3.Empty file")
            << QString(pathToHelpsFile).append("test_2.txt")
            << QStringList{};
    // Тест 4 : путь ведет на несуществующий файл
    QTest::newRow("4.File doesn't exist")
            << QString(pathToHelpsFile).append("test_3.txt")
            << QStringList{"Error: File doesn't exist"};
}


// тесты checkingEnterVariables
void tests::test_checkingEnterVariables(){
    // Входные данные
    QFETCH(QString, pathToVariablesList);
    QFETCH(QString, errorMes);
    QFETCH(bool, expectedRes);
    QStringList variablesList;
    readFile(pathToVariablesList, variablesList);

    // Выполнение функции
    QString actualMes = QString("");
    bool actual = false;
    try {
        actual = checkingEnterVariables(variablesList);
    }  catch (QString message) {
        actualMes = message;
    }
    QCOMPARE(actual, expectedRes);
    QCOMPARE(actualMes, errorMes);
}

void tests::test_checkingEnterVariables_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/checkingEnterVariables/");

    QTest::addColumn<QString>("pathToVariablesList");
    QTest::addColumn<QString>("errorMes");
    QTest::addColumn<bool>("expectedRes");

    // Тест 1 : на вход был подан списк имен переменных, все имена могут
    // являться переменными программы на языке Си
    QTest::newRow("1.Simple test")
            << QString(pathToHelpsFile).append("test_1.txt")
            << QString("")
            << true;
    // Тест 2 : ..., среди имен есть совпадение с ключевым словом
    QTest::newRow("2.There is Keyword")
            << QString(pathToHelpsFile).append("test_2.txt")
            << QString("Error: One of the variable names matches the keyword")
            << false;
    // Тест 3 : ..., среди имен переменных есть имя в котором есть недопустимые символ
    QTest::newRow("3.Variable can't exist")
            << QString(pathToHelpsFile).append("test_3.txt")
            << QString("Error: One of the variable names cannot exist")
            << false;
    // Тест 4 : ..., среди имен переменных есть имя которое начинается с цифры
    QTest::newRow("4.Variable starts from the number")
            << QString(pathToHelpsFile.append("test_4.txt"))
            << QString("Error: One of the variable names cannot exist")
            << false;
}


// тесты getAndCheckImputDataFromFiles
void tests::test_getAndCheckImputDataFromFiles(){
    // Входные данные
    QFETCH(QString, pathToCodeText);
    QFETCH(QString, pathToVariablesList);
    QFETCH(QString, pathToResultCodeText);
    QFETCH(QString, pathToResultVariablesList);
    QFETCH(QString, expectedErrorMessage);

    QStringList codeText;
    QStringList variablesList;
    QStringList expectedCodeText;
    QStringList expectedVariablesList;
    QString errorMessage = QString("");

    readFile(pathToResultCodeText, expectedCodeText);
    readFile(pathToResultVariablesList, expectedVariablesList);


    // Выполнение функции
    try {
        getAndCheckImputDataFromFiles(pathToCodeText, pathToVariablesList, codeText, variablesList);
    }  catch (QString message) {
        errorMessage = message;
    }

    // Проверка результатов
    QCOMPARE(codeText == expectedCodeText, true);
    QCOMPARE(variablesList == expectedVariablesList, true);
    QCOMPARE(errorMessage, expectedErrorMessage);
}

void tests::test_getAndCheckImputDataFromFiles_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/getAndCheckImputDataFromFiles/");
    // столбцы ...
    // путь к файлу с тектом проргаммы
    QTest::addColumn<QString>("pathToCodeText");
    // путь к файлу со списком имен переменных
    QTest::addColumn<QString>("pathToVariablesList");
    // путь к файлу с тектом программы, который получиться в результате выполнения функции
    QTest::addColumn<QString>("pathToResultCodeText");
    // список имен переменных , который получиться в результате выполнения функции
    QTest::addColumn<QString>("pathToResultVariablesList");
    // Сообщение об ошибке, которое может возникнуть в результате выполнения функции
    QTest::addColumn<QString>("expectedErrorMessage");

    // Тест 1 : на вход подается путь к тексту на языке Си и путь к именам
    // переменных, формат файла правильный, имена переменных допустимы
    QTest::newRow("1.Simple test")
            << QString(pathToHelpsFile).append("test_1/text.txt")
            << QString(pathToHelpsFile).append("test_1/varList.txt")
            << QString(pathToHelpsFile).append("test_1/resultText.txt")
            << QString(pathToHelpsFile).append("/test_1/resultVarList.txt")
            << QString("");

    // Тест 2 : на вход был подан файл отличный от .txt(файл с кодом)
    QTest::newRow("2.Wrong format CodeFile")
            << QString(pathToHelpsFile).append("test_2/text.exe")
            << QString(pathToHelpsFile).append("test_2/varList.txt")
            << QString(pathToHelpsFile).append("test_2/resultText.txt")
            << QString(pathToHelpsFile).append("test_2/resultVarList.txt")
            << QString("Error: File with code in the wrong format\n");
    // Тест 3 : на вход был подан файл отличный от .txt(файл со списком имен переменных)
    QTest::newRow("3.Wrong format variablesList")
            << QString(pathToHelpsFile).append("test_3/text.txt")
            << QString(pathToHelpsFile).append("test_3/varList.cpp")
            << QString(pathToHelpsFile).append("test_3/resultText.txt")
            << QString(pathToHelpsFile).append("test_3/resultVarList.txt")
            << QString("Error: File with variables in the wrong format\n");
    // Тест 4 : на вход был подан путь к файлу который не существует
    QTest::newRow("4.One of files doesn't exist")
            << QString(pathToHelpsFile).append("test_4/text1.txt")
            << QString(pathToHelpsFile).append("test_4/varList.txt")
            << QString(pathToHelpsFile).append("test_4/resultText.txt")
            << QString(pathToHelpsFile).append("test_4/resultVarList.txt")
            << QString("Error: File doesn't exist");
    // Тест 5 : на вход был подан файл с именами переменными, который содержит
    // имя идентичное ключевому слову
    QTest::newRow("5.One name of variables is keyword")
            << QString(pathToHelpsFile).append("test_5/text.txt")
            << QString(pathToHelpsFile).append("test_5/varList.txt")
            << QString(pathToHelpsFile).append("test_5/resultText.txt")
            << QString(pathToHelpsFile).append("test_5/resultVarList.txt")
            << QString("Error: One of the variable names matches the keyword");
}


// тесты deleteAllCommentsAndStringConstnts
void tests::test_deleteAllCommentsAndStringConstnts(){
    // Входные данные
    QFETCH(QString, pathToCodeText);
    QFETCH(QString, pathToResultCodeText);

    QStringList textOfProgramm;
    QStringList resultText;

    readFile(pathToCodeText, textOfProgramm);
    readFile(pathToResultCodeText, resultText);

    // Выполнение функции
    deleteAllCommentsAndStringConstnts(textOfProgramm);

    // Проверка результатов
    QCOMPARE(textOfProgramm == resultText, true);
}

void tests::test_deleteAllCommentsAndStringConstnts_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/deleteAllCommentsAndStringConstnts/");

    // столбцы ...
    // путь к тексту программы на языке Си
    QTest::addColumn<QString>("pathToCodeText");
    // путь к тесту программы на языке Си без комментариев и строковых констант
    QTest::addColumn<QString>("pathToResultCodeText");

    // Тесты
    // Тест 1 : тест программы не содержит комментариев и строковых констант
    QTest::newRow("1.Program text doesn't have comment and string consts")
            << QString(pathToHelpsFile).append("test_1/text.txt")
            << QString(pathToHelpsFile).append("test_1/result.txt");
    // Тест 2 :  код содержит только однострочные комментарии
    // (комментарий в начале строки)
    QTest::newRow("2.Program text have oneline comment in the start of str")
            << QString(pathToHelpsFile).append("test_2/text.txt")
            << QString(pathToHelpsFile).append("test_2/result.txt");

    // Тест 3 : код содержит только однострочные комментарии
    // (комментарий в конце строки)
    QTest::newRow("3.Program text have oneline comment in the end of str")
            << QString(pathToHelpsFile).append("test_3/text.txt")
            << QString(pathToHelpsFile).append("test_3/result.txt");

    // Тест 4 : код содержит только многострочные коментарии
    //(комментарий начиается в начале строки и заканчивается на той же строке)
    QTest::newRow("4.Program text have multiline comment start and end in one str")
            << QString(pathToHelpsFile).append("test_4/text.txt")
            << QString(pathToHelpsFile).append("test_4/result.txt");

    // Тест 5 : код содержит только многострочные коментарии
    //(комментарий начиается в начале строки и конец на другой строке )
    QTest::newRow("5.Program text have multiline comment start in one str and end in another ")
            << QString(pathToHelpsFile).append("test_5/text.txt")
            << QString(pathToHelpsFile).append("test_5/result.txt");

    // Тест 6 : код содержит только многострочные коментарии
    //(комментарий начиается в середине строки и конец на той же строке чуть дальше середины )
    QTest::newRow("6.Program text have multiline comment start and end in the middel of str")
            << QString(pathToHelpsFile).append("test_6/text.txt")
            << QString(pathToHelpsFile).append("test_6/result.txt");

    // Тест 7 : код содержит только многострочные коментарии
    //(комментарий начиается в конце строки и конец на другой строке )
    QTest::newRow("7.Program text have multiline comment start in the end of str and end of comment in other str")
            << QString(pathToHelpsFile).append("test_7/text.txt")
            << QString(pathToHelpsFile).append("test_7/result.txt");

    // Тест 8 : код содержит строковую константу
    // (начало строковой константы находится в начале строки)
    QTest::newRow("8.Text have str const in the start of the str ")
            << QString(pathToHelpsFile).append("test_8/text.txt")
            << QString(pathToHelpsFile).append("test_8/result.txt");

    // Тест 9 :код содержит строковую константу
    // (начало строковой константы находится в середине строки)
    QTest::newRow("9.Text have str const in the middle of the str ")
            << QString(pathToHelpsFile).append("test_9/text.txt")
            << QString(pathToHelpsFile).append("test_9/result.txt");

    // Тест 10 : код содержит строковую константу
    // (внутри строковой константы находится завершающая эту константу
    // escape последовательность)
    QTest::newRow("10.Text have str const and this const str have /\" ")
            << QString(pathToHelpsFile).append("test_10/text.txt")
            << QString(pathToHelpsFile).append("test_10/result.txt");

    // Тест 11 : код содержит строковую константу
    // (внутри строковой константы находится последовательность похожая
    // на начало однострочного комментария)
    QTest::newRow("11.Text have str const and this const str have // ")
            << QString(pathToHelpsFile).append("test_11/text.txt")
            << QString(pathToHelpsFile).append("test_11/result.txt");

    // Тест 12 : код содержит как комментарии так и строковые константы
    QTest::newRow("12.Text have const str and comments")
            << QString(pathToHelpsFile).append("test_12/text.txt")
            << QString(pathToHelpsFile).append("test_12/result.txt");

}




QTEST_APPLESS_MAIN(tests)

#include "tst_tests.moc"
