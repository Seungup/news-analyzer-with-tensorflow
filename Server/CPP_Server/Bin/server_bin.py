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


# In[12]:


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
        def Newspaper(self, url):
            news = newspaper.Article(url)
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
    

