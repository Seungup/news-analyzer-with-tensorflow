#!/usr/bin/env python
# coding: utf-8

# In[1]:


from konlpy.tag import Okt
from tensorflow import keras
import pickle
import numpy as np
okt = Okt()

model = keras.models.load_model('d:/UNIV/Python_Project/University/CPP_Server/Bin/model.h5')


# In[2]:


with open('d:/UNIV/Python_Project/University/CPP_Server/Bin/wdata.p', 'rb') as file:
    selected_words = pickle.load(file)
    
def tokenize(doc):
    return ['/'.join(t) for t in okt.pos(doc, norm=True, stem=True)]

def term_frequency(doc):
    return [doc.count(word) for word in selected_words]


# In[6]:


def predict_pos_neg(review):
    token = tokenize(review)
    tf = term_frequency(token)
    data = np.expand_dims(np.asarray(tf).astype('float32'), axis=0)
    score = float(model.predict(data))
    if(score > 0.5):
        return (review, score * 100, 0)
    else:
        return (review, (1 - score) * 100, 1)






