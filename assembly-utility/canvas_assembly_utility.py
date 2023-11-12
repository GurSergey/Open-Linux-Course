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

import requests
import json
import os

# Canvas API URL and token
CANVAS_API_URL = "https://your_canvas_instance/api/v1"
CANVAS_API_TOKEN = "your_canvas_api_token"

# Course details
COURSE_ID = "your_course_id"
COURSE_NAME = "Your Course Name"

# Function to create a module
def create_module(module_name):
    url = f"{CANVAS_API_URL}/courses/{COURSE_ID}/modules"
    headers = {"Authorization": f"Bearer {CANVAS_API_TOKEN}"}
    data = {"module[name]": module_name, "module[workflow_state]": "active"}

    response = requests.post(url, headers=headers, data=data)
    module_id = json.loads(response.text)["id"]
    return module_id

# Function to upload file content to Canvas
def upload_file_to_canvas(file_path, content_type, module_id):
    url = f"{CANVAS_API_URL}/courses/{COURSE_ID}/modules/{module_id}/files"
    headers = {"Authorization": f"Bearer {CANVAS_API_TOKEN}"}
    files = {"upload_file": (os.path.basename(file_path), open(file_path, "rb"), content_type)}

    response = requests.post(url, headers=headers, files=files)
    file_id = json.loads(response.text)["id"]
    return file_id

# Function to add content to a module
def add_content_to_module(module_id, title, content, content_type):
    url = f"{CANVAS_API_URL}/courses/{COURSE_ID}/modules/{module_id}/items"
    headers = {"Authorization": f"Bearer {CANVAS_API_TOKEN}"}
    data = {
        "module_item[title]": title,
        "module_item[type]": "Page",
        "module_item[content_id]": None,
        "module_item[content_type]": content_type,
        "module_item[page_url]": None,
    }

    if content_type == "File":
        data["module_item[content_id]"] = upload_file_to_canvas(content, "application/pdf", module_id)
    elif content_type == "Page":
        data["module_item[page_url]"] = content

    response = requests.post(url, headers=headers, data=data)

# Read Markdown files and assemble the course
def assemble_course():
    course_modules = [
        {"name": "Module 1", "content": "path/to/module1.md", "type": "Page"},
        {"name": "Module 2", "content": "path/to/module2.pdf", "type": "File"},
        # Add more modules as needed
    ]

    # Create the course
    print(f"Creating course: {COURSE_NAME}")
    create_module(COURSE_NAME)

    # Add modules and content
    for module in course_modules:
        module_name = module["name"]
        module_content = module["content"]
        module_type = module["type"]

        print(f"Creating module: {module_name}")
        module_id = create_module(module_name)

        print(f"Adding content to module: {module_name}")
        add_content_to_module(module_id, module_name, module_content, module_type)

    print("Course assembly completed!")

# Run the script
assemble_course()