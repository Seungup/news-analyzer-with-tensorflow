# **It is designed for university assignments.**

# Summary
![chart](https://github.com/Seungup/NASA/blob/master/follow.png)
## The program automatically parses, summarizes, translates, and analyzes links to news articles on the client.
### Here is the [Demo Video](https://www.youtube.com/watch?v=oADv6G2cCwk) for you The server is connected through [ngrok](https://ngrok.com/).

# Before using TODO

## **C++ Client is will be work MS Visual Studio 2019**


**/Server/CPP_Server/Bin/server_model.py** file there are absolute path

```python
model = keras.models.load_model('d:/UNIV/Python_Project/University/CPP_Server/Bin/model.h5')
```

**/Server/CPP_Server/Bin/Lib.py** if you want automatic translation you must singup [Naver Develpoment](https://developers.naver.com/main/) 

### **Fortunately, I used Google translation API for you without Papago API key.** So, Papago API Key is Option

```python
class CppAssignment:
    
    class Papago:
        
        def __init__(self, text, papago_id = 'your Client ID', papago_secret = 'your Client Secret'):
            self.papago_id = papago_id
            self.papago_secret = papago_secret
            self.text = text
```

# If you want Papago API then replace this section.

file PATH : **/Server/CPP_Server/Server.ipynb**

```python
@app.route('/input/<data>')
def hello_user(data):
...
# <--Papago API Section-->
...
    try:
        if source != 'ko':
            print("[use google translator]")
            text = translator.translate(data, dest='ko').text
            print("ori :", data[0:50])
            print("tra :", text[0:50])
            sentence_data = libray.KoNLPy(text).sentence()
            data_pn_score = []
            obj = [0]
            for i in range(len(sentence_data)):
                if len(sentence_data[i]) < 21:
                    score = 0
                    tf = 0
                else:
                    _, score, tf = libray.model().text(sentence_data[i])
                    data_pn_score.append(libray.model().text(sentence_data[i])[1:])
                    #tf == 1 부정

                if tf == 1:
                    obj.append(-score)
                else:
                    obj.append(score)

            print("\n총 점수 : ",round(int(sum(obj)) / len(obj), 1))

            for i in range(len(sentence_data)):
                print(obj[i+1], sentence_data[i])

            if int(sum(obj)) < 0:
                tf = "Negative"
            elif(int(sum(obj)) == 0):
                tf = "neutral"
            else:
                tf = "Positive"


            a = f"""[{str(tf)} : {str(round(int(sum(obj)) / len(obj), 1))}] ************** {str(text)}"""
            return a
```

# Server Result
***127.0.0.1 - - [08/Dec/2019 05:31:25] "GET / HTTP/1.1" 200 -
URL : https://www.bbc.com/news/world-asia-india-50697139
SUMM : Five men, including the alleged rapists, have been
SOURCE : en
[use google translator]
ori : Five men, including the alleged rapists, have been...
tra : 주장 강간범을 포함하여 다섯 사람은, 인도 경찰 say.Rape과 여성에 대한 성폭력은 수...***

***127.0.0.1 - - [08/Dec/2019 05:31:36] "GET /input/https%3A%7C%7Cwww.bbc.com%7Cnews%7Cworld-asia-india-50697139 HTTP/1.1" 200 -
총 점수 :  -49.8
-100.0 주장 강간범을 포함하여 다섯 사람은, 인도 경찰 say.Rape 과 여성에 대한 성폭력은 수도 델 리에서 버스에서 젊은 여자의 12 월 2012 년 집단 강간과 살인 이후 인도의 초점이 되었습니다
0 체포되었다.
-99.983857384359 별도로, 금요일에, 인도 경찰은 강간과 하이 데 라 바 드의 남부 도시 지난 주에 젊은 여성 수의사를 살해 한 혐의 죽은 네 사람을 쐈다.***
#
#
# **Server**
![SUM](https://github.com/Seungup/NASA/blob/master/2019-11-12-%EC%84%9C%EB%B2%84-%EB%B2%88%EC%97%AD%EA%B8%B0%EB%8A%A5-%EC%8B%9C%ED%98%84.png)
![SUM](https://github.com/Seungup/NASA/blob/master/2019-11-21-%EC%84%9C%EB%B2%84-%EB%B0%8F-%EC%9B%B9-%EA%B5%AC%EB%8F%99%EC%8B%9C%ED%98%84.png)
#
#
# **client** 
![SUM](https://github.com/Seungup/NASA/blob/master/2019_11_24_Cpp_%ED%81%B4%EB%9D%BC%EC%9D%B4%EC%96%B8%ED%8A%B8-%EC%8B%9C%EC%97%B0.png)
#
#
# How it Works?

![NN](https://github.com/Seungup/NASA/blob/master/NN.png)

# Data Sets

## I used the movie review dataset on Naver site.

## ( Traning Set : Test Set ) : ( 0.7 : 0.3 )
Due to my lack of memory management ability, weight file was saved and imported separately as binary file.

That file : **./Server/CPP_Server/Bin/wdata.p**
is can open like this follow

```python
import pickle
with open('wdata.p', 'wb') as file:
    pickle.dump(selected_words, file)
```
 The file currently uploaded is already pre-processed. And if you want to make a new **model.h** file 
 [Here is the Orignal Data Sets link](https://github.com/e9t/nsmc/)
 
Model Source code is built on this [site](https://cyc1am3n.github.io/2018/11/10/classifying_korean_movie_review.html)
