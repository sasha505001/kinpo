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
}

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


