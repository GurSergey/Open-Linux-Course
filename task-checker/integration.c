//
// Created by serge on 02.10.2021.
//

#include <stdio.h>
#include <curl/curl.h>
#include "config.h"
#include "integration.h"


int setInMarkInLms(char* task_num) {
    CURL *curl;
    CURLcode res;
    int status = -1;
    curl_global_init(CURL_GLOBAL_ALL);
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        char buf_url[150];
        sprintf(buf_url,"%s/api/grade/", CONFIG_BASE_URL);
        curl_easy_setopt(curl, CURLOPT_URL, buf_url);
        char json_buffer[200];
//        printf("%s \n", json_buffer);
        sprintf(json_buffer, "{ \"passCode\":\"%s\", \n \"number\": \"%s\" }", CONFIG_PASS_CODE, task_num);
        /* Now specify the POST data */
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_slist_append(headers, "Accept: */*");
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_buffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */

        long http_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("Http code: %ld \n", http_code);
        printf("Http code: %d \n", res);
        if (http_code == 200 && res != CURLE_ABORTED_BY_CALLBACK) {
            status = LMS_OK_STATUS;
        } else {
            status = -1;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return status;
}