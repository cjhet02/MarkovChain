from os import access
import requests as rq
import json

streamer = 'loltyler1'
authURL = 'https://id.twitch.tv/oauth2/token'
Client_ID = '6dzwm0ri8t01u98icpibehfw5boqpt'
Secret = '92u3zlx0pynkz92u4v5lq3z55lvcr2'

AuthParams = {'client_id' : Client_ID, 'client_secret' : Secret, 'grant_type' : 'client_credentials'}

AuthCall = rq.post(url=authURL, params=AuthParams)
access_token = AuthCall.json()['access_token']
head = {
     'Client-ID' : Client_ID,
    'Authorization' : "Bearer " + access_token
}
channelURL = 'https://api.twitch.tv/helix/users?login=' + streamer
channelSearch = rq.get(channelURL, headers = head)
streamerID = channelSearch.json()['data'][0]['id']

vidURL = 'https://api.twitch.tv/helix/videos?user_id=' + streamerID + '&first=10'
titles = rq.get(vidURL, headers = head).json()

words = ""
for video in titles['data']:
    words += json.dumps(video['title'])

print(words)