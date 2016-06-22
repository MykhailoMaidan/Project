#include "compiler.h"

Compiler::Compiler(std::vector<std::string> &vec)
{
program_text.insert(program_text.begin(),vec.begin(), vec.end());
error=false;
  line = new char[10];
   Left_Coutn=0;
   Right_Count=0;
}
void Compiler::GetLexem()
{
    char* line_code = new char[100];
    memset(line_code,0,100);
    for(unsigned int i=0; i< program_text.size(); i++)
    {
        string temp=program_text[i];
        strcpy(line_code,temp.c_str());
        char* point=strtok(line_code," ");
        while(point!=NULL)
        {
    if(!strcmp(point,"Name")) //Перевірка на ім'я програми.
        {
                    strcpy(lexema.name,"Name");
                    lexema.type=Name;
                    lexema.value=0;
                    lexema.line=i;
                    table_lexema.push_back(lexema);
                    point=strtok(NULL," ");
       if(point!=NULL)
       {
                    strcpy(lexema.name,point);
                    lexema.line=i;
                    lexema.value=0;
                    lexema.type=NameProg;
                    table_lexema.push_back(lexema);
       }
       else
       {
                    strcpy(lexema.name,"unknow");
                    lexema.type=unknow;
                    lexema.value=0;
                    lexema.line=i;
                    table_lexema.push_back(lexema);

       }
    }

    else if(!strcmp(point, "Data")) //Первірка на оголошення сегменту даних.
     {

                    strcpy(lexema.name,"Data");
                    lexema.line=i;
                    lexema.type=Data;
                    lexema.value=0;
                    table_lexema.push_back(lexema);
     }
    else if(!strcmp(point,"INTEGER16"))
     {
                    strcpy(lexema.name,"INTEGER16");
                    lexema.line=i;
                    lexema.type=INTEGER16;
                    lexema.value=0;
                    table_lexema.push_back(lexema);



     }
    else  if(isdigit(*point))
     {

        if(point[strlen(point)-1]==',')
        {
                     char* temp=new char[strlen(point)];
                     strncpy(temp,point,strlen(point)-1);
                     strcpy(lexema.name,"number");
                     lexema.value=atoi(point);
                     lexema.line=i;
                     lexema.type=number;
                     table_lexema.push_back(lexema);
                     strcpy(lexema.name, ",");
                     lexema.line=i;
                     lexema.type=koma;
                     lexema.value=0;
                     table_lexema.push_back(lexema);
}
                     else
                     {
                     strcpy(lexema.name,"number");
                     lexema.value=atoi(point);
                     lexema.line=i;
                     lexema.type=number;
                     table_lexema.push_back(lexema);
                     }



     }
    else if(point[strlen(point)]==',')
     {
                    strcpy(lexema.name,",");
                    lexema.type=koma;
                    lexema.value=0;
                    lexema.line=i;
                    table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"::=")==0)
     {
                    strcpy(lexema.name,"::=");
                    lexema.type=doriv;
                    lexema.value=0;
                    lexema.line=i;
                    table_lexema.push_back(lexema);
     }
    else if(point[0]=='_')
     {
        if(point[strlen(point)-1]==',')

        {
                     char* temp=new char[strlen(point)];
                     memset(temp,0,strlen(point));
                     strncpy(temp,point,strlen(point)-1);
                     memset(lexema.name,0,50);
                     strcpy(lexema.name,temp);
                     lexema.type=var;
                     lexema.line=i;
                     lexema.value=0;
                     table_lexema.push_back(lexema);
                     strcpy(lexema.name, ",");
                     lexema.line=i;
                     lexema.type=koma;
                     lexema.value=0;
                     table_lexema.push_back(lexema);
        }
                     else
                     {
                      strcpy(lexema.name,point);
                      lexema.type=var;
                      lexema.line=i;
                      lexema.value=0;
                      table_lexema.push_back(lexema);

                     }



    }
    else if(strcmp(point,"Body")==0)
     {
                     strcpy(lexema.name, point);
                     lexema.type=Body;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, "End")==0)
     {
                     strcpy(lexema.name, "End");
                     lexema.type=End;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);

     }
    else if(strcmp(point,"IF")==0)
     {
                     strcpy(lexema.name,"IF");
                     lexema.type=if_;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);


     }
    else if(strcmp(point,"Eg")==0)
     {
                     strcpy(lexema.name,"Eg");
                     lexema.type=equ;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"Ne")==0)
     {
                     strcpy(lexema.name,"Ne");
                     lexema.type=notequ;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"Le")==0)
     {
                     strcpy(lexema.name,"Le");
                     lexema.type=le;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
    }
    else if(strcmp(point,"Ge")==0)
     {
                     strcpy(lexema.name,"Ge");
                     lexema.type=ge;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"GOTO")==0)
     {
                     strcpy(lexema.name,"GOTO");
                     lexema.type=goto_;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }   
    else if(strcmp(point, "++")==0)
     {
                     strcpy(lexema.name,"++");
                     lexema.type=inc;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, "--")==0)
     {
                     strcpy(lexema.name,"--");
                     lexema.type=dec;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, "Mul")==0)
     {
                     strcpy(lexema.name, "*");
                     lexema.type=Mul;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"Mod")==0)
     {
                     strcpy(lexema.name, "Mod");
                     lexema.type=Mod;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, "Div")==0)
     {
                     strcpy(lexema.name,"Div");
                     lexema.type=Div;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"||")==0)
     {
                     strcpy(lexema.name,"||");
                     lexema.type=or_;
                     lexema.line=i;
                     lexema.value=0;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, "&&")==0)
     {
                     strcpy(lexema.name, "&&");
                     lexema.type=and_;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"!!")==0)
     {
                     strcpy(lexema.name, "!!");
                     lexema.type=not_;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, ";")==0)
     {
                     strcpy(lexema.name,";");
                     lexema.type=EndGroup;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"/*")==0)
     {
                     point=strtok(NULL," ");
     }
    else if(strcmp(point,"*/")==0)
    {
                     point=strtok(NULL," ");
    }
    else if(point[0]=='@')
     {
                     strcpy(lexema.name,point);
                     lexema.type=lable;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point,"Output")==0)
     {
                     strcpy(lexema.name,point);
                     lexema.value=0;
                     lexema.line=i;
                     lexema.type=Output;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, "Input")==0)
     {               strcpy(lexema.name,point);
                     lexema.type=Input;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
     }
    else if(strcmp(point, "(")==0)
     {
                     strcpy(lexema.name,point);
                     lexema.type=LeftBraket;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
                     Left_Coutn++;
     }
    else if(strcmp(point,")")==0)
     {
                     strcpy(lexema.name,point);
                     lexema.type=RightBraket;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
                     Right_Count++;

     }
    else
    {
                     strcpy(lexema.name,point);
                     lexema.type=unknow;
                     lexema.value=0;
                     lexema.line=i;
                     table_lexema.push_back(lexema);
    }

    point=strtok(NULL, " ");
}
    }
Insert_table();

    ofstream file_out("D:\\data.txt");
    for(unsigned int i =0; i<table_lexema.size(); i++)
    {
        file_out << "name:" << table_lexema[i].name << "\n" << "line: " << table_lexema[i].line << "\n"
                  << "type: " << table_lexema[i].type << "\n" << "value: " << table_lexema[i].value <<endl;
    }


}
void Compiler::GetIndTable()
{
    for(unsigned int i=0; i<table_lexema.size(); i++)
    {
        if(table_lexema[i].type==INTEGER16)
        {
           while(table_lexema[i].type!= EndGroup)
           {
               if(table_lexema[i].type==var)
               {
                   strcpy(table_id.name,table_lexema[i].name);
                   i++;
               }
               else if(table_lexema[i].type==number)
               {
                  table_id.value=table_lexema[i].value;
                  i++;
                  IDTable_lexema.push_back(table_id);
               }
               else
               {
                   i++;
               }

            }
         }

    }
    ofstream file_o("D:\\table_id.txt");
    for(unsigned int i =0; i<IDTable_lexema.size(); i++)
    {
        file_o << "name:" << IDTable_lexema[i].name << "\n" << "value:" << IDTable_lexema[i].value << endl;
}

}
void Compiler::Insert_table()
{
    vector<Lexem>:: iterator it;
    it=table_lexema.begin();
    int pos_line;
    for(unsigned int i=0; i<table_lexema.size(); i++)
    {

        if(table_lexema[i].type==INTEGER16)
        {
            pos_line=table_lexema[i].line;
            while(table_lexema[i].type!=Body)
            {
              if(table_lexema[i].type == var && table_lexema[i+1].type != doriv)
              {
                        it=table_lexema.begin()+i+1;
                              strcpy(lexema.name,"::=");
                              lexema.value=0;
                              lexema.line=pos_line;
                              lexema.type=doriv;
                              table_lexema.insert(it,lexema);
                        it=table_lexema.begin()+i+2;
                              strcpy(lexema.name,"number");
                              lexema.value=0;
                              lexema.line=pos_line;
                              lexema.type=number;
                              table_lexema.insert(it,lexema);
               i++;
               }
              else
                {
                  i++;
                }
            }
        }

    }
}
bool Compiler::SynstaxAnalis(){

    QString temp;
    if(table_lexema[0].type != Name )
    {        error=true;

        line = itoa((table_lexema[0].line),line,10);
        roster_error << "Error occurred on ";
        roster_error.append(line);
        roster_error<< " line: No operator program name.\n";
    }
    if(table_lexema[1].type!=NameProg)
    {
        error=true;
        line = itoa((table_lexema[1].line),line,10);
        roster_error << "Error occurred on ";
        roster_error.append(line);
        roster_error <<" line: The program no name.\n";
    }
    if(table_lexema[2].type==EndGroup)
    {
        error=true;
        line = itoa((table_lexema[2].line),line,10);
        roster_error <<"Error occurred on ";
        roster_error.append(line);
        roster_error<<" line: After the name of the program do not have to be ; \n ";
    }
   if(table_lexema[2].type!=Data)
   {
       error=true;
       line = itoa((table_lexema[2].line),line,10);
       roster_error <<"Error occurred on ";
       roster_error.append(line);
       roster_error <<" line: Not announced data segment \n ";
   }
   if(table_lexema[3].type==EndGroup)
   {
       error=true;
       line = itoa((table_lexema[3].line),line,10);
       roster_error <<  "Error occurred on ";
       roster_error.append(line);
       roster_error<<" line: After the keyword <Data> do not have to be ; \n ";
   }
   if(table_lexema[table_lexema.size()-1].type!=End)
   {
       error=true;
       line = itoa((table_lexema[table_lexema.size()-1].line),line,10);
       roster_error << "Error occurred on ";
       roster_error.append(line);
       roster_error<< " line: No operator end segment code\n";
   }

   if(BodyAnaliz()==true)
   {
             error=true;
             roster_error << "Error occurred on line: No start code segment\n";
   }
   if(Left_Coutn != Right_Count)
   {
       error=true;
       roster_error << "Error occurred on : Odd number of brackets\n";
   }
  for (unsigned int i = 0; i < table_lexema.size(); i++)
    {
      if(table_lexema[i].type == var)
      {
          QRegExp obj("_[A-Z]{1,8}");
          temp=table_lexema[i].name;
          if(!temp.contains(obj))
          {
              error=true;
             line = itoa((table_lexema[i].line),line,10);
             roster_error << "Error occurred on ";
             roster_error.append(line);
             roster_error<< " line: Incorrectly declared variable\n";
          }
      }

        else if(table_lexema[i].type==Body && table_lexema[i+1].type==EndGroup)
      {
          error=true;
          line = itoa((table_lexema[i+1].line),line,10);
          roster_error << "Error occurred on ";
          roster_error.append(line);
          roster_error<< " line: After the keyword <Body> do not have to be ; \n ";
      }
      else if(table_lexema[i].type==unknow)
      {
          error=true;
          line = itoa((table_lexema[i].line),line,10);
          roster_error << "Error occurred on ";
          roster_error.append(line);
          roster_error<< " line: Unknown token \n ";
      }
     else if(table_lexema[i].type==Div && table_lexema[i+1].type!=var && table_lexema[i+1].type!=LeftBraket)
      {
          error=true;
          line = itoa((table_lexema[i].line),line,10);
          roster_error << "Error occurred on ";
          roster_error.append(line);
          roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==Mod && table_lexema[i+1].type!=var && table_lexema[i+1].type!=LeftBraket)
      {
          error=true;
          line = itoa((table_lexema[i].line),line,10);
          roster_error << "Error occurred on ";
          roster_error.append(line);
          roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==Mul && table_lexema[i+1].type!=var && table_lexema[i+1].type!=LeftBraket)
      {
              error=true;
              line = itoa((table_lexema[i].line),line,10);
              roster_error << "Error occurred on ";
              roster_error.append(line);
              roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==not_ && table_lexema[i+1].type!=var && table_lexema[i+1].type!=LeftBraket)
      {
              error=true;
              line = itoa((table_lexema[i].line),line,10);
              roster_error << "Error occurred on ";
              roster_error.append(line);
              roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==and_ && table_lexema[i+1].type!=var && table_lexema[i+1].type!=LeftBraket)
      {
              error=true;
              line = itoa((table_lexema[i].line),line,10);
              roster_error << "Error occurred on ";
              roster_error.append(line);
              roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==or_ && table_lexema[i+1].type!=var && table_lexema[i+1].type!=LeftBraket)
      {
              error=true;
              line = itoa((table_lexema[i].line),line,10);
              roster_error << "Error occurred on ";
              roster_error.append(line);
              roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==dec && table_lexema[i+1].type!=EndGroup && table_lexema[i-1].type!=var)
      {
              error=true;
              line = itoa((table_lexema[i].line),line,10);
              roster_error << "Error occurred on ";
              roster_error.append(line);
              roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==inc && table_lexema[i+1].type!=EndGroup && table_lexema[i-1].type!=var)
      {
                  error=true;
                  line = itoa((table_lexema[i].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==End && i!=table_lexema.size()-1 )
      {
                  error=true;
                  line = itoa((table_lexema[i+1].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: After the end of the innocent contained nothing \n ";
      }
      else if(table_lexema[i].type==if_)
      {
          int pos=0;
          int j=i;
          pos=table_lexema[i].line;
          for(j=i; i<table_lexema.size(); j++)
          {
              if(table_lexema[j].type==goto_ && pos!=table_lexema[j].line)
              {
                  error=true;
                  line = itoa((table_lexema[j].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< "line: After if no goto ; \n ";
                  break;
              }
              else if(table_lexema[j].type==goto_ && pos==table_lexema[j].line)
              {
                  break;
              }
          }

      }
      else if(table_lexema[i].type==goto_ &&  table_lexema[i+1].type!=lable)
      {
                  error=true;
                  line = itoa((table_lexema[i+1].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: After goto no tags \n ";
      }
      else if(table_lexema[i].type==doriv && table_lexema[i+1].type!=var && table_lexema[i+1].type!=LeftBraket &&
              table_lexema[i+1].type!=number)
      {
                  error=true;
                  line = itoa((table_lexema[i].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: Incorrect assignment \n ";
      }
      else if(table_lexema[i].type==equ && table_lexema[i+1].type!=var && table_lexema[i-1].type!=var)
      {
                  error=true;
                  line = itoa((table_lexema[i].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==notequ && table_lexema[i+1].type!=var && table_lexema[i-1].type!=var)
      {
                  error=true;
                  line = itoa((table_lexema[i].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==ge && table_lexema[i+1].type!=var && table_lexema[i-1].type!=var)
      {
                  error=true;
                  line = itoa((table_lexema[i].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: After surgery goes wrong operand \n ";
      }
      else if(table_lexema[i].type==le && table_lexema[i+1].type!=var && table_lexema[i-1].type!=var)
      {
                  error=true;
                  line = itoa((table_lexema[i].line),line,10);
                  roster_error << "Error occurred on ";
                  roster_error.append(line);
                  roster_error<< " line: After surgery goes wrong operand \n ";
      }



  }
  for(unsigned int i = 0; i < table_lexema.size(); i++)
{
      if(table_lexema[i].line==table_lexema[i-1].line)
      {
          continue;
      }
      else
      {
      if(table_lexema[i].type == INTEGER16 || table_lexema[i].type == var || table_lexema[i].type == Output ||
              table_lexema[i].type == Input || table_lexema[i].type == if_ || table_lexema[i].type == goto_)
      {
             int pos;
             unsigned int j=i;
          int a;
          LexemType x;
             pos=table_lexema[i].line;
             for(j=i; j<table_lexema.size(); j++)
             { a=table_lexema[j].line;
                 x=table_lexema[j].type;

                 if(table_lexema[j].type == EndGroup && pos!=table_lexema[j].line)
                 {
                     error=true;
                     line = itoa((table_lexema[i].line),line,10);
                     roster_error << "Error occurred on ";
                     roster_error.append(line);
                     roster_error<< "line: No end of line ; \n ";
                     break;
                 }
                 else if(table_lexema[j].type == EndGroup && pos==table_lexema[j].line)
                 {
                     break;
                 }
                 else continue;

              }



      }
      }
  }



    return error;
}
bool Compiler::BodyAnaliz()
{

    for(unsigned int i=0; i<table_lexema.size(); i++)
    {
        if(table_lexema[i].type==Body)
        {
            BodyError=false;
            break;

        }
        else
        {
           BodyError=true;


        }
    }
return BodyError;
}
QStringList Compiler:: GetError()
{
    SynstaxAnalis();
    if(error==true)
    {
        return roster_error;
    }
    else
    {
        roster_error.clear();
        roster_error << "Bild done....";
        return roster_error;
    }

}
void Compiler :: GetPostfiksForm(int i)
{
    vector<string> op;
        LexemType t;
        int j;
        zamin=i;
                j=i;
                while(table_lexema[j++].type!=EndGroup)
                {

                    if(table_lexema[j].type==not_ || table_lexema[j].type == and_ || table_lexema[j].type==or_)
                {        setlog=true;
                          break;
                    }
                    else
                    {
                        setlog=false;

                    }
                }
                if(setlog==true)
                {

                }
                else
                {
                i++;
                while (table_lexema[++i].type != EndGroup)
                {

                      t = table_lexema[i].type;
                      switch (t) {
                      case LeftBraket:
                      {
                          op.push_back("(");
                          break;
                      }
                      case RightBraket:
                      {
                        temp=op[op.size()-1];
                          while(temp!="(")
                          {
                              postfix.push_back(temp );
                              op.pop_back();
                              if(op.size()-1>0)
                              {
                              temp=op[op.size()-1];
                              }
                              else break;
                          }
                          op.pop_back();
                          break;
                      }
                       case Div:
                      {
                          if(op.empty()==true)
                          {
                              op.push_back("/");
                              break;
                          }
                          else
                          {
                          temp=op[op.size()-1];
                          while(!op.empty())
                          {
                           if((temp=="/") || (temp=="%") || (temp=="*"))
                           {
                               postfix.push_back(temp);
                               op.pop_back();
                               if(op.empty()==false)
                               {
                                   temp=op[op.size()-1];
                               }
                               else
                               {
                               op.push_back("/");
                               break;
                               }
                           }
                           else
                           {
                                op.push_back("/");
                                break;
                           }


                            }
                          break;
                          }
                      }
                       case Mod:
                      {
                          if(op.empty()==true)
                          {
                             op.push_back("%");
                             break;
                          }
                          else
                          {
                          temp=op[op.size()-1];
                          while(!op.empty())
                          {
                           if((temp=="/") || (temp=="%") || (temp=="*"))
                           {
                               postfix.push_back(temp);
                               op.pop_back();
                               if(op.empty()==false)
                               {
                                   temp=op[op.size()-1];
                               }
                               else
                               {
                               op.push_back("%");
                               break;
                               }
                           }
                           else
                           {
                                op.push_back("%");
                                break;
                           }

                            }
                          break;
                          }

                      }
                       case Mul:
                      {
                          if(op.empty()==true)
                          {
                             op.push_back("*");
                             break;
                          }
                          else
                          {
                          temp=op[op.size()-1];
                          while(!op.empty())
                          {
                           if((temp=="/") || (temp=="%") || (temp=="*"))
                           {
                               postfix.push_back(temp);
                               op.pop_back();
                               if(op.empty()==false)
                               {
                                   temp=op[op.size()-1];
                               }
                               else
                               {
                               op.push_back("*");
                               break;
                               }
                           }
                           else
                           {
                                op.push_back("*");
                                break;
                           }

                            }
                          break;
                          }
                      }
                       case var:
                      {
                          postfix.push_back(table_lexema[i].name);

                          break;
                      }
                      default:


                          break;
                      }
                }

                if(table_lexema[i].type == EndGroup)
                {
                    while(!op.empty())
                    {
                        temp= op[op.size()-1];
                        if(temp == "(")
                        {
                            op.pop_back();

                        }
                        else
                        {
                           postfix.push_back(temp);
                           op.pop_back();

                        }

                    }

                }

            }




        std::ofstream post;
        post.open("D:\\POSTFIX.txt");
        for(unsigned int i=0; i < postfix.size(); i++)
        {
        post << postfix[i] << " ";
        post << "\n";     }
        post.close();
    }
void Compiler :: StartASMProgram()
{

    name_temp.append("D:\\");
    name_temp.append(table_lexema[1].name);
    name_temp.append(".asm");
    file_out.open(name_temp.c_str());
    file_out << "include \\masm32\\include\\masm32rt.inc";
    file_out.close();
}
void Compiler :: WriteDataSeg()
{
    file_out.open(name_temp.c_str(),std::ios_base::app);
    file_out << std::endl << ".DATA" << std::endl;
    file_out << "data_buf db 15 dup(0)" << std::endl;
    for(unsigned int i = 0; i < IDTable_lexema.size(); i++)
    {
        file_out << IDTable_lexema[i].name << " dd " << IDTable_lexema[i].value << std::endl;
    }
    file_out.close();
}
void Compiler :: GetPostfiksFormLogicFun(int i)
{
    vector  <string> operation;
    LexemType zmin;
    zamin=i;



            i++;
            while (table_lexema[++i].type!=EndGroup) {
                zmin=table_lexema[i].type;
               switch (zmin) {
               case not_:
               {
                   if(operation.empty()==true)
                   {
                       operation.push_back("!!");
                       break;
                   }
                   else
                   {   temp=operation[operation.size()-1];
                       while (!operation.empty()) {
                           if(temp=="!!")
                           {
                               postfix_lg.push_back(temp);
                               operation.pop_back();
                               if(operation.empty()==false)
                                {
                               temp=operation[operation.size()-1];
                                }
                               else
                                {
                                   operation.push_back("!!");
                                   break;
                                }
                            }
                           else
                            {
                                  operation.push_back("!!");
                                  break;
                            }
                       }
                       break;
                 }
               }
                case and_:
               {
                   if(operation.empty()==true)
                   {
                       operation.push_back("&&");
                       break;
                   }
                   else
                   {   temp=operation[operation.size()-1];
                       while (!operation.empty()) {
                           if(temp=="!!" || temp=="&&" || temp=="||")
                           {
                               postfix_lg.push_back(temp);
                               operation.pop_back();
                               if(operation.empty()==false)
                                {
                               temp=operation[operation.size()-1];
                                }
                               else
                                {
                                   operation.push_back("&&");
                                   break;
                                }
                            }
                           else
                            {
                                  operation.push_back("&&");
                                  break;
                            }
                       }
                       break;
                 }
               }
                case or_:
               {
                   if(operation.empty()==true)
                   {
                       operation.push_back("||");
                       break;
                   }
                   else
                   {   temp=operation[operation.size()-1];
                       while (!operation.empty()) {
                           if(temp=="!!" ||  temp=="||")
                           {
                               postfix_lg.push_back(temp);
                               operation.pop_back();
                               if(operation.empty()==false)
                                {
                               temp=operation[operation.size()-1];
                                }
                               else
                                {
                                   operation.push_back("||");
                                   break;
                                }
                            }
                           else
                            {
                                  operation.push_back("||");
                                  break;
                            }
                       }
                       break;
                   }
               }
                case var:
               {
                   postfix_lg.push_back(table_lexema[i].name);
                   break;
               }
               case LeftBraket:
               {
                   operation.push_back("(");
                   break;
               }
               case RightBraket:
               {
                 temp=operation[operation.size()-1];
                   while(temp!="(")
                   {
                       postfix_lg.push_back(temp);
                       operation.pop_back();
                       if(operation.size()-1>0)
                       {
                       temp=operation[operation.size()-1];
                       }
                       else break;
                   }
                   operation.pop_back();
                   break;
               }
               default:
                   break;
               }
            }
            zmin=table_lexema[i].type;
            if(table_lexema[i].type == EndGroup)
            {
                while(!operation.empty())
                {
                    temp = operation[operation.size()-1];
                    if(temp == "(")
                    {
                        operation.pop_back();

                    }
                    else
                    {
                       postfix_lg.push_back(temp);
                       operation.pop_back();

                    }

                }

            }




    ofstream fil_in;
    fil_in.open("D:\\POSTFIX_lg.txt");
    for( unsigned int i=0; i< postfix_lg.size(); i++)
    {
    fil_in << postfix_lg[i]<< " ";
    }

    fil_in.close();
}
void Compiler :: GenericLogic()
{
    vector<string>:: iterator it;
    it=postfix_lg.begin();
    ofstream file_out;
    int pos;
    string s;
    int x;
    file_out.open(name_temp.c_str(),std::ios_base::app);;
    for(unsigned int i=0; i<postfix_lg.size(); i++)
    {
        s=postfix_lg[i];
        if(postfix_lg[i]=="||")
        {
            pos=i;
            string sa;
            x=pos-2;
            string zamina_1;
            string zamina_2;
            file_out << "mov " << "eax" << ", " << postfix_lg[pos-2] << "\n";
            file_out << "or " << "eax" << ", " << postfix_lg[pos-1] << "\n";
             sa=postfix_lg[0];
             if(postfix_lg.size()==1)
             {
                 i=0;
             }
             else
             {
             i=-1;
             }



             int j=1;
             if(postfix_lg[0]!="ebx")
             {
                 postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                 postfix_lg.insert(postfix_lg.begin()+(pos-2),"ebx");
                 file_out<< "xchg eax, ebx\n";


             }
             else
             {
            while(j<pos)
            {

                if(postfix_lg[j]=="ebx" && postfix_lg.size()>1 )
                {

                    postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                    postfix_lg.insert(postfix_lg.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                     else if(postfix_lg[j]=="ecx" && postfix_lg.size()>1)
                {
                    postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                    postfix_lg.insert(postfix_lg.begin()+(pos-2),"edx");
                    file_out<< "xchg eax, edx\n";
                    j++;
                    break;
                }
                else if(postfix_lg[j]=="edx" && postfix_lg.size()>1)
                {
                    postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                    postfix_lg.insert(postfix_lg.begin()+(pos-2),"ebp");
                    file_out<< "xchg eax, esx\n";
                    j++;
                    break;
                }

                else
                {
                    postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                    postfix_lg.insert(postfix_lg.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                j++;
            }
             }


        }
        else if(postfix_lg[i]=="&&")
        {
            pos=i;
            string sa;
            x=pos-2;
            file_out << "mov " << "eax" << ", " << postfix_lg[pos-2] << "\n";
            file_out << "and " << "eax" << ", " << postfix_lg[pos-1] << "\n";
             sa=postfix_lg[0];
             if(postfix_lg.size()==1)
             {
                 i=0;
             }
             else
             {
             i=-1;
             }
             int j=1;
             if(postfix_lg[0]!="ebx")
             {
                postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                 postfix_lg.insert(postfix_lg.begin()+(pos-2),"ebx");
                 file_out<< "xchg eax, ebx\n";
             }
             else
             {
            while(j<pos)
            {

                if(postfix_lg[j]=="ebx" && postfix_lg.size()>1 )
                {

                    postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                    postfix_lg.insert(postfix_lg.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                     else if(postfix_lg[j]=="ecx" && postfix_lg.size()>1)
                {
                    postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                    postfix_lg.insert(postfix_lg.begin()+(pos-2),"edx");
                    file_out<< "xchg eax, edx\n";
                    j++;
                    break;
                }


                else
                {
                   postfix_lg.erase(postfix_lg.begin()+(pos-2),postfix_lg.begin()+(pos+1));
                    postfix_lg.insert(postfix_lg.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                j++;
            }
             }

        }
    }
    if(setlog==true)
    {
     file_out << "mov " << table_lexema[zamin].name << "," << postfix_lg[0] << "\n";
    }
     postfix_lg.clear();
     file_out.close();
  }
void Compiler :: GenericArifmetic()
{
    vector<string>:: iterator it;


    int pos;
    string s;
    int x;
    file_out.open(name_temp.c_str(),std::ios_base::app);
    for(unsigned int i=0; i<postfix.size(); i++)
    {
        s=postfix[i];
        if(postfix[i]=="/")
        {
            pos=i;
            string sa;
            x=pos-2;
            file_out << "mov " << "eax" << ", " << postfix[pos-2] << "\n";
            file_out << "mov edx, 0\n";
            file_out << "div " << "  " << postfix[pos-1] << "\n";
             sa=postfix[0];
             if(postfix.size()==1)
             {
                 i=0;
             }
             else
             {
             i=-1;
             }



             int j=1;
             if(postfix[0]!="ebx")
             {
                 postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                 postfix.insert(postfix.begin()+(pos-2),"ebx");
                 file_out<< "xchg eax, ebx\n";


             }
             else
             {
            while(j<pos)
            {

                if(postfix[j]=="ebx" && postfix.size()>1 )
                {

                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                     else if(postfix[j]=="ecx" && postfix.size()>1)
                {
                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"edx");
                    file_out<< "xchg eax, edx\n";
                    j++;
                    break;
                }


                else
                {
                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                j++;
            }
             }


        }
        else if(postfix[i]=="%")
        {
            pos=i;
            string sa;
            x=pos-2;
            file_out << "mov " << "eax" << ", " << postfix[pos-2] << "\n";
            file_out << "mov edx, 0\n";
            file_out << "div"  << " " << postfix[pos-1] << "\n";
            file_out<< "xchg eax, edx\n";
             sa=postfix[0];
             if(postfix.size()==1)
             {
                 i=0;
             }
             else
             {
             i=-1;
             }
             int j=1;
             if(postfix[0]!="ebx")
             {
                postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                 postfix.insert(postfix.begin()+(pos-2),"ebx");
                 file_out<< "xchg eax, ebx\n";
             }
             else
             {
            while(j<pos)
            {

                if(postfix[j]=="ebx" && postfix.size()>1 )
                {

                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                     else if(postfix[j]=="ecx" && postfix.size()>1)
                {
                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"edx");
                    file_out<< "xchg eax, edx\n";
                    j++;
                    break;
                }
                else if(postfix[j]=="edx" && postfix.size()>1)
                {
                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"esx");
                    file_out<< "xchg eax, esx\n";
                    j++;
                    break;
                }

                else
                {
                   postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                j++;
            }
             }

        }
        else if(postfix[i]=="*")
    {
            pos=i;
            string sa;
            x=pos-2;
            file_out << "mov " << "eax" << ", " << postfix[pos-2] << "\n";
            file_out << "mul" << " " << postfix[pos-1] << "\n";
             sa=postfix[0];
             if(postfix.size()==1)
             {
                 i=0;
             }
             else
             {
             i=-1;
             }
             int j=1;
             if(postfix[0]!="ebx")
             {
                postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                 postfix.insert(postfix.begin()+(pos-2),"ebx");
                 file_out<< "xchg eax, ebx\n";
             }
             else
             {
            while(j<pos)
            {

                if(postfix[j]=="ebx" && postfix.size()>1 )
                {

                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                     else if(postfix[j]=="ecx" && postfix.size()>1)
                {
                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"edx");
                    file_out<< "xchg eax, edx\n";
                    j++;
                    break;
                }
                else if(postfix[j]=="edx" && postfix.size()>1)
                {
                    postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"esx");
                    file_out<< "xchg eax, esx\n";
                    j++;
                    break;
                }

                else
                {
                   postfix.erase(postfix.begin()+(pos-2),postfix.begin()+(pos+1));
                    postfix.insert(postfix.begin()+(pos-2),"ecx");
                    file_out<< "xchg eax, ecx\n";
                    j++;
                    break;
                }
                j++;
            }
             }
    }
  }
    if(setlog==false)
    {
     file_out << "mov " << table_lexema[zamin].name << "," << postfix[0] << "\n";
    }
     postfix.clear();
     file_out.close();
}
void Compiler :: Translator()
{
    if(table_lexema[0].type==Name && table_lexema[1].type==NameProg)
    {
        StartASMProgram();
    }

    for(unsigned int i=0; i< table_lexema.size(); i++)
    {
        GetStatoperation(i);
         if(table_lexema[i].type==Data)
         {
             GetIndTable();
             WriteDataSeg();
         }
         else if((table_lexema[i].type == var) &&  (table_lexema[i+1].type == doriv) && (table_lexema[i+2].type!=number ) && setlog==false)
         {
                    GetPostfiksForm(i);
                    GenericArifmetic();
         }
         else if((table_lexema[i].type == var) &&  (table_lexema[i+1].type == doriv) && (table_lexema[i+2].type!=number ) && setlog==true)
         {
                    GetPostfiksFormLogicFun(i);
                    GenericLogic();
         }
         else if(table_lexema[i].type==Body)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << ".code \n";
             file_out << "start:\n";
             file_out.close();
         }
         else if(table_lexema[i].type==End)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out<<"invoke Sleep,1000\n";
             file_out <<"call ExitProcess\n";
             file_out << "end start\n";
             file_out.close();
         }
         else if(table_lexema[i].type==if_)
         {
             IF_GOTO(i);
         }
         else if(table_lexema[i].type==goto_ && table_lexema[i-1].type==EndGroup)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << "jmp " << table_lexema[i+1].name << "\n";
             file_out.close();
         }
         else if(table_lexema[i].type==lable && table_lexema[i-1].type==EndGroup)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << table_lexema[i].name << " :\n";
             file_out.close();
         }
         else if(table_lexema[i].type==Input)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << "\ninvoke StdIn, addr data_buf, 15" <<"\n";
             file_out << "invoke atol, addr data_buf" << "\n";
             file_out << "mov " << table_lexema[i+2].name<< ", eax" <<"\n";
             file_out.close();
         }
         else if(table_lexema[i].type==Output)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << "print str$(" << table_lexema[i+2].name << "),13,10\n";
             file_out.close();
         }
         else if(table_lexema[i].type==inc)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << "inc " << table_lexema[i-1].name << "\n";
             file_out.close();
         }
         else if(table_lexema[i].type==dec)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << "dec " << table_lexema[i-1].name << "\n";
             file_out.close();
         }
         else if (table_lexema[i].type==not_)
         {
             file_out.open(name_temp.c_str(),std::ios_base::app);
             file_out << "not " << table_lexema[i+1].name << "\n";
             file_out.close();
         }

    }
}
void Compiler :: GetStatoperation(int i)
{ int j;
    j=i;
    if(j==table_lexema.size()-1)
    {

       return ;
    }
    else
    {
    while(table_lexema[j++].type!=EndGroup)
    {

        if(table_lexema[j].type==not_ || table_lexema[j].type == and_ || table_lexema[j].type==or_)
    {        setlog=true;
              break;
        }
        else
        {
            setlog=false;

        }
    }
}
}
void Compiler :: IF_GOTO(int i)
{
    string if_temp;
    int posi;
    int j=i;
    file_out.open(name_temp.c_str(),std::ios_base::app);
    while(table_lexema[j++].type!=EndGroup)
    {
        if(table_lexema[j].type==var)
        {
            if_temp+=table_lexema[j].name;
            if_temp+=table_lexema[j+2].name;
            posi=j;
            break;
        }

    }
    file_out << "mov " << "eax, " << table_lexema[posi].name << "\n";
    file_out << "cmp " <<" eax, " << table_lexema[posi+2].name << "\n";
    if(table_lexema[posi+1].type==equ)
    {
        file_out << "je " << table_lexema[posi+5].name << "\n ";
    }
    else if(table_lexema[posi+1].type==notequ)
    {
         file_out << "jne" << table_lexema[posi+5].name << "\n ";
    }
    else if(table_lexema[posi+1].type==le)
    {
        file_out << "jna" << table_lexema[posi+5].name << "\n ";
    }
    else if(table_lexema[posi+1].type==ge)
    {
        file_out << "jnb " << table_lexema[posi+5].name << "\n ";
    }
    file_out.close();
}
