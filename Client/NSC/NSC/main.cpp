/*--

    NEWS SUMMEARY CLIENT

    Copyright (c) 2019, Seungup Noh
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <ORGANIZATION> nor the names of its
        contributors may be used to endorse or promote products derived from
        this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
    OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

--*/

#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/*--
*
*             TODO
*           [Client]
--*/

/*
*     0. user input URL                 [O]
*   1-0. Replace "/" to "|"             [O]
*   1-1. Convert "string" to "wchar_t"  [O]
*   1-2. URL Incording Process          [O]
*   1-3. Rest API URL + Incording URL   [O]
*
*
*   2. URL Request & Get HTML           [O]
*
*   3. Display Result                   [O]
*/

class Input
{
    /*************************************************
    *
    *       Input Class 
    *
    *    ��� ���� : ������ ���۵� ��ũ �ۼ� �� ���� ���� �׽�Ʈ, ��� Ȯ���� ����.
    *
    *    <-- �Է� --> 
    *
    *    1. ���� �ڵ�
    *    2. ����� ���� ��ũ
    *
    *    <-- ��� -->
    *
    *    1. ���� ���� �׽�Ʈ -> 0 or 1
    *    2. ����� ���� ��ũ -> ���� ��� ���
    *
    *************************************************/


    private:
        string InitialURL;
        string InputURL;
        string UtilsDir;
    public:

        // �⺻ �����ڴ� ����
        Input()
        {
            InitialURL = "http://localhost:5000/input/";
            InputURL = InitialURL + "";
            UtilsDir = "dist\\utils\\utils.exe -u=\"";
        };

        // �ܺ� ������ ��� �������� ��������� ���� �ּ� �Է� �� ���� ����
        Input(string Number, string URL)
        {
            UtilsDir = "dist\\utils\\utils.exe -u=\"";
            InitialURL = UtilsDir + "http://" + Number + ".ngrok.io/input/" + URL + "\"";
        };

        void ShowResult()
        {
            
            // �� �Ľ� ��� ��� 


            // _popen(htmlstrUni, "r") �� const char ���·� �����ؾ� ��밡���ϹǷ� ��ȯ

            string htmlname(InitialURL.begin(), InitialURL.end());
            const char* htmlstrUni = htmlname.c_str();



            FILE* html_stream = _popen(htmlstrUni, "r");
            ostringstream htmloutput;

            while (!feof(html_stream) && !ferror(html_stream))
            {
                // ���۴� 2048 ����Ʈ
                char buf[2048]; 
                int bytesRead = fread(buf, 1, 128, html_stream);
                htmloutput.write(buf, bytesRead);
            }
            string html_result = htmloutput.str();
            cout << html_result << endl;
        }

        int Test(string Number)
        {
            // �׽�Ʈ Ŭ���� ������ ������ ���������� �Ǿ��� ��� 
            // ù ȭ�� �Ľ� ����� 14����Ʈ���� Ȯ��.
            // 14 ����Ʈ�� ��� 1 �ƴϸ� 0 ��ȯ


            string testUrl;
            testUrl = UtilsDir + "http://" + Number + ".ngrok.io/";

            // _popen �� ����ϱ� ���� string to char
            string htmlname(testUrl.begin(), testUrl.end());
            const char* htmlstrUni = htmlname.c_str();


            FILE* html_stream = _popen(htmlstrUni, "r");
            ostringstream htmloutput;

            while (!feof(html_stream) && !ferror(html_stream))
            {
                char buf[2048];
                int bytesRead = fread(buf, 1, 128, html_stream);
                htmloutput.write(buf, bytesRead);
            }

            string html_result = htmloutput.str();

            if (html_result.size() == 14)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        };
};





class CODING
{
    /*************************************************
    *
    *   CODING Class
    *
    *   ��� ���� : ������ ���۵� ��ũ �ۼ�
    *
    *    <-- �Է� -->
    *
    *   1. ����� ���� ��� UTF-8 ���ڵ� + �������� �ν� �����ϵ��� ����
    *
    *   <-- ��� -->
    *
    *    1. ���ڵ��� ���� URL
    *
    *************************************************/

    private:
        string Incoding;
        string IncodingDir;

    public:
        CODING()
        {
            IncodingDir = "dist\\encoding\\encoding.exe -u=\"";
            Incoding = IncodingDir + "";
        };

        CODING(string URL)
        {
            IncodingDir = "dist\\encoding\\encoding.exe -u=\"";
            Incoding = IncodingDir + URL + "\"";
        };

        string GetResult()
        {
            string htmlname(Incoding.begin(), Incoding.end());
            const char* htmlstrUni = htmlname.c_str();

            FILE* html_stream = _popen(htmlstrUni, "r");
            ostringstream htmloutput;

            while (!feof(html_stream) && !ferror(html_stream))
            {
                char buf[2048];
                int bytesRead = fread(buf, 1, 128, html_stream);
                htmloutput.write(buf, bytesRead);
            }
            string html_result = htmloutput.str();
            return html_result;
        };
};



int main()
{
    string link, ngrok;
    ifstream eread, uread;


    // ���� �������� Ȯ�� 
    eread.open("dist\\encoding\\encoding.exe");
    uread.open("dist\\utils\\utils.exe");

    // ���� ���� ���� Ȯ��.
    if (!eread && !uread)
    {
        // ����
        cout << "can't find utils" << endl;
    }
    else
    {
        // �����ҽ�
        while (1)
        {
            // ���� �ڵ� �Է�
            cout << "CODE : ";
            cin >> ngrok;
            cin.clear();
            fflush(stdin);

            if (ngrok == "0")
            {
                break;
            }
            else
            {
                Input test(ngrok, "");
                if (test.Test(ngrok) == 1)
                {
                    while (1)
                    {
                        // ����� ���� ��ũ �Է�
                        cout << "LINK : ";
                        cin >> link;
                        if (link == "0")
                        {
                            break;
                        }
                        else
                        {
                            // ���� ��� ��ົ ���
                            cin.clear();
                            fflush(stdin);
                            system("cls");
                            CODING URL(link);
                            string ICU = URL.GetResult();
                            Input input(ngrok, ICU);
                            cout << endl;
                            input.ShowResult();
                        }

                    }

                }
                else
                {
                    // ���� ���� ���н�
                    system("cls");
                    cout << "Code Error" << endl;
                }
            }
        }
    }

    return 0;
};