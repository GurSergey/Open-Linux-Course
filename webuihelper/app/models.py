from django.contrib.auth.models import User
from django.db import models
import secrets
import string


def generate_token():
    return ''.join(secrets.choice(string.ascii_uppercase + string.ascii_lowercase) for i in range(100))


class Student(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    access_token = models.CharField(max_length=100, unique=True, default=generate_token)
    canvas_lms_id = models.CharField(max_length=100, unique=True)

