#!/usr/bin/env python
# coding: utf-8

# In[1]:


import newspaper
from gensim.summarization.summarizer import summarize
from konlpy.tag import Kkma
from konlpy.utils import pprint
import os, sys
import urllib.request
import json
import re
import server_bin
import server_model


# In[2]:


execute = server_bin.CppAssignment()
news = execute.Newspaper()


class CppAssignment:
    
    class Papago:
        
        def __init__(self, text, papago_id = 'HuA_wT4ehgG82Bo3mWct', papago_secret = 'KDtf1qSTnW'):
            self.papago_id = papago_id
            self.papago_secret = papago_secret
            self.text = text
            
        def GetLangage(self):
            client_id = self.papago_id
            client_secret = self.papago_secret
            data = "query=" + self.text
            url = "https://openapi.naver.com/v1/papago/detectLangs"
            request = urllib.request.Request(url)
            request.add_header("X-Naver-Client-Id",client_id)
            request.add_header("X-Naver-Client-Secret",client_secret)
            response = urllib.request.urlopen(request, data=data.encode("utf-8"))
            rescode = response.getcode()
            if(rescode==200):
                response_body = response.read()
                data = response_body.decode('utf-8')
                data = json.loads(data)
                return data['langCode']
            else:
                print("Error Code:" + rescode)
            
            
        def NMT(self, source, target):
            encText = urllib.parse.quote(self.text)
            data = f"source={source}&target={target}&text=" + encText
            url = "https://openapi.naver.com/v1/papago/n2mt"
            request = urllib.request.Request(url)
            request.add_header("X-Naver-Client-Id",self.papago_id)
            request.add_header("X-Naver-Client-Secret",self.papago_secret)
            response = urllib.request.urlopen(request, data=data.encode("utf-8"))
            rescode = response.getcode()
            if(rescode==200):
                response_body = response.read()
                data = response_body.decode('utf-8')
                data = json.loads(data)
                return data['message']['result']['translatedText']
            else:
                print("Error Code:" + rescode)
            
    
    class Newspaper:
        def Newspaper(self, url, language='ko'):
            news = newspaper.Article(url, language=language)
            news.download()
            news.parse()
            data = summarize(news.text)
            return data.replace('\n', '')
        
        def KeyWord(self, url):
            article = Article(url)
            article.download()
            article.parse()
            return article.keyword
        
        def Hot(self):
            return newspaper.hot()
        
        def PopularUrl(self):
            return newspaper.popular_urls()
        
        
    class KoNLPy:
        def __init__(self, text):
            self.text = text
            
        def sentence(self):
            data = Kkma().sentences(phrase=u'{}'.format(self.text))
            return data

    class model:
        def pn_score(self, url):
            data = news.Newspaper(url=url)
            sentence = execute.KoNLPy(text=data).sentence()
            pred = []
            for i in range(len(sentence)):
                if(len(sentence[i]) > 5):
                    pred.append(sentence[i])
            score = []
            tf = []
            for i in range(len(pred)):
                model = server_model.predict_pos_neg(pred[i])
                score.append(model[1])
                tf.append(model[2])
            acc = []
            for i in range(len(tf)):
                if(tf[i] == 0):
                    acc.append(score[i])
                else:
                    acc.append(-score[i])
            acc_s = sum(acc) / len(tf)

            if max(acc_s, 0):
                print(f"긍정 점수 : {round(acc_s, 2)}점")
                return 1, round(acc_s, 2)
            else:
                print(f"부정 점수 : {round(-acc_s, 2)}점")
                return 0, round(-acc_s, 2)
            
        def text(self, text):
            model = server_model.predict_pos_neg(text)
            return model

