int getDigitSum(int a)
{
    int result = 0;
    
    result += a / 100;
    result += ( a / 10 ) % 10;    
    result += a % 10;

    return result;
}
