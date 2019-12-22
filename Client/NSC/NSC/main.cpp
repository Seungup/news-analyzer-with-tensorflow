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
    *    사용 목적 : 서버에 전송될 링크 작성 및 서버 연결 테스트, 결과 확인을 위함.
    *
    *    <-- 입력 --> 
    *
    *    1. 서버 코드
    *    2. 요약할 뉴스 링크
    *
    *    <-- 출력 -->
    *
    *    1. 서버 연결 테스트 -> 0 or 1
    *    2. 요약할 뉴스 링크 -> 서버 요약 결과
    *
    *************************************************/


    private:
        string InitialURL;
        string InputURL;
        string UtilsDir;
    public:

        // 기본 생성자는 로컬
        Input()
        {
            InitialURL = "http://localhost:5000/input/";
            InputURL = InitialURL + "";
            UtilsDir = "dist\\utils\\utils.exe -u=\"";
        };

        // 외부 접속의 경우 랜덤으로 만들어지는 서버 주소 입력 후 서버 접근
        Input(string Number, string URL)
        {
            UtilsDir = "dist\\utils\\utils.exe -u=\"";
            InitialURL = UtilsDir + "http://" + Number + ".ngrok.io/input/" + URL + "\"";
        };

        void ShowResult()
        {
            
            // 웹 파싱 결과 출력 


            // _popen(htmlstrUni, "r") 은 const char 형태로 변경해야 사용가능하므로 변환

            string htmlname(InitialURL.begin(), InitialURL.end());
            const char* htmlstrUni = htmlname.c_str();



            FILE* html_stream = _popen(htmlstrUni, "r");
            ostringstream htmloutput;

            while (!feof(html_stream) && !ferror(html_stream))
            {
                // 버퍼는 2048 바이트
                char buf[2048]; 
                int bytesRead = fread(buf, 1, 128, html_stream);
                htmloutput.write(buf, bytesRead);
            }
            string html_result = htmloutput.str();
            cout << html_result << endl;
        }

        int Test(string Number)
        {
            // 테스트 클래스 서버와 연결이 정상적으로 되었을 경우 
            // 첫 화면 파싱 결과가 14바이트인지 확인.
            // 14 바이트일 경우 1 아니면 0 반환


            string testUrl;
            testUrl = UtilsDir + "http://" + Number + ".ngrok.io/";

            // _popen 을 사용하기 위해 string to char
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
    *   사용 목적 : 서버에 전송될 링크 작성
    *
    *    <-- 입력 -->
    *
    *   1. 요약할 뉴스 기사 UTF-8 인코딩 + 서버에서 인식 가능하도록 변경
    *
    *   <-- 출력 -->
    *
    *    1. 인코딩된 뉴스 URL
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


    // 실행 가능한지 확인 
    eread.open("dist\\encoding\\encoding.exe");
    uread.open("dist\\utils\\utils.exe");

    // 파일 존재 유무 확인.
    if (!eread && !uread)
    {
        // 실패
        cout << "can't find utils" << endl;
    }
    else
    {
        // 존재할시
        while (1)
        {
            // 서버 코드 입력
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
                        // 요약할 뉴스 링크 입력
                        cout << "LINK : ";
                        cin >> link;
                        if (link == "0")
                        {
                            break;
                        }
                        else
                        {
                            // 뉴스 기사 요약본 출력
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
                    // 서버 연결 실패시
                    system("cls");
                    cout << "Code Error" << endl;
                }
            }
        }
    }

    return 0;
};