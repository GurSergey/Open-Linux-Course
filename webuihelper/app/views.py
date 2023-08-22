import os
import shutil

from django.shortcuts import render

# Create your views here.
import subprocess
from django.http import HttpResponse
from constance import config
import requests
import json

from django.views.decorators.csrf import csrf_exempt

from .models import Student
from .utils import get_id_task_by_number

CHECKER_SOURCE_PATH = os.getenv("CHECKER_SOURCE_PATH")
COMPILED_CHECKERS_PATH = os.getenv("COMPILED_CHECKERS_PATH")
NAME_TASK_CHECKER = 'linux_task_checker'


def get_utility(request):
    if request.user.is_authenticated:
        # if request.user.student
        if getattr(request.user, 'student', None) is not None:
            if os.path.exists(
                    COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id + os.sep + NAME_TASK_CHECKER):
                file_path = COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id + os.sep + NAME_TASK_CHECKER

                fh = open(file_path, 'rb')
                response = HttpResponse(fh.read(), content_type="application/vnd.ms-excel")
                response['Content-Disposition'] = 'inline; filename=' + os.path.basename(file_path)
                fh.close()
                shutil.rmtree(COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id)
                return response
            elif os.path.exists(
                    COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id + os.sep + '.lock'):
                html = "<html><body>Your checker is already compiling, please wait several seconds, " \
                       "and reload this page. <a href=\".\">Reload page link</a></body></html>"
            else:
                if not os.path.exists(COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id + os.sep):
                    os.makedirs(COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id + os.sep)
                open(COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id + os.sep + '.lock', "w") \
                    .close()
                env_compile = os.environ.copy()

                env_compile['LMS_BASE_URL'] = config.HELPER_URL
                env_compile['COURSE_ID_LMS'] = config.COURSE_ID
                env_compile['LMS_INTEGRATION'] = '1'
                env_compile['USER_NAME_LMS'] = request.user.username
                env_compile['PASS_CODE'] = request.user.student.access_token
                env_compile['CHECKERS_PATH'] = \
                    COMPILED_CHECKERS_PATH + os.sep + request.user.student.canvas_lms_id + os.sep

                print(subprocess.call(['bash ./compile.sh'], cwd=CHECKER_SOURCE_PATH,
                                      env=env_compile, shell=True))
                html = "<html><body>Your checker start compiling, please wait several seconds, " \
                       "and reload this page <a href=\".\">Reload page link</a></body></html>"
        else:
            html = "<html><body>You are not registered student. " \
                   "Please connect with admin of course</body></html>"
    else:

        html = "<html><body>User not authenticated</body></html>"
    return HttpResponse(html)


@csrf_exempt
def send_grade(request):
    body_unicode = request.body.decode('utf-8')
    body = json.loads(body_unicode)
    pass_code = body['passCode']
    id_task = get_id_task_by_number(int(body['number']))
    student = Student.objects.get(access_token=pass_code)
    url = "{}/api/v1/courses/{}/assignments/{}/submissions/{}/".format(
        config.CANVAS_LMS_URL, config.COURSE_ID, id_task, student.canvas_lms_id)

    payload = json.dumps({
        "submission": {
            "posted_grade": "100%"
        }
    })
    headers = {
        'Authorization': 'Bearer {}'.format(config.ADMIN_TOKEN),
        'Content-Type': 'application/json'
    }

    response = requests.request("PUT", url, headers=headers, data=payload)
    if response.status_code != 200:
        return HttpResponse(status=500)
    else:
        return HttpResponse("OK")
