from konlpy.tag import Okt
from tensorflow import keras
import pickle
import numpy as np
import os

okt = Okt()
nowDir = os.getcwd()
modelPATH = nowDir + '\\model.h5'
wdataPATH = nowDir + '\\wdata.p'

model = keras.models.load_model(modelPATH)
    
with open(wdataPATH, 'rb') as file:
    selected_words = pickle.load(file)

def tokenize(doc):
    return ['/'.join(t) for t in okt.pos(doc, norm=True, stem=True)]

def term_frequency(doc):
    return [doc.count(word) for word in selected_words]

def predict_pos_neg(review):
    token = tokenize(review)
    tf = term_frequency(token)
    data = np.expand_dims(np.asarray(tf).astype('float32'), axis=0)
    score = float(model.predict(data))
    if(score > 0.5):
        return (review, score * 100, 0)
    else:
        return (review, (1 - score) * 100, 1)






