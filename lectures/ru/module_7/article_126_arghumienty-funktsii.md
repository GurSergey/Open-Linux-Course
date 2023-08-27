Функции bash можно воспринимать как небольшие фрагменты кода, которые позволяют экономить время и место, избавляя нас от необходимости постоянно вводить с клавиатуры или копировать одни и те же наборы команд. Однако, возможности функций гораздо шире. В частности, речь идёт о передаче им аргументов.


Функции могут использовать стандартные позиционные параметры, в которые записывается то, что передаётся им при вызове. Например, имя функции хранится в параметре $0, первый переданный ей аргумент — в $1, второй — в $2, и так далее. Количество переданных функции аргументов можно узнать, обратившись к переменной $#


Аргументы передают функции, записывая их после её имени:


`myfunc $val1 10 20`


Пример:  
`#!/bin/bash`  
`function myfunc {`  
`echo $(( $1 + $2 ))`  
`}`  
`if [ $# -eq 2 ]`  
`then`  
`value=$(myfunc $1 $2)`  
`echo "The result is $value"`  
`else`  
`echo "Usage: myfunc a b"`  
`fi`
