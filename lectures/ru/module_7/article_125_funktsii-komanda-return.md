Команда return позволяет задавать возвращаемый функцией целочисленный код завершения. Есть два способа работы с тем, что является результатом вызова функции. Вот первый:  
`#!/bin/bash`  
`function myfunc {`  
`read -p "Enter a value: " value`  
`echo "adding value"`  
`return $(( $value + 10 ))`  
`}`  
`myfunc`  
`echo "The new value is $?"`


Команда echo вывела сумму введённого числа и числа 10.


Ещё один способ возврата результатов работы функции заключается в записи данных, выводимых функцией, в переменную. Такой подход позволяет обойти ограничения команды return и возвращать из функции любые данные. Рассмотрим пример:  
`#!/bin/bash`  
`function myfunc {`  
`read -p "Enter a value: " value`  
`echo $(( $value + 10 ))`  
`}`  
`result=$( myfunc)`  
`echo "The value is $result"`
