/*
 * Реализовать фукнцию isalpha, которая проверяет, является ли переданный символ буквой (конкретно латинской буквой)
 * Реализовать функцию tolower, которая превращает заглавные латинские буквы в маленькие, а другие символы возвращает неизменными
 */


bool isalpha(unsigned char c)
{
    if((int(c) >= 65 && int(c) <= 90) || (int(c) >= 97 && int(c) <= 122))
    {
        return true;
    }
    else{
        return false;
    }
}
unsigned char tolower(unsigned char c)
{
    if(int(c) >= 65 && int(c) <= 90)
    {
        return char(c + 32);
    }
    else
    {
        return c;
    }
}
