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

/**
    \brief Создание списка с ответом для каждой переменной, объявлена ли она в коде программы на языке Си
    \param[in] sourceCode - код программы на языке Си
    \param[in] namesOfVariables - имена переменных для которых нужно определить, объявлены ли они
    \return список имен переменных с ответами для каждой, объявлены ли они в коде программы на языке Си
*/
QStringList createListWithAnswers(QStringList sourceCode, QStringList namesOfVariables){
    // Удаление всех комментариев и строчных констант из текста программы
    deleteAllCommentsAndStringConstnts(sourceCode);

    // Преобразование всего кода программы в строку
    QString allCode;
    for(int i = 0; i < sourceCode.count(); i++){
        allCode.append(sourceCode[i]).append(' ');
    }

    // Создание списка всех переменных объявленных в коде программы на языке Си
    // Создание списка всех переменных объявленных в коде программы на языке Си
    QStringList progVariablesList;
    createVariblesList(allCode, progVariablesList);

    // Создание списка переменных с ответами на вопрос, объявлены ли эти переменные в коде проргаммы
    QStringList answerList = namesOfVariables;
    writeAnswerInList(answerList, progVariablesList);

    return answerList;
}

/**
    \brief Удаление всех комментариев и строковых констант из кода программы на языке Си
    \param[in,out] sourceCode - текст программы на языке Си
*/
void deleteAllCommentsAndStringConstnts(QStringList &sourceCode){

    // Текущая строка
    int curStr = 0;
    // Последний символ в строке на котором остановилась функция проверки
    int curPosInStr = 0;

    int textCountStr = sourceCode.count();  // Кол-во строк в тексте програмы

    // Пока не дошел до конца текста программы
    while (curStr < textCountStr) {
        // Длина текущей строки(с нулевым символом)
        int curStrLength = sourceCode[curStr].length();
        // Пока не дошел до предпоследнего символа строки
        while (curPosInStr < curStrLength - 1) {
            // Если была встречена последовательность символов начинающиая однострочный комментарий
            if( sourceCode[curStr][curPosInStr] == '/' &&
                    sourceCode[curStr][curPosInStr + 1] == '/'){
                // Удаляю все, все что было после первого символа начала однострочного комментария
                sourceCode[curStr].remove(curPosInStr, curStrLength - curPosInStr);
                curStrLength = sourceCode[curStr].length();
            }
            else
                // Если была встречена последовательность символов начинающая многострочный комментарий
                if( sourceCode[curStr][curPosInStr] == '/' &&
                        sourceCode[curStr][curPosInStr + 1] == '*'){
                    // Тогда ищу последовательность символов закрывающих многострочный комментарий
                    int closeMultiCommentsSimvols = sourceCode[curStr].indexOf("*/", curPosInStr + 2);
                    // Если последовательность не найдена на текущей строке
                    if(closeMultiCommentsSimvols == -1){
                        //тогда я очищаю все что было на текущей строке с последовательности символов начинающих
                        // многострочных комментарий и до конца текущей строки
                        sourceCode[curStr].remove(curPosInStr, curStrLength - curPosInStr);
                        // ищу символ на следующей строке
                        curStr++;
                        curPosInStr = 0;
                        closeMultiCommentsSimvols = sourceCode[curStr].indexOf("*/");

                        // Пока закрывающая последовательность не найдена и пока текущая строка не стала последней
                        while (closeMultiCommentsSimvols == -1 && curStr < textCountStr) {
                            // Удаляю строку прошлую строку, в которой не была найдена последовательность
                            // символов закрывающий многострочный комментарий
                            sourceCode.erase(sourceCode.begin() + curStr);
                            textCountStr--;
                            // Ищу последовательность на след. строчке
                            closeMultiCommentsSimvols = sourceCode[curStr].indexOf("*/");
                        }
                        // Как была найдена последовательность, удаляю все что было до этой последовательности
                        sourceCode[curStr].remove(0, closeMultiCommentsSimvols + 2);
                    }
                    else{
                        // Удаляю  последовательность с начала многострочного комментария и до его конца
                        sourceCode[curStr].remove(curPosInStr, closeMultiCommentsSimvols + 2 - curPosInStr);
                    }
                    curStrLength = sourceCode[curStr].length();
                    textCountStr = sourceCode.count();
                }
                else
                    // Если был встречен символ начинающий последовательность строковой константы
                    if(sourceCode[curStr][curPosInStr] == '\'' || sourceCode[curStr][curPosInStr] == '\"'){
                        int endOfConst = curPosInStr + 1;
                        // пока не дойду до концап строки или конца строковой константы
                        while (endOfConst < curStrLength && (sourceCode[curStr][endOfConst] != '\''
                                                             && sourceCode[curStr][endOfConst] != '\"')) {
                            // Если был встречен символ экранирования
                            if(sourceCode[curStr][endOfConst] == '\\'){
                                // перехожу к следующему символу
                                endOfConst++;
                            }
                            // перехожу к следующему символу
                            endOfConst++;
                        }
                        // Удаляю последовательность с начала строковой константы и до её конца
                        sourceCode[curStr].remove(curPosInStr, endOfConst - curPosInStr + 1);
                        curStrLength = sourceCode[curStr].length();
                    }
                    else
                        // Иду дальше по строке
                        curPosInStr++;

        }
        // Перехожу к след. строке
        curStr++;
        curPosInStr = 0;
    }
    sourceCode.removeAll("");
}


/**
    \brief Создание списка имен всех перменных объявленных в тексте программы на языка Си
    \param[in] sourceCode - код программы на языке Си
    \param[out] creatingList - список имен переменных
*/
void createVariblesList(QString sourceCode, QStringList &creatingList){
    // Исходные типы данных(в соответствии с ТЗ)
    QStringList dataTypes{"char", "int", "float", "double"};

    // Дополняю текущие типы данных, пользовательскими
    createTypesList(sourceCode, dataTypes);

    // Деление строчки из кода на действия
    QRegExp splitReg("[\\{|\\;|\\}]", Qt::CaseSensitive, QRegExp::RegExp2);
    // Разделитель - "{", ";", "}"
    QStringList codeList = sourceCode.split(splitReg);

    QRegExp myReg("",Qt::CaseSensitive, QRegExp::RegExp2);
    // для каждого типа данных
    for(int i = 0; i < dataTypes.count(); i++){
        // Регулярное выражение, которое захватывает все объявление переменных для текущего типа  данных
        // в коде программы(кроме множественных объявлений)
        myReg.setPattern(QString("\\b").append(dataTypes[i]).append("[\\s|\\*|\\(]+([a-z|A-Z|_]\\w*)[\\s|\\)]*[\\;|\\,|\\[|\\=|\\{]"));
        int lastFind = myReg.indexIn(sourceCode, 0);
        while (lastFind != -1) {
            QStringList lastStrFind = myReg.capturedTexts();
            lastFind += myReg.matchedLength();
            creatingList.append(lastStrFind[1]);
            lastFind = myReg.indexIn(sourceCode, lastFind);
        }

        // Решение для множественного объявления
        // для каждой разделенной строчки
        for(int j = 0; j < codeList.count(); j++){
            // ищу объявление переменной с типом
            int lastFind = myReg.indexIn(codeList[j], 0);
            // ищу первую открытую скобку в строке
            int lastPosOpenBracket = codeList[j].indexOf('(');

            // если было найдено объявление с типом
            //если скобка была найдена и она находиться после найденного объявления
            // или скобка не была найдена вообще
            if((lastFind != -1) &&
                    (((lastPosOpenBracket != -1) &&
                      (lastFind < lastPosOpenBracket)) || (lastPosOpenBracket == -1))){
                // тогда разделяю строку по запятым
                QStringList sepString = codeList[j].split(",");
                QRegExp variableName("[\\*|\\(|\\s]*([a-z|A-Z|_]\\w*)[\\s|\\)]*", Qt::CaseSensitive, QRegExp::RegExp2);
                // для каждой разделенной строчки
                for(int k = 1; k < sepString.count(); k++){
                    // ищу совпадение с регулярным выражением
                    variableName.indexIn(sepString[k]);
                    QStringList ValNameFind = variableName.capturedTexts();
                    creatingList.append(ValNameFind[1]);
                }
            }
        }
    }
    // Удаляю копии из списка имен переменных
    creatingList.removeDuplicates();
}



/**
    \brief Создание списка всех пользовательских типов переменных
    \param[in] sourceCode - текст программы на языке Си
    \param[in,out] creatingList - создаваемый список всех пользовательских типов переменых
*/
void createTypesList(QString sourceCode, QStringList &creatingList){
    // Ругулярное выражение для обнаружения пользовательских типов
    QRegExp myReg("\\b(?:struct|union|enum)\\s+([a-z|A-Z|_]\\w*)", Qt::CaseSensitive, QRegExp::RegExp2);

    // Первое нахождение совпадения c определением пользовательского типа
    int lastFind = myReg.indexIn(sourceCode, 0);

    // Пока существуют определения пользовательского типа в строке кода
    while ( lastFind != -1) {
        // Запоминаю захваченные регулярным выражением строки
        QStringList lastStrFind = myReg.capturedTexts();
        // Иду дальше по строке
        lastFind += myReg.matchedLength();
        // Добавляю в список имен типов захваченные регулярным выражением строки
        creatingList.append(lastStrFind[1]);
        // Ищу совпадения с регулярным выражением
        lastFind = myReg.indexIn(sourceCode, lastFind);
    }
}


/**
    \brief Функция для записи результата функции в список variablesList
    \param[in,out] variablesList - список имен переменных, для которых нужно проверить объявлены ли они в коде программы на языке Си
    \param[in] createdList - список имен переменных, найденных в коде программы на языке Си
*/
void writeAnswerInList(QStringList &variablesList, QStringList const &createdList){
    // Для каждого имени переменной которое нужно проверить
    for(int i = 0; i < variablesList.count(); i++){
        // Если строчка из имен переменных есть в списке имен переменных найденных в коде
        if(createdList.contains(variablesList[i])){
            // То фиксирую что эта переменная объявлена в этом коде
            variablesList[i].append(" - true");
        }
        else{
            // То фиксирую что эта переменная не объявлена в этом коде
            variablesList[i].append(" - false");
        }
    }
}
