#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <sstream>
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


/*--

             TODO
           [Client]
--*/

/*
0. user input URL                   [O]
1-0. Replace "/" to "|"             [O]
1-1. Convert "string" to "wchar_t"  [O]
1-2. URL Incording Process          [O]
1-3. Rest API URL + Incording URL   [O]

2. URL Request & Get HTML           [O]

3. Display Result                   [O]
*/

using namespace  std;

int main(int argc, CHAR* argv[])
{
    // user_input part
    string s;
    cout << "URL : ";
    cin >> s;
    cin.clear();
    fflush(stdin);

    // input url part

    // convt part
    /*--
        string to char
    --*/
    string name(s.begin(), s.end());
    const char* strUni = name.c_str();
    //convt part

    // URL encoding part
    char encoding[] = "dist\\encoding\\encoding.exe -u=\"";
    strcat(encoding, strUni);
    char lastend[] = "\"";
    strcat(encoding, lastend);
    cout << encoding << endl;
    // URL encoding part

    // read part
    /*--
    this part encodes in a suitable way to send request to the rest api server
    the encoding.exe process's follow

    1. get URL
    2. replace "/" to "|"
    3. URL encoding
    4. display encoded url as text

    this part is to get result of encoded URL
    --*/

    /*
        "r" type is shortcut of the "read" word so, when get out some result in encoding.exe file, we can get some result in the display.
    */
    FILE* stream = _popen(encoding, "r");
    ostringstream output;

    while (!feof(stream) && !ferror(stream))
    {
        char buf[1024];
        int bytesRead = fread(buf, 1, 128, stream);
        output.write(buf, bytesRead);
    }
    string result = output.str();
    //cout << "ebcidubg URL      : "<< result << endl;
// read part


// convt part
    string htmlname(result.begin(), result.end());
    const char* htmlstrUni = htmlname.c_str();
    // convt part

    // char + char
    char html[] = "dist\\utils\\utils.exe -u=\"http://localhost:5000/input/"; // rest api sever url
    strcat(html, htmlstrUni);
    char htmllast[] = "\"";
    strcat(html, lastend);
    cout << "ADDED URL      : " << html << endl;
    // char + char

    // read HTML part        
        /*--
            "utils.exe" is just do download HTML and show

            so, when called URL with "-u" arguments, this application just display HTML file as text without any filter

            and utils.exe file work follow is this

            1. get URL
            2. download HTML file
            3. display HTML file as text

            when my rest api server return the some of the results(without error messages),
            that was have only text without any tag or somthing else in HTML file
            so, we can get only text in HTML file! so, i can get too easy work follow.
            because i did not stored or processed in any form to the result, like json type, etc..

        --*/
    FILE* html_stream = _popen(html, "r");
    ostringstream htmloutput;

    while (!feof(html_stream) && !ferror(html_stream))
    {
        char buf[1024];
        int bytesRead = fread(buf, 1, 128, html_stream);
        htmloutput.write(buf, bytesRead);
    }
    string html_result = htmloutput.str();
    cout << html_result << endl;
    // read HTML part

    return 0;
}