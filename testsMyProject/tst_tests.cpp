#include <QtTest>
#include "../isVariablesDeclarationExist/functions.cpp"

// add necessary includes here

// Сравнение не по порядку а по содержимому списка
bool compareContentOfList(QStringList &obj1, QStringList &obj2){
    if(!(obj1.count() == obj2.count()))
        return false;

    for(int i = 0; i < obj1.count(); i++){
        if(!(obj2.contains(obj1[i]))){
            return false;
        }
    }
    return true;
}

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

    // тесты для createTypesList
    void test_createTypesList();
    void test_createTypesList_data();

    // тесты для createVariblesList
    void test_createVariblesList();
    void test_createVariblesList_data();

    // тесты для createListWithAnswers
    void test_createListWithAnswers();
    void test_createListWithAnswers_data();

    // тесты для writeAnswerInList
    void test_writeAnswerInList();
    void test_writeAnswerInList_data();

    // тесты для writeFile
    void test_writeFile();
    void test_writeFile_data();
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

// тесты для createTypesList
void tests::test_createTypesList(){
    // Входные данные
    QFETCH(QString, pathToTextOfProgramm);
    QFETCH(QString, pathToResult);

    QStringList textOfProgramm;
    QStringList resultList;
    readFile(pathToTextOfProgramm, textOfProgramm);
    readFile(pathToResult, resultList);
    QStringList actualList;
    // преобразование всего кода в строку
    // Преобразование всего кода программы в строку
    QString allCode;
    for(int i = 0; i < textOfProgramm.count(); i++){
        allCode.append(textOfProgramm[i]).append(' ');
    }
    // Выполнение программы
    createTypesList(allCode, actualList);

    // Сравнение результатов
    QCOMPARE(compareContentOfList(actualList, resultList) ,true);
}

void tests::test_createTypesList_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/createTypesList/");

    // входные результаты
    QTest::addColumn<QString>("pathToTextOfProgramm");
    QTest::addColumn<QString>("pathToResult");
    // тесты

    // Тест 1 : тест программы не содержит не одного объявления пользовательского типа
    QTest::newRow("1.Text without custom types")
            << QString(pathToHelpsFile).append("test_1/text.txt")
            << QString(pathToHelpsFile).append("test_1/result.txt");

    // Тест 2 : текст программы содержит структуры
    //(2 структуры: в 1 структура разбита на строки, 2 записана в строку)
    QTest::newRow("2.Text has structs")
            << QString(pathToHelpsFile).append("test_2/text.txt")
            << QString(pathToHelpsFile).append("test_2/result.txt");

    // Тест 3 : текст программы содержит только объединения
    //(2 объединения: в 1 объединение разбита на строки, 2 записана в строку)
    QTest::newRow("3.Text has union")
            << QString(pathToHelpsFile).append("test_3/text.txt")
            << QString(pathToHelpsFile).append("test_3/result.txt");

    // Тест 4 : текст программы содержит только перечисления
    //(2 перечисления: в 1 перечисление разбито на строки, 2 записана в строку)
    QTest::newRow("4.Text has enum")
            << QString(pathToHelpsFile).append("test_4/text.txt")
            << QString(pathToHelpsFile).append("test_4/result.txt");

    // Тест 5 : текст программы содержит структуры, объединения, перечисления
    QTest::newRow("5.Text has custom types")
            << QString(pathToHelpsFile).append("test_5/text.txt")
            << QString(pathToHelpsFile).append("test_5/result.txt");

    // Тест 6: текст программы содержит структуры, объединения, перечисления
    // ключевое слово(struct, union, enum) находит на отдельной строке
    QTest::newRow("6.Text has custom types parts of str in different terms")
            << QString(pathToHelpsFile).append("test_6/text.txt")
            << QString(pathToHelpsFile).append("test_6/result.txt");
}

// тесты для createVariblesList
void tests::test_createVariblesList(){
    // Входные данные
    QFETCH(QString, pathToTextOfProgramm);
    QFETCH(QString, pathToResult);

    QStringList textOfProgramm;
    QStringList resultList;
    readFile(pathToTextOfProgramm, textOfProgramm);
    readFile(pathToResult, resultList);
    QStringList actualList;

    // преобразование всего кода в строку
    // Преобразование всего кода программы в строку
    QString allCode;
    for(int i = 0; i < textOfProgramm.count(); i++){
        allCode.append(textOfProgramm[i]).append(' ');
    }

    // Выполнение программы
    createVariblesList(allCode, actualList);

    // Сравнение результатов

    QCOMPARE(compareContentOfList(actualList, resultList) ,true);
}

void tests::test_createVariblesList_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/createVariblesList/");

    // входные результаты
    QTest::addColumn<QString>("pathToTextOfProgramm");
    QTest::addColumn<QString>("pathToResult");

    // тесты

    // Тест 1 : простой тест без пользовательских типов
    QTest::newRow("1. Simple test")
            << QString(pathToHelpsFile).append("test_1/text.txt")
            << QString(pathToHelpsFile).append("test_1/result.txt");


    // Тест 2 : в тесте программы находятся множестевенные объявления
    QTest::newRow("2. Text has multiple variable declaration")
            << QString(pathToHelpsFile).append("test_2/text.txt")
            << QString(pathToHelpsFile).append("test_2/result.txt");

    // Тест 3 :  объявления переменных разбиты по разным строкам
    //(тип на одной, имя на другой, значение на другой)
    QTest::newRow("3. Declarations are divided into different terms")
            << QString(pathToHelpsFile).append("test_3/text.txt")
            << QString(pathToHelpsFile).append("test_3/result.txt");


    // Тест 4 : объявление находится в протипе / заголовке функции
    QTest::newRow("4. Declarations is into header/prototype of function")
            << QString(pathToHelpsFile).append("test_4/text.txt")
            << QString(pathToHelpsFile).append("test_4/result.txt");

    // Тест 5 : объявление находится вне функции
    QTest::newRow("5. Declarations is are outside of function")
            << QString(pathToHelpsFile).append("test_5/text.txt")
            << QString(pathToHelpsFile).append("test_5/result.txt");

    // Тест 6 : имя переменной совпадает с именем пользователского типа
    QTest::newRow("6. Name of variable is matches the name of the custom type")
            << QString(pathToHelpsFile).append("test_6/text.txt")
            << QString(pathToHelpsFile).append("test_6/result.txt");

    // Тест 7 : в тексте программы есть множественные объявления
    //(Частичная инициализация, инициализация всех перменных, без инициализации)
    QTest::newRow("7. Multiple variables declarations with initialization and without")
            << QString(pathToHelpsFile).append("test_7/text.txt")
            << QString(pathToHelpsFile).append("test_7/result.txt");

    // Тест 8 : объявляется массив и объявляется указатель
    QTest::newRow("8. Declare of pointer and array")
            << QString(pathToHelpsFile).append("test_7/text.txt")
            << QString(pathToHelpsFile).append("test_7/result.txt");
}

// тесты для createListWithAnswers
void tests::test_createListWithAnswers(){
    // Входные данные
    QFETCH(QString, pathToCode);
    QFETCH(QString, pathToVarList);
    QFETCH(QString, pathToExpectedRes);
    QStringList textOfProgramm;
    QStringList varList;
    QStringList expectedRes;
    readFile(pathToCode, textOfProgramm);
    readFile(pathToVarList, varList);
    readFile(pathToExpectedRes, expectedRes);

    // Выполнение функции
    QStringList actualRes = createListWithAnswers(textOfProgramm, varList);

    // Сравнение результатов
    QCOMPARE(compareContentOfList(actualRes, expectedRes), true);
}

void tests::test_createListWithAnswers_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/createListWithAnswers/");

    QTest::addColumn<QString>("pathToCode");
    QTest::addColumn<QString>("pathToVarList");
    QTest::addColumn<QString>("pathToExpectedRes");

    // тесты

    // Тест 1 : проверяемое имя было объявлено в закомментированной части кода
    QTest::newRow("1. The variable was declared in the commented part of code")
            << QString(pathToHelpsFile).append("test_1/text.txt")
            << QString(pathToHelpsFile).append("test_1/var.txt")
            << QString(pathToHelpsFile).append("test_1/result.txt");

    // Тест 2 : проверяемое имя было объявлено в строковой константе
    QTest::newRow("2. The variable was declared in the string const")
            << QString(pathToHelpsFile).append("test_2/text.txt")
            << QString(pathToHelpsFile).append("test_2/var.txt")
            << QString(pathToHelpsFile).append("test_2/result.txt");

    // Тест 3 :  проверяемое имя переменной не было объявлено,
    // но в программе есть одноименные пользовательские тип
    QTest::newRow("3. The variable wasn't declared but there is the same name of custom data type")
            << QString(pathToHelpsFile).append("test_2/text.txt")
            << QString(pathToHelpsFile).append("test_2/var.txt")
            << QString(pathToHelpsFile).append("test_2/result.txt");
}

// тесты для writeAnswerInList
void tests::test_writeAnswerInList(){
    // Входные данные

    QFETCH(QString, pathToChangeList);
    QFETCH(QString, pathToVarList);
    QFETCH(QString, pathToExpectedRes);
    QStringList changeList;
    QStringList varList;
    QStringList expectedRes;
    readFile(pathToChangeList, changeList);
    readFile(pathToVarList, varList);
    readFile(pathToExpectedRes, expectedRes);

    // Выполнение функции
    writeAnswerInList(changeList, varList);

    // Проверка результатов
    QCOMPARE(changeList == expectedRes, true);


}

void tests::test_writeAnswerInList_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/writeAnswerInList/");

    QTest::addColumn<QString>("pathToChangeList");
    QTest::addColumn<QString>("pathToVarList");
    QTest::addColumn<QString>("pathToExpectedRes");

    // Тест 1 :
    QTest::newRow("1. Simple test")
            << QString(pathToHelpsFile).append("test_1/list.txt")
            << QString(pathToHelpsFile).append("test_1/var.txt")
            << QString(pathToHelpsFile).append("test_1/result.txt");
}

// тесты для writeFile
void tests::test_writeFile(){

    QFETCH(QString, pathToWrite);
    QFETCH(QString, pathToList);
    QFETCH(QString, pathToExpectedRes);


    QStringList listToWrite;
    QStringList expectedRes;

    readFile(pathToList, listToWrite);
    readFile(pathToExpectedRes, expectedRes);

    QStringList actual;

    try {
        writeFile(pathToWrite, listToWrite);
        readFile(pathToWrite, actual);
    }  catch (QString message) {
        actual.append(message);
    }

    QCOMPARE(actual == expectedRes, true);
}

void tests::test_writeFile_data(){
    // путь к вспомогательным файлам
    QString pathToHelpsFile = PRO_FILE_PWD;
    pathToHelpsFile.append("/files/writeFile/");

    QTest::addColumn<QString>("pathToWrite");
    QTest::addColumn<QString>("pathToList");
    QTest::addColumn<QString>("pathToExpectedRes");

    // Тест 1 : запись информации в файл
    QTest::newRow("1. Simple test")
            << QString(pathToHelpsFile).append("test_1/actual.txt")
            << QString(pathToHelpsFile).append("test_1/text.txt")
            << QString(pathToHelpsFile).append("test_1/result.txt");

    // Тест 2 : путь где должен храниться файл был подан пустой путь
    QTest::newRow("2. Path is empty")
            << QString("")
            << QString(pathToHelpsFile).append("test_2/text.txt")
            << QString(pathToHelpsFile).append("test_2/result.txt");


    // Тест 3 : производится запись пустого файла
    QTest::newRow("3. File is empty")
            << QString(pathToHelpsFile).append("test_3/actual.txt")
            << QString(pathToHelpsFile).append("test_3/text.txt")
            << QString(pathToHelpsFile).append("test_3/result.txt");
}


QTEST_APPLESS_MAIN(tests)

#include "tst_tests.moc"
