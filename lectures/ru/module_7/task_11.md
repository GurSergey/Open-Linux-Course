Перед началом работы с этим заданием замените язык вывода консольных утилит на английский. Для этого перед началом работы в любом терминале напишите команду export LANG=en\_US.UTF-8. Это важно для проверяющей системы, т.к. проверка курса автоматизирована.   
В этом задании вам необходимо написать скрипт bash, он должен быть написан в файле info.sh. Этот скрипт будет выводить информацию о компьютере в следующем виде:


  
Computer name: <имя хоста>  
Processor: <название модели процессора> (<частота в Ггц >GHz), <кол-во ядер> cores  
RAM size: <объем Озу>GB (<процент свободной>% free)  
HDD capacity: <объем системного диска>GB (<процент свободного пространства>% free)  
Current uptime: <часы с момента запуска системы>H <минуты с момента запуска системы>M


  
Пример вывода:  
Computer name: serge-pc  
Processor: Intel(R) Core(TM) i3-9100F (3.60GHz), 4 cores  
RAM size: 16GB (20% free)  
HDD capacity: 220GB (60% free)  
Current uptime: 2H 34M


В выводе наименования процессора не должна встречаться абривиатура CPU. При расчете объема ОЗУ и объема диска, примите приближение что 1000КБ=1МБ   
и 1000МБ=1ГБ, в результате должно получится целое число, дробную часть отбрасываем. При расчете объема диска примите во внимание только объем системного раздела (swap файлы и другие разделы не нужно принимать во внимание). При расчете времени работы системы, нужно посчитать целое число часов с момента запуска, и кол-во минут в остатке (то что не поделилось на 60), кол-во секунд считать не надо
