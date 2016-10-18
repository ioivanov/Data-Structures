# Писане на `UnitTests` във `VisualStudio`
### Първи етап - създаване на `Win32 Console Application`
По познатия ни вече начин създаваме конзолно приложение, което съдържа кода, който ще тестваме. Нека проекта ни се казва `BankAccount`.
Към него добавяме файла `BankAccount.h`.

### Втори етап - създаване на `Native Unit Тest Project`
Към вече готовият `Solution 'BankAccount'` добавяме нов проект от тип `Native Unit Тest Project` с име `BankAccountTest`.
* Десен бутон на `Solution 'BankAccount'`->`Add`->`New Project...`->`Visual C++`->`Test`->`Native Unit Тest Project`.

Препоръчително е `Location` на `BankAccountTest` да е `..\Projects\BankAccount` т.е. в директорията на проекта, който ще тестваме.

### Трети етап - определяне на зависимостите между двата проекта
Първо добавяме файловете съдържащи сорс код към проекта `BankAccountTest`. В нашият случай това е само `BankAccount.h`
* Десен бутон на проекта `BankAccountTest`->`Add`->`Existing Item...` и избираме `BankAccount.h` от директорията `../BankAccount`

След това трябва да направим `BankAccountTest` зависим от `BankAccount`
* Десен бутон на `Solution 'BankAccount'`->`Project Dependencies` от падащото меню под `Projects:` избираме `BankAccountTest` и под `Depends on:`
слагаме отметката на `BankAccount`.

### Пускане на тестовете
От менюто `Test` избираме `Run`->`All Tests`. Отваря се `Test Explorer`, който ни дава информация за това как са преминали тестовете.

# Пояснения към кода в `BankAccountTest.cpp`

* `TEST_MODULE_INITIALIZE` - се извиква веднъж при стартирането на тестовете.
* `TEST_MODULE_CLEANUP` - се извиква веднъж след изпълнението на тестовете.
* `TEST_CLASS_INITIALIZE` - се извиква при стартирането на тестовете от даден клас.
* `TEST_CLASS_CLEANUP` - се извиква след изпълнението на тестовете от даден клас.
* Конструктура се извиква за при началото на всеки `TEST_METHOD`.
* Деструктора се извиква след всеки `TEST_METHOD`.

Защо има `L` пред стринговете? - http://stackoverflow.com/questions/6384118/what-does-the-l-in-front-a-string-mean-in-c

Какъв аргумент приема `ExpectException`? - http://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11
