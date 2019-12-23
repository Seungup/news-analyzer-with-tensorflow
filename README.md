# **It is designed for university assignments.**

# Summary
![chart](https://github.com/Seungup/news-analyzer-with-tensorflow/blob/master/PNG/follow.png)
## The program automatically parses, summarizes, translates, and analyzes links to news articles on the client.
### Here is the [Demo Video](https://www.youtube.com/watch?v=oADv6G2cCwk) for you The server is connected through [ngrok](https://ngrok.com/).

# Before using TODO

## ngork http 5000 

## **C++ Client is will be work MS Visual Studio 2019**

# If you want Papago API then replace this section.

file PATH : **/Server/CPP_Server/Server.ipynb**

```python
@app.route('/input/<data>')
def hello_user(data):

...
# <--Papago API Get Langage Section-->
...

    try:
        if source != 'ko':
            print("[use google translator]")
            text = translator.translate(data, dest='ko').text # if you want to use Papago API just fix this code
        ...
```
# How it Works?

![NN](https://github.com/Seungup/news-analyzer-with-tensorflow/blob/master/PNG/NN.png)

# Data Sets

## I used the movie review dataset on Naver site.

## ( Traning Set : Test Set ) : ( 0.7 : 0.3 )
Due to my lack of memory management ability, weight file was saved and imported separately as binary file.

 The file currently uploaded is already pre-processed. And if you want to make a new **model.h** file 
 [Here is the Orignal Data Sets link](https://github.com/e9t/nsmc/)
 
Model Source code is built on this [site](https://cyc1am3n.github.io/2018/11/10/classifying_korean_movie_review.html)
