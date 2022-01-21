#testing.py

import requests as rq

r = rq.post("https://api.deepai.org/api/text-generator",
    data={
        'text': 'GREAT AMONG ALL . well of coursed ! CAUSE ? T1 !! get just the way bud have timer ! KEEP DOMINATE !!!!!!!!!',
    },
    headers={'api-key': 'quickstart-QUdJIGlzIGNvbWluZy4uLi4K'}
)
print(r.json())