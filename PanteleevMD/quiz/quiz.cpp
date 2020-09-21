#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <vector>
#include <locale>


using namespace std;

class Question 
{
    private:
        string theme;
        string text;
        string answers[4];
        int correctAnswer;
    public:
        Question(string qTheme, string qText, string qAnswers[], int qCorrectAns)
        {
            setQuestion(qTheme, qText, qAnswers, qCorrectAns);
        }
        Question()
        {
            string fu[4] = {"", "", "", ""};
            setQuestion("", "", fu, 0);
        }

        void setQuestion(string qTheme, string qText, string qAnswers[], int qCorrectAns)
        {
            theme = qTheme;
            text = qText;
            for (int i = 0; i < 4; ++i) {
                answers[i] = qAnswers[i];
            }
            correctAnswer = qCorrectAns;
            //swap(answers, qAnswers);
            //answers = qAnswers;
        }
        void getQuestion()
        {
            cout << '\n' << "Theme: " << theme
                 << "\n" << text << "\n" ;
            for (int counter = 1; counter <= 4; counter++)
            {
                cout << counter << ' ' << answers[counter-1] << '\t';
                cout << "\n" ;
            }
        }
        char getRightAnswer()
        {
            return (char)(correctAnswer + (int)'0');
        }
};

vector<Question> ReadQuestions()
{
    string line;
    vector<Question> qArray;
    ifstream qustionnaire ("questionnaire.txt");

    if (qustionnaire.is_open())
    {
        //cout << "Ready to read" << '\n';
        /*     
        int number_of_lines = 0;
        while (getline(qustionnaire, line))
            ++number_of_lines;
        cout << number_of_lines << '\n';
        */
        int lineNum = 0;
        int index = 0;
        vector<string> strings;

        strings = {"C++", "How many C++ programmers does it take to screw in a lightbulb?", 
                    "1", "Zero. It's a hardware problem", "Русский язык", "Four, plus one senior analyst to manage the project", "\n2"};

        string theme;
        string text;
        string answers[4];
        int correctAnser;

        qustionnaire.clear(); 
        qustionnaire.seekg(0,ios::beg);

        while ( getline(qustionnaire, line, ';') ) 
        {
            if (lineNum % 7 == 0) 
            {
                string vecToArray[] = {strings[2].substr(1, strings[2].size() - 1), strings[3], strings[4], strings[5]};
                //cout << (strings.at(6)[2]);
                string vecToStr = strings.at(6);
                int strToInt = (int)vecToStr[1] - '0';

                Question tempQ;
                tempQ.setQuestion(strings[0], strings[1], vecToArray, strToInt);
                qArray.push_back(tempQ);

                strings.clear();
                index++;
            }
            //cout << line;

            strings.push_back(line);            

            lineNum++;
        }
        qustionnaire.close();

        
    }

    else cout << "Unable to open file"; 

    return qArray;
}

void GenerateQuestionSet(vector<Question> filledVector)
{
    cout << '\n' << "Quiz begins.";
    int randmax = filledVector.size();
    //int points = 0;
    for (int counter = 0; counter < 5; counter++)
    {
        int ID = rand() % randmax;
        
        filledVector.at(ID).getQuestion();
        string input = "9";
        while (input[0] != filledVector.at(ID).getRightAnswer())
        {
            //cout << input[0] << '=' << filledVector.at(ID).getRightAnswer() << '\n';
            cin >> input;
            
        }
    }
    cout << "Well done!";
    //return 5;
}


int main()
{
    setlocale(0,"");

    vector<Question> filledVector = ReadQuestions();
    
    //int result = 0;
    GenerateQuestionSet(filledVector);

    return 0;
}