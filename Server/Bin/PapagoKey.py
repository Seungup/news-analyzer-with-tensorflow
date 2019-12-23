import os, sys, re
import re, json

def GetPapagoApiKey():
    try:
        f = open("Papago.data", 'r')
        data = f.read()
        data  = data.replace("###Papago_id = ", " ").replace("###Papago_pw = ", " ")
        papagoid, papagopw = data.split()
        f.close()
        return papagoid, papagopw
    
    except FileNotFoundError:
        
        Papago_Client_ID = str(input("Papago Client : "))
        Papago_Client_PW = str(input("Papago Secret : "))
        
        f = open("Papago.data", "w")
        papago_id = f"###Papago_id = {Papago_Client_ID}\n"
        papago_pw = f"###Papago_pw = {Papago_Client_PW}"
        f.write(papago_id)
        f.write(papago_pw)
        f.close()
        
def ActiveChecker(papago_id, papago_pw):
        client_id = papago_id
        client_secret = papago_pw
        data = "query=" + "안녕"
        try:
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
                return 1
            else:
                print("Error Code:" + rescode)
        except:
            return 0