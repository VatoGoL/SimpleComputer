# SimpleComputer
## Описание проекта
Целью проекта было разработать программную модель простейшей вычислительной машины. Она в состоянии обрабатывать некоторе колличество комманд и производить вычисления.
Также к "компьютеру" прилагается 2 компилятора с языков Basic (немного модифицированного) и Assembler.
![Интерфейс](https://ia.wampi.ru/2022/06/15/SC_DemoWork.png)
## Процесс компиляции
Так как данная программная модель эмулирует работу реальной вычислительной машины, то и процесс компиляции максимально приближен к реальному. Написанные программы компилируются с языка более высокого уровня в язык более низкого. Т.е. SimpleBasic -> SimpleAssembler -> SimpleComputer (машинный код).
## Описание интерфейса
![Описание интерфейса](https://ie.wampi.ru/2022/06/15/SC_DemoWorkTwo.png)
1. Memory - память нашего нашей модели, что-то наподобии оперативной памяти. Каждая ячейка памяти преставляет собой закодированное значение записанное в виде 16-ти ричного числа. Знак '+' означает что в данной ячейке памяти закодирована команда, отсутствие знака '+' означает что там закодировано число.
2. Accumulator - временное хранилище в нашем компьютере. Используется аккумулятор для того чтобы способствовать выполнению операций, например сложению (сложить число по указанной ячейке памяти с числом в аккумуляторе, результат записать в аккумулятор, подробная информация находится в описании к компилятору SimpleAssembler) или как временное хранилище. Хранит в себе либо ячейку памяти либо число в 16-ти ричном виде.
3. Instruction Counter - данное поле отображает номер ячейки памяти на которой находится указатель. Номер представлен в виде 16-ти ричного числа.
4. Operation - поле, отображающее декодированное значение ячейки памяти, на которой находится указатель компьютера. представлено в формате - [номер команды] : [операнд команды]. Все номера представлены в 16-ти ричном виде.
5. Flags - флаги состояний компьютера, они сигнализируют о том в каком режиме работает компьютер или какая исключительная ситуация возникла при работе компьютера:
  - P - переполнение памяти при выполнении операции, т.е когда результат вычислений больше чем позволено.
  - 0 - ошибка деления на ноль.
  - M - выход за границы ячеек памяти компьютера.
  - T - игнорирование тактовых импульсов внутреннего счётчика.
  - E - указана неверная комманда в ячейке памяти или при вводе с клавиатуры.
6. Big Chars - Зона визуализации ячейки памяти в более крупном шрифте.
7. Keys - Справка по горячим клавишам компьютера.
8. Console Zone - Зона консоли компьютера
