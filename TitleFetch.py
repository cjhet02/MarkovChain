from os import access
import requests as rq
import json

streamer = 'loltyler1'
authURL = 'https://id.twitch.tv/oauth2/token'
Client_ID = '6dzwm0ri8t01u98icpibehfw5boqpt'
Secret = '5pyubfbb49ndn91g4ktgv7972gf2tj'

AuthParams = {'client_id' : Client_ID, 'client_secret' : Secret, 'grant_type' : 'client_credentials'}

AuthCall = rq.post(url=authURL, params=AuthParams)
access_token = AuthCall.json()['access_token']

Streamer_ID = rq.get('https://api.twitch.tv/helix/search/channels?query=' + streamer).json()['id']
URL = 'https://api.twitch.tv/helix/videos?user_id=' + Streamer_ID + '&first=100'

head = {
     'Client-ID' : Client_ID,
    'Authorization' : "Bearer " + access_token
}

r = rq.get(URL, headers = head).json()

for id in r['data']:
    print(id['title'])