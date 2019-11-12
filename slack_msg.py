import json
import requests


webhook_url = 'https://hooks.slack.com/services/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'# enter your own web hook url
slack_data = {'text': "Alert! Someone is using your OS!!! Is it You??"}

response = requests.post(
    webhook_url, data=json.dumps(slack_data),
    headers={'Content-Type': 'application/json'}
)
if response.status_code != 200:
    raise ValueError(
        'Request to slack returned an error %s, the response is:\n%s'
        % (response.status_code, response.text)
    )
