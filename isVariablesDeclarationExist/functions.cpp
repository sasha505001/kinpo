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
    // Чтение текста программы из кода
    readFile(pathToCodeFile, textOfProgramm);
    // Чтение файла с именами переменных для которых нужно опеределить объявлены ли они в коде
    readFile(pathToVariablesFile, namesOfVariables);

    // Удаление пустых строчек в коде программы
    textOfProgramm.removeAll("");

    // Проверка имен переменных
    checkingEnterVariables(namesOfVariables);
}

/**
    \brief Функция для чтения из файла
    \param[in] path - полный путь к файлу
    \param[out] text - спиок который будет хранить все содержимое файла
    \return было ли чтение проведено успешно
    \throw Файд не существует
    \throw Путь к файлу пустой
*/
bool readFile(const QString &path, QStringList &text){
    // Если путь к файлу не пустой
    if(!path.isEmpty()){
        QFile file(path);
        // Если файл успешно открылся в режиме чтения
        if(file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);
            // Считываем файл строка за строкой
            for(int i = 0; !in.atEnd(); i++){
                QString line = in.readLine();
                text.append(line);
            }
            return true;
        }
        else {
            throw QString("Error: File doesn't exist");
            return false;
        }
    }
    else{
        throw QString("Error: Path to file is empty");
        return false;
    }
}

/**
    \brief Функция проверки входных данных(имен переменных)
    \param[in] variablesList - список имен всех переменных
    \return могут ли все строчки из списка быть именами переменных
    \throw Переменная не может существовать
    \throw Совпадение одного из имен перменных с ключевым словом
*/
bool checkingEnterVariables(const QStringList variablesList){
    // Проверка не пустой ли файл был получен
    if(variablesList.count() == 0){
        throw QString("Error: The variable file is empty");
        return false;
    }
    // Проверка на совпадение файла с ключевыми словами

    // Список ключевых слов в Си
    QStringList keywords{"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                      "enum", "extern", "float", "for", "goto", "if", "inline", "switch", "long", "register",
                      "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
                      "union", "unsigned", "void", "volatile", "while"};

    // Для каждого имени переменной
    for(int i = 0; i < variablesList.count(); i++){
        // Может текущая строка являться именем переменной
        QRegExp regForVariable("\\s*[a-z|A-Z|_]\\w*\\s*", Qt::CaseSensitive, QRegExp::RegExp2);
        if(!regForVariable.exactMatch(variablesList[i])){
            throw QString("Error: One of the variable names cannot exist");
            return false;
        }
        // Если имя переменной является ключевым словом
        if(keywords.contains(variablesList[i])){
            throw QString("Error: One of the variable names matches the keyword");
            return false;
        }
    }
    return true;
}
