При работе с регулярными выражениями мы в основном будем использовать нашу старую добрую приятельницу — программу grep. Название grep в действительности произошло от фразы «global regular expression print» (глобальный поиск с помощью регулярного выражения и вывод), то есть, как видите, grep имеет некоторое отношение к регулярным выражениям. В сущности, grep просматривает текстовые файлы в поисках совпадений с указанным регулярным выражением и выводит в стандартный вывод все строки с такими совпадениями.  
До сих пор мы передавали программе grep фиксированные строки, например:  
`[me@linuxbox ~]$ ls /usr/bin | grep zip`  
Эта команда выведет список всех файлов из каталога /usr/bin, имена которых содержат подстроку zip.  
Программа grep имеет следующий синтаксис:  
`grep [параметры] регулярное\_выражение [файл...]`  
В табл. перечислены наиболее часто используемые параметры grep.




|  |  |
| --- | --- |
| Параметры команды grep | Описание |
| -i | Игнорировать регистр символов. Требует не различать символы верхнего и нижнего регистра. Аналогично работает параметр --ignore-case |
| -v | Инвертировать критерий. Обычно grep выводит строки с совпадениями. Этот параметр заставляет grep выводить строки, не содержащие совпадений. Аналогично работает параметр --invert-match |
| -c  | Вывести число совпадений (или «несовпадений») в присутствии параметра -v вместо самих текстовых строк. Аналогично работает параметр --count |
| -l  | Вместо строк с совпадениями выводить только имена файлов с найденными строками. Аналогично работает параметр --files-with-matches |
| -L |  Действует подобно параметру -l, но выводит только имена файлов, где не найдено ни одного совпадения. Аналогично работает параметр --files- without-match |
| -n | В начале каждой строки с совпадением вывести ее номер в файле. Аналогично работает параметр --line-number |
| -h | Подавить вывод имен файлов при поиске по нескольким файлам. Аналогично работает параметр --no-filename |


 
