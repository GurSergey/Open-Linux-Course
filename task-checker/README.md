## Linux Task Checker with integration OpenOLAT

RU  
Этот репозиторий содержит исходный код утилиты для проверки ДЗ курса по Linux  
Имеется интеграция с OpenOLAT по REST - оценки выставляются автоматически  
Для сборки проекта запустите compile.sh

EN  
This repository contains the source code of a utility for checking the homework course on Linux  
Available integration with OpenOLAT via REST - score is released automatically  
To build the project, run compile.sh

#### RU Параметры сборки (выставляются как переменные окружения перед компиляцией)

USER_ID_LMS - идентификатор пользователя в LMS  
LMS_BASE_URL - url LMS  
LMS_INTEGRATION - 0 или 1, включение и отключение интеграции  
USER_NAME_LMS - имя пользователя (нужно для надписей пользователю)  
COURSE_ID_LMS - идентификатор курса  
LOGIN_LMS_ROBOT - логин для REST  
PASS_LMS_ROBOT - пароль для REST  
ZERO_TASK_ID ... TENTH_TASK_ID - идентификаторы задач в LMS  
ZERO_TASK_SCORE ... TENTH_TASK_SCORE - оценки за успешное решение  

#### EN parameters of compilation (sets as env variables)

USER_ID_LMS - user ID in LMS  
LMS_BASE_URL - LMS address  
LMS_INTEGRATION - 0 or 1, enable or disable the REST integration  
USER_NAME_LMS - username (needed for user labels)  
COURSE_ID_LMS - course ID  
LOGIN_LMS_ROBOT - login for REST  
PASS_LMS_ROBOT - password for REST  
ZERO_TASK_ID ... TENTH_TASK_ID - task identifiers in LMS  
ZERO_TASK_SCORE ... TENTH_TASK_SCORE - score for a successful solution  
