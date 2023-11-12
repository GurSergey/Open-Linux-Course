import requests
import json

account_id = input()
token = input()
base_url = input()


# /api/v1/accounts/:account_id/courses

def make_request(url: str, type: str, body: dict = None, headers: dict = None) -> requests.Response:
    return requests.request(type, url, headers=headers, data=json.dumps(body))


def create_course(name: str, token):
    headers = {
        'Authorization': f'Bearer {token}',
        'Content-Type': 'application/json'
    }
    body = {
        "name": name,
        "public_description": "description",
        "course_code": "OpenLinux"

    }
    make_request(f"{base_url}/api/v1/accounts/{account_id}/courses", "PUT", headers, body)

