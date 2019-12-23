
# Summary#
![NN](https://github.com/Seungup/news-analyzer-with-tensorflow/blob/master/PNG/NN.png)**It is designed for university assignments.**
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
# Data Sets
 [Here is the Orignal Data Sets link](https://github.com/e9t/nsmc/)
