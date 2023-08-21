from django.shortcuts import render

# Create your views here.
from django.http import HttpResponse
from .models import Student


def compile_utility(request):
    if request.user.is_authenticated:
        # if request.user.student
        if getattr(request.user, 'student', None) is not None:

            html = "<html><body>It is now %s.</body></html>" % request.user.student.access_token
        else:
            html = "<html><body>You are not registered student. " \
                   "Please connect with admin of course</body></html>"
    else:

        html = "<html><body>User not authenticated</body></html>"
    return HttpResponse(html)