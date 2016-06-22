#ifndef COMPILER_H
#define COMPILER_H

#include <QMainWindow>
#include <string>
#include <QRegExp>
#include <QStringList>
#include <vector>
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
class Compiler
{
public:
    Compiler(std::vector<std::string> &vec);

  void GetLexem();
  void GetIndTable();
  void Insert_table();
  bool SynstaxAnalis();
  bool BodyAnaliz();
  QStringList GetError();
  void GetPostfiksForm(int);
  void StartASMProgram();
  void WriteDataSeg();
  void GetPostfiksFormLogicFun(int);
  void GenericLogic();
  void GenericArifmetic();
  void Translator();
  void GetStatoperation(int);
  void IF_GOTO(int);


private:
  enum LexemType       //
    {	Name,             // Назва програми
        Data,             // Оголошення змінних
        INTEGER16,        // short
        number,           // число
        Body,             // Початок програми
        End,              // Кінець програми
        Input,            //Оператор вводу
        Output,           //Оператор виводу
        NameProg,
        if_,          // Умовний перехід
        goto_,            // Безумовний перехід
        inc,              // ++
        dec,              // --
        Mul,              // **
        Div,              // /
        Mod,              // %
        equ,              // eg ==
        notequ,           // ne !=
        le,               // <=
        ge,               // >=
        not_,             // not !!
        and_,             // &&
        or_,              // ||
        EndGroup,         // ;
        ident,            // Ідентифікатор
        koma,
        doriv,
        var,
        lable,
        condition,
        LeftBraket,       // (
        RightBraket,      // )
        unknow,
        null//
    };
     struct Lexem
    {
        char name[50];
        int value;
        LexemType type;
        int line;
    };


     struct Table_iD
     {
         char name[50];
         int value;
     };

     Lexem lexema;
     Table_iD table_id;
     QStringList roster_error;
     vector<Lexem> table_lexema;
     vector<string> program_text;
     vector<Table_iD> IDTable_lexema;
     bool BodyError;
     bool error;
     ofstream file_out;
     string name_temp; // змінна для того, щоб можна було створити файл з назвою програми.
     string temp;
     vector<string> postfix_lg;
     vector <string> postfix;
     int zamin;
     bool setlog;
      char* line;
      int Left_Coutn;
      int Right_Count;


};

#endif // COMPILER_H
