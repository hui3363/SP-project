from bs4 import BeautifulSoup
import requests

url="http://cspro.sogang.ac.kr/~gr120160213/"
visited_list=[]
ind=0

def crawl(url):
    urls="http://cspro.sogang.ac.kr/~gr120160213/"
    try:
        global ind
        req=requests.get(url)
        soup=BeautifulSoup(req.content,"html.parser")
        results=soup.find_all('a')

        for link in results:
            hiperLink=link.get('href')
            #hiperLink
            if urls in hiperLink:
                hiperLink=hiperLink[39:]
            if 'index.html' not in hiperLink and urls+hiperLink not in visited_list and 'notfound' not in hiperLink:
                visited_list.append(urls+hiperLink)
                req2=requests.get(urls+hiperLink)
                soup2=BeautifulSoup(req2.content,"html.parser")
                ind=ind+1
                doo=open('Output_%04d.txt'%ind,"w")
                doo.write(soup2.get_text())
                crawl(urls+hiperLink)
    except requests.exceptions.ConnectionError:
        print "Error while opening this link"+url

crawl("http://cspro.sogang.ac.kr/~gr120160213")

han=open("URL.txt","w")
han.write("\n".join(visited_list))

