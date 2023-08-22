//
// Created by serge on 03.10.2021.
//

#include "config.h"

#ifndef LINUX_TASK_CHECKER_DEBUG_INFO_H
#define LINUX_TASK_CHECKER_DEBUG_INFO_H

#define DEBUG_NUM -10

char* debug_info = "This is debug information about task checker \n"
             "Information build \n"
             "Version of program: 0.5 \n"
             "Lms integration include: " CONFIG_WITH_LMS_CHECKING "\n"
             "User name in LMS: " CONFIG_USER_NAME "\n"
               "URL lms: " CONFIG_BASE_URL "\n"
                   "lms pass hash: " CONFIG_HASH_PASS_CODE "\n"
                   "Id course in LMS: " CONFIG_COURSE_ID "\n\n"
             "About \n"
             "This program developed for automation checking tasks Linux course \n"
             "You can send feedback to emails: gyrsergey@yandex.ru, gyrsergey@gmail.com \n"
             "Or skype login: gyrsergey";

#endif //LINUX_TASK_CHECKER_DEBUG_INFO_H
