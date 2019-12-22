# **Before entering, It is designed for university assignments.**

# Summary

## The program automatically parses, summarizes, translates, and analyzes links to news articles on the client.
### Here is the [Demo Video](https://www.youtube.com/watch?v=oADv6G2cCwk) for you The server is connected through ngrok.

# Before using TODO

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

and check it out the PATH of the file **wdata.p** location

```python
with open('d:/UNIV/Python_Project/University/CPP_Server/Bin/wdata.p', 'rb') as file:
    selected_words = pickle.load(file)
```

and also **/Server/CPP_Server/Bin/server_bin.py /** file too

```python
class CppAssignment:
    
    class Papago:
        
        def __init__(self, text, papago_id = 'your Client ID', papago_secret = 'your Client Secret'):
            self.papago_id = papago_id
            self.papago_secret = papago_secret
            self.text = text
```

![NN](https://github.com/Seungup/NASA/blob/master/NN.png)

# Data Sets

## I used the movie review dataset on Naver site.

## ( Traning Set : Test Set ) : ( 0.7 : 0.3 )
Due to my lack of memory management ability, weight file was saved and imported separately as binary file.
That file : ./Server/CPP_Server/Bin/wdata.p 
is can open like this follow

```python
import pickle
with open('wdata.p', 'wb') as file:
    pickle.dump(selected_words, file)
```
 The file currently uploaded is already pre-processed. And if you want to make a new **model.h** file 
 [Here is the Orignal Data Sets](https://github.com/e9t/nsmc/)
 
