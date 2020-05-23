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



QTEST_APPLESS_MAIN(tests)

#include "tst_tests.moc"
