## Linux Task Checker with integration OpenOLAT

EN  
This repository contains the source code of a utility for checking the homework course on Linux  
Available integration via REST - score is released automatically  
To build the project, run compile.sh

#### EN parameters of compilation (sets as env variables)

USER_ID_LMS - user ID in LMS  
LMS_BASE_URL - LMS address  
LMS_INTEGRATION - 0 or 1, enable or disable the REST integration  
USER_NAME_LMS - username (needed for user labels)  
COURSE_ID_LMS - course ID
$PASS_CODE - password for REST  
ZERO_TASK_ID ... TENTH_TASK_ID - task identifiers in LMS  
ZERO_TASK_SCORE ... TENTH_TASK_SCORE - score for a successful solution  
