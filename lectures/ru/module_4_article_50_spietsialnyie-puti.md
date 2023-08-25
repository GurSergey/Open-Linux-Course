В оболочке существуют так называемые специальные пути, каждый имеет особенное назначение. 


 


**Текущая директория**  
Точка (.) Представляет текущий каталог. Вы увидите это в списках каталогов, если используете -a опцию (все) с ls.  
`ls -a .`  
Вы также можете использовать точку в командах для представления пути к вашей текущей директории. Например, если вы хотите запустить скрипт из текущего каталога, вы бы вызвали его так:  
`./script.sh`  
Это говорит Bash искать script.sh файл в текущем каталоге . Таким образом, он не будет искать каталоги в вашем пути для поиска исполняемого файла или сценария.


**Parent Directory**  
Двойной период или «двойная точка» (..) представляет родительский каталог вашего текущего. Вы можете использовать это, чтобы перейти на один уровень вверх в дереве каталогов.  
Вы также можете использовать эту команду с относительными путями - например, если вы хотите подняться на один уровень вверх в дереве каталогов, а затем ввести другой каталог на этом уровне.  
Вы также можете использовать эту технику для быстрого перехода к каталогу на том же уровне в дереве каталогов, что и текущий. Вы запрыгиваете на один уровень вверх, а затем обратно в другой каталог.  
`cd ../gc\_help`


**Домашний каталог**  
Тильда (~) является сокращением для вашего домашнего каталога. Это означает, что вам не нужно вводить полный путь к вашей домашней директории в командах. Где бы вы ни находились в файловой системе, вы можете использовать эту команду для перехода в ваш домашний каталог:  
`cd ~`  
Вы также можете использовать эту команду с относительными путями. Например, если вы находитесь в файловой системе, которая не находится в вашей домашней папке, и хотите перейти в archive каталог в вашем workкаталоге, используйте тильду, чтобы сделать это:  
`cd ~/work/archive`


![image.png](./images/spietsialnyie-puti_1.png)
