FROM ubuntu:22.04
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1
COPY ./app /webuihelper/app
COPY ./static /webuihelper/static
COPY ./templates /webuihelper/templates
COPY ./webuihelper /webuihelper/webuihelper
COPY ./manage.py /webuihelper
COPY ./requirements.txt /webuihelper
COPY ./start.sh /webuihelper
RUN chmod 755 /webuihelper/start.sh
COPY ./task-checker /task-checker
RUN apt update
RUN apt install -y build-essential libcurl4-openssl-dev libncurses-dev libncurses5-dev libncursesw5-dev
RUN apt install -y python3.11 python3-pip python-is-python3
RUN pip install -r /webuihelper/requirements.txt

RUN mkdir -p /compiled
WORKDIR /webuihelper
CMD ["/bin/bash","-c","./start.sh"]

